modded class Hacksaw
{
	override void SetActions()
	{
		super.SetActions();
		
		RemoveAction(ActionSawPlanks);
	}
}

modded class Pickaxe
{
	override bool CanMakeGardenplot()
	{
		return false;
	}
	
	override void SetActions()
	{
		super.SetActions();
		
		RemoveAction(ActionTogglePlaceObject);
		RemoveAction(ActionDigGardenPlot);
		RemoveAction(ActionMineRock);
		RemoveAction(ActionDigOutStash);
		RemoveAction(ActionDigInStash);
	}
}

modded class Shovel
{
	override bool CanMakeGardenplot()
	{
		return false;
	}

	override void SetActions()
	{
		super.SetActions();
		
		RemoveAction(ActionTogglePlaceObject);
		RemoveAction(ActionDigGardenPlot);
		RemoveAction(ActionDigOutStash);
		RemoveAction(ActionDigInStash);
	}
}

modded class HandSaw
{
	override void SetActions()
	{
		super.SetActions();
		
		RemoveAction(ActionSawPlanks);
	}
}

modded class SledgeHammer
{
	override void SetActions()
	{
		super.SetActions();
		
		RemoveAction(ActionMineRock);
	}
}
