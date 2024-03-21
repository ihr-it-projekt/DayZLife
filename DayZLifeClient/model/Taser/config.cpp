class CfgPatches {
    class DZ_Pistols_FNX45 {
        units[] = {};
        weapons[] = {
            "Taser"
        };
        requiredVersion = 0.1;
        requiredAddons[] = {
            "DZ_Data",
            "DZ_Pistols",
            "DZ_Sounds_Weapons",
            "DZ_Nonlethal_Shockpistol",
            "DZ_Weapons_Magazines",
            "DZ_Weapons_Ammunition"
        };
        magazines[] = {
            "Mag_taser",
            "Ammo_taser"
        };
        ammo[] = {
            "Bullet_Taser",
            "Bullet_Taser",
            "Bullet_Taser"
        };
    };
};
class Mode_Safe;
class Mode_SemiAuto;
class Mode_Burst;
class Mode_FullAuto;
class OpticsInfoPistol;
class cfgWeapons {
    class FNX45;
    class Taser_Base: FNX45 {
        scope = 0;
        weight = 550;
        PPDOFProperties[] = {};
        chamberSize = 1;
        class NoiseShoot {
            strength = 5;
            type = "shot";
        };
        class OpticsInfo: OpticsInfoPistol {
            memoryPointCamera = "eye";
            discreteDistance[] = {25};
            discreteDistanceInitIndex = 0;
            modelOptics = "-";
            distanceZoomMin = 100;
            distanceZoomMax = 100;
        };
        magazines[] = {
            "Mag_Taser"
        };
        chamberableFrom[] = {
            "Ammo_Taser"
        };
        drySound[] = {
            "dz\sounds\weapons\nonlethal\shockpistol\Shockpistol_dry",
            0.5,
            1,
            20
        };
        reloadMagazineSound[] = {
            "dz\sounds\weapons\firearms\FNX45\FNX45_reload",
            0.80000001,
            1,
            20
        };
        modes[] = {
            "SemiAuto"
        };
        class SemiAuto: Mode_SemiAuto {
            soundSetShot[] = {
                "Shockpistol_Shot_SoundSet",
                "Shockpistol_Tail_SoundSet",
                "Shockpistol_InteriorTail_SoundSet"
            };
            soundSetShotExt[] = {

                {
                    "Shockpistol_Shot_SoundSet",
                    "Shockpistol_Tail_SoundSet",
                    "Shockpistol_InteriorTail_SoundSet"
                }
            };
            reloadTime = 0.086000003;
            recoil = "recoil_fnx";
            recoilProne = "recoil_fnx_prone";
            dispersion = 0.0060000001;
            magazineSlot = "magazine";
        };
    };
    class Taser: Taser_Base {
        scope = 2;
        displayName = "Taser X2 Defender";
        descriptionShort = "";
        model = "\dz\weapons\nonlethal\shockpistol\shockpistol.p3d";
        attachments[] = {};
        itemSize[] = {4, 2};
        class DamageSystem {
            class GlobalHealth {
                class Health {
                    hitpoints = 100;
                    healthLevels[] = {

                        {
                            1,

                            {
                                "DZ\weapons\pistols\fnx45\data\herstal45.rvmat"
                            }
                        },

                        {
                            0.69998997,

                            {
                                "DZ\weapons\pistols\fnx45\data\herstal45.rvmat"
                            }
                        },

                        {
                            0.5,

                            {
                                "DZ\weapons\pistols\fnx45\data\herstal45_damage.rvmat"
                            }
                        },

                        {
                            0.300001,

                            {
                                "DZ\weapons\pistols\fnx45\data\herstal45_damage.rvmat"
                            }
                        },

                        {
                            0,

                            {
                                "DZ\weapons\pistols\fnx45\data\herstal45_destruct.rvmat"
                            }
                        }
                    };
                };
            };
        };
    };
};
class cfgRecoils {
    recoil_fnx[] = {
        0,
        0,
        0,
        0.039999999,
        "0.036943*(1)",
        "0.0134348*(3)",
        0.079999998,
        "0.019755*(1)",
        "0.003056*(3)",
        0.090000004,
        0,
        0,
        0.14,
        "-0.003138*(1)",
        "-0.0005*(3)",
        0.079999998,
        "-0.001177*(1)",
        "-0.000188*(3)",
        0.12,
        0,
        0
    };
    recoil_fnx_prone[] = {
        0,
        0,
        0,
        0.039999999,
        "0.036943*(0.5)",
        "0.0134348*(1)",
        0.079999998,
        "0.019755*(0.5)",
        "0.003056*(1)",
        0.090000004,
        0,
        0,
        0.14,
        "-0.003138*(0.5)",
        "-0.0005*(1)",
        0.079999998,
        "-0.001177*(0.5)",
        "-0.000188*(1)",
        0.12,
        0,
        0
    };
};
class CfgMagazines {
    class Mag_FNX45_15Rnd;
    class Mag_taser: Mag_FNX45_15Rnd {
        scope = 2;
        displayName = "X2 Twin Taser Cartridge";
        descriptionShort = "Cartridge for the X2 Taser with two projectile charges";
        model = "\DZ\weapons\attachments\magazine\shockpistol_cartridge.p3d";
        weight = 143;
        itemSize[] = {2, 1};
        count = 7;
        ammo = "Bullet_Taser";
        ammoItems[] = {
            "Ammo_Taser"
        };
        tracersEvery = 0;
        mass = 10;
        class DamageSystem {
            class GlobalHealth {
                class Health {
                    hitpoints = 100;
                    healthLabels[] = {1, 0.69999999, 0.5, 0.30000001, 0};
                    healthLevels[] = {

                        {
                            1,

                            {
                                "DZ\weapons\pistols\fnx45\data\herstal45.rvmat"
                            }
                        },

                        {
                            0.5,

                            {
                                "DZ\weapons\pistols\fnx45\data\herstal45_damage.rvmat"
                            }
                        },

                        {
                            0,

                            {
                                "DZ\weapons\pistols\fnx45\data\herstal45_destruct.rvmat"
                            }
                        }
                    };
                };
            };
        };
    };
    class Ammo_22;
    class Ammo_Taser: Ammo_22 {
        scope = 2;
        displayName = "Magical taser bullets. Do not ingest.";
        descriptionShort = "stop trying to eject the taser rounds pls. Nah but seriously, these are useless, get rid of them";
        model = "\dz\weapons\ammunition\9mm_LooseRounds.p3d";
        weight = 2;
        count = 7;
        ammo = "Bullet_Taser";
    };
};
class CfgNonAIVehicles {
    class ProxyAttachment;
    class ProxyFNP45: ProxyAttachment {
        scope = 2;
        inventorySlot = "pistol";
        model = "\dz\weapons\nonlethal\shockpistol\shockpistol.p3d";
    };
};
class cfgAmmoTypes {
    class AType_Bullet_Taser {
        name = "Bullet_Taser";
    };
};
class cfgAmmo {
    class Bullet_22;
    class Bullet_Taser: Bullet_22 {
        scope = 2;
        lootCategory = "Crafted";
        cartridge = "FxCartridge_22";
        spawnPileType = "Ammo_Taser";
        hit = 4.5;
        indirectHit = 0;
        indirectHitRange = 0;
        visibleFire = 2;
        audibleFire = 3.5;
        visibleFireTime = 3;
        cost = 1;
        tracerScale = 0.60000002;
        tracerStartTime = -1;
        tracerEndTime = 1;
        deflecting = 30;
        caliber = 0.69999999;
        airFriction = -0.00076899998;
        typicalSpeed = 280;
        initSpeed = 280;
        timeToLive = 0.045000002;
        weight = 0.0024999999;
        soundFly[] = {};
        supersonicCrackNear[] = {};
        supersonicCrackFar[] = {};
        class DamageApplied {
            type = "Projectile";
            dispersion = 0;
            bleedThreshold = 0;
            class Health {
                damage = 0;
            };
            class Blood {
                damage = 0;
            };
            class Shock {
                damage = 1000;
            };
        };
        class NoiseHit {
            strength = 3;
            type = "shot";
        };
    };
};
