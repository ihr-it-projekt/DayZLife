class CfgPatches {
    class DZL_ParkingMeter {
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
    class DZLParkingMeter: HouseNoDestruct {
        model = "\DayZLifeClient\model\ParkingMeter\DZL_ParkingMeter.p3d";
    };
};