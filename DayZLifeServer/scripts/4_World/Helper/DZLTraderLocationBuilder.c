class DZLTraderLocationBuilder: DZLLicenceLocationBuilder {

    override static void Create() {
		array<ref DZLTraderPosition> positions = DZLConfig.Get().traderConfig.positions.positions;
		
		foreach(DZLTraderPosition position: positions) {
           PlayerBase trader = DZLTraderLocationBuilder.CreatePositions(position, false, false, true, false);
        }
	}
};
