class CfgPatches {
    class DayZLifeClient {
        units[] = {};
        weapons[] = {};
        requiredVersion = 1.0;
        requiredAddons[] = {
            "DZ_Data",
            "DZ_Scripts",
            "DZ_Structures_Residential"
        };
    };
};

class CfgAddons {
    class PreloadBanks {};
    class PreloadAddons {
        class dayz {
            list[] = {
                "TBRealEstateClient",
                "TBRevivePlayerClient"
            };
        };
    };
};

class CfgMods {
    class DayZLifeClient {
        dir = "DayZLifeClient";
        hideName = 0;
        name = "DayZLifeClient";
        credits = "TheBuster, Sense";
        author = "TheBuster Sense";
        authorID = "76561198196317725";
        version = "0.0.1";
        extra = 0;
        type = "mod";

        dependencies[] = {"Game", "World", "Mission"};

        class defs {
            class gameScriptModule {
                value = "";
                files[] = {
                    "DayZLifeClient/scripts/3_Game"
                };
            };
            class worldScriptModule {
                value = "";
                files[] = {
                    "DayZLifeClient/scripts/4_World"
                };
            };
            class missionScriptModule {
                value = "";
                files[] = {
                    "DayZLifeClient/scripts/5_Mission"
                };
            };
        };
    };
};

class cfgSoundSets {
    class DZL_Message_SoundSet {
        soundShaders[] = {
            "DZL_Message_SoundShader"
        };
        sound3DProcessingType = "character3DProcessingType";
        volumeCurve = "characterAttenuationCurve";
        spatial = 1;
        doppler = 0;
        loop = 0;
    };
};
class cfgSoundShaders {
    class DZL_Message_SoundShader {
        samples[] = {
            {
                "DayZLifeClient\Data\sound\message",
                1
            }
        };
        volume = 1;
        range = 10;
        limitation = 0;
    };
};
class CfgVehicles {
    class HouseNoDestruct;
    class Inventory_Base;
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