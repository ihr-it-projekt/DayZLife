class DZLTraderPositionCollection
{
    string version = "2";
    ref array<ref DZLTraderPosition> positions;

    void DZLTraderPositionCollection() {
        if (!Load()){
            positions = new array<ref DZLTraderPosition>;
            array<string> catNames = new array<string>;

            if (DAY_Z_LIFE_DEBUG) {

                catNames.Insert("Tools");
                catNames.Insert("Food");
                catNames.Insert("Meat");
                catNames.Insert("Drinks");
                catNames.Insert("Weapons");
                catNames.Insert("Magazines");
                catNames.Insert("Ammo");
                catNames.Insert("Ore");
                catNames.Insert("Cars");
                positions.Insert(new DZLTraderPosition("6596.131348 8.982534 2423.773682", "-137.999985 0 0", "DZL_Trader", catNames, "6590.140625 5.810940 2441.690674"));
            } else {
                //TODO normal base config add
				catNames = new array<string>;
				catNames.Insert("Jewelry Dealer");
                catNames.Insert("Food");
                catNames.Insert("Drinks");
				positions.Insert(new DZLTraderPosition("1361.565918 137.619003 4004.216309", "-6 0 0", "DZL_Trader", catNames, "0 0 0"));
                
				catNames = new array<string>;
				catNames.Insert("Coal Dealer");
                catNames.Insert("Food");
                catNames.Insert("Drinks");
				positions.Insert(new DZLTraderPosition("3571.295654 5.991199 2205.106201", "85 0 0", "DZL_Trader", catNames, "0 0 0"));
                
				catNames = new array<string>;
				catNames.Insert("Money Dealer");
				positions.Insert(new DZLTraderPosition("7371.827637 4.913576 2606.656494", "15 0 0", "DZL_Trader", catNames, "0 0 0"));
                
				catNames = new array<string>;
				catNames.Insert("Gold Dealer");
                catNames.Insert("Food");
                catNames.Insert("Drinks");
				positions.Insert(new DZLTraderPosition("11508.634766 242.879730 5509.993652", "-174 0 0", "DZL_Trader", catNames, "0 0 0"));
                
				catNames = new array<string>;
				catNames.Insert("Cement Dealer");
                catNames.Insert("Food");
                catNames.Insert("Drinks");
				positions.Insert(new DZLTraderPosition("13088.675781 7.193148 7145.185547", "93 0 0", "DZL_Trader", catNames, "0 0 0"));
                
				catNames = new array<string>;
				catNames.Insert("Copper Dealer");
				catNames.Insert("Iron Dealer");
                catNames.Insert("Food");
                catNames.Insert("Drinks");
				positions.Insert(new DZLTraderPosition("9736.766602 298.949829 8868.407227", "-58 0 0", "DZL_Trader", catNames, "0 0 0"));
                
				catNames = new array<string>;
				catNames.Insert("Paper and Wood Dealer");
                catNames.Insert("Food");
                catNames.Insert("Drinks");
				positions.Insert(new DZLTraderPosition("6337.460938 301.036987 7681.634766", "165 0 0", "DZL_Trader", catNames, "0 0 0"));
                
				catNames = new array<string>;
				catNames.Insert("Drug Dealer");
                catNames.Insert("Food");
                catNames.Insert("Drinks");
				positions.Insert(new DZLTraderPosition("14298.921875 3.697711 13301.237305", "170 0 0", "DZL_Trader", catNames, "0 0 0"));
                
				catNames = new array<string>;
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
				positions.Insert(new DZLTraderPosition("6573.415527 5.991199 2453.483154", "-25 0 0", "DZL_Trader", catNames, "6590.140625 5.810940 2441.690674"));
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
