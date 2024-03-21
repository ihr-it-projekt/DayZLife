class CfgPatches {
    class DZL_Other {
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
    class Pot;
    class WoodenLog;
    class WoodenPlank;
    class Paper;
    class DZLTraderActionObject: HouseNoDestruct {
        model = "\DZ\structures\furniture\generalstore\pultskasou.p3d";
    };
    class DZLShopActionObject: HouseNoDestruct {
        model = "\DZ\structures\furniture\generalstore\cashier.p3d";
    };
    class DZLLicenseActionObject: HouseNoDestruct {
        model = "\DZ\structures\furniture\generalstore\pultskasou.p3d";
    };
    class DZLLicenceCraftingActionObject: HouseNoDestruct {
        model = "\DZ\structures\furniture\various\workbench_dz.p3d";
    };
    class DZL_sign_relic_tree: HouseNoDestruct {
        scope = 1;
        model = "\DZ\structures\signs\misc\sign_relic_tree.p3d";
    };
    class DZL_sign_parking: HouseNoDestruct {
        scope = 1;
        model = "\DZ\structures\signs\traffic\sign_parking.p3d";
    };
    class DZL_WoodenLog: WoodenLog {
        scope = 2;
        displayName = "$STR_CfgVehicles_WoodenLog0";
        descriptionShort = "$STR_CfgVehicles_WoodenLog1";
        model = "\dz\gear\camping\wooden_log.p3d";
        weight = 20000;
        itemSize[] = {2, 2};
        varQuantityDestroyOnMin = 1;
        itemBehaviour = 0;
        canBeSplit = 1;
        varQuantityInit = 1;
        varQuantityMin = 0;
        varQuantityMax = 1;
        varStackMax = 1;
    };
    class DZL_WoodenPlank: WoodenPlank {
        scope = 2;
        displayName = "$STR_CfgVehicles_WoodenPlank0";
        descriptionShort = "$STR_CfgVehicles_WoodenPlank1";
        model = "\dz\gear\consumables\single_plank.p3d";
        weight = 1500;
        itemSize[] = {2, 2};
        canBeSplit = 1;
        varQuantityInit = 1;
        varQuantityMin = 0;
        varQuantityMax = 1;
        varStackMax = 1;
    };
    class DZL_Sandpaper: Paper {
        scope = 2;
        displayName = "#Sandpaper";
        descriptionShort = "#Sandpaper";
        model = "\dz\gear\consumables\Paper.p3d";
        rotationFlags = 17;
        lootCategory = "Crafted";
        weight = 450;
        itemSize[] = {1, 1};
        absorbency = 0.2;
        canBeSplit = 1;
        varQuantityInit = 1;
        varQuantityMin = 0;
        varQuantityMax = 1;
        varQuantityDestroyOnMin = 1;
        varStackMax = 1;
        hiddenSelections[] = {
            "zbytek"
        };
        hiddenSelectionsTextures[] = {
            "DayZLifeClient\model\Other\Data\Sandpaper.paa"
        };
    };
    class DZL_Bucket: Pot {
        scope = 1;
        displayName = "#Bucket";
        descriptionShort = "#Bucket";
        model = "\DZ\structures\furniture\decoration\bucket\bucket.p3d";
        weight = 1000;
        itemSize[] = {2, 2};
        itemsCargoSize[] = {0, 0};
        canBeDigged = 0;
    };
};