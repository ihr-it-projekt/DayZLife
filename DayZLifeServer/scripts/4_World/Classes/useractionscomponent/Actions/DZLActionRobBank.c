modded class DZLActionRobBank: ActionInteractBase {

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if(!super.ActionCondition(player, target, item)) return false;

        if(!config.canStartRaidIfShopRaidRuns && DZLDatabaseLayer.Get().GetCrimeData().ShopRaidRuns()) {
            DZLSendMessage(player.GetIdentity(), "#one_shop_rob_is_already_started");
            return false;
        }

        if(config.raidIsCopControlled && config.minCountCopsForRaid > 0) {
            if(DZLDatabaseLayer.Get().GetCopCount() < config.minCountCopsForRaid) {
                DZLSendMessage(player.GetIdentity(), "#raid_can_not_start_to_less_players");
                return false;
            }
        }

        if(config.raidTimeControlled) {
            DZLDate date = new DZLDate;
            if(date.hour < config.raidStartTimeHour || date.hour > config.raidEndTimeHour) {
                DZLSendMessage(player.GetIdentity(), "#raid_can_not_start_wrong_time");
                return false;
            }
            if((date.hour == config.raidEndTimeHour && date.minute > config.raidEndTimeMinute) || (date.hour == config.raidStartTimeHour && date.minute < config.raidStartTimeMinute)) {
                DZLSendMessage(player.GetIdentity(), "#raid_can_not_start_wrong_time");
                return false;
            }
        }
        DZLBank bank = DZLDatabaseLayer.Get().GetBank();
        if(bank.RaidRuns()) {
            DZLSendMessage(player.GetIdentity(), "#raid_all_ready_started (" + bank.GetCountDownRaid() + "s)");
            return false;
        }

        if(bank.HasMoneyToRaid()) {
            DZLSendMessage(player.GetIdentity(), "#safe_is_open");
            return false;
        }
        return true;
    }

    override void OnStartServer(ActionData action_data) {
        PlayerBase player = action_data.m_Player;

        if(!player) return;

        vector playerPosition = action_data.m_Player.GetPosition();
        foreach(DZLBankingPosition position: config.positionOfBankingPoints) {
            if(!position) continue;
            if(!position.position) continue;
            if(vector.Distance(position.position, playerPosition) > config.maximumRaidDistanceToBank) continue;

            DZLBank bank = DZLDatabaseLayer.Get().GetBank();
            bank.StartRaid(position.position, config.raidTimeBankInSeconds);
            DZLSendMessage(null, "#bank_rob_was_started");
            DZLLogRaid(player.GetPlayerId(), "start bank raid", "bank", player.GetPosition());
            return
        }
    }

};
