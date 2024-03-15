class DZLHouseConfig {
    string version = "7";
    int minCountOfCopsForRaid = 3;

    // deprecated remove 08.03.25
    private ref array<ref DZLJobHouseDefinition> copHouseConfigs = new array<ref DZLJobHouseDefinition>();
    private ref array<ref DZLJobHouseDefinition> medicHouseConfigs = new array<ref DZLJobHouseDefinition>();
    private ref array<ref DZLJobHouseDefinition> armyHouseConfigs = new array<ref DZLJobHouseDefinition>();
    // deprecated end

    private ref array<ref DZLJobHouseDefinitionCollection> jobHouseDefinitions = new array<ref DZLJobHouseDefinitionCollection>();

    void DZLHouseConfig(array <string> jobs) {
        if(!Load()) {
            CreateJobConfigs(jobs);

            Save();
        }

        if(version == "5") {
            foreach(DZLJobHouseDefinitionCollection definition: jobHouseDefinitions) {
                definition.MigrateToVersion6(DAY_Z_LIFE_JOB_COP, copHouseConfigs);
                definition.MigrateToVersion6(DAY_Z_LIFE_JOB_MEDIC, medicHouseConfigs);
                definition.MigrateToVersion6(DAY_Z_LIFE_JOB_ARMY, armyHouseConfigs);
            }

            version = "6";
            Save();
        }

        if(version == "6") {
            version = "7";
            Save();
        }
        CheckAllHouseConfigExist(jobs);

    }

    private void CheckAllHouseConfigExist(array<string> jobNames) {
        foreach(string jobName: jobNames) {
            bool found = false;
            foreach(DZLJobHouseDefinitionCollection jobHouseDefinition: jobHouseDefinitions) {
                if(jobHouseDefinition.jobId == jobName) {
                    found = true;
                    break;
                }
            }
            if(found) continue;
            jobHouseDefinitions.Insert(new DZLJobHouseDefinitionCollection(jobName));
            Save();
        }
    }

    DZLJobHouseDefinition GetJobHouseDefinition(notnull Building building) {
        array<ref DZLJobHouseDefinition> houseJobConfig = new array<ref DZLJobHouseDefinition>();

        foreach(DZLJobHouseDefinitionCollection collection: jobHouseDefinitions) {
            DZLJobHouseDefinition definition = collection.GetDefinitionByType(building.GetType());

            if(definition) return definition;
        }
        return null;
    }

    private void CreateJobConfigs(array<string> jobs) {
        array<string> types;
        foreach(string job: jobs) {
            if(job == DAY_Z_LIFE_JOB_COP) {
                types = {"Land_Village_PoliceStation", "Land_City_PoliceStation", "Land_Prison_Main", "Land_Prison_Side", "Land_Village_PoliceStation_Enoch", "Land_City_PoliceStation_Enoch"};
                jobHouseDefinitions.Insert(CreateJobHouseConfigs(job, types));
                continue;
            }
            if(job == DAY_Z_LIFE_JOB_MEDIC) {
                types = {"Land_City_Hospital", "Land_Village_HealthCare"};
                jobHouseDefinitions.Insert(CreateJobHouseConfigs(job, types));
                continue;
            }
            if(job == DAY_Z_LIFE_JOB_ARMY) {
                types = {"Land_Tisy_HQ", "Land_Mil_ATC_Small", "Land_Mil_ATC_Big", "Land_Mil_Airfield_HQ"};
                jobHouseDefinitions.Insert(CreateJobHouseConfigs(job, types));
                continue;
            }

            jobHouseDefinitions.Insert(new DZLJobHouseDefinitionCollection(job));
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
