class DZLLicenceConfig
{
	ref array<ref DZLLicence> licences;
	ref array<ref DZLLicencePosition> positionOfLicencePoints;

	void DZLLicenceConfig() {
        if (!Load()) {
			licences = new array<ref DZLLicence>;
			licences.Insert(new DZLLicence(100, "Cement Licence", "12310 140 12633", 20, ""));
			licences.Insert(new DZLLicence(100, "Cement Licence 2", "12310 140 12633", 20, "Cement Licence"));

			positionOfLicencePoints = new array<ref DZLLicencePosition>;
            array<string> attachments = new array<string>;
            attachments.Insert("ManSuit_Black");
            attachments.Insert("SlacksPants_Black");
            attachments.Insert("ThickFramesGlasses");
            attachments.Insert("DressShoes_Black");

            positionOfLicencePoints.Insert(new DZLLicencePosition("11055.101563 226.815567 12388.920898", "0 0 0", "SurvivorM_Boris", attachments));
            positionOfLicencePoints.Insert(new DZLLicencePosition("12333.892578 140.493500 12659.409180", "0 0 0", "SurvivorM_Rolf", attachments));
			
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