class DZLBankingLocationBuilder: DZLLicenceLocationBuilder {

    void DZLBankingLocationBuilder() {
        Init();
    }

    override void Create() {
		array<ref DZLBankingPosition> positions = DZLConfig.Get().bankConfig.positionOfBankingPoints;
		
		foreach(DZLBankingPosition position: positions) {
            npcs.Insert(new DZLNPCKeepPosition(CreatePositions(position, true, false, false, false, false)));
        }
	}
};
