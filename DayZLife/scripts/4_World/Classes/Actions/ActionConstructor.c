modded class ActionConstructor
{
	override void RegisterActions(TTypenameArray actions)
    {
        super.RegisterActions(actions);
		
		actions.Insert(ActionOpenHouseMenu);
		actions.Insert(ActionOpenTraderMenu);
		actions.Insert(DZLActionOpenBankingMenu);
		actions.Insert(ActionRobMoney);
		actions.Insert(ActionRobMoneyFromDead);
		actions.Insert(ActionRobBank);
		actions.Insert(DZLActionHarvestItem);
		actions.Insert(ActionOpenLicenseMenu);
		actions.Insert(ActionLicenceCrafting);
		actions.Insert(DZLActionLockDoors);
		actions.Insert(DZLActionRaidDoors);
		actions.Insert(DZLActionUnLockDoors);
		actions.Insert(DZLActionTransferMoney);
		actions.Insert(ActionOpenLoadOutMenu);
		actions.Insert(ActionOpenArrestMenu);
		actions.Insert(ActionOpenTicketMenu);
		actions.Insert(DZLActionOpenCarMenu);
		actions.Insert(ActionGetOwnerName);
		actions.Insert(ActionOpenCarStorageMenu);
		actions.Insert(DZLActionRaidCar);
		actions.Insert(ActionGetInsurance);
		actions.Insert(DZLActionPaybackRobtMoney);
		actions.Insert(ActionStopRobBank);
		actions.Insert(ActionTakeRobtMoneyBank);
		actions.Insert(ActionTakeRobtMoneyShop);
		actions.Insert(ActionRobShop);
		actions.Insert(DZLActionGiveNumber);
    }
}
