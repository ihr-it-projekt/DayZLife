class DZLBuildingHelper
{
    static ref DZLBuilding ActionTargetToDZLBuilding(ActionTarget target){
        Building building;
        if(Class.CastTo(building, target.GetObject()))
        {
            return new DZLBuilding(building);
        }
        return NULL;
    }

}