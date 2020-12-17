class DZLBankingLocationBuilder: DZLLicenceLocationBuilder {

    override static void Create() {
        DZLBankingConfig bankingConfig = DZLConfig.Get().bankConfig;
		array<ref DZLBankingPosition> positions = bankingConfig.positionOfBankingPoints;
		
		foreach(DZLBankingPosition position: positions) {
            DZLBankingLocationBuilder.CreatePositions(position, true, false, false);
        }
	}
};
