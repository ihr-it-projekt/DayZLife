class DZLBuildingHelper
{
    static ref DZLBuilding ActionTargetToDZLBuilding(ActionTarget target){
        Building building = Building.Cast(target.GetObject());
        if(building) {
            return new DZLBuilding(building);
        }
        return null;
    }
	
	static ref DZLHouse ActionTargetToDZLHouse(ActionTarget target){
        Building building = Building.Cast(target.GetObject());
        if(building) {
            return new DZLHouse(building);
        }
        return null;
    }
}