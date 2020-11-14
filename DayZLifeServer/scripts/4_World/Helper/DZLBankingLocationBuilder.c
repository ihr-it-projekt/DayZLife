class DZLBankingLocationBuilder: DZLLicenceLocationBuilder {

    override static void Create() {
        DZLBankingConfig bankingConfig = new DZLBankingConfig;
		array<ref DZLBankingPosition> positions = bankingConfig.positionOfBankingPoints;
		
		foreach(DZLBankingPosition position: positions) {
            DZLBankingLocationBuilder.CreatePositions(position, true, false, false);
        }
	}
};