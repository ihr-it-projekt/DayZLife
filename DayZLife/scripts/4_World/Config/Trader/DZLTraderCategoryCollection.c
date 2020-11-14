class DZLTraderCategoryCollection
{
     ref array<ref DZLTraderCategory> categories;

     void DZLTraderConfigParams(string name) {
        if (!Load()){
            categories = new array<ref DZLTraderCategory>;

            array<ref DZLTraderType> items = new array<ref DZLTraderType>;

            DZLTraderType type = new DZLTraderType("Crowbar", 200, 500);
            items.Insert(type);

            DZLTraderCategory category = new DZLTraderCategory("Weapons", items);

            categories.Insert(new DZLTraderCategory("Weapons", items));
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