class CfgPatches
{
	class Plants
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
	class HouseNoDestruct;
	class Inventory_Base;
	class DZL_Coca_Plant: HouseNoDestruct
	{
		scope=1;
		model="DZ\gear\cultivation\Cannabis_plant.p3d";
		physLayer="item_small";
		carveNavmesh=0;
		hiddenSelections[]=
		{
			"plantstage_03",
			"plantstage_02",
			"plantstage_04",
			"plantstage_05",
			"plantstage_01",
			"infestedparts"
		};
		hiddenSelectionsTextures[]=
		{
			"DZL_Misc\Plants\Data\coca_plant_co.paa",
			"DZL_Misc\Plants\Data\coca_plant_co.paa",
			"DZL_Misc\Plants\Data\coca_plant_co.paa",
			"DZL_Misc\Plants\Data\coca_plant_co.paa",
			"DZL_Misc\Plants\Data\coca_plant_co.paa",
			"DZL_Misc\Plants\Data\coca_plant_co.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"dz\gear\cultivation\data\Cannabis_plant.rvmat"
		};
	};
	class DZL_Cannabis_Plant: HouseNoDestruct
	{
		scope=1;
		model="DZ\gear\cultivation\Cannabis_plant.p3d";
		physLayer="item_small";
		carveNavmesh=0;
	};
	class DZL_Cannabis: Inventory_Base
	{
		scope=2;
		displayName="Cannabis";
		descriptionShort="$STR_Cannabis1";
		model="\dz\gear\food\cannabis_seedman.p3d";
		rotationFlags=34;
		weight=15;
		itemSize[]={1,1};
	};
};
