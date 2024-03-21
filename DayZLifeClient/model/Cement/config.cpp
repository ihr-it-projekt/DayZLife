class CfgPatches {
    class DZL_Cement {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {
            "DZ_Data"
        };
    };
};

class CfgVehicles {
    class Inventory_Base;
    class DZL_Cement: Inventory_Base {
        scope = 2;
        displayName = "#Cement";
        descriptionShort = "#Cement";
        model = "\DayZLifeClient\model\Cement\DZL_Cement.p3d";
        weight = 20000;
        itemSize[] = {2, 2};
        hiddenSelections[] = {
            "camoDZL"
        };
        hiddenSelectionsTextures[] = {
            "DayZLifeClient\model\Cement\Data\DZL_Cement.paa"
        };
        class DamageSystem {
            class GlobalHealth {
                class Health {
                    hitpoints = 200;
                    healthLevels[] = {
                        {
                            1,

                            {
                                "DZ\gear\consumables\data\stone.rvmat"
                            }
                        },
                        {
                            0.7,

                            {
                                "DZ\gear\consumables\data\stone.rvmat"
                            }
                        },
                        {
                            0.5,
                            {
                                "DZ\gear\consumables\data\stone_damage.rvmat"
                            }
                        },
                        {
                            0.3,
                            {
                                "DZ\gear\consumables\data\stone_damage.rvmat"
                            }
                        },
                        {
                            0,
                            {
                                "DZ\gear\consumables\data\stone_destruct.rvmat"
                            }
                        }
                    };
                };
            };
        };
    };
};