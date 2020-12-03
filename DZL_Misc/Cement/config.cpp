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
