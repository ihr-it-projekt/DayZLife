class CfgPatches
{
	class Cocain
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
			"DZL_Misc\Drugs\Cocain\Cocain_Plant.paa",
			"DZL_Misc\Drugs\Cocain\Cocain_Plant.paa",
			"DZL_Misc\Drugs\Cocain\Cocain_Plant.paa",
			"DZL_Misc\Drugs\Cocain\Cocain_Plant.paa",
			"DZL_Misc\Drugs\Cocain\Cocain_Plant.paa",
			"DZL_Misc\Drugs\Cocain\Cocain_Plant.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"dz\gear\cultivation\data\Cannabis_plant.rvmat"
		};
	};
};
