class CfgPatches {
    class Money {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {
            "DZ_Data"
        };
    };
};
class CfgVehicles {
    class Paper;
    class Inventory_Base;
    class DZL_Paper: Inventory_Base {
        scope = 2;
        displayName = "$STR_CfgVehicles_Paper0";
        descriptionShort = "$STR_CfgVehicles_Paper1";
        model = "\dz\gear\consumables\Paper.p3d";
        isMeleeWeapon = 0;
        weight = 2;
        absorbency = 1;
        itemSize[] = {1, 1};
        rotationFlags = 16;
    };
    class DZL_Color: Inventory_Base {
        scope = 2;
        displayName = "#Color";
        descriptionShort = "$STR_CfgVehicles_Spraycan_Black0";
        model = "\dz\gear\consumables\spraycan.p3d";
        isMeleeWeapon = 0;
        weight = 2;
        absorbency = 1;
        itemSize[] = {1, 2};
        rotationFlags = 16;
    };
    class DZL_Money: Paper {
        scope = 2;
        displayName = "#Counterfeit_money";
        descriptionShort = "#Counterfeit_money";
        model = "DZL_Misc\Money\DZL_Money.p3d";
        isMeleeWeapon = 0;
        weight = 2;
        absorbency = 1;
        itemSize[] = {1, 2};
        rotationFlags = 16;
        canBeSplit = 1;
        varQuantityInit = 1;
        varQuantityMin = 0;
        varQuantityMax = 1;
        varQuantityDestroyOnMin = 1;
        varStackMax = 1;
    };
};
