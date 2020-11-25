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

    static Building GetBuilding(DZLHouse house) {
        array<Object> objects = new array<Object>;
        array<CargoBase> proxyCargos = new array<CargoBase>;

        GetGame().GetObjectsAtPosition(house.position, 2, objects, proxyCargos);
		
        foreach (Object object: objects) {
            if (object.GetType() == house.name) {
                return Building.Cast(object);
            }
        }
     	
        return null;
    }
}