class DZLBankingLocationBuilder: DZLLicenceLocationBuilder {

    override void Create() {
		array<ref DZLBankingPosition> positions = DZLConfig.Get().bankConfig.positionOfBankingPoints;
		
		foreach(DZLBankingPosition position: positions) {
		    DZLBaseActionObject object = CreatePositions(position, "DZLBankActionObjectYellow");
        }
	}
};
