class CfgPatches
{
	class Cannabis
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
	class Container_Base;
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
	class DZL_Cannabis_Brick: Container_Base
	{	
		scope=2;
		displayName="Cannabis Brick";
		descriptionShort="Model Platzhalter!";
		model="\dz\gear\containers\FirstAidKit.p3d";
		rotationFlags=17;
		lootCategory="Crafted";
		weight=450;
		itemSize[]={3,3};
		absorbency=0.2;
		isMeleeWeapon=1;
		hiddenSelections[]=
		{
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"DZL_Misc\Drugs\Cannabis\Data\Cannabis_Brick.paa"
		};
	};
};
