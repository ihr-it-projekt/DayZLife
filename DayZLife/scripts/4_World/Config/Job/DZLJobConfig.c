class DZLJobConfig
{
    ref array<ref DZLWorkZone> workZones;

    void DZLJobConfig() {
        if (!Load()) {
            workZones = new array<ref DZLWorkZone>;
            array<ref DZLHarvestItemToolRelation> harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;
            array<string> itemsThatCanHarvest = new array<string>;
            array<string> itemsThatNeededForHarvest = new array<string>;


			if (DAY_Z_LIFE_DEBUG) {
			    //first zone
                // First harvest
                itemsThatCanHarvest.Insert("Stone");
                itemsThatCanHarvest.Insert("SmallStone");
                itemsThatCanHarvest.Insert("SmallStone");
                itemsThatCanHarvest.Insert("SmallStone");

                itemsThatNeededForHarvest.Insert("Pickaxe");
                itemsThatNeededForHarvest.Insert("Sledgehammer");

                DZLHarvestItemToolRelation relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);

                harvestItemToolRelation.Insert(relation);
                // End First harvest
                // Second harvest
                itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;

                itemsThatCanHarvest.Insert("SmallStone");

                itemsThatNeededForHarvest.Insert("WoodAxe");
                itemsThatNeededForHarvest.Insert("FirefighterAxe");

                relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
                harvestItemToolRelation.Insert(relation);

                // end Second harvest

                DZLWorkZone zone = new DZLWorkZone("12330 140 12666", 20, "Mining Zone", 10, 2, harvestItemToolRelation);
                workZones.Insert(zone);
                //end first zone
                // start second zone
                itemsThatCanHarvest = new array<string>;
                itemsThatNeededForHarvest = new array<string>;
                harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>

                itemsThatCanHarvest.Insert("Stone");
                itemsThatCanHarvest.Insert("SmallStone");
                itemsThatCanHarvest.Insert("SmallStone");
                itemsThatCanHarvest.Insert("SmallStone");

                itemsThatNeededForHarvest.Insert("Pickaxe");
                itemsThatNeededForHarvest.Insert("Sledgehammer");

                relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);

                harvestItemToolRelation.Insert(relation);

                zone = new DZLWorkZone("12330 140 12666", 20, "Mining Zone", 10, 2, harvestItemToolRelation);
                workZones.Insert(zone);
                // end second zone
            } else {
             // add life config;
            }


			
		    Save();
        }
    }

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "workZone.json")) {
            JsonFileLoader<DZLJobConfig>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "workZone.json", this);
            return true;
        }
        return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
            CheckDZLConfigPath();
            JsonFileLoader<DZLJobConfig>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "workZone.json", this);
        }
    }
}