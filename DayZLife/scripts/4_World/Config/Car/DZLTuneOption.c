class DZLTuneOption
{
    string car;
    ref array<ref DZLCarTuneConfig>targetCars;

    void DZLTuneOption(string _car, array<ref DZLCarTuneConfig> _targetCars) {
        car = _car;
        targetCars = _targetCars;
    }

}