class DZLArrestConfig
{
	string version = "1";

	bool shouldDeleteAllItemsOnPrissoner = true;
	bool shouldDeleteAllItemsOnExPrissoner = true;
	ref array<string> prisonerItems;
	ref array<string> exPrisonerItems;
	ref array<vector> arrestAreas;
	ref array<vector> exPrisonerAreas;
	int arrestAreaRadius = 110;

    void DZLArrestConfig() {
        if (!Load()) {
            prisonerItems = new array<string>;
            prisonerItems.Insert("Pickaxe");
            prisonerItems.Insert("PrisonerCap");
            prisonerItems.Insert("PrisonUniformPants");
            prisonerItems.Insert("PrisonUniformJacket");
            prisonerItems.Insert("AthleticShoes_Black");
            prisonerItems.Insert("SodaCan_Cola");
            prisonerItems.Insert("SodaCan_Cola");
            prisonerItems.Insert("TunaCan");
            prisonerItems.Insert("TunaCan");

            exPrisonerItems = new array<string>;
            exPrisonerItems.Insert("CanvasPants_Blue");
            exPrisonerItems.Insert("TShirt_RedBlackStripes");
            exPrisonerItems.Insert("AthleticShoes_Brown");
            exPrisonerItems.Insert("SodaCan_Kvass");
            exPrisonerItems.Insert("SodaCan_Kvass");
            exPrisonerItems.Insert("TunaCan");
            exPrisonerItems.Insert("TunaCan");

            arrestAreas = new array<vector>;
			arrestAreas.Insert("2746.173340 26.421398 1301.691162");

            exPrisonerAreas = new array<vector>;
			exPrisonerAreas.Insert("3662.574219 6.720572 2396.926514");

            Save();
        }
    }

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "arrest.json")) {
            JsonFileLoader<DZLArrestConfig>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "arrest.json", this);
            return true;
        }
        return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
            CheckDZLConfigPath();
            JsonFileLoader<DZLArrestConfig>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "arrest.json", this);
        }
    }
}
