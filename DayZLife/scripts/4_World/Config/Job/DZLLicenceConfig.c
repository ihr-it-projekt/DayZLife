class DZLLicenceConfig
{
	ref array<ref DZLLicence> licences;
	ref array<ref DZLLicencePosition> positionOfLicencePoints;

	void DZLLicenceConfig() {
        if (!Load()) {
			licences = new array<ref DZLLicence>;
			
			array<ref DZLLicenceCraftItem> craftItems = new array<ref DZLLicenceCraftItem>;
			craftItems.Insert(new DZLLicenceCraftItem("Stone", 1, 50));
			craftItems.Insert(new DZLLicenceCraftItem("SmallStone", 2, 50));

			array<ref DZLLicenceToolItem> toolItems = new array<ref DZLLicenceToolItem>;
			toolItems.Insert(new DZLLicenceToolItem("Bucket", 100, 10, 10));

			licences.Insert(new DZLLicence(100, "Cement Licence", "12310 140 12633", 20, "", new DZLLicenceCraftedItem("Hatchet", 2, 100), 5, toolItems, craftItems));

			positionOfLicencePoints = new array<ref DZLLicencePosition>;
            array<string> attachments = new array<string>;
            attachments.Insert("ManSuit_Black");
            attachments.Insert("SlacksPants_Black");
            attachments.Insert("ThickFramesGlasses");
            attachments.Insert("DressShoes_Black");

            positionOfLicencePoints.Insert(new DZLLicencePosition("11055.101563 226.815567 12388.920898", "0 0 0", "SurvivorM_Boris", attachments));
            positionOfLicencePoints.Insert(new DZLLicencePosition("12333.892578 140.493500 12659.409180", "0 0 0", "SurvivorM_Rolf", attachments));
			
			Save();
		} else {
		    foreach(DZLLicence licence: licences) {
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