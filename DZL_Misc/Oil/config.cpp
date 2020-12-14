class CfgPatches
{
	class Oil
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
	class Barrel_ColorBase;
	class DZL_Oil_Barrel: Barrel_ColorBase
	{
		displayName="Fass mit Ölschlamm";
		descriptionShort="Kann zu Öl oder Plastik weiter verarbeitet werden";
		canBeDigged=0;
		itemSize[]={3,5};
		carveNavmesh=1;
		quantityBar=1;
		scope=2;
		hiddenSelectionsTextures[]=
		{
			"\DZL_Misc\Oil\Data\RustyBarrel.paa"
		};
		class Cargo
		{
			itemsCargoSize[]={0,0};
			openable=0;
			allowOwnedCargoManipulation=1;
		};
	};
};
