class DZLBankRaidListener : Managed 
{
    ref DZLBankingConfig config;
    float time = 300;
	int timeHappened = 0;
    private ref Timer raidTimer;
    private PlayerBase playerWhoStartedRaid;

    void DZLBankRaidListener() {
        config = new DZLBankingConfig;
        time = config.raidTimeBankInSeconds;
        GetDayZGame().Event_OnRPC.Insert(Start);
        raidTimer = new Timer;
    }

    void ~DZLBankRaidListener() {
       GetDayZGame().Event_OnRPC.Remove(Start);
    }

	void Start(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_START_BANK_RAID) {
			DebugMessageDZL("Recive Rob bank");
            autoptr Param1<PlayerBase> param;
            if (ctx.Read(param)){
				DZLBank bank = new DZLBank;
				if (!bank.raidRuns) {
					bank.StartRaid();
					timeHappened = 0;
					playerWhoStartedRaid = param.param1;
					GetGame().RPCSingleParam(target, ERPCs.RPC_USER_ACTION_MESSAGE, new Param1<string>("#bank_rob_was_started"), true);
			        raidTimer.Run(1, this, "Finish", null, true);
					DebugMessageDZL("Rob started");
				} else {
					GetGame().RPCSingleParam(target, ERPCs.RPC_USER_ACTION_MESSAGE, new Param1<string>("#raid_allready_started"), true, sender);
				}
			}
		}
    }

    void Finish() {
		if (time > timeHappened) {
            if (!isInNearOfBank()) {
				DebugMessageDZL("is not in near");
                raidTimer.Stop();
                DZLBank bank_cancel = new DZLBank;
                bank_cancel.CancelRaid();
                GetGame().RPCSingleParam(playerWhoStartedRaid, ERPCs.RPC_USER_ACTION_MESSAGE, new Param1<string>("#bank_rob_was_canceled"), true);
                return;
            }
			
		    timeHappened++;
			return;
		}
		DebugMessageDZL("Rob finished");
        raidTimer.Stop();
		DZLBank bank = new DZLBank;
        bank.RaidIsFinished();
        DZLPlayer dzlPlayer = new DZLPlayer(playerWhoStartedRaid.GetIdentity().GetId());

        int money = bank.PlayerRaidBank(new DZLPlayer(playerWhoStartedRaid.GetIdentity().GetId()), config.percentOfMoneyWhenRaid);
        GetGame().RPCSingleParam(playerWhoStartedRaid, ERPCs.RPC_USER_ACTION_MESSAGE, new Param1<string>("#bank_rob_was_successful " + money.ToString()), true);
        GetGame().RPCSingleParam(playerWhoStartedRaid, DAY_Z_LIFE_PLAYER_BANK_DATA_RESPONSE, new Param1<ref DZLBank>(bank), true);
        GetGame().RPCSingleParam(playerWhoStartedRaid, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(new DZLPlayer(playerWhoStartedRaid.GetIdentity().GetId())), true, playerWhoStartedRaid.GetIdentity());

        array<Man> _players = new array<Man>;
        GetGame().GetPlayers(_players);

        if (_players) {
            foreach(Man _player: _players) {
                GetGame().RPCSingleParam(_player, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(new DZLPlayer(_player.GetIdentity().GetId())), true, _player.GetIdentity());
            }
        }
    }

    private bool isInNearOfBank() {
        if (!playerWhoStartedRaid) {
            return false;
        }
        vector playerPosition = playerWhoStartedRaid.GetPosition();
        if (!playerPosition) {
            return false;
        }
        foreach(DZLBankingPosition position: config.positionOfBankingPoints) {
            if (vector.Distance(position.position, playerPosition) <= config.maximumRaidDistanceToBank){
                return true;
            }
        }
        return false;
    }

}