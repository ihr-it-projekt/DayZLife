class CfgPatches {
    class DZL_WeaponsBlanks {
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
    class DZL_W_AK74: Inventory_Base {
        scope = 2;
        displayName = "AK74 Rohling";
        descriptionShort = "$STR_cfgWeapons_AK741";
        model = "\dz\weapons\firearms\AK101\ak101.p3d";
        weight = 3070;
        itemSize[] = {8, 3};
        color = "Green";
        hiddenSelectionsTextures[] = {
            "#(argb,8,8,3)color(0.35,0.36,0.28,1.0,CO)",
            "#(argb,8,8,3)color(0.15,0.15,0.15,1.0,CO)"
        };
    };
    class DZL_W_AKS74U: Inventory_Base {
        scope = 2;
        displayName = "AKS74U Rohling";
        descriptionShort = "$STR_cfgWeapons_AKS74U1";
        model = "\dz\weapons\firearms\AK74\aks74u.p3d";
        weight = 2700;
        itemSize[] = {6, 3};
        color = "Green";
        hiddenSelectionsTextures[] = {
            "#(argb,8,8,3)color(0.35,0.36,0.28,1.0,CO)",
            "#(argb,8,8,3)color(0.15,0.15,0.15,1.0,CO)"
        };
    };
    class DZL_W_AK101: Inventory_Base {
        scope = 2;
        displayName = "AK101 Rohling";
        descriptionShort = "$STR_CfgWeapons_AK1011";
        model = "\dz\weapons\firearms\AK101\ak101.p3d";
        weight = 3077;
        itemSize[] = {8, 3};
        color = "Green";
        hiddenSelectionsTextures[] = {
            "#(argb,8,8,3)color(0.35,0.36,0.28,1.0,CO)"
        };
    };
    class DZL_W_AKM: Inventory_Base {
        scope = 2;
        displayName = "AKM Rohling";
        descriptionShort = "$STR_cfgWeapons_AKM1";
        model = "\dz\weapons\firearms\AKM\AKM.p3d";
        weight = 2140;
        itemSize[] = {8, 3};
        color = "Green";
        hiddenSelectionsTextures[] = {
            "#(argb,8,8,3)color(0.35,0.36,0.28,1.0,CO)"
        };
    };
    class DZL_W_B95: Inventory_Base {
        scope = 2;
        displayName = "B95 Rohling";
        descriptionShort = "$STR_cfgWeapons_B951";
        model = "\dz\weapons\firearms\B95\b95.p3d";
        weight = 2820;
        itemSize[] = {9, 3};
        color = "Green";
        hiddenSelectionsTextures[] = {
            "#(argb,8,8,3)color(0.35,0.36,0.28,1.0,CO)"
        };
        hiddenSelectionsMaterials[] = {
            "dz\weapons\firearms\B95\data\b95_painted.rvmat"
        };
    };
    class DZL_W_CZ61: Inventory_Base {
        scope = 2;
        displayName = "CZ61 Rohling";
        descriptionShort = "$STR_CfgWeapons_CZ611";
        model = "\dz\weapons\firearms\cz61\CZ61.p3d";
        weight = 1280;
        itemSize[] = {4, 3};
        color = "Green";
        hiddenSelectionsTextures[] = {
            "#(argb,8,8,3)color(0.35,0.36,0.28,1.0,CO)"
        };
    };
    class DZL_W_CZ527: Inventory_Base {
        scope = 2;
        displayName = "CZ527 Rohling";
        descriptionShort = "$STR_cfgWeapons_CZ5271";
        model = "\dz\weapons\firearms\cz527\cz527.p3d";
        weight = 2720;
        itemSize[] = {8, 3};
        color = "Green";
        hiddenSelectionsTextures[] = {
            "#(argb,8,8,3)color(0.35,0.36,0.28,1.0,CO)"
        };
    };
    class DZL_W_FAL: Inventory_Base {
        scope = 2;
        displayName = "FAL Rohling";
        descriptionShort = "$STR_cfgWeapons_FAL1";
        model = "\dz\weapons\firearms\fal\fal.p3d";
        weight = 3700;
        itemSize[] = {8, 3};
        color = "Green";
        hiddenSelectionsTextures[] = {
            "#(argb,8,8,3)color(0.35,0.36,0.28,1.0,CO)"
        };
    };
    class DZL_W_Izh18: Inventory_Base {
        scope = 2;
        displayName = "Izh18 Rohling";
        descriptionShort = "$STR_cfgWeapons_Izh181";
        model = "\dz\weapons\firearms\Izh18\Izh18.p3d";
        weight = 3200;
        itemSize[] = {8, 3};
        color = "Green";
        hiddenSelectionsTextures[] = {
            "#(argb,8,8,3)color(0.35,0.36,0.28,1.0,CO)"
        };
    };
    class DZL_W_M4A1: Inventory_Base {
        scope = 2;
        displayName = "M4A1 Rohling";
        descriptionShort = "$STR_cfgWeapons_M4A11";
        model = "\dz\weapons\firearms\m4\m4a1.p3d";
        weight = 1746;
        itemSize[] = {8, 3};
        color = "Green";
        hiddenSelectionsTextures[] = {
            "dz\weapons\firearms\m4\data\m4_body_green_co.paa"
        };
        hiddenSelectionsMaterials[] = {
            "dz\weapons\firearms\m4\data\m4_body_camo.rvmat"
        };
    };
    class DZL_W_Mosin9130: Inventory_Base {
        scope = 2;
        displayName = "Mosin9130 Rohling";
        descriptionShort = "$STR_cfgWeapons_Mosin91301";
        model = "\dz\weapons\firearms\mosin9130\mosin9130.p3d";
        weight = 4000;
        itemSize[] = {8, 3};
        color = "Green";
        hiddenSelectionsTextures[] = {
            "#(argb,8,8,3)color(0.35,0.36,0.28,1.0,CO)"
        };
    };
    class DZL_W_MP5K: Inventory_Base {
        scope = 2;
        displayName = "MP5K Rohling";
        descriptionShort = "$STR_cfgWeapons_MP5K1";
        model = "\dz\weapons\firearms\MP5\MP5K.p3d";
        weight = 1840;
        itemSize[] = {4, 3};
        color = "Green";
        hiddenSelectionsTextures[] = {
            "#(argb,8,8,3)color(0.35,0.36,0.28,1.0,CO)"
        };
    };
    class DZL_W_Repeater: Inventory_Base {
        scope = 2;
        displayName = "Repeater Rohling";
        descriptionShort = "$STR_cfgWeapons_Repeater1";
        model = "\dz\weapons\firearms\repeater\repeater.p3d";
        weight = 2720;
        itemSize[] = {8, 3};
        color = "Green";
        hiddenSelectionsTextures[] = {
            "#(argb,8,8,3)color(0.35,0.36,0.28,1.0,CO)"
        };
    };
    class DZL_W_Ruger1022: Inventory_Base {
        scope = 2;
        displayName = "Ruger1022 Rohling";
        descriptionShort = "$STR_cfgWeapons_Ruger10221";
        model = "\dz\weapons\firearms\Ruger1022\Ruger1022.p3d";
        weight = 2300;
        itemSize[] = {8, 3};
        color = "Green";
        hiddenSelectionsTextures[] = {
            "#(argb,8,8,3)color(0.35,0.36,0.28,1.0,CO)"
        };
    };
    class DZL_W_SKS: Inventory_Base {
        scope = 2;
        displayName = "SKS Rohling";
        descriptionShort = "$STR_cfgWeapons_SKS1";
        model = "\dz\weapons\firearms\SKS\SKS.p3d";
        weight = 3850;
        itemSize[] = {8, 3};
        color = "Green";
        hiddenSelectionsTextures[] = {
            "dz\weapons\firearms\SKS\data\sks_green_co.paa",
            "",
            ""
        };
        hiddenSelectionsMaterials[] = {
            "dz\weapons\firearms\SKS\data\sks_painted.rvmat",
            "",
            ""
        };
    };
    class DZL_W_SVD: Inventory_Base {
        scope = 2;
        displayName = "SVD Rohling";
        descriptionShort = "$STR_cfgWeapons_SVD1";
        model = "\dz\weapons\firearms\svd\svd.p3d";
        weight = 3700;
        itemSize[] = {8, 3};
        color = "Green";
        hiddenSelectionsTextures[] = {
            "#(argb,8,8,3)color(0.35,0.36,0.28,1.0,CO)"
        };
    };
    class DZL_W_Trumpet: Inventory_Base {
        scope = 2;
        displayName = "Trumpet Rohling";
        descriptionShort = "$STR_cfgWeapons_Trumpet1";
        model = "\dz\weapons\firearms\Trumpet\trumpet.p3d";
        weight = 3700;
        itemSize[] = {8, 3};
        color = "Green";
        hiddenSelectionsTextures[] = {
            "#(argb,8,8,3)color(0.35,0.36,0.28,1.0,CO)"
        };
    };
    class DZL_W_UMP45: Inventory_Base {
        scope = 2;
        displayName = "UMP45 Rohling";
        descriptionShort = "$STR_cfgWeapons_UMP451";
        model = "\dz\weapons\firearms\UMP45\ump.p3d";
        weight = 2500;
        itemSize[] = {4, 3};
        color = "Green";
        hiddenSelectionsTextures[] = {
            "#(argb,8,8,3)color(0.35,0.36,0.28,1.0,CO)"
        };
    };
    class DZL_W_VSS: Inventory_Base {
        scope = 2;
        displayName = "VSS Rohling";
        descriptionShort = "$STR_cfgWeapons_VSS1";
        model = "\dz\weapons\firearms\VSS\VSS.p3d";
        weight = 2600;
        itemSize[] = {6, 3};
        color = "Green";
        hiddenSelectionsTextures[] = {
            "#(argb,8,8,3)color(0.35,0.36,0.28,1.0,CO)"
        };
    };
    class DZL_W_Winchester: Inventory_Base {
        scope = 2;
        displayName = "Winchester Rohling";
        descriptionShort = "$STR_cfgWeapons_Winchester701";
        model = "\dz\weapons\firearms\winchester70\winchester70.p3d";
        weight = 2721;
        itemSize[] = {6, 3};
        hiddenSelectionsTextures[] = {
            "#(argb,8,8,3)color(0.35,0.36,0.28,1.0,CO)"
        };
    };
};
