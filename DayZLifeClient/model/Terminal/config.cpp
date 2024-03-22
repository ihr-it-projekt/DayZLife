class CfgPatches {
    class DZL_Terminal {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {
            "DZ_Data"
        };
    };
};

class CfgVehicles {
    class HouseNoDestruct;
    class DZLBaseActionObject: HouseNoDestruct {};
    class DZLLoadoutActionObject: DZLBaseActionObject {
        scope = 1;
        model = "\DayZLifeClient\model\Terminal\DZL_Terminal.p3d";
        hiddenSelections[] = {
            "camoDZL"
        };
        hiddenSelectionsTextures[] = {
            "DayZLifeClient\model\Terminal\Data\DZL_Terminal_Yellow.paa"
        };
    };
    class DZLTuningActionObject: DZLBaseActionObject {
        scope = 1;
        model = "\DayZLifeClient\model\Terminal\DZL_Terminal.p3d";
        hiddenSelections[] = {
            "camoDZL"
        };
        hiddenSelectionsTextures[] = {
            "DayZLifeClient\model\Terminal\Data\DZL_Terminal_Red.paa"
        };
    };
};