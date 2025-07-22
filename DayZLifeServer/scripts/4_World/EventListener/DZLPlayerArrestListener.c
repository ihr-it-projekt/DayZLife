class DZLPlayerArrestListener: DZLBaseEventListener {
    private ref Timer timerArrest;
    private ref array<ref DZLEscapedPlayer> escapeePlayers = new array<ref DZLEscapedPlayer>;
    private ref array<ref DZLOpenTicketPlayer> openTicketPlayers = new array<ref DZLOpenTicketPlayer>;
    int copCount = 0;
    int civCount = 0;
    int medicCount = 0;
    int armyCont = 0;

    static ref DZLPlayerArrestListener instance;

    void DZLPlayerArrestListener() {
        instance = this;
        timerArrest = new Timer;
        timerArrest.Run(60, this, "CheckPrisoners", null, true);
    }

    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DZL_RPC.ARREST_PLAYER) {
            Param3<PlayerBase, int, string> paramArrestPlayer;
            if(ctx.Read(paramArrestPlayer)) {
                PlayerBase cop = PlayerBase.Cast(target);
                PlayerBase prisoner = paramArrestPlayer.param1;
                int arrestTime = paramArrestPlayer.param2;
                string arrestReason = paramArrestPlayer.param3;

                DZLPlayer copDzl = cop.GetDZLPlayer();
                DZLPlayer prisonerDzl = prisoner.GetDZLPlayer();

                if(copDzl.IsActiveJob(DAY_Z_LIFE_JOB_MEDIC) || copDzl.IsActiveAsCivil()) return;
                if(copDzl.arrestTimeInMinutes != 0) return;
                if(true == prisonerDzl.IsActiveJob(DAY_Z_LIFE_JOB_COP) && true == copDzl.IsActiveJob(DAY_Z_LIFE_JOB_COP)) return;
                if(true == prisonerDzl.IsActiveJob(DAY_Z_LIFE_JOB_ARMY) && true == copDzl.IsActiveJob(DAY_Z_LIFE_JOB_ARMY)) return;

                prisonerDzl.ArrestPlayer(arrestReason, arrestTime);

                DZLArrestConfig arrestConfig = DZLConfig.Get().jobConfig.arrestConfig;

                ChangeItems(prisoner, arrestConfig.prisonerItems, arrestConfig.shouldDeleteAllItemsOnPrissoner);

                if(arrestConfig.teleportArrestedIntoJail) {
                    prisoner.SetPosition(arrestConfig.teleportPosition.ToVector());
                }

                g_Game.RPCSingleParam(null, DZL_RPC.EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, null, true, prisoner.GetIdentity());
                g_Game.RPCSingleParam(null, DZL_RPC.ARREST_PLAYER_RESPONSE, null, true, sender);
                DZLSendMessage(prisoner.GetIdentity(), "#you_got_arrest_in_minutes: " + arrestTime.ToString());
                DZLSendMessage(cop.GetIdentity(), "#you_set_arrest_to_player_in_minutes: " + arrestTime.ToString());
                DZLLogArrest(prisoner.GetPlayerId(), "got arrest", arrestTime);
            }
        } else if(rpc_type == DZL_RPC.GET_ESCAPED_PLAYERS) {
            g_Game.RPCSingleParam(null, DZL_RPC.GET_ESCAPED_PLAYERS_RESPONSE, new Param5<ref array<ref DZLEscapedPlayer>, int, int, int, int>(escapeePlayers, copCount, medicCount, civCount, armyCont), true, sender);
        } else if(rpc_type == DZL_RPC.GET_OPEN_TICKET_PLAYERS) {
            g_Game.RPCSingleParam(null, DZL_RPC.GET_OPEN_TICKET_PLAYERS_RESPONSE, new Param1<ref array<ref DZLOpenTicketPlayer>>(openTicketPlayers), true, sender);
        } else if(rpc_type == DZL_RPC.GET_MEDIC_COUNT) {
            g_Game.RPCSingleParam(null, DZL_RPC.GET_MEDIC_COUNT_RESPONSE, new Param1<int>(medicCount), true, sender);
        }
    }

    void CheckPrisoners() {
        array<Man> allPlayers = new array<Man>;
        g_Game.GetPlayers(allPlayers);
        escapeePlayers.Clear();
        openTicketPlayers.Clear();
        civCount = 0;
        copCount = 0;
        medicCount = 0;
        armyCont = 0;

        foreach(Man playerMan: allPlayers) {
            PlayerBase player = PlayerBase.Cast(playerMan);
            DZLPlayer dzlPlayer = player.GetDZLPlayer();
            if(!dzlPlayer) continue;

            if(dzlPlayer.HasTickets()) openTicketPlayers.Insert(new DZLOpenTicketPlayer(player));

            if(dzlPlayer.IsActiveJob(DAY_Z_LIFE_JOB_COP)) {
                copCount ++;
            } else if(dzlPlayer.IsActiveJob(DAY_Z_LIFE_JOB_ARMY)) {
                armyCont ++;
            } else if(dzlPlayer.IsActiveJob(DAY_Z_LIFE_JOB_MEDIC)) {
                medicCount ++;
            } else {
                civCount ++;
            }

            if(!dzlPlayer.IsPlayerInArrest()) continue;
            vector playerPosition = player.GetPosition();

            bool isInPrison = false;
            int prisonArea = -1;
            DZLArrestConfig arrestConfig = DZLConfig.Get().jobConfig.arrestConfig;
            foreach(int index, vector position: arrestConfig.arrestAreas) {
                if(vector.Distance(position, playerPosition) < arrestConfig.arrestAreaRadius) {
                    dzlPlayer.ArrestCountDown();
                    g_Game.RPCSingleParam(null, DZL_RPC.EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, null, true, player.GetIdentity());
                    isInPrison = true;
                    prisonArea = index;
                    break;
                }
            }

            if(!isInPrison) {
                escapeePlayers.Insert(new DZLEscapedPlayer(player));
                continue;
            }

            if(!isInPrison) continue;
            if(dzlPlayer.IsPlayerInArrest()) continue;

            ChangeItems(PlayerBase.Cast(player), arrestConfig.exPrisonerItems, arrestConfig.shouldDeleteAllItemsOnExPrissoner);
            vector randPosition = arrestConfig.exPrisonerAreas.Get(prisonArea);

            if(randPosition) player.SetPosition(randPosition);
        }
        DZLDatabaseLayer.Get().SetCopCount(copCount).SetMedicCount(medicCount).SetCivCount(civCount).SetArmyCount(armyCont);

        g_Game.RPCSingleParam(null, DZL_RPC.GET_MEDIC_COUNT_RESPONSE, new Param1<int>(medicCount), true);
    }

    private void ChangeItems(PlayerBase prisoner, array<string> items, bool shouldDeleteAllItems) {

        if(shouldDeleteAllItems) {
            prisoner.RemoveAllItems();
        }

        foreach(string type: items) {
            EntityAI item;
            InventoryLocation inventoryLocation = new InventoryLocation;
            if(prisoner.GetInventory().FindFirstFreeLocationForNewEntity(type, FindInventoryLocationType.ANY, inventoryLocation)) {
                item = prisoner.GetHumanInventory().CreateInInventory(type);
            } else if(!prisoner.GetHumanInventory().GetEntityInHands()) {
                item = prisoner.GetHumanInventory().CreateInHands(type);
            }

            if(!item) {
                item = prisoner.SpawnEntityOnGroundPos(type, prisoner.GetPosition());
            }
        }

    }
}
