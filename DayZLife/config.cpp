class CfgPatches
{
	class DayZLife
	{
		units[]={};
        weapons[]={};
        requiredVersion=1.0;
        requiredAddons[]={
            "DZ_Data",
            "DZ_Scripts",
            "DZ_Structures_Residential"
        };
	};
};

class CfgAddons
{
	class PreloadBanks {};
	class PreloadAddons
	{
		class dayz
		{
			list[] ={};
		};
	};
};

class CfgMods
{
	class DayZLife
	{
	    dir = "DayZLife";
        hideName = 0;
		name = "DayZLife";
		credits = "TheBuster, Sense";
		author = "TheBuster Sense";
		authorID = "76561198196317725";
		version = "0.0.1";
		extra = 0;
		type = "mod";
		
		dependencies[] = {"Game", "World", "Mission"};

		class defs
		{
            class gameScriptModule
            {
                value="";
                files[]=
                {
                    "DayZLife/scripts/3_Game"
                };
            };
            class worldScriptModule
            {
                value="";
                files[]=
                {
                    "DayZLife/scripts/4_World"
                };
            };
			class missionScriptModule
			{
				value = "";
				files[] = {
				     "DayZLife/scripts/5_Mission"
				};
			};
		};
	};
};

class CfgVehicles
{
	class Stone;
	class Container_Base;
	class DZL_Crate_Base: Container_Base
	{
		scope=2;
		autocenter = false;
		canBeDigged=0;
	};
	class DZL_Wooden_Crate_1: DZL_Crate_Base
	{
		displayName="1er Holzkiste";
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
		displayName="3er Holzkisten";
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
		displayName="5er Holzkisten";
		descriptionShort=".";
		model="\DZ\structures_bliss\residential\Misc\Misc_WoodenCrate_5x.p3d";
		class Cargo
		{
			itemsCargoSize[]={10,25};
			openable=0;
			allowOwnedCargoManipulation=1;
		};
	};
	//Item Platzhalter
	class DLZ_Ore_Gold: Stone
	{
		scope=2;
		displayName="Golderz";
		descriptionShort="Platzhalter";
		weight=4000;
		itemSize[]={2,2};
	};
	class DLZ_Ore_Copper: Stone
	{
		scope=2;
		displayName="Copper";
		descriptionShort="Platzhalter";
		weight=4000;
		itemSize[]={2,2};
	};
	class DLZ_Ore_Iron: Stone
	{
		scope=2;
		displayName="Iron";
		descriptionShort="Platzhalter";
		weight=4000;
		itemSize[]={2,2};
	};
	class DLZ_Ore_Silver: Stone
	{
		scope=2;
		displayName="Silver";
		descriptionShort="Platzhalter";
		weight=4000;
		itemSize[]={2,2};
	};
	class DLZ_Ore_Diamond: Stone
	{
		scope=2;
		displayName="Diamond";
		descriptionShort="Platzhalter";
		weight=4000;
		itemSize[]={2,2};
	};
	class DLZ_Ore_WoodenLog: Stone
	{
		scope=2;
		displayName="WoodenLog";
		descriptionShort="Platzhalter";
		weight=4000;
		itemSize[]={2,2};
	};
	class DLZ_Ore_Scrap_1: Stone
	{
		scope=2;
		displayName="Scrap";
		descriptionShort="Platzhalter";
		weight=4000;
		itemSize[]={2,2};
	};
	class DLZ_Ore_Scrap_2: Stone
	{
		scope=2;
		displayName="Scrap";
		descriptionShort="Platzhalter";
		weight=4000;
		itemSize[]={2,2};
	};
	class DLZ_Ore_Scrap_3: Stone
	{
		scope=2;
		displayName="Scrap";
		descriptionShort="Platzhalter";
		weight=4000;
		itemSize[]={2,2};
	};
	class DLZ_Ore_Scrap_4: Stone
	{
		scope=2;
		displayName="Scrap";
		descriptionShort="Platzhalter";
		weight=4000;
		itemSize[]={2,2};
	};
	class DLZ_Ore_Scrap_5: Stone
	{
		scope=2;
		displayName="Scrap";
		descriptionShort="Platzhalter";
		weight=4000;
		itemSize[]={2,2};
	};
	class DLZ_Ore_Scrap_6: Stone
	{
		scope=2;
		displayName="Scrap";
		descriptionShort="Platzhalter";
		weight=4000;
		itemSize[]={2,2};
	};
	class DLZ_Ore_Scrap_7: Stone
	{
		scope=2;
		displayName="Scrap";
		descriptionShort="Platzhalter";
		weight=4000;
		itemSize[]={2,2};
	};
	class DLZ_Ore_Scrap_8: Stone
	{
		scope=2;
		displayName="Scrap";
		descriptionShort="Platzhalter";
		weight=4000;
		itemSize[]={2,2};
	};
	class DLZ_Ore_Scrap_9: Stone
	{
		scope=2;
		displayName="Scrap";
		descriptionShort="Platzhalter";
		weight=4000;
		itemSize[]={2,2};
	};
	class DLZ_Ore_Scrap_10: Stone
	{
		scope=2;
		displayName="Scrap";
		descriptionShort="Platzhalter";
		weight=4000;
		itemSize[]={2,2};
	};
};
