class DZLTuningConfig {
    ref array<ref DZLTuneOption> options;
    ref array<ref DZLTunerPosition> tuner;
    string version = "1";

    array<ref DZLCarTuneConfig> GetTargetCarsForCar(string orgType) {
        foreach(DZLTuneOption option: options) {
            if(orgType.Contains(option.car)) {
                return option.targetCars;
            }
        }
        return null;
    }

    DZLCarTuneConfig GetOptionByType(string searchedType) {
        foreach(DZLTuneOption option: options) {
            foreach(DZLCarTuneConfig targetConfig: option.targetCars) {
                if(targetConfig.type == searchedType) {
                    return targetConfig;
                }
            }
        }
        return null;
    }
}