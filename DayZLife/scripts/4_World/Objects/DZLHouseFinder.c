class DZLHouseFinder
{
	private ref DZLObjectFinder objectFinder;
	private ref DZLConfig config;

	void DZLHouseFinder() {
	    objectFinder = new DZLObjectFinder;
	}
	
	void SetConfig(DZLConfig config) {
		this.config = config;
		objectFinder.SetConfig(config.GetHouseDeinitions());
	}

    DZLHouseDefinition find() {
		DayZPlayer player = GetGame().GetPlayer();

        vector dir = GetGame().GetPointerDirection();
        vector from = GetGame().GetCurrentCameraPosition();
        vector to = from + ( dir * 100 );

        Object object = objectFinder.GetObjectsAt(from, to, player);

        if (!object) {
            DebugMessageDZL("has object not found");
            return null;
        }
        DebugMessageDZL("has object found");

        Building house = Building.Cast(object);
        
		DZLHouseDefinition actualHouseDef = GetHouseDefinitionByBuilding(house);

        if (!actualHouseDef) {
            DebugMessageDZL("has house not found");
            return null;
        }

        return actualHouseDef;
    }
	
	DZLHouseDefinition GetHouseDefinitionByBuilding(Building house) {
		DZLHouseDefinition actualHouseDef;

        foreach(DZLHouseDefinition houseDef: config.GetHouseDeinitions()) {
            if(house.GetType() == houseDef.houseType) {
                actualHouseDef = houseDef;
                break;
            }
        }
		
		return actualHouseDef;
	}
}