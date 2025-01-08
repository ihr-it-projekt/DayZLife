class DZLShopRaidListener: DZLBaseEventListener {
    private ref Timer robTimer;
    private int moneyForRob = 0;
    private PlayerBase raider;
    private DZLCrimePosition shopPosition;
    private int robDuration;
    private bool policeMessageWasSend = false;
    private ref DZLDate lastRaidTime;

    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        lastRaidTime = DZLDatabaseLayer.Get().GetCrimeData().GetLastRaidTime();
        if(rpc_type == DZL_RPC.START_ROB_MONEY_FROM_SHOP) {
            PlayerBase playerStart = PlayerBase.Cast(target);
            if(playerStart) {
                DZLCrimePosition positionStart = DZLConfig.Get().crimeConfig.GetShopByPosition(playerStart.GetPosition());
                if(positionStart) {
                    StartRob(playerStart, positionStart);
                }
            }
        } else if(rpc_type == DZL_RPC.PAY_ROB_MONEY_FROM_SHOP) {
            PlayerBase playerGetMoney = PlayerBase.Cast(target);

            if(moneyForRob == 0 && !robTimer) {
                DZLSendMessage(playerGetMoney.GetIdentity(), "#there_is_no_money_to_take");
                return;
            }

            if(playerGetMoney) {
                DZLCrimePosition positionTake = DZLConfig.Get().crimeConfig.GetShopByPosition(playerGetMoney.GetPosition());
                if(positionTake.position == shopPosition.position) {
                    DZLPlayer dzlPlayer = playerGetMoney.GetDZLPlayer();
                    dzlPlayer.AddMoneyToPlayer(moneyForRob);
                    shopPosition = null;
                    raider = null;

                    if(robTimer) {
                        robTimer.Stop();
                        robTimer = null;
                    }

                    lastRaidTime = new DZLDate;
                    DZLDatabaseLayer.Get().GetCrimeData().SetShopRaid(false);
                    DZLDatabaseLayer.Get().GetCrimeData().SetLastRaidTime(lastRaidTime);

                    DZLSendMessage(playerGetMoney.GetIdentity(), "#you_got: " + moneyForRob.ToString() + "$");
                    moneyForRob = 0;
                } else {
                    DZLSendMessage(playerGetMoney.GetIdentity(), "#you_can_not_take_the_money_wrong_position");
                }
            }
        }
    }

    void StartRob(PlayerBase player, DZLCrimePosition position) {
        if(robTimer) {
            DZLSendMessage(player.GetIdentity(), "#there_is_one_shop_robbery_run_at_the_moment");
            return;
        }
        if(raider) {
            DZLSendMessage(player.GetIdentity(), "#one_shop_is_already_robt_take_the_money_there");
            return;
        }

        int raidTimeLeft = GetRaidCoolDownTime();

        if(raidTimeLeft > 0) {
            DZLSendMessage(player.GetIdentity(), "#raid_can_started_earliest_in " + raidTimeLeft.ToString() + " #seconds");
            return;
        }

        if(!IsBankRelevantAndOkay()) {
            DZLSendMessage(player.GetIdentity(), "#one_bank_rob_is_already_started");
            return;
        }

        robTimer = new Timer;
        raider = player;
        shopPosition = position;
        robDuration = 0;
        moneyForRob = 0;
        policeMessageWasSend = false;

        DZLDatabaseLayer.Get().GetCrimeData().SetShopRaid(true);

        DZLSendMessage(null, "#rob_raid_was_started");
        DZLSendMessage(player.GetIdentity(), "#rob_raid_was_started_raider");
        robTimer.Run(DZLConfig.Get().crimeConfig.raidDurationTickInSeconds, this, "TickRob", null, true);
    }

    void TickRob() {
        if(!raider || raider.GetHealth() < 1 || raider.IsUnconscious() || raider.IsRestrained() || vector.Distance(shopPosition.position, raider.GetPosition()) > DZLConfig.Get().crimeConfig.maximumRaidDistanceToShop) {
            raider = null;
            robTimer.Stop();
            robTimer = null;
			moneyForRob = 0;
            DZLSendMessage(null, "#rob_raid_was_stopped");
            DZLDatabaseLayer.Get().GetCrimeData().SetShopRaid(false);
            return;
        }
        DZLCrimeConfig config = DZLConfig.Get().crimeConfig;
        robDuration += config.raidDurationTickInSeconds;
        moneyForRob += Math.RandomIntInclusive(config.minMoneyPerTick, config.maxMoneyPerTick);

        int factorForCopMessage = 0;

        string message = "";
        if(moneyForRob >= config.maxMoneyPerRob) {
            message = "#max_money_for_shop_rob_reached_take_fast_the_money";
            moneyForRob = config.maxMoneyPerRob;
            factorForCopMessage = 1;
            robTimer.Stop();
            robTimer = null;
            DZLDatabaseLayer.Get().GetCrimeData().SetShopRaid(false);
        }

        if(robDuration >= config.maxRaidDurationInSeconds) {
            robDuration = config.maxRaidDurationInSeconds;
            message = "#max_money_for_shop_rob_reached_take_fast_the_money";
            factorForCopMessage = 1;
            robTimer.Stop();
            robTimer = null;
            DZLDatabaseLayer.Get().GetCrimeData().SetShopRaid(false);
        }

        if(factorForCopMessage != 1) {
            float raidTimeDonePercent = robDuration / (config.maxRaidDurationInSeconds / 100);
            float raidMoneyDonePercent = moneyForRob / (config.maxMoneyPerRob / 100);

            factorForCopMessage = (raidTimeDonePercent + raidMoneyDonePercent) / 200;
        }

        float randAlarm = Math.RandomFloatInclusive(factorForCopMessage, 1);

        if(randAlarm >= config.copAlarmFactorForCopMessage && !policeMessageWasSend) {
            DZLMessageListener.SendMessage(raider, "", "#shop_is_raided_by_sender " + raider.GetDZLPlayer().playerName, DZLMessage.TYPE_COP, shopPosition.position);
            policeMessageWasSend = true;
            message = message + " #police_was_informed_that_you_raid_the_shop";
        }

        if(message != "") {
            DZLSendMessage(raider.GetIdentity(), message);
        }
    }

    private int GetRaidCoolDownTime() {
        DZLDate currentDate = new DZLDate();
        lastRaidTime = DZLDatabaseLayer.Get().GetCrimeData().GetLastRaidTime();
        int wait = 0;
        if(!lastRaidTime) return 0;

        DZLCrimeConfig config = DZLConfig.Get().crimeConfig;
        wait = currentDate.inSeconds - lastRaidTime.inSeconds < config.raidCoolDownTimeInSeconds;

        if(wait < 0) {
            DZLDatabaseLayer.Get().GetCrimeData().SetLastRaidTime(null);
            return 0;
        }

        return config.raidCoolDownTimeInSeconds - (currentDate.inSeconds - lastRaidTime.inSeconds);;
    }

    private bool IsBankRelevantAndOkay() {
        if(!DZLConfig.Get().crimeConfig.canStartRaidIfBankRaidRuns) {
            return !DZLDatabaseLayer.Get().GetBank().RaidRuns();
        }
        return true;
    }
}
