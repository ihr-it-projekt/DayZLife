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
	class SmallStone;
	class DZL_Ore_Gold: Stone
	{
		scope=2;
		displayName="#Gold_ore";
		descriptionShort="#Gold_ore_desc";
		model="\DZL_Misc\Ore\Gold\DZL_Ore_Gold.p3d";
		weight=1000;
		itemSize[]={2,2};
	};
	class DZL_Gold: SmallStone
	{
		scope=2;
		displayName="#Gold";
		descriptionShort="#Gold_desc";
		model="\DZL_Misc\Ore\Gold\DZL_Gold_Small.p3d";
		animClass="NoFireClass";
		weight=250;
		itemSize[]={1,1};
		rotationFlags=17;
	};
	class DZL_Ore_Copper: Stone
	{
		scope=2;
		displayName="#Copper_ore";
		descriptionShort="#Copper_ore_desc";
		model="\DZL_Misc\Ore\Copper\DZL_Ore_Copper.p3d";
		weight=2000;
		itemSize[]={2,2};
	};
	class DZL_Copper: SmallStone
	{
		scope=2;
		displayName="#Copper";
		descriptionShort="#Copper_desc";
		model="\DZL_Misc\Ore\Copper\DZL_Copper_Small.p3d";
		animClass="NoFireClass";
		weight=1000;
		itemSize[]={1,1};
		rotationFlags=17;
	};
	class DZL_Ore_Coal: Stone
	{
		scope=2;
		displayName="#Coal";
		descriptionShort="#Coal_desc";
		model="\DZL_Misc\Ore\Coal\DZL_Ore_Coal.p3d";
		weight=500;
		itemSize[]={2,2};
	};
	class DZL_Ore_Iron: Stone
	{
		scope=2;
		displayName="#Iron_ore";
		descriptionShort="#Iron_ore_desc";
		model="\DZL_Misc\Ore\Iron\DZL_Ore_Iron.p3d";
		weight=2000;
		itemSize[]={2,2};
	};
	class DZL_Iron: SmallStone
	{
		scope=2;
		displayName="#Iron";
		descriptionShort="#Iron_desc";
		model="\DZL_Misc\Ore\Iron\DZL_Iron_Small.p3d";
		animClass="NoFireClass";
		weight=1000;
		itemSize[]={1,1};
		rotationFlags=17;
	};
	class DZL_Ore_Diamond: SmallStone
	{
		scope=2;
		displayName="#raw_Diamond";
		descriptionShort="#raw_Diamond_desc";
		model="\DZL_Misc\Ore\Diamond\DZL_Ore_Diamond_Small.p3d";
		weight=500;
		itemSize[]={2,2};
	};
	class DZL_Diamond_Polished: SmallStone
	{
		scope=2;
		displayName="#Diamond_cut";
		descriptionShort="#Diamond_cut_desc";
		model="\DZL_Misc\Ore\Diamond\DZL_Ore_Diamond_Small.p3d";
		weight=100;
		itemSize[]={1,1};
	};
	class DZL_Jewelry: SmallStone
	{
		scope=2;
		displayName="#Jewelry";
		descriptionShort="#Jewelry_desc";
		model="\DZL_Misc\Ore\Copper\DZL_Copper_Small.p3d";
		weight=100;
		itemSize[]={1,1};
	};
};
