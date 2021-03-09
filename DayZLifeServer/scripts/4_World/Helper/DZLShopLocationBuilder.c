class DZLShopLocationBuilder: DZLLicenceLocationBuilder {

    override void Create() {
		array<ref DZLCrimePosition> positions = DZLConfig.Get().crimeConfig.shopPosition;
		
		foreach(DZLCrimePosition position: positions) {
		    DZLBaseActionObject object = CreatePositions(position, "DZLShopActionObject");
        }
	}
};
