class DZLTraderCategoryCollection
{
     ref array<ref DZLTraderCategory> categories;

     void DZLTraderCategoryCollection() {
        if (!Load()){
            categories = new array<ref DZLTraderCategory>;
            array<ref DZLTraderType> items = new array<ref DZLTraderType>;

			items.Insert(new DZLTraderType("Crowbar", 50, 500, new array<string>));
			items.Insert(new DZLTraderType("Shovel", 50, 600, new array<string>));
			items.Insert(new DZLTraderType("Pickaxe", 60, 1000, new array<string>));
			items.Insert(new DZLTraderType("SledgeHammer", 120, 2000, new array<string>));
			items.Insert(new DZLTraderType("WoodAxe", 80, 1000, new array<string>));
			items.Insert(new DZLTraderType("FirefighterAxe", 200, 500, new array<string>));
			items.Insert(new DZLTraderType("LugWrench", 10, 40, new array<string>));
			items.Insert(new DZLTraderType("Screwdriver", 30, 250, new array<string>));
			items.Insert(new DZLTraderType("Wrench", 10, 40, new array<string>));
			items.Insert(new DZLTraderType("Pliers", 20, 140, new array<string>));
			items.Insert(new DZLTraderType("Hammer", 130, 1400, new array<string>));
			items.Insert(new DZLTraderType("Hacksaw", 130, 1400, new array<string>));
			items.Insert(new DZLTraderType("HandSaw", 130, 1400, new array<string>));
			items.Insert(new DZLTraderType("Hatchet", 130, 1600, new array<string>));
			categories.Insert(new DZLTraderCategory("Tools", items));
			
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
            
            Save();
        } else {
            foreach(DZLTraderCategory category: categories) {
                foreach(DZLTraderType _items: category.items) {
                    if (!_items.HasCorrectId()) {
                        _items.SetId();
                    }
                }
            }
            Save();
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