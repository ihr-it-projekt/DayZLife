class ActionTakeRobtMoneyBank: ActionInteractBase {
    ref DZLBankingConfig config;

    DZLBankingConfig GetConfig() {
        if(!config) {
            config = DZLConfig.Get().bankConfig;
        }

        return config;
    }

    void ActionTakeRobtMoneyBank() {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
        m_HUDCursorIcon = CursorIcons.None;
    }

    override string GetText() {
        return "#take_robt_money";
    }

    override void CreateConditionComponents() {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new DZL_CCTActionObject;
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if(GetGame().IsClient()) {
            if(!player.GetConfig()) return false;
            config = player.GetConfig().bankConfig;
        } else {
            GetConfig();
        }

        DZLBaseActionObject objectTarget = DZLBaseActionObject.Cast(target.GetObject());

        if(!objectTarget || !objectTarget.IsBank()) return false;

        if(GetGame().IsServer()) {
            DZLBank bank = DZLDatabaseLayer.Get().GetBank();
            if(bank.RaidRuns()) {
                DZLSendMessage(player.GetIdentity(), "#raid_has_not_finished (" + bank.GetCountDownRaid() + "s)");
                return false;
            }


            if(!bank.HasMoneyToRaid()) {
                DZLSendMessage(player.GetIdentity(), "#dzl_safe_is_closed");
                return false;
            }

            if(vector.Distance(bank.GetRaidPosition(), player.GetPosition()) <= config.maximumRaidDistanceToBank) {
                return true;
            }
            DZLSendMessage(player.GetIdentity(), "#not_in_near_of_raided_bank");
            return false;
        }
        return true;
    }

    override void OnStartServer(ActionData action_data) {
        GetConfig();
        PlayerBase player = action_data.m_Player;

        if(player) {
            DZLBank bank = DZLDatabaseLayer.Get().GetBank();
            int money = bank.PlayerRaidBank(player.GetDZLPlayer(), config.percentOfMoneyWhenRaid);
            DZLSendMessage(null, "#bank_rob_was_successful " + money.ToString());
            DZLLogRaid(player.GetPlayerId(), "bank raid finished", "bank", player.GetPosition());

            GetGame().RPCSingleParam(null, DAY_Z_LIFE_PLAYER_BANK_DATA_RESPONSE, new Param1<ref DZLBank>(bank), true);
            GetGame().RPCSingleParam(null, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(player.GetDZLPlayer()), true, player.GetIdentity());
        }
    }
};
