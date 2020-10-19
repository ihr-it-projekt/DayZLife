class DZL_Crate_Base : Container_Base
{
	override bool CanPutIntoHands(EntityAI parent)
	{
		if( !super.CanPutIntoHands(parent) )
		{
			return false;
		}
		return false;
	}
	
	override bool CanPutInCargo(EntityAI parent)
	{
		if( !super.CanPutInCargo(parent) )
		{
			return false;
		}
		return false;
	}
};

class DZL_Wooden_Crate_1 : DZL_Crate_Base
{
	
};

class DZL_Wooden_Crate_3 : DZL_Crate_Base
{
	
};

class DZL_Wooden_Crate_5 : DZL_Crate_Base
{
	
};