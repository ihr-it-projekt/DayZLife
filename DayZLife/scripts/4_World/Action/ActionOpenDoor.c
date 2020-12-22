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
			    DZLCopHouseDefinition definition;
			    DZLPlayer dzlPlayer;
			    if (GetGame().IsServer()) {
			       if (!DZLLicenceCheck.Get().HasActiveLicence(player.GetIdentity())) return false;
			       definition = DZLConfig.Get().houseConfig.GetCopHouseDefinition(building);
			       dzlPlayer = DZLDatabaseLayer.Get().GetPlayer(player.GetIdentity().GetId());
			    } else if (player.config && player.dzlPlayer) {
			       definition = player.config.houseConfig.GetCopHouseDefinition(building);
			       dzlPlayer = player.dzlPlayer;
			    } else {
			        return false;
			    }

                if(definition) {
                    return dzlPlayer.IsActiveAsCop();
                }
					
				if (GetGame().IsServer()) {
	                DZLHouse dzlHouse = DZLBuildingHelper.ActionTargetToDZLHouse(target);
	                if (dzlHouse && !dzlHouse.IsDoorLooked(doorIndex)) {
	                    return true;
	                }
					return false;
				}
                DZLSendMessage(player.GetIdentity(), "#door_is_looked");

				return (!building.IsDoorOpen(doorIndex) && !building.IsDoorLocked(doorIndex));
			}
		}
		return false;
	}
	
	
}
