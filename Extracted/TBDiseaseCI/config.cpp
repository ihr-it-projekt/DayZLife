class CfgPatches
{
	class TBDiseaseCI
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
	class TBDiseaseCI
	{
	    dir = "TBDiseaseCI";
        hideName = 0;
		name = "TBDiseaseCI";
		credits = "TheBuster, Sense";
		author = "TheBuster Sense";
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
                    "TBDiseaseCI/scripts/4_World"
                };
            };
		};
	};
};
