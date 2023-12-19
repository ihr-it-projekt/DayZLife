class DZLGarageLocationBuilder: DZLLicenceLocationBuilder {

    override void Create() {
        array<ref DZLStoragePosition> positions = DZLConfig.Get().carConfig.garages;

        foreach(DZLStoragePosition position: positions) {
            DZLBaseActionObject object = CreatePositions(position, "DZLParkingMeter");
        }
    }
};
