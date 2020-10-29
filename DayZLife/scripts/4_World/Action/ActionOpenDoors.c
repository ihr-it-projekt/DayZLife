modded class ActionOpenDoors: ActionInteractBase
{
	ref DZLHouseConfig config;

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if(GetGame().IsClient()){
			return super.ActionCondition(player, target, item); 
		}

		if(super.ActionCondition(player, target, item)){
			if (config) {
				config = new DZLHouseConfig;
			}
			
			array<ref DZLHouseDefinition> houseConfigs = config.houseConfigs;
			Building building = Building.Cast(target.GetObject());
			bool hasFound = false;
			
			foreach(DZLHouseDefinition definition: houseConfigs) {
				if(definition.houseType == building.GetType()) {
					hasFound = true;
				}
			}
			
			if(hasFound) {
				DZLBuilding dzlBuilding = DZLBuildingHelper.ActionTargetToDZLBuilding(target);
	
				if(dzlBuilding && (dzlBuilding.HasOwner() && dzlBuilding.IsOwner(player))){
					return true;
				} else if (dzlBuilding && dzlBuilding.HasOwner() && !dzlBuilding.IsOwner(player)) {
	                return false;
				} else if (dzlBuilding && !dzlBuilding.HasOwner()) {
	                return true;
				}
			} else {
				return true;
			}
		}
		return false;
	}

};