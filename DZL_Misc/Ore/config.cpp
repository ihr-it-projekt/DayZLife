class CfgPatches
{
	class Ore
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
	class Stone;
	class DZL_Ore_Gold: Stone
	{
		scope=2;
		displayName="Golderz";
		descriptionShort="Golderz";
		model="\DZL_Misc\Ore\Gold\DZL_Ore_Gold.p3d";
		weight=4000;
		itemSize[]={2,2};
	};
	class DZL_Ore_Copper: Stone
	{
		scope=2;
		displayName="Copper";
		descriptionShort="Copper";
		model="\DZL_Misc\Ore\Copper\DZL_Ore_Copper.p3d";
		weight=4000;
		itemSize[]={2,2};
	};
	class DZL_Ore_Coal: Stone
	{
		scope=2;
		displayName="Coal";
		descriptionShort="Coal";
		model="\DZL_Misc\Ore\Coal\DZL_Ore_Coal.p3d";
		weight=4000;
		itemSize[]={2,2};
	};
	class DZL_Ore_Iron: Stone
	{
		scope=2;
		displayName="Iron";
		descriptionShort="Iron";
		model="\DZL_Misc\Ore\Iron\DZL_Ore_Iron.p3d";
		weight=4000;
		itemSize[]={2,2};
	};
	class DZL_Ore_Diamond: Stone
	{
		scope=2;
		displayName="Diamond";
		descriptionShort="Diamond";
		model="\DZL_Misc\Ore\Diamond\DZL_Ore_Diamond.p3d";
		weight=4000;
		itemSize[]={2,2};
	};
};
