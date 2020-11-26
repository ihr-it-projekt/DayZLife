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
				craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Stone", 2, 50));
                toolItems.collection.Insert(new DZLLicenceToolItem("Sledgehammer", 1, 10));
                licences.collection.Insert(new DZLLicence(109, 100, "Cement Licence", "7999 117 12616", 5, "", new DZLLicenceCraftedItem("DZL_Cement", 1, 100), 5, toolItems, craftItems));
                craftItems = new DZLLicenceCraftItemCollection;
                toolItems = new DZLLicenceToolItemCollection;
				
				craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Ore_Coal", 2, 50));
                craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Ore_Copper", 1, 10));
                licences.collection.Insert(new DZLLicence(109, 100, "Copper Licence", "2876 215 12606", 5, "", new DZLLicenceCraftedItem("DZL_Copper", 1, 100), 5, toolItems, craftItems));
                craftItems = new DZLLicenceCraftItemCollection;
				
				craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Ore_Coal", 2, 50));
                craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Ore_Iron", 1, 10));
                licences.collection.Insert(new DZLLicence(109, 100, "Iron Licence", "7695 6 3193", 5, "Copper Licence", new DZLLicenceCraftedItem("DZL_Iron", 1, 100), 5, toolItems, craftItems));
                craftItems = new DZLLicenceCraftItemCollection;
				
				craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Ore_Coal", 2, 50));
                craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Ore_Gold", 1, 10));
                licences.collection.Insert(new DZLLicence(109, 100, "Gold Licence", "4207 324 8963", 5, "Iron Licence", new DZLLicenceCraftedItem("DZL_Gold", 1, 100), 5, toolItems, craftItems));
                craftItems = new DZLLicenceCraftItemCollection;
				
				craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Sandpaper", 2, 50));
                craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Ore_Diamond", 1, 10));
                licences.collection.Insert(new DZLLicence(109, 100, "Diamond Licence", "7081 355 14572", 5, "Gold Licence", new DZLLicenceCraftedItem("DZL_Diamond", 1, 100), 5, toolItems, craftItems));
                craftItems = new DZLLicenceCraftItemCollection;
				
				craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Gold", 2, 10));
                craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Iron", 1, 10));
                craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Diamond", 1, 10));
                toolItems.collection.Insert(new DZLLicenceToolItem("Pliers", 1, 10));
                licences.collection.Insert(new DZLLicence(109, 100, "Jewelry Licence", "7306 263 7053", 5, "Diamond Licence", new DZLLicenceCraftedItem("DZL_Jewelry", 1, 100), 5, toolItems, craftItems));
                craftItems = new DZLLicenceCraftItemCollection;
                toolItems = new DZLLicenceToolItemCollection;
				
				craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_WoodenLog", 1, 50));
                toolItems.collection.Insert(new DZLLicenceToolItem("Hacksaw", 1, 10));
                licences.collection.Insert(new DZLLicence(109, 100, "Woodplank Licence", "5721 474 15228", 5, "", new DZLLicenceCraftedItem("DZL_WoodenPlank", 2, 100), 5, toolItems, craftItems));
                craftItems = new DZLLicenceCraftItemCollection;
                toolItems = new DZLLicenceToolItemCollection;
				
				craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_WoodenPlank", 1, 50));
                toolItems.collection.Insert(new DZLLicenceToolItem("Hacksaw", 1, 10));
                licences.collection.Insert(new DZLLicence(109, 100, "Papier Licence", "12905 7 6263", 5, "Woodplank Licence", new DZLLicenceCraftedItem("DZL_Paper", 5, 100), 5, toolItems, craftItems));
                craftItems = new DZLLicenceCraftItemCollection;
                toolItems = new DZLLicenceToolItemCollection;
				
				craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Paper", 10, 50));
				craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Color", 1, 50));
                licences.collection.Insert(new DZLLicence(109, 100, "Falschgeld Licence", "8884 222 11661", 5, "Papier Licence", new DZLLicenceCraftedItem("DZL_Money", 5, 100), 5, toolItems, craftItems));
                craftItems = new DZLLicenceCraftItemCollection;
				
                // Position of licence dealer
                positionOfLicencePoints.Insert(new DZLLicencePosition("4660.000000 339.282990 10315.000000", "0 0 0", "SurvivorM_Boris", attachments));
                // end position
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