class DZLBankingLocationBuilder: DZLLicenceLocationBuilder {

    override static void Create() {
		array<ref DZLBankingPosition> positions = DZLConfig.Get().bankConfig.positionOfBankingPoints;
		
		foreach(DZLBankingPosition position: positions) {
            DZLBankingLocationBuilder.CreatePositions(position, true, false, false, false);
        }
	}
};
