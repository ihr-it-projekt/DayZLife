class CfgPatches
{
	class TBStopHungerThirst
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
	class TBStopHungerThirst
	{
	    dir = "TBStopHungerThirst";
        hideName = 0;
		name = "TBStopHungerThirst";
		credits = "TheBuster";
		author = "TheBuster";
		authorID = "76561198196317725";
		version = "0.0.1";
		extra = 0;
		type = "mod";
		
		dependencies[] = {"World"};

		class defs
		{
            class worldScriptModule
            {
                value="";
                files[]=
                {
                    "TBStopHungerThirst/scripts/4_World"
                };
            };
		};
	};
};
