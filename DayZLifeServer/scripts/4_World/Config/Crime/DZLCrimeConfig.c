modded class DZLCrimeConfig {

    void DZLCrimeConfig() {
        if(!Load()) {
            robTools = new array<string>;
            robTools.Insert("Deagle");
            shopPosition = new array<ref DZLCrimePosition>;
            shopPosition.Insert(new DZLCrimePosition("6873.430176 8.302020 3093.559082", "135.000015 0.000000 0.000000"));
            Save();
        }
    }

    private bool Load() {
        if(FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "CrimeConfig.json")) {
            JsonFileLoader<DZLCrimeConfig>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "CrimeConfig.json", this);

            if(version == "1") {
                version = "2";
                Save();
                return true;
            }

            return true;
        }

        return false;
    }

    private void Save() {
        JsonFileLoader<DZLCrimeConfig>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "CrimeConfig.json", this);
    }
}