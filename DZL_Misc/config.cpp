class CfgPatches
{
	class DZL_Misc
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

class CfgMods
{
	class DZL_Misc
	{
		dir = "DayZLifeMisc";
        hideName = 0;
		name = "DayZLife";
		credits = "TheBuster, Sense";
		author = "TheBuster Sense";
		authorID = "76561198196317725";
		version = "0.0.1";
		extra = 0;
		type = "mod";
		dependencies[]=
		{
			"World"
		};
		class defs
		{
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"DZL_Misc/scripts/4_World"
				};
			};
		};
	};
};
class CfgVehicles
{
	class WoodenLog;
	class WoodenPlank;
	class Paper;
	class Stone;
	class SmallStone;
	class Spraycan_Black;
	class Container_Base;
	class Pot;
	class HouseNoDestruct;
	class M65Jacket_Black;
	class DZL_WoodenLog: WoodenLog
	{
		scope=2;
		displayName="$STR_CfgVehicles_WoodenLog0";
		descriptionShort="$STR_CfgVehicles_WoodenLog1";
		model="\dz\gear\camping\wooden_log.p3d";
		weight=20000;
		itemSize[]={2,8};
		varQuantityDestroyOnMin=1;
		itemBehaviour=0;
		canBeSplit=1;
		varQuantityInit=1;
		varQuantityMin=0;
		varQuantityMax=1;
		varStackMax=1;
	};
	class DZL_WoodenPlank: WoodenPlank
	{
		scope=2;
		displayName="$STR_CfgVehicles_WoodenPlank0";
		descriptionShort="$STR_CfgVehicles_WoodenPlank1";
		model="\dz\gear\consumables\single_plank.p3d";
		weight=1500;
		itemSize[]={2,8};
		canBeSplit=1;
		varQuantityInit=5;
		varQuantityMin=0;
		varQuantityMax=5;
		varQuantityDestroyOnMin=1;
		varStackMax=5;
	};
	class DZL_Paper: Paper
	{
		scope=2;
		displayName="$STR_CfgVehicles_Paper0";
		descriptionShort="$STR_CfgVehicles_Paper1";
		model="\dz\gear\consumables\Paper.p3d";
		isMeleeWeapon=1;
		weight=2;
		absorbency=1;
		itemSize[]={1,1};
		rotationFlags=16;
		canBeSplit=1;
		varQuantityInit=10;
		varQuantityMin=0;
		varQuantityMax=10;
		varQuantityDestroyOnMin=1;
		varStackMax=10;
	};
	class DZL_Sandpaper: Paper
	{
		scope=2;
		displayName="#Sandpaper";
		descriptionShort="";
		model="\dz\gear\consumables\Paper.p3d";
		rotationFlags=17;
		lootCategory="Crafted";
		weight=450;
		itemSize[]={3,3};
		absorbency=0.2;
		canBeSplit=1;
		varQuantityInit=1;
		varQuantityMin=0;
		varQuantityMax=1;
		varQuantityDestroyOnMin=1;
		varStackMax=1;
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"DZL_Misc\Data\Sandpaper.paa"
		};
	};
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
	class DZL_Color: Spraycan_Black
	{
		scope=2;
		displayName="#Color";
		descriptionShort="$STR_CfgVehicles_Spraycan_Black0";
		color="Black";
		hiddenSelectionsTextures[]=
		{
			"DZ\gear\consumables\data\spraycan_black_co.paa"
		};
	};
	class DZL_Crate_Base: Container_Base
	{
		scope=2;
		autocenter = false;
		canBeDigged=0;
	};
	class DZL_Wooden_Crate_1: DZL_Crate_Base
	{
		displayName="#1_wood_crate";
		descriptionShort=".";
		model="\DZ\structures_bliss\residential\Misc\Misc_WoodenCrate.p3d";
		class Cargo
		{
			itemsCargoSize[]={10,5};
			openable=0;
			allowOwnedCargoManipulation=1;
		};
	};
	class DZL_Wooden_Crate_3: DZL_Crate_Base
	{
		displayName="#3_wood_crate";
		descriptionShort=".";
		model="\DZ\structures_bliss\residential\Misc\Misc_WoodenCrate_3x.p3d";
		class Cargo
		{
			itemsCargoSize[]={10,15};
			openable=0;
			allowOwnedCargoManipulation=1;
		};
	};
	class DZL_Wooden_Crate_5: DZL_Crate_Base
	{
		displayName="#5_wood_crate";
		descriptionShort=".";
		model="\DZ\structures_bliss\residential\Misc\Misc_WoodenCrate_5x.p3d";
		class Cargo
		{
			itemsCargoSize[]={10,25};
			openable=0;
			allowOwnedCargoManipulation=1;
		};
	};
	class DZL_Bucket: Pot
	{
		scope=1;
		displayName="#Bucket";
		descriptionShort="Bucket";
		model="\DZ\structures\furniture\decoration\bucket\bucket.p3d";
		weight=1000;
		itemSize[]={2,3};
		itemsCargoSize[]={0,0};
		canBeDigged=0;
	};
	class DZL_sign_relic_tree: HouseNoDestruct
	{
		scope=1;
		model="\DZ\structures\signs\misc\sign_relic_tree.p3d";
	};
	class DZL_sign_parking: HouseNoDestruct
	{
		scope=1;
		model="\DZ\structures\signs\traffic\sign_parking.p3d";
	};
	class DZL_M65Jacket_Black: M65Jacket_Black
	{
		itemsCargoSize[]={10,10};
	};
	// Model Platzhalter!
	class DZL_Jewelry: SmallStone
	{
		scope=2;
		displayName="#Jewelry";
		descriptionShort="Model Platzhalter!";
		model="\dz\gear\consumables\SmallStone.p3d";
		animClass="NoFireClass";
		weight=500;
		itemSize[]={1,1};
		rotationFlags=17;
	};
	// Model Platzhalter Ende!
};
