class DZLTraderPositionCollection
{
    string version = "2";
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
				attachments = new array<string>;
				catNames = new array<string>;
				attachments.Insert("SlacksPants_White");
                attachments.Insert("DressShoes_White");
                attachments.Insert("ManSuit_White");
                attachments.Insert("AviatorGlasses");
				catNames.Insert("Jewelry Dealer");
                catNames.Insert("Food");
                catNames.Insert("Drinks");
				positions.Insert(new DZLTraderPosition("1361.565918 137.619003 4004.216309", "-6 0 0", "SurvivorM_Mirek", attachments, catNames, "0 0 0"));
                
				attachments = new array<string>;
				catNames = new array<string>;
				attachments.Insert("WorkingGloves_Black");
                attachments.Insert("ConstructionHelmet_Red");
                attachments.Insert("NioshFaceMask");
                attachments.Insert("JumpsuitPants_Grey");
                attachments.Insert("JumpsuitJacket_Gray");
                attachments.Insert("WorkingBoots_Brown");
				catNames.Insert("Coal Dealer");
                catNames.Insert("Food");
                catNames.Insert("Drinks");
				positions.Insert(new DZLTraderPosition("3571.295654 5.991199 2205.106201", "85 0 0", "SurvivorM_Boris", attachments, catNames, "0 0 0"));
                
				attachments = new array<string>;
				catNames = new array<string>;
				attachments.Insert("CargoPants_Beige");
                attachments.Insert("Sneakers_Black");
                attachments.Insert("Hoodie_Black");
                attachments.Insert("BaseballCap_Black");
                attachments.Insert("SportGlasses_Black");
				catNames.Insert("Money Dealer");
				positions.Insert(new DZLTraderPosition("7371.827637 4.913576 2606.656494", "15 0 0", "SurvivorM_Oliver", attachments, catNames, "0 0 0"));
                
				attachments = new array<string>;
				catNames = new array<string>;
				attachments.Insert("SlacksPants_White");
                attachments.Insert("DressShoes_White");
                attachments.Insert("ManSuit_White");
                attachments.Insert("AviatorGlasses");
				catNames.Insert("Gold Dealer");
                catNames.Insert("Food");
                catNames.Insert("Drinks");
				positions.Insert(new DZLTraderPosition("11508.634766 242.879730 5509.993652", "-174 0 0", "SurvivorM_Cyril", attachments, catNames, "0 0 0"));
                
				attachments = new array<string>;
				catNames = new array<string>;
				attachments.Insert("Jeans_Blue");
                attachments.Insert("Shirt_BlueCheck");
                attachments.Insert("ConstructionHelmet_Red");
                attachments.Insert("WorkingBoots_Yellow");
                attachments.Insert("WorkingGloves_Yellow");
				catNames.Insert("Cement Dealer");
                catNames.Insert("Food");
                catNames.Insert("Drinks");
				positions.Insert(new DZLTraderPosition("13088.675781 7.193148 7145.185547", "93 0 0", "SurvivorM_Manua", attachments, catNames, "0 0 0"));
                
				attachments = new array<string>;
				catNames = new array<string>;
				attachments.Insert("Jeans_Black");
                attachments.Insert("TShirt_Black");
                attachments.Insert("WorkingGloves_Black");
                attachments.Insert("WorkingBoots_Grey");
                attachments.Insert("ConstructionHelmet_Blue");
				catNames.Insert("Copper Dealer");
				catNames.Insert("Iron Dealer");
                catNames.Insert("Food");
                catNames.Insert("Drinks");
				positions.Insert(new DZLTraderPosition("9736.766602 298.949829 8868.407227", "-58 0 0", "SurvivorM_Kaito", attachments, catNames, "0 0 0"));
                
				attachments = new array<string>;
				catNames = new array<string>;
				attachments.Insert("CargoPants_Grey");
                attachments.Insert("Shirt_WhiteCheck");
                attachments.Insert("WorkingBoots_Beige");
				catNames.Insert("Paper and Wood Dealer");
                catNames.Insert("Food");
                catNames.Insert("Drinks");
				positions.Insert(new DZLTraderPosition("6337.460938 301.036987 7681.634766", "165 0 0", "SurvivorM_Rolf", attachments, catNames, "0 0 0"));
                
				attachments = new array<string>;
				catNames = new array<string>;
				attachments.Insert("Jeans_Black");
                attachments.Insert("Sneakers_Black");
                attachments.Insert("Hoodie_Black");
                attachments.Insert("SportGlasses_Blue");
                attachments.Insert("RadarCap_Black");
                attachments.Insert("Bandana_RedPattern");
                attachments.Insert("FNX45");
				catNames.Insert("Drug Dealer");
                catNames.Insert("Food");
                catNames.Insert("Drinks");
				positions.Insert(new DZLTraderPosition("14298.921875 3.697711 13301.237305", "170 0 0", "SurvivorM_Taiki", attachments, catNames, "0 0 0"));
                
				attachments = new array<string>;
				catNames = new array<string>;
				attachments.Insert("ManSuit_Black");
                attachments.Insert("SlacksPants_Black");
                attachments.Insert("ThickFramesGlasses");
                attachments.Insert("DressShoes_Black");
                catNames.Insert("Clothing");
                catNames.Insert("Medic");
                catNames.Insert("Tools");
                catNames.Insert("Food");
                catNames.Insert("Meat");
                catNames.Insert("Drinks");
                catNames.Insert("Weapons");
                catNames.Insert("Magazines");
                catNames.Insert("Ammo");
                catNames.Insert("Cars");
				positions.Insert(new DZLTraderPosition("6573.415527 5.991199 2453.483154", "-25 0 0", "SurvivorM_Rolf", attachments, catNames, "6577.331543 6.198332 2469.446777"));
                
            }

            Save();
        }

        if (version == "1") {
            version = "2";
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
