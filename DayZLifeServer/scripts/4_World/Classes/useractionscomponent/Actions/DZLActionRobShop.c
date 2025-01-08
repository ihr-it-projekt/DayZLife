modded class DZLActionRobShop {

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if(!super.ActionCondition(player, target, item)) return false;

        if(config.raidIsCopControlled && config.minCountCopsForRaid > 0) {
            if(DZLDatabaseLayer.Get().GetCopCount() < config.minCountCopsForRaid) {
                DZLSendMessage(player.GetIdentity(), "#raid_can_not_start_to_less_cops");
                return false;
            }
        }

        if(config.raidTimeControlled) {
            DZLDate date = new DZLDate;

            if(date.hour < config.raidStartTimeHour || date.hour > config.raidEndTimeHour) {
                DZLSendMessage(player.GetIdentity(), "#raid_can_not_start_wrong_time");
                return false;
            } else if((date.hour == config.raidEndTimeHour && date.minute > config.raidEndTimeMinute) || (date.hour == config.raidStartTimeHour && date.minute < config.raidStartTimeMinute)) {
                DZLSendMessage(player.GetIdentity(), "#raid_can_not_start_wrong_time");
                return false;
            }
        }

        return true;
    }

};
