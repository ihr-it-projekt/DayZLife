modded class ActionConstructor
{
	override void RegisterActions(TTypenameArray actions)
    {
        super.RegisterActions(actions);
		
		actions.Insert(ActionOpenBuyHouseMenu);
		actions.Insert(ActionOpenUpgradeHouseMenu);
		actions.Insert(ActionOpenBankingMenu);
		actions.Insert(ActionRobMoney);
		actions.Insert(ActionRobBank);
		actions.Insert(ActionHarvestItem);
		actions.Insert(ActionOpenLicenseMenu);
		actions.Insert(ActionLicenceCrafting);
    }
}