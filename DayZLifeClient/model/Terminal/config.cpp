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
    class DZLLoadoutActionObject: HouseNoDestruct {};
    class DZL_Terminal_Blue: DZLLoadoutActionObject {
        scope = 1;
        model = "\DZL_Misc\Terminal\DZL_Terminal.p3d";
        hiddenSelections[] = {
            "camoDZL"
        };
        hiddenSelectionsTextures[] = {
            "DayZLifeClient\model\Terminal\Data\DZL_Terminal_Blue.paa"
        };
    };
    class DZL_Terminal_Red: DZLLoadoutActionObject {
        scope = 1;
        model = "\DZL_Misc\Terminal\DZL_Terminal.p3d";
        hiddenSelections[] = {
            "camoDZL"
        };
        hiddenSelectionsTextures[] = {
            "DayZLifeClient\model\Terminal\Data\DZL_Terminal_Red.paa"
        };
    };
    class DZL_Terminal_Yellow: DZLLoadoutActionObject {
        scope = 1;
        model = "\DZL_Misc\Terminal\DZL_Terminal.p3d";
        hiddenSelections[] = {
            "camoDZL"
        };
        hiddenSelectionsTextures[] = {
            "DayZLifeClient\model\Terminal\Data\DZL_Terminal_Yellow.paa"
        };
    };
    class DZL_Terminal: DZL_Terminal_Yellow {};
};