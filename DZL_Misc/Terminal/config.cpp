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
    class DZL_Terminal: HouseNoDestruct {
        scope = 2;
        model = "\DZL_Misc\Terminal\DZL_Terminal.p3d";
        autocenter = false;
    };
};