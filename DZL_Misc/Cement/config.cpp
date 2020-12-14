class CfgPatches
{
	class Cement
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data"
		};
	};
};
class CfgVehicles
{
	class Inventory_Base;
	class Stone;
	class DZL_Stone: Stone
	{
		scope=2;
		displayName="$STR_CfgVehicles_Stone0";
		descriptionShort="$STR_CfgVehicles_Stone1";
		model="\dz\gear\consumables\Stone.p3d";
		weight=1500;
		itemSize[]={2,2};
		canBeSplit=1;
		varQuantityDestroyOnMin=1;
		varQuantityInit=1;
		varQuantityMin=0;
		varQuantityMax=1;
		varStackMax=1;
	};
	class DZL_Cement: Inventory_Base
	{
		scope=2;
		displayName="#Cement";
		descriptionShort="#Cement";
		model="DZL_Misc\Cement\DZL_Cement.p3d";
		weight=20000;
		itemSize[]={3,4};
	};
};
