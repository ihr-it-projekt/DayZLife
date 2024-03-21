class CfgPatches {
    class DZL_ATM {
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
    class DZLBankAutomate_Blue: HouseNoDestruct {
        scope = 1;
        model = "DayZLifeClient\model\ATM\DZL_ATM.p3d";
        hiddenSelections[] = {
            "camoDZL"
        };
        hiddenSelectionsTextures[] = {
            "DayZLifeClient\model\ATM\Data\ATM_Blue.paa"
        };
    };
    class DZLBankAutomate_Red: HouseNoDestruct {
        scope = 1;
        model = "DayZLifeClient\model\ATM\DZL_ATM.p3d";
        hiddenSelections[] = {
            "camoDZL"
        };
        hiddenSelectionsTextures[] = {
            "DayZLifeClient\model\ATM\Data\ATM_Red.paa"
        };
    };
    class DZLBankAutomate_Yellow: HouseNoDestruct {
        scope = 1;
        model = "DayZLifeClient\model\ATM\DZL_ATM.p3d";
        hiddenSelections[] = {
            "camoDZL"
        };
        hiddenSelectionsTextures[] = {
            "DayZLifeClient\model\ATM\Data\ATM_Yellow.paa"
        };
    };
};