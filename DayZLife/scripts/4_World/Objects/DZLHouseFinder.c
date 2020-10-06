class DZLHouseFinder
{
	private ref DZLObjectFinder objectFinder;
	private ref DZLServerConfig config;

	void DZLHouseFinder() {
	    objectFinder = new DZLObjectFinder;
	}
	
	void SetConfig(DZLServerConfig config) {
		this.config = config;
		objectFinder.SetConfig(config.houseConfig);
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
        DZLHouseDefinition actualHouseDef;

        foreach(DZLHouseDefinition houseDef: config.houseConfig.houseConfigs) {
            if(house.GetType() == houseDef.houseType) {
                actualHouseDef = houseDef;
                break;
            }
        }

        if (!actualHouseDef) {
            DebugMessageDZL("has house not found");
            return null;
        }

        return actualHouseDef;
    }
}