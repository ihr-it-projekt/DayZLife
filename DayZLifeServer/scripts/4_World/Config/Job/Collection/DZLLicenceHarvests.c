modded class DZLWorkZones {

    void DZLWorkZones() {
        if(!Load()) {
            workZones = new array<ref DZLWorkZone>;
            array<ref DZLHarvestItemToolRelation> harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;
            array<string> itemsThatCanHarvest = new array<string>;
            array<string> itemsThatNeededForHarvest = new array<string>;



            // add life config;
            // Harvest Apple 1
            itemsThatCanHarvest = new array<string>;
            itemsThatNeededForHarvest = new array<string>;
            harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

            itemsThatCanHarvest.Insert("Apple");

            itemsThatNeededForHarvest.Insert("CombatKnife");
            itemsThatNeededForHarvest.Insert("HuntingKnife");
            itemsThatNeededForHarvest.Insert("KitchenKnife");
            itemsThatNeededForHarvest.Insert("SteakKnife");

            DZLHarvestItemToolRelation relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);

            harvestItemToolRelation.Insert(relation);

            DZLWorkZone zone = new DZLWorkZone(74, "7592 6 3483", 10, "#Apple_orchard", 4, 5, harvestItemToolRelation, true);
            workZones.Insert(zone);
            // Harvest Apple 1 end

            // Harvest Apple 2
            itemsThatCanHarvest = new array<string>;
            itemsThatNeededForHarvest = new array<string>;
            harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

            itemsThatCanHarvest.Insert("Apple");

            itemsThatNeededForHarvest.Insert("CombatKnife");
            itemsThatNeededForHarvest.Insert("HuntingKnife");
            itemsThatNeededForHarvest.Insert("KitchenKnife");
            itemsThatNeededForHarvest.Insert("SteakKnife");

            relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);

            harvestItemToolRelation.Insert(relation);

            zone = new DZLWorkZone(74, "12162 49 8984", 10, "#Apple_orchard", 4, 5, harvestItemToolRelation, true);
            workZones.Insert(zone);
            // Harvest Apple 2 end

            // Harvest Apple 3
            itemsThatCanHarvest = new array<string>;
            itemsThatNeededForHarvest = new array<string>;
            harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

            itemsThatCanHarvest.Insert("Apple");

            itemsThatNeededForHarvest.Insert("CombatKnife");
            itemsThatNeededForHarvest.Insert("HuntingKnife");
            itemsThatNeededForHarvest.Insert("KitchenKnife");
            itemsThatNeededForHarvest.Insert("SteakKnife");

            relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);

            harvestItemToolRelation.Insert(relation);

            zone = new DZLWorkZone(74, "11992 90 13926", 10, "#Apple_orchard", 4, 5, harvestItemToolRelation, true);
            workZones.Insert(zone);
            // Harvest Apple 3 end

            // Harvest Apple 4
            itemsThatCanHarvest = new array<string>;
            itemsThatNeededForHarvest = new array<string>;
            harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

            itemsThatCanHarvest.Insert("Apple");

            itemsThatNeededForHarvest.Insert("CombatKnife");
            itemsThatNeededForHarvest.Insert("HuntingKnife");
            itemsThatNeededForHarvest.Insert("KitchenKnife");
            itemsThatNeededForHarvest.Insert("SteakKnife");

            relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);

            harvestItemToolRelation.Insert(relation);

            zone = new DZLWorkZone(74, "2637 204 5381", 10, "#Apple_orchard", 4, 5, harvestItemToolRelation, true);
            workZones.Insert(zone);
            // Harvest Apple 4 end

            //Harvest Stone
            itemsThatCanHarvest = new array<string>;
            itemsThatNeededForHarvest = new array<string>;
            harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

            itemsThatCanHarvest.Insert("DZL_Stone");

            itemsThatNeededForHarvest.Insert("Pickaxe");

            relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
            harvestItemToolRelation.Insert(relation);

            zone = new DZLWorkZone(109, "13274 9 6095", 10, "#Stone_quarry", 10, 10, harvestItemToolRelation, true);
            workZones.Insert(zone);
            //Harvest Stone end

            //Harvest Coal
            itemsThatCanHarvest = new array<string>;
            itemsThatNeededForHarvest = new array<string>;
            harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

            itemsThatCanHarvest.Insert("DZL_Ore_Coal");

            itemsThatNeededForHarvest.Insert("Pickaxe");

            relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
            harvestItemToolRelation.Insert(relation);

            zone = new DZLWorkZone(109, "8722 99 13264", 10, "#coal_mine", 12, 10, harvestItemToolRelation, true);
            workZones.Insert(zone);
            //Harvest Coal end

            // Harvest Copper
            itemsThatCanHarvest = new array<string>;
            itemsThatNeededForHarvest = new array<string>;
            harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

            itemsThatCanHarvest.Insert("DZL_Ore_Copper");

            itemsThatNeededForHarvest.Insert("Pickaxe");

            relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
            harvestItemToolRelation.Insert(relation);

            zone = new DZLWorkZone(109, "8540 8 2978", 10, "#Copper_mine", 14, 10, harvestItemToolRelation, true);
            workZones.Insert(zone);
            // Harvest Copper end

            //Harvest Iron
            itemsThatCanHarvest = new array<string>;
            itemsThatNeededForHarvest = new array<string>;
            harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

            itemsThatCanHarvest.Insert("DZL_Ore_Iron");

            itemsThatNeededForHarvest.Insert("Pickaxe");

            relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
            harvestItemToolRelation.Insert(relation);

            zone = new DZLWorkZone(109, "919 180 6689", 10, "#Iron_mine", 16, 10, harvestItemToolRelation, true);
            workZones.Insert(zone);
            //Harvest Iron end

            //Harvest Gold
            itemsThatCanHarvest = new array<string>;
            itemsThatNeededForHarvest = new array<string>;
            harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

            itemsThatCanHarvest.Insert("DZL_Ore_Gold");

            itemsThatNeededForHarvest.Insert("Pickaxe");

            relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
            harvestItemToolRelation.Insert(relation);

            zone = new DZLWorkZone(109, "14098 2 13406", 10, "#Gold_mine", 18, 10, harvestItemToolRelation, true);
            workZones.Insert(zone);
            //Harvest Gold end

            //Harvest Diamond
            itemsThatCanHarvest = new array<string>;
            itemsThatNeededForHarvest = new array<string>;
            harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

            itemsThatCanHarvest.Insert("DZL_Ore_Diamond");

            itemsThatNeededForHarvest.Insert("Pickaxe");

            relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
            harvestItemToolRelation.Insert(relation);

            zone = new DZLWorkZone(109, "13672 49 12299", 10, "#Diamond_mine", 20, 10, harvestItemToolRelation, true);
            workZones.Insert(zone);
            //Harvest Diamond end

            //Harvest WoodenLog
            itemsThatCanHarvest = new array<string>;
            itemsThatNeededForHarvest = new array<string>;
            harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

            itemsThatCanHarvest.Insert("DZL_WoodenLog");

            itemsThatNeededForHarvest.Insert("WoodAxe");
            itemsThatNeededForHarvest.Insert("FirefighterAxe");

            relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
            harvestItemToolRelation.Insert(relation);

            zone = new DZLWorkZone(86, "932 180 7723", 10, "#Sawmill", 10, 5, harvestItemToolRelation, true);
            workZones.Insert(zone);
            //Harvest WoodenLog end

            // Harvest Cannabis
            itemsThatCanHarvest = new array<string>;
            itemsThatNeededForHarvest = new array<string>;
            harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

            itemsThatCanHarvest.Insert("DZL_Cannabis");

            itemsThatNeededForHarvest.Insert("CombatKnife");
            itemsThatNeededForHarvest.Insert("HuntingKnife");
            itemsThatNeededForHarvest.Insert("KitchenKnife");
            itemsThatNeededForHarvest.Insert("SteakKnife");

            relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);

            harvestItemToolRelation.Insert(relation);

            zone = new DZLWorkZone(74, "2227 433 15259", 10, "#Cannabis_plantation", 10, 10, harvestItemToolRelation, false);
            workZones.Insert(zone);
            // Harvest Cannabis end

            // Harvest Coca
            itemsThatCanHarvest = new array<string>;
            itemsThatNeededForHarvest = new array<string>;
            harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

            itemsThatCanHarvest.Insert("DZL_Cocaine");

            itemsThatNeededForHarvest.Insert("CombatKnife");
            itemsThatNeededForHarvest.Insert("HuntingKnife");
            itemsThatNeededForHarvest.Insert("KitchenKnife");
            itemsThatNeededForHarvest.Insert("SteakKnife");

            relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);

            harvestItemToolRelation.Insert(relation);

            zone = new DZLWorkZone(74, "12115 140 15263", 10, "#Cocaine_plantation", 10, 10, harvestItemToolRelation, false);
            workZones.Insert(zone);
            // Harvest Coca end

            //Gather Vehicle Parts
            itemsThatCanHarvest = new array<string>;
            itemsThatNeededForHarvest = new array<string>;
            harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

            itemsThatCanHarvest.Insert("DZL_CivSedanDoors_BackLeft_BlackRust");
            itemsThatCanHarvest.Insert("DZL_CivSedanDoors_BackLeft_WhiteRust");
            itemsThatCanHarvest.Insert("DZL_CivSedanDoors_BackLeft_WineRust");
            itemsThatCanHarvest.Insert("DZL_CivSedanDoors_BackRight_BlackRust");
            itemsThatCanHarvest.Insert("DZL_CivSedanDoors_BackRight_WhiteRust");
            itemsThatCanHarvest.Insert("DZL_CivSedanDoors_BackRight_WineRust");
            itemsThatCanHarvest.Insert("DZL_CivSedanDoors_CoDriver_BlackRust");
            itemsThatCanHarvest.Insert("DZL_CivSedanDoors_CoDriver_WhiteRust");
            itemsThatCanHarvest.Insert("DZL_CivSedanDoors_CoDriver_WineRust");
            itemsThatCanHarvest.Insert("DZL_CivSedanDoors_Driver_BlackRust");
            itemsThatCanHarvest.Insert("DZL_CivSedanDoors_Driver_WhiteRust");
            itemsThatCanHarvest.Insert("DZL_CivSedanDoors_Driver_WineRust");
            itemsThatCanHarvest.Insert("DZL_CivSedanHood_BlackRust");
            itemsThatCanHarvest.Insert("DZL_CivSedanHood_WhiteRust");
            itemsThatCanHarvest.Insert("DZL_CivSedanHood_WineRust");
            itemsThatCanHarvest.Insert("DZL_CivSedanTrunk_BlackRust");
            itemsThatCanHarvest.Insert("DZL_CivSedanTrunk_WhiteRust");
            itemsThatCanHarvest.Insert("DZL_CivSedanTrunk_WineRust");
            itemsThatCanHarvest.Insert("DZL_HatchbackDoors_CoDriver_BlueRust");
            itemsThatCanHarvest.Insert("DZL_HatchbackDoors_CoDriver_GreenRust");
            itemsThatCanHarvest.Insert("DZL_HatchbackDoors_CoDriver_WhiteRust");
            itemsThatCanHarvest.Insert("DZL_HatchbackDoors_Driver_BlueRust");
            itemsThatCanHarvest.Insert("DZL_HatchbackDoors_Driver_GreenRust");
            itemsThatCanHarvest.Insert("DZL_HatchbackDoors_Driver_WhiteRust");
            itemsThatCanHarvest.Insert("DZL_HatchbackHood_BlueRust");
            itemsThatCanHarvest.Insert("DZL_HatchbackHood_GreenRust");
            itemsThatCanHarvest.Insert("DZL_HatchbackHood_WhiteRust");
            itemsThatCanHarvest.Insert("DZL_HatchbackTrunk_BlueRust");
            itemsThatCanHarvest.Insert("DZL_HatchbackTrunk_GreenRust");
            itemsThatCanHarvest.Insert("DZL_HatchbackTrunk_WhiteRust");
            itemsThatCanHarvest.Insert("DZL_Hatchback_02_Door_1_1_BlackRust");
            itemsThatCanHarvest.Insert("DZL_Hatchback_02_Door_1_1_BlueRust");
            itemsThatCanHarvest.Insert("DZL_Hatchback_02_Door_1_1_RedRust");
            itemsThatCanHarvest.Insert("DZL_Hatchback_02_Door_1_2_BlackRust");
            itemsThatCanHarvest.Insert("DZL_Hatchback_02_Door_1_2_BlueRust");
            itemsThatCanHarvest.Insert("DZL_Hatchback_02_Door_1_2_RedRust");
            itemsThatCanHarvest.Insert("DZL_Hatchback_02_Door_2_1_BlackRust");
            itemsThatCanHarvest.Insert("DZL_Hatchback_02_Door_2_1_BlueRust");
            itemsThatCanHarvest.Insert("DZL_Hatchback_02_Door_2_1_RedRust");
            itemsThatCanHarvest.Insert("DZL_Hatchback_02_Door_2_2_BlackRust");
            itemsThatCanHarvest.Insert("DZL_Hatchback_02_Door_2_2_BlueRust");
            itemsThatCanHarvest.Insert("DZL_Hatchback_02_Door_2_2_RedRust");
            itemsThatCanHarvest.Insert("DZL_Hatchback_02_Hood_BlackRust");
            itemsThatCanHarvest.Insert("DZL_Hatchback_02_Hood_BlueRust");
            itemsThatCanHarvest.Insert("DZL_Hatchback_02_Hood_RedRust");
            itemsThatCanHarvest.Insert("DZL_Hatchback_02_Trunk_BlackRust");
            itemsThatCanHarvest.Insert("DZL_Hatchback_02_Trunk_BlueRust");
            itemsThatCanHarvest.Insert("DZL_Hatchback_02_Trunk_RedRust");
            itemsThatCanHarvest.Insert("DZL_Sedan_02_Door_1_1_GreyRust");
            itemsThatCanHarvest.Insert("DZL_Sedan_02_Door_1_1_RedRust");
            itemsThatCanHarvest.Insert("DZL_Sedan_02_Door_1_1_YellowRust");
            itemsThatCanHarvest.Insert("DZL_Sedan_02_Door_1_2_GreyRust");
            itemsThatCanHarvest.Insert("DZL_Sedan_02_Door_1_2_RedRust");
            itemsThatCanHarvest.Insert("DZL_Sedan_02_Door_1_2_YellowRust");
            itemsThatCanHarvest.Insert("DZL_Sedan_02_Door_2_1_GreyRust");
            itemsThatCanHarvest.Insert("DZL_Sedan_02_Door_2_1_RedRust");
            itemsThatCanHarvest.Insert("DZL_Sedan_02_Door_2_1_YellowRust");
            itemsThatCanHarvest.Insert("DZL_Sedan_02_Door_2_2_GreyRust");
            itemsThatCanHarvest.Insert("DZL_Sedan_02_Door_2_2_RedRust");
            itemsThatCanHarvest.Insert("DZL_Sedan_02_Door_2_2_YellowRust");
            itemsThatCanHarvest.Insert("DZL_Sedan_02_Hood_GreyRust");
            itemsThatCanHarvest.Insert("DZL_Sedan_02_Hood_RedRust");
            itemsThatCanHarvest.Insert("DZL_Sedan_02_Hood_YellowRust");
            itemsThatCanHarvest.Insert("DZL_Sedan_02_Trunk_GreyRust");
            itemsThatCanHarvest.Insert("DZL_Sedan_02_Trunk_RedRust");
            itemsThatCanHarvest.Insert("DZL_Sedan_02_Trunk_YellowRust");
            itemsThatCanHarvest.Insert("DZL_Truck_01_Hood_Orange");
            itemsThatCanHarvest.Insert("DZL_Truck_01_Hood_Blue");
            itemsThatCanHarvest.Insert("DZL_Truck_01_Hood");
            itemsThatCanHarvest.Insert("DZL_Truck_01_Door_2_1_Orange");
            itemsThatCanHarvest.Insert("DZL_Truck_01_Door_2_1_Blue");
            itemsThatCanHarvest.Insert("DZL_Truck_01_Door_2_1");
            itemsThatCanHarvest.Insert("DZL_Truck_01_Door_1_1_Orange");
            itemsThatCanHarvest.Insert("DZL_Truck_01_Door_1_1_Blue");
            itemsThatCanHarvest.Insert("DZL_Truck_01_Door_1_1");
            itemsThatCanHarvest.Insert("CarRadiator");
            itemsThatCanHarvest.Insert("CarBattery");
            itemsThatCanHarvest.Insert("TruckBattery");
            itemsThatCanHarvest.Insert("SparkPlug");

            itemsThatNeededForHarvest.Insert("Wrench");
            itemsThatNeededForHarvest.Insert("LugWrench");

            relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
            harvestItemToolRelation.Insert(relation);

            zone = new DZLWorkZone(74, "12538 55 13790", 10, "#Scrap_yard", 15, 5, harvestItemToolRelation, true);
            workZones.Insert(zone);
            //Gather Vehicle Parts end

            // Ölschlamm
            itemsThatCanHarvest = new array<string>;
            itemsThatNeededForHarvest = new array<string>;
            harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;

            itemsThatCanHarvest.Insert("DZL_Oil_Barrel");

            itemsThatNeededForHarvest.Insert("FieldShovel");

            relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);

            harvestItemToolRelation.Insert(relation);

            zone = new DZLWorkZone(90, "3765.302002 3.634198 2271.211914", 10, "Oilschlamm", 20, 10, harvestItemToolRelation, true);
            workZones.Insert(zone);
            // Ölschlamm ende


            Save();
        }
        if(version == "1") {
            version = "2";
            Save();
        }
    }

    private bool Load() {
        if(GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "workZone.json")) {
            JsonFileLoader<DZLWorkZones>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "workZone.json", this);
            return true;
        }
        return false;
    }

    private void Save() {
        if(GetGame().IsServer()) {
            CheckDZLConfigPath();
            JsonFileLoader<DZLWorkZones>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "workZone.json", this);
        }
    }
}
