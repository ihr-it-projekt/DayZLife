class DZLLicenceConfig
{
	ref DZLLicenceCollection licences;
	ref array<ref DZLLicencePosition> positionOfLicencePoints;
	string version = "1";

	void DZLLicenceConfig() {
        if (!Load()) {
            licences = new DZLLicenceCollection;
            positionOfLicencePoints = new array<ref DZLLicencePosition>;

            DZLLicenceCraftItemCollection craftItems = new DZLLicenceCraftItemCollection;
            DZLLicenceToolItemCollection toolItems = new DZLLicenceToolItemCollection;

            array<string> attachments = new array<string>;
            attachments.Insert("ManSuit_Black");
            attachments.Insert("SlacksPants_Black");
            attachments.Insert("ThickFramesGlasses");
            attachments.Insert("DressShoes_Black");

            if (DAY_Z_LIFE_DEBUG) {
                // Start Crafting
                craftItems.collection.Insert(new DZLLicenceCraftItem("SmallStone", 2, 50));
                toolItems.collection.Insert(new DZLLicenceToolItem("Sledgehammer", 1, 10));
                licences.collection.Insert(new DZLLicence(109, 100, "Cement Licence", "4620.000000 339.609009 10340.000000", 5, "", new DZLLicenceCraftedItem("DZL_Cement", 1, 100), 5, toolItems, craftItems));
                craftItems = new DZLLicenceCraftItemCollection;
                toolItems = new DZLLicenceToolItemCollection;
				
                craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Ore_Copper", 1, 50));
                craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Ore_Coal", 1, 50));
                licences.collection.Insert(new DZLLicence(109, 100, "Copper Licence", "4640.000000 339.609009 10340.000000", 5, "", new DZLLicenceCraftedItem("DZL_Copper", 1, 100), 5, toolItems, craftItems));
                craftItems = new DZLLicenceCraftItemCollection;
				
				craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Ore_Iron", 1, 50));
                craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Ore_Coal", 2, 50));
                licences.collection.Insert(new DZLLicence(109, 100, "Iron Licence", "4650.000000 339.609009 10340.000000", 5, "", new DZLLicenceCraftedItem("DZL_Iron", 1, 100), 5, toolItems, craftItems));
                craftItems = new DZLLicenceCraftItemCollection;
				
				craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Ore_Gold", 1, 50));
                craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Ore_Coal", 3, 50));
                licences.collection.Insert(new DZLLicence(109, 100, "Gold Licence", "4670.000000 339.609009 10340.000000", 5, "", new DZLLicenceCraftedItem("DZL_Gold", 1, 100), 5, toolItems, craftItems));
                craftItems = new DZLLicenceCraftItemCollection;
				
				craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Ore_Diamond", 2, 50));
                licences.collection.Insert(new DZLLicence(109, 100, "", "4680.000000 339.609009 10340.000000", 5, "Diamond Licence", new DZLLicenceCraftedItem("DZL_Diamond", 1, 100), 5, toolItems, craftItems));
                craftItems = new DZLLicenceCraftItemCollection;
				// End Crafting
                // Position of licence dealer
                positionOfLicencePoints.Insert(new DZLLicencePosition("4660.000000 339.282990 10315.000000", "0 0 0", "SurvivorM_Boris", attachments));
                // end position

            } else {
                //default config
            }
			
			Save();
		} else {
		    foreach(DZLLicence licence: licences.collection) {
		        if (!licence.HasCorrectId()) {
                    licence.SetId();
		        }
		    }
            Save();
		}
	}
	
	private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "licence.json")) {
            JsonFileLoader<DZLLicenceConfig>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "licence.json", this);
            return true;
        }
        return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
            CheckDZLConfigPath();
            JsonFileLoader<DZLLicenceConfig>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "licence.json", this);
        }
    }

}