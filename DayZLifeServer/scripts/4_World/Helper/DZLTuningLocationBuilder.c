class DZLTuningLocationBuilder: DZLLicenceLocationBuilder {

    override void Create() {
        array<ref DZLTunerPosition> positions = DZLConfig.Get().tuningConfig.tuner;

        foreach(DZLTunerPosition position: positions) {
            DZLBaseActionObject object = CreatePositions(position, "DZLTuningActionObject");
        }
    }
};
