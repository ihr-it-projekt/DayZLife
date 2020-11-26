class DZLTraderPositionCollection
{
    ref array<ref DZLTraderPosition> positions;
    string version = "1";

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

                catNames.Insert("Tools");
                catNames.Insert("Food");
                catNames.Insert("Meat");
                catNames.Insert("Drinks");
                catNames.Insert("Weapons");
                catNames.Insert("Magazines");
                catNames.Insert("Ammo");
                catNames.Insert("Ore");
                catNames.Insert("Cars");
                positions.Insert(new DZLTraderPosition("4660.000000 339.282990 10325.000000", "0 0 0", "SurvivorM_Boris", attachments, catNames, "4634.000000 338.049988 10319.981445"));
            } else {
                //TODO normal base config add
				attachments.Insert("ManSuit_Black");
                attachments.Insert("SlacksPants_Black");
                attachments.Insert("ThickFramesGlasses");
                attachments.Insert("DressShoes_Black");
				catNames.Insert("Diamond Dealer");
                catNames.Insert("Tools");
                catNames.Insert("Food");
                catNames.Insert("Drinks");
				positions.Insert(new DZLTraderPosition("1132.489258 6.120775 2438.399658", "0 0 0", "SurvivorM_Boris", attachments, catNames, "0 0 0"));
                
				attachments.Insert("ManSuit_Black");
                attachments.Insert("SlacksPants_Black");
                attachments.Insert("ThickFramesGlasses");
                attachments.Insert("DressShoes_Black");
				catNames.Insert("Coal Dealer");
                catNames.Insert("Tools");
                catNames.Insert("Food");
                catNames.Insert("Drinks");
				positions.Insert(new DZLTraderPosition("3583.166016 6.589246 2159.920654", "0 0 0", "SurvivorM_Boris", attachments, catNames, "0 0 0"));
                
				attachments.Insert("ManSuit_Black");
                attachments.Insert("SlacksPants_Black");
                attachments.Insert("ThickFramesGlasses");
                attachments.Insert("DressShoes_Black");
				catNames.Insert("Money Dealer");
                catNames.Insert("Tools");
                catNames.Insert("Food");
                catNames.Insert("Drinks");
				positions.Insert(new DZLTraderPosition("7488.084961 6.141221 2549.512451", "0 0 0", "SurvivorM_Boris", attachments, catNames, "0 0 0"));
                
				attachments.Insert("ManSuit_Black");
                attachments.Insert("SlacksPants_Black");
                attachments.Insert("ThickFramesGlasses");
                attachments.Insert("DressShoes_Black");
				catNames.Insert("Gold Dealer");
                catNames.Insert("Tools");
                catNames.Insert("Food");
                catNames.Insert("Drinks");
				positions.Insert(new DZLTraderPosition("11516.401367 243.029510 5495.224121", "0 0 0", "SurvivorM_Boris", attachments, catNames, "0 0 0"));
                
				attachments.Insert("ManSuit_Black");
                attachments.Insert("SlacksPants_Black");
                attachments.Insert("ThickFramesGlasses");
                attachments.Insert("DressShoes_Black");
				catNames.Insert("Cement Dealer");
                catNames.Insert("Tools");
                catNames.Insert("Food");
                catNames.Insert("Drinks");
				positions.Insert(new DZLTraderPosition("12965.688477 6.607363 9963.276367", "0 0 0", "SurvivorM_Boris", attachments, catNames, "0 0 0"));
                
				attachments.Insert("ManSuit_Black");
                attachments.Insert("SlacksPants_Black");
                attachments.Insert("ThickFramesGlasses");
                attachments.Insert("DressShoes_Black");
				catNames.Insert("Paper Dealer");
                catNames.Insert("Tools");
                catNames.Insert("Food");
                catNames.Insert("Drinks");
				positions.Insert(new DZLTraderPosition("6937.043457 297.071442 7685.254883", "0 0 0", "SurvivorM_Boris", attachments, catNames, "0 0 0"));
                
				attachments.Insert("ManSuit_Black");
                attachments.Insert("SlacksPants_Black");
                attachments.Insert("ThickFramesGlasses");
                attachments.Insert("DressShoes_Black");
				catNames.Insert("Copper Dealer");
				catNames.Insert("Iron Dealer");
                catNames.Insert("Tools");
                catNames.Insert("Food");
                catNames.Insert("Drinks");
				positions.Insert(new DZLTraderPosition("8178.198242 474.629242 9111.838867", "0 0 0", "SurvivorM_Boris", attachments, catNames, "0 0 0"));
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