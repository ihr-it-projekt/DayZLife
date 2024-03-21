class CfgPatches {
    class DZL_Ore {
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
    class DZLStoneOre_ColorBase: Inventory_Base {
        model = "\dz\gear\consumables\Stone.p3d";
        animClass = "NoFireClass";
        weight = 1500;
        itemSize[] = {2, 2};
        canBeSplit = 1;
        varQuantityDestroyOnMin = 1;
        varQuantityInit = 1;
        varQuantityMin = 0;
        varQuantityMax = 32;
        varStackMax = 1;
        isMeleeWeapon = 1;
        hiddenSelections[] = {
            "zbytek"
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
                            0.69999999,

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
                            0.30000001,
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
    class DZLOre_ColorBase: Inventory_Base {
        model = "\dz\gear\consumables\SmallStone.p3d";
        animClass = "NoFireClass";
        weight = 500;
        itemSize[] = {1, 1};
        rotationFlags = 17;
        hiddenSelections[] = {
            "zbytek"
        };
        class DamageSystem {
            class GlobalHealth {
                class Health {
                    hitpoints = 100;
                    healthLevels[] = {

                        {
                            1,

                            {
                                "DZ\gear\consumables\data\stone.rvmat"
                            }
                        },

                        {
                            0.69999999,

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
                            0.30000001,

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
    class DZL_Stone: DZLStoneOre_ColorBase {
        scope = 2;
        displayName = "$STR_CfgVehicles_Stone0";
        descriptionShort = "$STR_CfgVehicles_Stone1";
    };
    class DZL_Gold: DZLStoneOre_ColorBase {
        scope = 2;
        displayName = "#Gold";
        descriptionShort = "#Gold_desc";
        hiddenSelectionsTextures[] = {
            "DayZLifeClient\model\Ore\Gold\Gold_Stone.paa"
        };
    };
    class DZL_Gold: DZLOre_ColorBase {
        scope = 2;
        displayName = "#Gold";
        descriptionShort = "#Gold_desc";
        hiddenSelectionsTextures[] = {
            "DayZLifeClient\model\Ore\Gold\Gold_Stone_Small.paa"
        };
    };
    class DZL_Copper: DZLStoneOre_ColorBase {
        scope = 2;
        displayName = "#Copper_ore";
        descriptionShort = "#Copper_ore_desc";
        hiddenSelectionsTextures[] = {
            "DayZLifeClient\model\Ore\Copper\Copper_Stone.paa"
        };
    };
    class DZL_Copper: DZLOre_ColorBase {
        scope = 2;
        displayName = "#Copper";
        descriptionShort = "#Copper_desc";
        hiddenSelectionsTextures[] = {
            "DayZLifeClient\model\Ore\Copper\Copper.paa"
        };
    };
    class DZL_Coal: DZLStoneOre_ColorBase {
        scope = 2;
        displayName = "#Coal";
        descriptionShort = "#Coal_desc";
        hiddenSelectionsTextures[] = {
            "DayZLifeClient\model\Ore\Coal\coal_stone.paa"
        };
    };
    class DZL_Ore_Iron: DZLStoneOre_ColorBase {
        scope = 2;
        displayName = "#Iron_ore";
        descriptionShort = "#Iron_ore_desc";
        hiddenSelectionsTextures[] = {
            "DayZLifeClient\model\Ore\Iron\iron_stone.paa"
        };
    };
    class DZL_Iron: DZLOre_ColorBase {
        scope = 2;
        displayName = "#Iron";
        descriptionShort = "#Iron_desc";
        hiddenSelectionsTextures[] = {
            "DayZLifeClient\model\Ore\Iron\Iron.paa"
        };
    };
    class DZL_Ore_Diamond: DZLOre_ColorBase {
        scope = 2;
        displayName = "#raw_Diamond";
        descriptionShort = "#raw_Diamond_desc";
        hiddenSelectionsTextures[] = {
            "DayZLifeClient\model\Ore\Diamond\Diamond_Stone.paa"
        };
    };
    class DZL_Diamond_Polished: DZLOre_ColorBase {
        scope = 2;
        displayName = "#Diamond_cut";
        descriptionShort = "#Diamond_cut_desc";
        hiddenSelectionsTextures[] = {
            "DayZLifeClient\model\Ore\Diamond\Diamond_Stone.paa"
        };
    };
};