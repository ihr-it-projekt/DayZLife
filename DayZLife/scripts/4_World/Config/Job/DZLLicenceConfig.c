class DZLLicenceConfig
{
	string version = "4";
	ref DZLLicenceCollection licences;
	ref DZLLicenceCraftingCollection licenceCollection;
	ref array<ref DZLLicencePosition> positionOfLicencePoints;

	void DZLLicenceConfig() {
        if (!Load()) {
            licences = new DZLLicenceCollection;
            licenceCollection = new DZLLicenceCraftingCollection;
            positionOfLicencePoints = new array<ref DZLLicencePosition>;

            DZLLicenceCraftItemCollection craftItems = new DZLLicenceCraftItemCollection;
            DZLLicenceToolItemCollection toolItems = new DZLLicenceToolItemCollection;


            if (DAY_Z_LIFE_DEBUG) {
                // Start Crafting
                craftItems.collection.Insert(new DZLLicenceCraftItem("SmallStone", 2, 50));
                toolItems.collection.Insert(new DZLLicenceToolItem("Sledgehammer", 1, 10));
                licenceCollection.collection.Insert(new DZLCraftLicence(100, "Cement Licence", "4620.000000 339.609009 10340.000000", "", new DZLLicenceCraftedItem("DZL_Cement", 1, 100), 5, toolItems, craftItems));
                craftItems = new DZLLicenceCraftItemCollection;
                toolItems = new DZLLicenceToolItemCollection;
				
                craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Ore_Copper", 1, 50));
                craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Ore_Coal", 1, 50));
                licenceCollection.collection.Insert(new DZLCraftLicence(100, "Copper Licence", "4640.000000 339.609009 10340.000000", "", new DZLLicenceCraftedItem("DZL_Copper", 1, 100), 5, toolItems, craftItems));
                craftItems = new DZLLicenceCraftItemCollection;
				
				craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Ore_Iron", 1, 50));
                craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Ore_Coal", 2, 50));
                licenceCollection.collection.Insert(new DZLCraftLicence(100, "Iron Licence", "4650.000000 339.609009 10340.000000", "", new DZLLicenceCraftedItem("DZL_Iron", 1, 100), 5, toolItems, craftItems));
                craftItems = new DZLLicenceCraftItemCollection;
				
				craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Ore_Gold", 1, 50));
                craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Ore_Coal", 3, 50));
                licenceCollection.collection.Insert(new DZLCraftLicence(100, "Gold Licence", "4670.000000 339.609009 10340.000000", "", new DZLLicenceCraftedItem("DZL_Gold", 1, 100), 5, toolItems, craftItems));
                craftItems = new DZLLicenceCraftItemCollection;
				
				craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Ore_Diamond", 2, 50));
                licenceCollection.collection.Insert(new DZLCraftLicence(100, "Diamond Licence", "4680.000000 339.609009 10340.000000", "", new DZLLicenceCraftedItem("DZL_Diamond", 1, 100), 5, toolItems, craftItems));
				// End Crafting
                // Position of licence dealer
                positionOfLicencePoints.Insert(new DZLLicencePosition("6601.938965 9.378500 2424.097168", "131.999954 0 0"));
                // end position

            } else {
				craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Stone", 2, 50));
                toolItems.collection.Insert(new DZLLicenceToolItem("Sledgehammer", 1, 10));
                licenceCollection.collection.Insert(new DZLCraftLicence(100, "Cement Licence", "7996.683594 117.331841 12620.922852", "", new DZLLicenceCraftedItem("DZL_Cement", 1, 100), 5, toolItems, craftItems));
                craftItems = new DZLLicenceCraftItemCollection;
                toolItems = new DZLLicenceToolItemCollection;
				
				craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Ore_Coal", 2, 50));
                craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Ore_Copper", 1, 10));
                licenceCollection.collection.Insert(new DZLCraftLicence(150, "Copper Licence", "2876.725830 215.348999 12604.768555", "", new DZLLicenceCraftedItem("DZL_Copper", 1, 100), 5, toolItems, craftItems));
                craftItems = new DZLLicenceCraftItemCollection;
				
				craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Ore_Coal", 2, 50));
                craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Ore_Iron", 1, 10));
                licenceCollection.collection.Insert(new DZLCraftLicence(150, "Iron Licence", "7235.813965 6.100000 3231.249268", "Copper Licence", new DZLLicenceCraftedItem("DZL_Iron", 1, 100), 5, toolItems, craftItems));
                craftItems = new DZLLicenceCraftItemCollection;
				
				craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Ore_Coal", 2, 50));
                craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Ore_Gold", 1, 10));
                licenceCollection.collection.Insert(new DZLCraftLicence(150, "Gold Licence", "4112.656738 324.450012 8913.142578", "Iron Licence", new DZLLicenceCraftedItem("DZL_Gold", 1, 100), 5, toolItems, craftItems));
                craftItems = new DZLLicenceCraftItemCollection;
				
				craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Sandpaper", 2, 50));
                craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Ore_Diamond", 1, 10));
                licenceCollection.collection.Insert(new DZLCraftLicence(150, "Diamond Licence", "7080.515625 355.850006 14572.783203", "Gold Licence", new DZLLicenceCraftedItem("DZL_Diamond_Polished", 1, 100), 5, toolItems, craftItems));
                craftItems = new DZLLicenceCraftItemCollection;
				
				craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Gold", 2, 10));
                craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Iron", 1, 10));
                craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Diamond_Polished", 1, 10));
                toolItems.collection.Insert(new DZLLicenceToolItem("Pliers", 1, 10));
                licenceCollection.collection.Insert(new DZLCraftLicence(150, "Jewelry Licence", "5071.761719 175.170273 13092.766602", "Diamond Licence", new DZLLicenceCraftedItem("DZL_Jewelry", 1, 100), 5, toolItems, craftItems));
                craftItems = new DZLLicenceCraftItemCollection;
                toolItems = new DZLLicenceToolItemCollection;
				
				craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_WoodenLog", 1, 50));
                toolItems.collection.Insert(new DZLLicenceToolItem("HandSaw", 1, 10));
                licenceCollection.collection.Insert(new DZLCraftLicence(150, "Woodplank Licence", "5783.562988 474.809998 15207.916016", "", new DZLLicenceCraftedItem("DZL_WoodenPlank", 2, 100), 5, toolItems, craftItems));
                craftItems = new DZLLicenceCraftItemCollection;
                toolItems = new DZLLicenceToolItemCollection;
				
				craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_WoodenPlank", 1, 50));
                toolItems.collection.Insert(new DZLLicenceToolItem("HandSaw", 1, 10));
                licenceCollection.collection.Insert(new DZLCraftLicence(150, "Papier Licence", "12906.038086 7.482306 6262.768555", "Woodplank Licence", new DZLLicenceCraftedItem("DZL_Paper", 2, 100), 5, toolItems, craftItems));
                craftItems = new DZLLicenceCraftItemCollection;
                toolItems = new DZLLicenceToolItemCollection;
				
				craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Paper", 5, 50));
				craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Color", 1, 50));
                toolItems.collection.Insert(new DZLLicenceToolItem("Pen_Black", 1, 10));
                licenceCollection.collection.Insert(new DZLCraftLicence(150, "Falschgeld Licence", "8886.539063 221.465805 11661.134766", "Papier Licence", new DZLLicenceCraftedItem("DZL_Money", 5, 100), 5, toolItems, craftItems));
                craftItems = new DZLLicenceCraftItemCollection;
                toolItems = new DZLLicenceToolItemCollection;
				
				craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Cannabis", 10, 50));
                toolItems.collection.Insert(new DZLLicenceToolItem("DuctTape", 1, 10));
                licenceCollection.collection.Insert(new DZLCraftLicence(150, "Cannabis Licence", "10241.296875 237.953644 5052.820313", "", new DZLLicenceCraftedItem("DZL_Cannabis_Brick", 5, 100), 5, toolItems, craftItems));
                craftItems = new DZLLicenceCraftItemCollection;
                toolItems = new DZLLicenceToolItemCollection;
				
				craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Cocaine", 10, 50));
                toolItems.collection.Insert(new DZLLicenceToolItem("DuctTape", 1, 10));
                licenceCollection.collection.Insert(new DZLCraftLicence(150, "Cocaine Licence", "3691.775635 402.000000 5972.513672", "", new DZLLicenceCraftedItem("DZL_Cocaine_Brick", 5, 100), 5, toolItems, craftItems));
                craftItems = new DZLLicenceCraftItemCollection;
                toolItems = new DZLLicenceToolItemCollection;
				
				craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Oil_Barrel", 1, 50));
                toolItems.collection.Insert(new DZLLicenceToolItem("FieldShovel", 1, 10));
                licenceCollection.collection.Insert(new DZLCraftLicence(150, "Oil Licence", "11809.800781 27.400000 14259.675781", "", new DZLLicenceCraftedItem("DZL_Oil", 2, 100), 5, toolItems, craftItems));
                craftItems = new DZLLicenceCraftItemCollection;
                toolItems = new DZLLicenceToolItemCollection;
				
				craftItems.collection.Insert(new DZLLicenceCraftItem("DZL_Oil_Barrel", 2, 50));
                toolItems.collection.Insert(new DZLLicenceToolItem("FieldShovel", 1, 10));
                licenceCollection.collection.Insert(new DZLCraftLicence(150, "Plastik Licence", "12845.079102 5.980000 9919.536133", "Oil Licence", new DZLLicenceCraftedItem("DZL_Stone", 1, 100), 5, toolItems, craftItems));

                // Position of licence dealer
                positionOfLicencePoints.Insert(new DZLLicencePosition("6601.938965 9.378500 2424.097168", "131.999954 0 0"));
                // end position
            }
			
			Save();
		}

		if(licences.collection) {
		    foreach(DZLLicence licence: licences.collection) {
		        if (!licence.HasCorrectId()) {
                    licence.SetId();
		        }
		    }
            Save();
		}

		if(licenceCollection.collection) {
		    foreach(DZLCraftLicence licenceCraft: licenceCollection.collection) {
		        if (!licenceCraft.HasCorrectId()) {
                    licenceCraft.SetId();
		        }
		    }
            Save();
		}

        if (version == "1") {
            version = "2";
            Save();
        }

        if (version == "2") {
            version = "3";
            licenceCollection = new DZLLicenceCraftingCollection;
            foreach(DZLLicence _l: licences.collection) {
                DZLCraftLicence craftLicence = new DZLCraftLicence(_l.price, _l.name, _l.position, _l.dependencyLicence, _l.craftedItem, _l.durationForCrafting, _l.toolItems, _l.craftItems);
                craftLicence.SetId(_l.GetId());
                licenceCollection.collection.Insert(craftLicence);
            }
            licences = null;
            Save();
        }

        if (version == "3") {
            version = "4";
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
