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
	class HouseNoDestruct;
	class HouseInfoPoint: HouseNoDestruct
	{
		scope = 1;
		model = "\DZ\structures\residential\misc\misc_noticeboard1.p3d";
	};
};
