class CfgPatches {
    class DayZLifeServer {
        units[] = {};
        weapons[] = {};
        requiredVersion = 1.0;
        requiredAddons[] = {
            "DZ_Data",
            "DZ_Scripts",
            "DayZLifeClient"
        };
    };
};

class CfgAddons {
    class PreloadBanks {};
    class PreloadAddons {
        class dayz {
            list[] = {
                "DayZLifeClient"
            };
        };
    };
};

class CfgMods {
    class DayZLifeServer {
        dir = "DayZLifeServer";
        picture = "";
        action = "";
        hideName = 0;
        inputs = "DayZLifeServer/inputs.xml";
        name = "DayZLifeServer";
        credits = "TheBuster, Sense";
        creditsJson = "DayZLifeServer/Scripts/Data/Credits.json";
        versionPath = "DayZLifeServer/scripts/Data/Version.hpp";
        author = "TheBuster Sense";
        authorID = "76561198196317725";
        version = "1.1.1";
        extra = 0;
        type = "mod";

        dependencies[] = {"Game", "World", "Mission", "JM_CF_Scripts", "DayZLifeClient"};

        class defs {
            class gameScriptModule {
                value = "";
                files[] = {
                    "DayZLifeServer/scripts/3_Game"
                };
            };
            class worldScriptModule {
                value = "";
                files[] = {
                    "DayZLifeServer/scripts/4_World"
                };
            };
            class missionScriptModule {
                value = "";
                files[] = {
                    "DayZLifeServer/scripts/5_Mission"
                };
            };
        };
    };
};
