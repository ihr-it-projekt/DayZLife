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
class CfgVehicles
{
	class WoodenLog;
	class WoodenPlank;
	class Paper;
	class Stone;
	class SmallStone;
	class Spraycan_Black;
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
	class DZL_Money: Paper
	{
		scope=2;
		displayName="Falschgeld";
		descriptionShort="$STR_CfgVehicles_Paper1";
		model="\dz\gear\consumables\Paper.p3d";
		isMeleeWeapon=1;
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
	class DZL_Sandpaper: Paper
	{
		scope=2;
		displayName="Sandpaper";
		descriptionShort="$STR_CfgVehicles_Paper1";
		model="\dz\gear\consumables\Paper.p3d";
		isMeleeWeapon=1;
		weight=2;
		absorbency=1;
		itemSize[]={1,1};
		rotationFlags=16;
		canBeSplit=1;
		varQuantityInit=1;
		varQuantityMin=0;
		varQuantityMax=1;
		varQuantityDestroyOnMin=1;
		varStackMax=1;
	};
	class DZL_Cement: Paper
	{
		scope=2;
		displayName="Cement";
		descriptionShort="$STR_CfgVehicles_Paper1";
		model="\dz\gear\consumables\Paper.p3d";
		isMeleeWeapon=1;
		weight=2;
		absorbency=1;
		itemSize[]={1,1};
		rotationFlags=16;
		canBeSplit=1;
		varQuantityInit=1;
		varQuantityMin=0;
		varQuantityMax=1;
		varQuantityDestroyOnMin=1;
		varStackMax=1;
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
	class DZL_Jewelry: SmallStone
	{
		scope=2;
		displayName="Jewelry";
		descriptionShort="$STR_CfgVehicles_SmallStone1";
		model="\dz\gear\consumables\SmallStone.p3d";
		animClass="NoFireClass";
		weight=500;
		itemSize[]={1,1};
		rotationFlags=17;
	};
	class DZL_Copper: SmallStone
	{
		scope=2;
		displayName="Copper";
		descriptionShort="$STR_CfgVehicles_SmallStone1";
		model="\dz\gear\consumables\SmallStone.p3d";
		animClass="NoFireClass";
		weight=500;
		itemSize[]={1,1};
		rotationFlags=17;
	};
	class DZL_Iron: SmallStone
	{
		scope=2;
		displayName="Iron";
		descriptionShort="$STR_CfgVehicles_SmallStone1";
		model="\dz\gear\consumables\SmallStone.p3d";
		animClass="NoFireClass";
		weight=500;
		itemSize[]={1,1};
		rotationFlags=17;
	};
	class DZL_Gold: SmallStone
	{
		scope=2;
		displayName="Gold";
		descriptionShort="$STR_CfgVehicles_SmallStone1";
		model="\dz\gear\consumables\SmallStone.p3d";
		animClass="NoFireClass";
		weight=500;
		itemSize[]={1,1};
		rotationFlags=17;
	};
	class DZL_Diamond: SmallStone
	{
		scope=2;
		displayName="Diamond";
		descriptionShort="$STR_CfgVehicles_SmallStone1";
		model="\dz\gear\consumables\SmallStone.p3d";
		animClass="NoFireClass";
		weight=500;
		itemSize[]={1,1};
		rotationFlags=17;
	};
	class DZL_Color: Spraycan_Black
	{
		scope=2;
		displayName="Farbe";
		descriptionShort="$STR_CfgVehicles_Spraycan_Black0";
		color="Black";
		hiddenSelectionsTextures[]=
		{
			"DZ\gear\consumables\data\spraycan_black_co.paa"
		};
	};
	class Pot;
	class HouseNoDestruct;
	class M65Jacket_Black;
	class DZL_Bucket: Pot
	{
		scope=1;
		displayName="Bucket";
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
};
	