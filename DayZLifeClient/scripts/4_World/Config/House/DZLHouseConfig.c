class DZLHouseConfig {
    string version = "6";
    int minCountOfCopsForRaid = 3;

    // deprecated remove 08.03.25
    private ref array<ref DZLJobHouseDefinition> copHouseConfigs = new array<ref DZLJobHouseDefinition>();
    private ref array<ref DZLJobHouseDefinition> medicHouseConfigs = new array<ref DZLJobHouseDefinition>();
    private ref array<ref DZLJobHouseDefinition> armyHouseConfigs = new array<ref DZLJobHouseDefinition>();
    // deprecated end

    private ref array<ref DZLJobHouseDefinitionCollection> jobHouseDefinitions = new array<ref DZLJobHouseDefinitionCollection>();

    ref array<ref DZLHouseDefinition> houseConfigs = new array<ref DZLJobHouseDefinition>();

    void DZLHouseConfig(array <string> jobs) {
        if(!Load()) {
            CreateCivilHouseDefinition();
            CreateJobConfigs(jobs);

            Save();
        }

        if (version == "5") {
            foreach(DZLJobHouseDefinitionCollection definition: jobHouseDefinitions) {
                definition.MigrateToVersion6(DAY_Z_LIFE_JOB_COP, copHouseConfigs);
                definition.MigrateToVersion6(DAY_Z_LIFE_JOB_MEDIC, medicHouseConfigs);
                definition.MigrateToVersion6(DAY_Z_LIFE_JOB_ARMY, armyHouseConfigs);
            }

            version = "6";
            Save();
        }
    }

    DZLHouseDefinition GetHouseDefinitionByBuilding(notnull Building building) {
        foreach(DZLHouseDefinition definition: houseConfigs) {
            if(definition.houseType == building.GetType()) {
                return definition;
            }
        }

        return null;
    }

    bool HasHouseDefinition(string type) {
        foreach(DZLHouseDefinition definition: houseConfigs) {
            if(definition.houseType == type) {
                return true;
            }
        }

        return false;
    }

    DZLJobHouseDefinition GetJobHouseDefinition(notnull Building building) {
        array<ref DZLJobHouseDefinition> houseJobConfig = new array<ref DZLJobHouseDefinition>();

        foreach(DZLJobHouseDefinitionCollection collection: jobHouseDefinitions) {
            DZLJobHouseDefinition definition = collection.GetDefinitionByType(building.GetType());

            if (definition) return definition;
        }
        return null;
    }

    private void CreateCivilHouseDefinition() {
        array<string> civTypes = {"Land_Garage_Row_Small","Land_Garage_Row_Small","Land_Shed_W6","Land_Garage_Office","Land_Factory_Small","Land_House_1B01_Pub","Land_House_1W10", "Land_House_1W10_Brown", "Land_House_1W03", "Land_House_1W09_Yellow", "Land_House_1W04", "Land_House_2W01", "Land_House_1W08", "Land_House_1W08_Brown", "Land_House_2B02", "Land_House_2B01", "Land_House_1W07", "Land_House_1W11", "Land_House_1W05", "Land_House_1W05_Yellow", "Land_House_1W01", "Land_House_1W06", "Land_House_2W02", "Land_House_2W03", "Land_House_2W04", "Land_House_2W04_Yellow", "Land_House_2B03"};
        foreach(string type: civTypes) {
            houseConfigs.Insert(new DZLHouseDefinition(type));
        }
    }

    private void CreateJobConfigs(array<string> types) {
        foreach(job: jobs) {
                if (job == DAY_Z_LIFE_JOB_COP) {
                    array<string> types = {"Land_Village_PoliceStation", "Land_City_PoliceStation", "Land_Prison_Main", "Land_Prison_Side", "Land_Village_PoliceStation_Enoch", "Land_City_PoliceStation_Enoch"};
                    jobHouseDefinitions.Insert(CreateJobHouseConfigs(job, types));
                    continue;
                }
                if (job == DAY_Z_LIFE_JOB_MEDIC) {
                    array<string> types = {"Land_City_Hospital", "Land_Village_HealthCare"};
                    jobHouseDefinitions.Insert(CreateJobHouseConfigs(job, types));
                    continue;
                }
                if (job == DAY_Z_LIFE_JOB_ARMY) {
                    array<string> types = {"Land_Tisy_HQ", "Land_Mil_ATC_Small", "Land_Mil_ATC_Big", "Land_Mil_Airfield_HQ"};
                    jobHouseDefinitions.Insert(CreateJobHouseConfigs(job, types));
                    continue;
                }

                jobHouseDefinitions.Insert(new DZLJobHouseDefinitionCollection(job, {}));
            }
    }

    private DZLJobHouseDefinitionCollection CreateJobHouseConfigs(string jobId, array<string> types) {
        DZLJobHouseDefinitionCollection collection = new DZLJobHouseDefinitionCollection(jobId);
        foreach(string type: types) {
            collection.houseDefinitions.Insert(new DZLJobHouseDefinition(type, 30));
        }

        return collection;
    }

    private bool Load() {
        if(GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "house.json")) {
            JsonFileLoader<DZLHouseConfig>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "house.json", this);
            return true;
        }
        return false;
    }

    private void Save() {
        if(GetGame().IsServer()) {
            CheckDZLConfigPath();
            JsonFileLoader<DZLHouseConfig>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "house.json", this);
        }
    }

}
