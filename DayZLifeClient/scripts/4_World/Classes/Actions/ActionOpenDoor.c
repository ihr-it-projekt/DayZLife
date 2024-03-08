modded class ActionOpenDoors {
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if(!target) return false;

        if(!IsBuilding(target)) return false;

        Building building = Building.Cast(target.GetObject());
        if(building) {
            int doorIndex = building.GetDoorIndex(target.GetComponentIndex());
            if(doorIndex != -1) {
                DZLPlayer dzlPlayer = player.GetDZLPlayer();
                if(!player.GetConfig()) return false;

                bool canOpenByJob = DZLCanDoDoorAction.canDoByJob(building, player, doorIndex);

                if(GetGame().IsServer()) {
                    DZLHouse dzlHouse = DZLBuildingHelper.ActionTargetToDZLHouse(target);

#ifdef TBRealEstateClient
                    if(!canOpenByJob && !super.ActionCondition(player, target, item)) return false;
#endif

                    if(!dzlHouse) return false;

                    if(!dzlHouse.IsDoorLooked(doorIndex)) return true;

                    if((DZLConfig.Get().adminIds.CanManageCops(dzlPlayer.dayZPlayerId) && dzlPlayer.HasJob(DAY_Z_LIFE_JOB_COP)) || (DZLConfig.Get().adminIds.CanManageArmy(dzlPlayer.dayZPlayerId) && dzlPlayer.HasJob(DAY_Z_LIFE_JOB_ARMY))) {
                        return true;
                    }
                    DZLSendMessage(player.GetIdentity(), "#door_is_looked");
                    return false;
                }

                return canOpenByJob && !building.IsDoorOpen(doorIndex) && !building.IsDoorLocked(doorIndex));
            }
        }
        return false;
    }
};