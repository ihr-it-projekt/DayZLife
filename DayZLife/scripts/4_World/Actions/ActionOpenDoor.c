modded class ActionOpenDoors
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if(!target) return false;

		if(!IsBuilding(target)) return false;

		Building building = Building.Cast(target.GetObject());
		if(building) {
			int doorIndex = building.GetDoorIndex(target.GetComponentIndex());
			if (doorIndex != -1) {
			    DZLJobHouseDefinition definition;
			    DZLJobHouseDefinition medicDefinition;
			    DZLPlayer dzlPlayer = player.GetDZLPlayer();
			    if (GetGame().IsServer()) {
			       if (!DZLLicenceCheck.Get().HasActiveLicence(player.GetIdentity())) return false;
			       definition = DZLConfig.Get().houseConfig.GetCopHouseDefinition(building);
			       if (!definition) {
                       medicDefinition = DZLConfig.Get().houseConfig.GetMedicHouseDefinition(building);
                   }
			    } else if (player.config && player.GetDZLPlayer()) {
			       definition = player.config.houseConfig.GetCopHouseDefinition(building);
			       if (!definition) {
                       medicDefinition = player.config.houseConfig.GetMedicHouseDefinition(building);
                   }
			    } else {
			        return false;
			    }
                bool canOpen = true;
                if(definition && !dzlPlayer.IsActiveAsCop()) {
                    canOpen = false;
                } else if (medicDefinition && !dzlPlayer.IsActiveAsMedic()) {
                    canOpen = false;
                }
					
				if (GetGame().IsServer()) {
	                DZLHouse dzlHouse = DZLBuildingHelper.ActionTargetToDZLHouse(target);
	                if (dzlHouse && !dzlHouse.IsDoorLooked(doorIndex) || (DZLConfig.Get().adminIds.CanManageCops(dzlPlayer.dayZPlayerId) && dzlPlayer.IsActiveAsCop())) {
	                    return true;
	                }
					return false;
				}
                DZLSendMessage(player.GetIdentity(), "#door_is_looked");

				return canOpen && !building.IsDoorOpen(doorIndex) && !building.IsDoorLocked(doorIndex);
			}
		}
		return false;
	}
	
	
}
