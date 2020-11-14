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
                positions.Insert(new DZLTraderPosition("12336.892578 140.493500 12659.409180", "0 0 0", "SurvivorM_Boris", attachments, catNames, "12332.892578 140.493500 12659.409180"));
            } else {
                //TODO normal base config add
            }
            Save();
        }
    }

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "traderPosition.json")) {
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