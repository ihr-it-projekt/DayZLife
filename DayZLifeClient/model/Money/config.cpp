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
    class DZL_Money: Inventory_Base {
        scope = 2;
        displayName = "#Counterfeit_money";
        descriptionShort = "#Counterfeit_money";
        model = "\DayZLifeClient\model\Money\DZL_Money.p3d";
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
        hiddenSelections[] = {
            "camoDZL"
        };
        hiddenSelectionsTextures[] = {
            "DayZLifeClient\model\Terminal\Data\DZL_Terminal_Blue.paa"
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