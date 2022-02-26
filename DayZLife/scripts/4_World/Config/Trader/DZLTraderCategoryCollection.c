class DZLTraderCategoryCollection
{
     string version = "2";
     ref array<ref DZLTraderCategory> categories;

     void DZLTraderCategoryCollection() {
        if (!Load()){
            categories = new array<ref DZLTraderCategory>;
            array<ref DZLTraderType> items = new array<ref DZLTraderType>;

			items.Insert(new DZLTraderType("Crowbar", 10, 200, new array<string>));
			items.Insert(new DZLTraderType("Shovel", 10, 200, new array<string>));
			items.Insert(new DZLTraderType("Pickaxe", 10, 200, new array<string>));
			items.Insert(new DZLTraderType("SledgeHammer", 10, 200, new array<string>));
			items.Insert(new DZLTraderType("WoodAxe", 10, 200, new array<string>));
			items.Insert(new DZLTraderType("FirefighterAxe", 10, 200, new array<string>));
			items.Insert(new DZLTraderType("LugWrench", 10, 200, new array<string>));
			items.Insert(new DZLTraderType("Screwdriver", 10, 200, new array<string>));
			items.Insert(new DZLTraderType("Wrench", 10, 200, new array<string>));
			items.Insert(new DZLTraderType("Pliers", 10, 200, new array<string>));
			items.Insert(new DZLTraderType("Hammer", 10, 200, new array<string>));
			items.Insert(new DZLTraderType("Hacksaw", 10, 200, new array<string>));
			items.Insert(new DZLTraderType("HandSaw", 10, 200, new array<string>));
			items.Insert(new DZLTraderType("Hatchet", 10, 200, new array<string>));
			items.Insert(new DZLTraderType("DZL_Sandpaper", 10, 50, new array<string>));
			items.Insert(new DZLTraderType("DZL_Color", 10, 50, new array<string>));
			categories.Insert(new DZLTraderCategory("Tools", items));
			
			items = new array<ref DZLTraderType>;
			items.Insert(new DZLTraderType("DZL_Stone", 5, 50000, new array<string>));
			items.Insert(new DZLTraderType("DZL_Cement", 30, 50000, new array<string>));
			categories.Insert(new DZLTraderCategory("Cement and Stone Dealer", items));
			
			items = new array<ref DZLTraderType>;
			items.Insert(new DZLTraderType("DZL_Ore_Coal", 40, 50000, new array<string>));
			categories.Insert(new DZLTraderCategory("Coal Dealer", items));
			
			items = new array<ref DZLTraderType>;
			items.Insert(new DZLTraderType("DZL_Ore_Copper", 45, 50000, new array<string>));
			items.Insert(new DZLTraderType("DZL_Copper", 200, 50000, new array<string>));
			categories.Insert(new DZLTraderCategory("Copper Dealer", items));
			
			items = new array<ref DZLTraderType>;
			items.Insert(new DZLTraderType("DZL_Ore_Iron", 60, 50000, new array<string>));
			items.Insert(new DZLTraderType("DZL_Iron", 350, 50000, new array<string>));
			categories.Insert(new DZLTraderCategory("Iron Dealer", items));
			
			items = new array<ref DZLTraderType>;
			items.Insert(new DZLTraderType("DZL_Ore_Gold", 80, 50000, new array<string>));
			items.Insert(new DZLTraderType("DZL_Gold", 600, 50000, new array<string>));
			categories.Insert(new DZLTraderCategory("Gold Dealer", items));
			
			items = new array<ref DZLTraderType>;
			items.Insert(new DZLTraderType("DZL_Ore_Diamond", 120, 50000, new array<string>));
			items.Insert(new DZLTraderType("DZL_Diamond", 1000, 50000, new array<string>));
			categories.Insert(new DZLTraderCategory("Diamond Dealer", items));
			
			items = new array<ref DZLTraderType>;
			items.Insert(new DZLTraderType("DZL_Jewelry", 3500, 50000, new array<string>));
			categories.Insert(new DZLTraderCategory("Jewelry Dealer", items));
			
			items = new array<ref DZLTraderType>;
			items.Insert(new DZLTraderType("DZL_WoodenLog", 55, 50000, new array<string>));
			items.Insert(new DZLTraderType("DZL_WoodenPlank", 70, 50000, new array<string>));
			items.Insert(new DZLTraderType("DZL_Paper", 60, 50000, new array<string>));
			categories.Insert(new DZLTraderCategory("Paper and Wood Dealer", items));
			
			items = new array<ref DZLTraderType>;
			items.Insert(new DZLTraderType("DZL_Money", 8000, 50000, new array<string>));
			categories.Insert(new DZLTraderCategory("Money Dealer", items));
			
			items = new array<ref DZLTraderType>;
			items.Insert(new DZLTraderType("DZL_Cannabis", 10000, 50000, new array<string>));
			items.Insert(new DZLTraderType("DZL_Coacain", 10000, 50000, new array<string>));
			categories.Insert(new DZLTraderCategory("Drug Dealer", items));
			
			items = new array<ref DZLTraderType>;
			items.Insert(new DZLTraderType("PowderedMilk", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("BoxCerealCrunchin", 50, 200, new array<string>));
			items.Insert(new DZLTraderType("Rice", 80, 400, new array<string>));
			items.Insert(new DZLTraderType("Marmalade", 80, 400, new array<string>));
			items.Insert(new DZLTraderType("SpaghettiCan", 50, 150, new array<string>));
			items.Insert(new DZLTraderType("BakedBeansCan", 50, 150, new array<string>));
			items.Insert(new DZLTraderType("TacticalBaconCan", 80, 400, new array<string>));
			categories.Insert(new DZLTraderCategory("Food", items));
			
			items = new array<ref DZLTraderType>;
			items.Insert(new DZLTraderType("Apple", 10, 60, new array<string>));
			items.Insert(new DZLTraderType("ChickenBreastMeat", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("GoatSteakMeat", 30, 40, new array<string>));
			items.Insert(new DZLTraderType("SheepSteakMeat", 30, 40, new array<string>));
			items.Insert(new DZLTraderType("PigSteakMeat", 30, 60, new array<string>));
			items.Insert(new DZLTraderType("BoarSteakMeat", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("WolfSteakMeat", 30, 80, new array<string>));
			items.Insert(new DZLTraderType("DeerSteakMeat", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("CowSteakMeat", 30, 60, new array<string>));
			items.Insert(new DZLTraderType("BearSteakMeat", 30, 160, new array<string>));
			items.Insert(new DZLTraderType("Sardines", 30, 140, new array<string>));
			items.Insert(new DZLTraderType("Carp", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("Mackerel", 30, 140, new array<string>));
			categories.Insert(new DZLTraderCategory("Meat", items));
			
			items = new array<ref DZLTraderType>;
			items.Insert(new DZLTraderType("SodaCan_Cola", 30, 160, new array<string>));
			items.Insert(new DZLTraderType("SodaCan_Kvass", 30, 160, new array<string>));
			items.Insert(new DZLTraderType("SodaCan_Pipsi", 30, 160, new array<string>));
			items.Insert(new DZLTraderType("SodaCan_Spite", 30, 160, new array<string>));
			items.Insert(new DZLTraderType("WaterBottle", 30, 300, new array<string>));
			items.Insert(new DZLTraderType("Canteen", 30, 360, new array<string>));
			items.Insert(new DZLTraderType("Vodka", 30, 400, new array<string>));
			categories.Insert(new DZLTraderCategory("Drinks", items));
			
			items = new array<ref DZLTraderType>;
			items.Insert(new DZLTraderType("Stone", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("SmallStone", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("DZL_Ore_Coal", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("DZL_Ore_Copper", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("DZL_Ore_Iron", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("DZL_Ore_Gold", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("DZL_Ore_Diamond", 30, 100, new array<string>));
			categories.Insert(new DZLTraderCategory("Ore", items));
			
			items = new array<ref DZLTraderType>;
			array<string> attachments = new array<string>;
			attachments.Insert("HuntingOptic");
			items.Insert(new DZLTraderType("B95", 30, 100, attachments, true, false));
			
			attachments = new array<string>;
			attachments.Insert("HuntingOptic");
			items.Insert(new DZLTraderType("Winchester70", 30, 100, attachments, true, false));
			
			attachments = new array<string>;
			attachments.Insert("PUScopeOptic");
			items.Insert(new DZLTraderType("Mosin9130", 30, 100, attachments, true, false));
			
			attachments = new array<string>;
			attachments.Insert("AK74_WoodBttstck");
			attachments.Insert("AK_WoodHndgrd");
			attachments.Insert("PSO1Optic");
			attachments.Insert("Mag_AKM_Palm30Rnd");
			items.Insert(new DZLTraderType("AKM", 30, 100, attachments, true, false));
			
			attachments = new array<string>;
			attachments.Insert("AK_PlasticBttstck");
			attachments.Insert("AK_PlasticHndgrd");
			attachments.Insert("KobraOptic");
			attachments.Insert("Mag_AK101_30Rnd");
			items.Insert(new DZLTraderType("AK101", 30, 100, attachments, true, false));
			
			attachments = new array<string>;
			attachments.Insert("M4_CQBBttstck");
			attachments.Insert("M4_RISHndgrd");
			attachments.Insert("ACOGOptic");
			attachments.Insert("Mag_STANAG_30Rnd");
			items.Insert(new DZLTraderType("M4A1", 30, 100, attachments, true, false));
			
			attachments = new array<string>;
			attachments.Insert("Fal_OeBttstck");
			attachments.Insert("Mag_FAL_20Rnd");
			attachments.Insert("ACOGOptic");
			items.Insert(new DZLTraderType("FAL", 30, 100, attachments, true, false));
			
			attachments = new array<string>;
			attachments.Insert("PSO11Optic");
			attachments.Insert("Mag_SVD_10Rnd");
			items.Insert(new DZLTraderType("SVD", 30, 100, attachments, true, false));
			categories.Insert(new DZLTraderCategory("Weapons", items));
			
			items = new array<ref DZLTraderType>;
			items.Insert(new DZLTraderType("Mag_AKM_30Rnd", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("Mag_AKM_Palm30Rnd", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("Mag_AK101_30Rnd", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("Mag_STANAG_30Rnd", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("Mag_CMAG_10Rnd", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("Mag_CMAG_20Rnd", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("Mag_CMAG_30Rnd", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("Mag_CMAG_40Rnd", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("Mag_FAL_20Rnd", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("Mag_SVD_10Rnd", 30, 100, new array<string>));
			categories.Insert(new DZLTraderCategory("Magazines", items));
			
			items = new array<ref DZLTraderType>;
			items.Insert(new DZLTraderType("AmmoBox_556x45_20Rnd", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("AmmoBox_762x39_20Rnd", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("AmmoBox_308Win_20Rnd", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("AmmoBox_762x54_20Rnd", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("AmmoBox_556x45Tracer_20Rnd", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("AmmoBox_762x39Tracer_20Rnd", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("AmmoBox_308WinTracer_20Rnd", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("AmmoBox_762x54Tracer_20Rnd", 30, 100, new array<string>));
			categories.Insert(new DZLTraderCategory("Ammo", items));
			
			items = new array<ref DZLTraderType>;
			items.Insert(new DZLTraderType("M65Jacket_Black", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("M65Jacket_Khaki", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("M65Jacket_Olive", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("M65Jacket_Tan", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("CargoPants_Beige", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("CargoPants_Black", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("CargoPants_Blue", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("CargoPants_Green", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("CargoPants_Grey", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("MountainBag_Blue", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("MountainBag_Green", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("MountainBag_Orange", 30, 100, new array<string>));
			items.Insert(new DZLTraderType("MountainBag_Red", 30, 100, new array<string>));
			categories.Insert(new DZLTraderCategory("Clothing", items));
			
			items = new array<ref DZLTraderType>;
			items.Insert(new DZLTraderType("TetracyclineAntibiotics", 2, 5, new array<string>));
			items.Insert(new DZLTraderType("CharcoalTablets", 2, 5, new array<string>));
			items.Insert(new DZLTraderType("PainkillerTablets", 2, 5, new array<string>));
			items.Insert(new DZLTraderType("Splint", 2, 5, new array<string>));
			items.Insert(new DZLTraderType("BandageDressing", 2, 5, new array<string>));
			categories.Insert(new DZLTraderCategory("Medic", items));
			
			items = new array<ref DZLTraderType>;
			attachments = new array<string>;
			attachments.Insert("HatchbackDoors_CoDriver");
			attachments.Insert("HatchbackDoors_Driver");
			attachments.Insert("HatchbackHood");
			attachments.Insert("HatchbackTrunk");
			attachments.Insert("HatchbackWheel");
			attachments.Insert("HatchbackWheel");
			attachments.Insert("HatchbackWheel");
			attachments.Insert("HatchbackWheel");
			attachments.Insert("HatchbackWheel");
			attachments.Insert("SparkPlug");
			attachments.Insert("CarBattery");
			attachments.Insert("CarRadiator");
			attachments.Insert("HeadlightH7");
			attachments.Insert("HeadlightH7");
            items.Insert(new DZLTraderType("OffroadHatchback", 25000, 60000, attachments, false, true));
			
			attachments = new array<string>;
			attachments.Insert("Hatchback_02_Door_1_1");
			attachments.Insert("Hatchback_02_Door_1_2");
			attachments.Insert("Hatchback_02_Door_2_1");
			attachments.Insert("Hatchback_02_Door_2_2");
			attachments.Insert("Hatchback_02_Hood");
			attachments.Insert("Hatchback_02_Trunk");
			attachments.Insert("Hatchback_02_Wheel");
			attachments.Insert("Hatchback_02_Wheel");
			attachments.Insert("Hatchback_02_Wheel");
			attachments.Insert("Hatchback_02_Wheel");
			attachments.Insert("SparkPlug");
			attachments.Insert("CarBattery");
			attachments.Insert("CarRadiator");
			attachments.Insert("HeadlightH7");
			attachments.Insert("HeadlightH7");
            items.Insert(new DZLTraderType("Hatchback_02", 20000, 50000, attachments, false, true));
			categories.Insert(new DZLTraderCategory("Cars", items));
			
			attachments = new array<string>;
			attachments.Insert("Truck_01_Wheel");
			attachments.Insert("Truck_01_Wheel");
			attachments.Insert("Truck_01_Wheel");
			attachments.Insert("Truck_01_Wheel");
			attachments.Insert("Truck_01_WheelDouble");
			attachments.Insert("Truck_01_WheelDouble");
			attachments.Insert("Truck_01_WheelDouble");
			attachments.Insert("Truck_01_WheelDouble");
			attachments.Insert("Truck_01_Hood");
			attachments.Insert("Truck_01_Door_1_1");
			attachments.Insert("Truck_01_Door_2_1");
			attachments.Insert("TruckBattery");
			attachments.Insert("HeadlightH7");
			attachments.Insert("HeadlightH7");
            items.Insert(new DZLTraderType("Truck_01_Covered", 45000, 50000, attachments, false, true));
			categories.Insert(new DZLTraderCategory("Cars", items));
            
            Save();
        } else {
            bool mustSave = false;
            array<string> ids = new array<string>;
            foreach(DZLTraderCategory category: categories) {
                foreach(DZLTraderType _items: category.items) {
                    if (!_items.HasCorrectId()) {
                        _items.SetId();
                        mustSave = true;
                    }

                    if(-1 != ids.Find(_items.GetId())) {
                        _items.SetId();
                        mustSave = true;
                    }

                    ids.Insert(_items.GetId());
                }
            }
			
			if (version == "") {
				version = "1";
				mustSave = true;
			}

			if (version == "1") {
				version = "2";
				mustSave = true;
			}

            if (mustSave) {
               	Save();
            }
        }

        foreach(DZLTraderCategory cat: categories) {
            foreach(DZLTraderType item: cat.items) {
                if (item.isStorageItem) {
                    DZLDatabaseLayer.Get().GetTraderStorage().Insert(item);
                }
            }
        }
    }
	
	DZLTraderCategory GetCatByName(string name) {
		foreach(DZLTraderCategory cat: categories) {
			if (cat.name == name) {
				return cat;
			}
		}
	
		return null;
	}

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "traderCategories.json")) {
            JsonFileLoader<DZLTraderCategoryCollection>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "traderCategories.json", this);
            return true;
        }
        return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
            CheckDZLConfigPath();
            JsonFileLoader<DZLTraderCategoryCollection>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "traderCategories.json", this);
        }
    }
}
