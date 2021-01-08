class DZLTraderLocationBuilder: DZLLicenceLocationBuilder 
{
    void DZLTraderLocationBuilder() {
        Init();
    }

    override void Create() {
		array<ref DZLTraderPosition> positions = DZLConfig.Get().traderConfig.positions.positions;
		
		foreach(DZLTraderPosition position: positions) {
           npcs.Insert(new DZLNPCKeepPosition(CreatePositions(position, false, false, true, false, false)));
        }
	}
};
