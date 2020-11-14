class DZLTraderLocationBuilder: DZLLicenceLocationBuilder {

    override static void Create() {
        DZLTraderConfig config = new DZLTraderConfig;
		array<ref DZLTraderPosition> positions = config.positions.positions;
		
		foreach(DZLTraderPosition position: positions) {
           PlayerBase trader = DZLTraderLocationBuilder.CreatePositions(position, false, false, true);
        }
	}
};