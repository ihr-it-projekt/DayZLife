class CfgPatches
{
	class TBLoadOut
	{
		units[]={};
        weapons[]={};
        requiredVersion=1.0;
        requiredAddons[]={
            "DZ_Data",
            "DZ_Scripts",
            "DZ_Structures_Residential",
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
	class TBLoadOut
	{
	    dir = "TBLoadOut";
        hideName = 0;
		name = "TB LoadOut";
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
                    "TBLoadOut/scripts/3_Game"
                };
            };
            class worldScriptModule
            {
                value="";
                files[]=
                {
                    "TBLoadOut/scripts/4_World"
                };
            };
			class missionScriptModule
			{
				value = "";
				files[] = {
				     "TBLoadOut/scripts/5_Mission"
				};
			};
		};
	};
};

class CfgVehicles
{
	class HouseNoDestruct;

    class TBLOLoadoutActionObject: HouseNoDestruct
    {
		scope=2;
        model="\TBLoadOut\Terminal\TBLO_Terminal.p3d";
		hiddenSelections[]=
		{
			"camo"
		};
		hiddenSelectionsTextures[] = 
		{
			"TBLoadOut\Terminal\Data\Terminal.paa"
		};
    };
}

