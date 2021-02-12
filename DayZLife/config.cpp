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
    class Container_Base;
    class DZLDatabase: Container_Base
	{
		scope=2;
		autocenter = false;
		canBeDigged=0;
		displayName="The Database";
        descriptionShort="";
        model="\DZ\structures_bliss\residential\Misc\Misc_WoodenCrate_5x.p3d";
        class Cargo
        {
            itemsCargoSize[]={0,0};
            openable=0;
            allowOwnedCargoManipulation=0;
        };
	};

}

class cfgSoundSets
{
	class DZL_Message_SoundSet
	{
		soundShaders[]=
		{
			"DZL_Message_SoundShader"
		};
		sound3DProcessingType="character3DProcessingType";
		volumeCurve="characterAttenuationCurve";
		spatial=1;
		doppler=0;
		loop=0;
	};
};
class cfgSoundShaders
{
	class DZL_Message_SoundShader
	{
		samples[]=
		{
			{
				"DayZCasinoV2\data\sound\message",
				1
			}
		};
		volume=1;
		range=10;
		limitation=0;
	};
};
