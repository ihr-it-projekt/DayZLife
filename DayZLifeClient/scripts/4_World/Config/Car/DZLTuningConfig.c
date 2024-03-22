class DZLTuningConfig {
    ref array<ref DZLTuneOption> options = new array<ref DZLTuneOption>;
    ref array<ref DZLTunerPosition> tuner = new array<ref DZLTunerPosition>;
    string version = "1";
    string requiredJob = DAY_Z_LIFE_JOB_MECHANIC;

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