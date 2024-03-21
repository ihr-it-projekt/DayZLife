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
};