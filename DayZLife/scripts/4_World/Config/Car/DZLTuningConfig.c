class DZLTuningConfig
{
    ref array<ref DZLTuneOption> options;
    ref array<ref DZLTunerPosition> tuner;
    string version = "1";

    void DZLTuningConfig() {
        if(!Load()) {
            tuner = new array<ref DZLTunerPosition>;

            array<string> ids = new array<string>;

            DZLTunerPosition position = DZLTunerPosition("6572.2 7.2 2466.7", "0.0 0.0 0.0", ids);
            tuner.Insert(position);

            options = new array<ref DZLTuneOption>;

            array<ref DZLCarTuneConfig>option = new array<ref DZLCarTuneConfig>;

            array<ref CarTuneAttachment> tunedAttachments = new array<ref CarTuneAttachment>;
            CarTuneAttachment tunedAttachment = new CarTuneAttachment("hood", "Hatchback_02_Hood");
            tunedAttachments.Insert(tunedAttachment);
            tunedAttachment = new CarTuneAttachment("trunk", "Hatchback_02_Trunk");
            tunedAttachments.Insert(tunedAttachment);
            option.Insert(new DZLCarTuneConfig("Hatchback_02", tunedAttachments));

			tunedAttachments = new array<ref CarTuneAttachment>;
            tunedAttachment = new CarTuneAttachment("hood", "Hatchback_02_Hood_Blue");
            tunedAttachments.Insert(tunedAttachment);
            tunedAttachment = new CarTuneAttachment("trunk", "Hatchback_02_Trunk_Blue");
            tunedAttachments.Insert(tunedAttachment);
            option.Insert(new DZLCarTuneConfig("Hatchback_02_Blue", tunedAttachments));

			tunedAttachments = new array<ref CarTuneAttachment>;
            tunedAttachment = new CarTuneAttachment("hood", "Hatchback_02_Hood_Black");
            tunedAttachments.Insert(tunedAttachment);
            tunedAttachment = new CarTuneAttachment("trunk", "Hatchback_02_Trunk_Black");
            tunedAttachments.Insert(tunedAttachment);
            option.Insert(new DZLCarTuneConfig("Hatchback_02_Black", tunedAttachments));
			
			DZLTuneOption tuneOption = new DZLTuneOption("Hatchback_02", option);

            options.Insert(tuneOption);

            version = "1";
            Save();
        }
    }

    array<ref DZLCarTuneConfig> GetTargetCarsForCar(string orgType) {
        foreach(DZLTuneOption option: options) {
            if (orgType.Contains(option.car)) {
                return option.targetCars;
            }
        }
        return null;
    }

    DZLCarTuneConfig GetOptionByType(string searchedType) {
        foreach(DZLTuneOption option: options) {
            foreach(DZLCarTuneConfig targetConfig: option.targetCars) {
                if (targetConfig.type == searchedType) {
                    return targetConfig;
                }
            }
        }
        return null;
    }

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "CarTuningConfig.json")) {
            JsonFileLoader<DZLTuningConfig>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "CarTuningConfig.json", this);
            return true;
        }
        return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
            CheckDZLConfigPath();
            JsonFileLoader<DZLTuningConfig>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "CarTuningConfig.json", this);
        }
    }
}