class CfgPatches
{
	class WeaponsBlanks
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
	class DZL_RevolverBlank: Inventory_Base
	{
		scope=2;
		displayName="Revolver Rohling";
		descriptionShort="";
		model="DZL_Misc\WeaponsBlanks\RevolverBlank.p3d";
		weight=1000;
		itemSize[]={3,2};
	};
	class DZL_PistolBlank: Inventory_Base
	{
		scope=2;
		displayName="Pistol Rohling";
		descriptionShort="";
		model="DZL_Misc\WeaponsBlanks\PistolBlank.p3d";
		weight=1000;
		itemSize[]={3,2};
	};
};
