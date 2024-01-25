class DZLHouseFinder {
    ref DZLObjectFinder objectFinder;
    private ref DZLConfig config;

    void DZLHouseFinder() {
        objectFinder = new DZLObjectFinder;
    }

    void SetConfig(DZLConfig config) {
        this.config = config;
        objectFinder.SetConfig(config.GetHouseDefinitions());
    }

    DZLHouseDefinition find() {
        DayZPlayer player = GetGame().GetPlayer();

        vector dir = GetGame().GetPointerDirection();
        vector from = GetGame().GetCurrentCameraPosition();
        vector to = from + (dir * 100);

        Object object = objectFinder.GetObjectsAt(from, to, player);

        if(!object) {
            return null;
        }

        Building house = Building.Cast(object);

        DZLHouseDefinition actualHouseDef = GetHouseDefinitionByBuilding(house);

        if(!actualHouseDef) {
            return null;
        }

        return actualHouseDef;
    }

    DZLHouseDefinition GetHouseDefinitionByBuilding(Building house) {
        DZLHouseDefinition actualHouseDef;
        array<ref DZLHouseDefinition> houseDefs = config.GetHouseDefinitions();
        foreach(DZLHouseDefinition houseDef: houseDefs) {
            if(house.GetType() == houseDef.houseType) {
                actualHouseDef = houseDef;
                break;
            }
        }

        return actualHouseDef;
    }
}