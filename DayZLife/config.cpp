class CfgPatches
{
	class P2PTrader
	{
		units[]={};
        weapons[]={};
        requiredVersion=1.0;
        requiredAddons[]={
            "DZ_Data",
            "DZ_Scripts",
            "JM_CF_Scripts"
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
	class P2PTrader
	{
	    dir = "DayZLife";
        picture = "";
        action = "";
        hideName = 0;
		inputs = "DayZLife\inputs.xml";
		name = "DayZLife";
		credits = "TheBuster, Sense";
		creditsJson = "DayZLife/Scripts/Data/Credits.json";
		versionPath = "DayZLife/scripts/Data/Version.hpp";
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
