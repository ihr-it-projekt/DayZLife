class DZLJobConfig
{
    ref array<ref DZLWorkZone> workZones;

    void DZLJobConfig() {
        if (!Load()) {
            workZones = new array<ref DZLWorkZone>;
			
            array<ref DZLHarvestItemToolRelation> harvestItemToolRelation = new array<ref DZLHarvestItemToolRelation>;
			
			// First relation
            array<string> itemsThatCanHarvest = new array<string>;
            itemsThatCanHarvest.Insert("Stone");
            itemsThatCanHarvest.Insert("SmallStone");
            itemsThatCanHarvest.Insert("SmallStone");
            itemsThatCanHarvest.Insert("SmallStone");

            array<string> itemsThatNeededForHarvest = new array<string>;
            itemsThatNeededForHarvest.Insert("Pickaxe");
            itemsThatNeededForHarvest.Insert("Sledgehammer");

            DZLHarvestItemToolRelation relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
            harvestItemToolRelation.Insert(relation);
			
			
			// Second relation
            itemsThatCanHarvest = new array<string>;
            itemsThatCanHarvest.Insert("SmallStone");

            itemsThatNeededForHarvest = new array<string>;
            itemsThatNeededForHarvest.Insert("WoodAxe");
            itemsThatNeededForHarvest.Insert("FirefighterAxe");

            relation = new DZLHarvestItemToolRelation(itemsThatCanHarvest, itemsThatNeededForHarvest);
            harvestItemToolRelation.Insert(relation);
			
            DZLWorkZone zone = new DZLWorkZone("12330 140 12666", 20, "Mining Zone", DAY_Z_LIFE_ZONE_TYPE_HARVEST_1, 10, 2, harvestItemToolRelation);
			
			workZones.Insert(zone);
			
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