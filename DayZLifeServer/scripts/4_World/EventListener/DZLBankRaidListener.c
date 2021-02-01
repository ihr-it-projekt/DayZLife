class DZLBankRaidListener : Managed 
{
    ref DZLBankingConfig config;
    float time = 300;
	int timeHappened = 0;
    private ref Timer raidTimer;
    private PlayerBase playerWhoStartedRaid;
    private DZLBankingPosition position;

    void DZLBankRaidListener() {
        config = DZLConfig.Get().bankConfig;
        time = config.raidTimeBankInSeconds;
        GetDayZGame().Event_OnRPC.Insert(Start);
        raidTimer = new Timer;
    }

    void ~DZLBankRaidListener() {
       GetDayZGame().Event_OnRPC.Remove(Start);
    }

	void Start(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
		if (!DZLLicenceCheck.Get().HasActiveLicence(sender)) return;
        if (rpc_type == DAY_Z_LIFE_START_BANK_RAID) {
            array<Man> players = new array<Man>;
            GetGame().GetPlayers(players);

            if (config.raidIsPlayerControlled && config.minCountPlayerForRaid > 0) {
                if (players.Count() < config.minCountPlayerForRaid) {
                    DZLSendMessage(sender, "#raid_can_not_start_to_less_players");
                    return;
                }
            }

            if (config.raidTimeControlled) {
                DZLDate date = new DZLDate;

                if (date.hour < config.raidStartTimeHour || date.hour > config.raidEndTimeHour) {
                    DZLSendMessage(sender, "#raid_can_not_start_wrong_time");
                    return;
                } else if ((date.hour == config.raidEndTimeHour && date.minute > config.raidEndTimeMinute) || (date.hour == config.raidStartTimeHour && date.minute < config.raidStartTimeMinute)) {
                    DZLSendMessage(sender, "#raid_can_not_start_wrong_time");
                    return;
                }
            }

            DZLBank bank = DZLDatabaseLayer.Get().GetBank();

            if (!playerWhoStartedRaid) {
                foreach(DZLBankingPosition _position: config.positionOfBankingPoints) {
                    if (_position && _position.position && vector.Distance(_position.position, PlayerBase.Cast(target).GetPosition()) <= config.maximumRaidDistanceToBank){
                         if (_position.raidIsEnabled) {
                            playerWhoStartedRaid = PlayerBase.Cast(target);
                            position = _position;
                            break;
                         }
                    }
                }

                if (playerWhoStartedRaid) {
                    bank.StartRaid();
                    timeHappened = 0;
                    DZLSendMessage(null, "#bank_rob_was_started");
                    DZLLogRaid(sender.GetId(), "start bank raid", "bank", playerWhoStartedRaid.GetPosition());

                    raidTimer.Run(1, this, "Finish", null, true);
                }
            } else {
                DZLSendMessage(sender, "#raid_allready_started");
            }
        }
    }

    void Finish() {
		if (time > timeHappened) {
            if (!isInNearOfBankAndLocationIsEnabled()) {
                playerWhoStartedRaid = null;
                raidTimer.Stop();
                DZLBank bank_cancel = DZLDatabaseLayer.Get().GetBank();
                bank_cancel.CancelRaid();
                DZLSendMessage(null, "#bank_rob_was_canceled");
                return;
            }

            if (timeHappened % 300 == 1) {
                int leftMinutes = (time - timeHappened) / 60;
                DZLSendMessage(playerWhoStartedRaid.GetIdentity(), "#bank_rob_will_finished_in " + leftMinutes.ToString());
            }
			
		    timeHappened++;
			return;
		}

        raidTimer.Stop();
		DZLBank bank = DZLDatabaseLayer.Get().GetBank();
        bank.RaidIsFinished();
        DZLPlayer dzlPlayer = playerWhoStartedRaid.GetDZLPlayer();

        int money = bank.PlayerRaidBank(dzlPlayer, config.percentOfMoneyWhenRaid);
        DZLSendMessage(null, "#bank_rob_was_successful " + money.ToString());
        DZLLogRaid(playerWhoStartedRaid.GetPlayerId(), "bank raid finished", "bank", playerWhoStartedRaid.GetPosition());

        array<Man> allPlayers = new array<Man>;
        GetGame().GetPlayers(allPlayers);

        foreach(Man playerMan: allPlayers) {
            PlayerBase player = PlayerBase.Cast(playerMan);
            PlayerIdentity playerIdentity = player.GetIdentity();
            if (!player || !playerIdentity)  continue;

            GetGame().RPCSingleParam(null, DAY_Z_LIFE_PLAYER_BANK_DATA_RESPONSE, new Param1<ref DZLBank>(bank), true, playerIdentity);
            GetGame().RPCSingleParam(null, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(player.GetDZLPlayer()), true, playerIdentity);
        }

        playerWhoStartedRaid = null;
    }

    private bool isInNearOfBankAndLocationIsEnabled() {
        if (!playerWhoStartedRaid) {
            return false;
        }

        if (!playerWhoStartedRaid.IsAlive()) {
            return false;
        }

        vector playerPosition = playerWhoStartedRaid.GetPosition();
        if (!playerPosition) {
            return false;
        }

        return position && position.position && vector.Distance(position.position, playerPosition) <= config.maximumRaidDistanceToBank);
    }

}
