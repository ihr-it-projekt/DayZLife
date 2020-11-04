class DZLLicenceConfig
{
	ref DZLLicenceCollection licences;
	ref array<ref DZLLicencePosition> positionOfLicencePoints;

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
                // Crafting
                // start first licence
                craftItems.collection.Insert(new DZLLicenceCraftItem("Stone", 1, 50));
                craftItems.collection.Insert(new DZLLicenceCraftItem("SmallStone", 2, 50));
                toolItems.collection.Insert(new DZLLicenceToolItem("Sledgehammer", 1, 10));
                licences.collection.Insert(new DZLLicence(109, 100, "Cement Licence", "12310 140 12633", 20, "", new DZLLicenceCraftedItem("Hatchet", 1, 100), 5, toolItems, craftItems));
                // end first licence
                // start second licence
                craftItems = new DZLLicenceCraftItemCollection;
                toolItems = new DZLLicenceToolItemCollection;

                craftItems.collection.Insert(new DZLLicenceCraftItem("Stone", 1, 50));
                craftItems.collection.Insert(new DZLLicenceCraftItem("SmallStone", 2, 50));
                toolItems.collection.Insert(new DZLLicenceToolItem("Sledgehammer", 1, 10));
                licences.collection.Insert(new DZLLicence(109, 100, "Cement Licence 2", "12310 140 12633", 20, "Cement Licence", new DZLLicenceCraftedItem("Hatchet", 1, 100), 5, toolItems, craftItems));
                // end second license
                // Position of licence dealer

                positionOfLicencePoints.Insert(new DZLLicencePosition("11055.101563 226.815567 12388.920898", "0 0 0", "SurvivorM_Boris", attachments));
                positionOfLicencePoints.Insert(new DZLLicencePosition("12333.892578 140.493500 12659.409180", "0 0 0", "SurvivorM_Rolf", attachments));
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