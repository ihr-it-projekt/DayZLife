class DZLTuneOption {
    string car;
    ref array<ref DZLCarTuneConfig>targetCars;

    void DZLTuneOption(string carIn, array<ref DZLCarTuneConfig> _targetCars) {
        car = carIn;
        targetCars = _targetCars;
    }

}