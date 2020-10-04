class HouseInfoPoint : BuildingSuper
{	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionOpenBuyHouseMenu);
	}
}