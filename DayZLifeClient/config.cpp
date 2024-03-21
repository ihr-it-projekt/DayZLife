class CfgPatches {
    class DayZLifeClient {
        units[] = {};
        weapons[] = {};
        requiredVersion = 1.0;
        requiredAddons[] = {
            "DZ_Data",
            "DZ_Scripts",
            "DZ_Structures_Residential"
        };
    };
};

class CfgAddons {
    class PreloadBanks {};
    class PreloadAddons {
        class dayz {
            list[] = {
                "TBRealEstateClient",
                "TBRevivePlayerClient"
            };
        };
    };
};

class CfgMods {
    class DayZLifeClient {
        dir = "DayZLifeClient";
        hideName = 0;
        name = "DayZLifeClient";
        credits = "TheBuster, Sense";
        author = "TheBuster Sense";
        authorID = "76561198196317725";
        version = "0.0.1";
        extra = 0;
        type = "mod";

        dependencies[] = {"Game", "World", "Mission"};

        class defs {
            class gameScriptModule {
                value = "";
                files[] = {
                    "DayZLifeClient/scripts/3_Game"
                };
            };
            class worldScriptModule {
                value = "";
                files[] = {
                    "DayZLifeClient/scripts/4_World"
                };
            };
            class missionScriptModule {
                value = "";
                files[] = {
                    "DayZLifeClient/scripts/5_Mission"
                };
            };
        };
    };
};

class cfgSoundSets {
    class DZL_Message_SoundSet {
        soundShaders[] = {
            "DZL_Message_SoundShader"
        };
        sound3DProcessingType = "character3DProcessingType";
        volumeCurve = "characterAttenuationCurve";
        spatial = 1;
        doppler = 0;
        loop = 0;
    };
};
class cfgSoundShaders {
    class DZL_Message_SoundShader {
        samples[] = {
            {
                "DayZLifeClient\Data\sound\message",
                1
            }
        };
        volume = 1;
        range = 10;
        limitation = 0;
    };
};