class CfgPatches
{
	class Money
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
	class Paper;
	class DZL_Money: Paper
	{
		scope=2;
		displayName="#Counterfeit_money";
		descriptionShort="#Counterfeit_money";
		model="DZL_Misc\Money\DZL_Money.p3d";
		isMeleeWeapon=0;
		weight=2;
		absorbency=1;
		itemSize[]={1,2};
		rotationFlags=16;
		canBeSplit=1;
		varQuantityInit=10;
		varQuantityMin=0;
		varQuantityMax=10;
		varQuantityDestroyOnMin=1;
		varStackMax=10;
	};
};
