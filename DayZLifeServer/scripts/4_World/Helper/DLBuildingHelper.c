class DLBuildingHelper
{
    static ref DLBuilding ActionTargetToDLBuilding(ActionTarget target){
        Building building;
        if(Class.CastTo(building, target.GetObject()))
        {
            return new DLBuilding(building);
        }
        return NULL;
    }

}