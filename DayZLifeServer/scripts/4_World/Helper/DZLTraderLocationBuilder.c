class DZLTraderLocationBuilder: DZLLicenceLocationBuilder 
{
    override void Create() {
		array<ref DZLTraderPosition> positions = DZLConfig.Get().traderConfig.positions.positions;
		
		foreach(DZLTraderPosition position: positions) {
            DZLBaseActionObject object = CreatePositions(position);
            object.EnableTrader();
        }
	}
};
