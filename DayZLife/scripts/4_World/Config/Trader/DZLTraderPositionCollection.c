class DZLTraderPositionCollection
{
    ref array<ref DZLTraderPosition> positions;

    void DZLTraderPositionCollection() {
        if (!Load()){
            positions = new array<ref DZLTraderPosition>;
            array<string> catNames = new array<string>;
            array<string> attachments = new array<string>;


            if (DAY_Z_LIFE_DEBUG) {
                attachments.Insert("ManSuit_Black");
                attachments.Insert("SlacksPants_Black");
                attachments.Insert("ThickFramesGlasses");
                attachments.Insert("DressShoes_Black");

                catNames.Insert("Weapons");
                catNames.Insert("Cars");
                positions.Insert(new DZLTraderPosition("4660.000000 339.282990 10325.000000", "0 0 0", "SurvivorM_Boris", attachments, catNames, "4634.000000 338.049988 10319.981445"));
            } else {
                //TODO normal base config add
            }
            Save();
        }
    }

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "traderPositions.json")) {
            JsonFileLoader<DZLTraderPositionCollection>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "traderPositions.json", this);
            return true;
        }
        return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
            CheckDZLConfigPath();
            JsonFileLoader<DZLTraderPositionCollection>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "traderPositions.json", this);
        }
    }


}