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
	class Inventory_Base;
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
	class DZL_Oil: Inventory_Base
	{
		scope=2;
		displayName="5L Oil";
		descriptionShort="";
		model="\dz\vehicles\parts\oil_bottle.p3d"
		weight=5000;
		itemSize[]={2,3};
	};
};
