class DZLBuildingHelper
{
    static ref DZLBuilding ActionTargetToDZLBuilding(ActionTarget target){
        Building building = Building.Cast(target.GetObject());
        if(building) {
            return new DZLBuilding(building);
        }
        return NULL;
    }
}