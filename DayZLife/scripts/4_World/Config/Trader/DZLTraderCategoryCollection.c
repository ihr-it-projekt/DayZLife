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
            items.Insert(new DZLTraderType("OffroadHatchback", 25000, 60000, attachments, false));
			
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
            items.Insert(new DZLTraderType("Hatchback_02", 20000, 50000, attachments, false));
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