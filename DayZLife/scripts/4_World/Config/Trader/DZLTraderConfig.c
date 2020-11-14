class DZLTraderConfig
{
	ref DZLTraderConfigParams traderConfigParams;
    ref DZLTraderPositionCollection positions;
	ref DZLTraderCategoryCollection categories;

    void DZLTraderConfig()
    {
  		this.traderConfigParams = new DZLTraderConfigParams;
  		this.positions = new DZLTraderPositionCollection;
		this.categories = new DZLTraderCategoryCollection;
	}
}