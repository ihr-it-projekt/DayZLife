class DZLTraderCategoryCollection
{
     ref array<ref DZLTraderCategory> categories;

     void DZLTraderCategoryCollection() {
        if (!Load()){
            categories = new array<ref DZLTraderCategory>;
            array<ref DZLTraderType> items = new array<ref DZLTraderType>;

            DZLTraderType type = new DZLTraderType("Crowbar", 200, 500, new array<string>);
			categories.Insert(new DZLTraderCategory("Weapons", items));
			
			array<string> attachments = new array<string>;
			attachments.Insert("Sedan_02_Door_1_2");
			
            type = new DZLTraderType("Sedan_02", 200, 500, attachments, false);
			items = new array<ref DZLTraderType>;
            items.Insert(type);
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