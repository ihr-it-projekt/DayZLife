class DZLTraderPositionCollection {
    string version = "3";
    ref array<ref DZLTraderPosition> positions;

    void DZLTraderPositionCollection() {
        if(!Load()) {
            positions = new array<ref DZLTraderPosition>;
            array<string> catNames = {"Jewelry Dealer", "Food", "Drinks"};
            positions.Insert(new DZLTraderPosition("1361.565918 137.619003 4004.216309", "-6 0 0", catNames, "0 0 0"));

            catNames = {"Coal Dealer", "Food", "Drinks"};
            positions.Insert(new DZLTraderPosition("3571.295654 5.991199 2205.106201", "85 0 0", catNames, "0 0 0"));

            catNames = {"Money Dealer"};
            positions.Insert(new DZLTraderPosition("7371.827637 4.913576 2606.656494", "15 0 0", catNames, "0 0 0"));

            catNames = {"Gold Dealer", "Food", "Drinks"};
            positions.Insert(new DZLTraderPosition("11508.634766 242.879730 5509.993652", "-174 0 0", catNames, "0 0 0"));

            catNames = {"Cement Dealer", "Food", "Drinks"};
            positions.Insert(new DZLTraderPosition("13088.675781 7.193148 7145.185547", "93 0 0", catNames, "0 0 0"));

            catNames = {"Copper Dealer", "Iron Dealer", "Food", "Drinks"};
            positions.Insert(new DZLTraderPosition("9736.766602 298.949829 8868.407227", "-58 0 0", catNames, "0 0 0"));

            catNames = {"Paper and Wood Dealer", "Food", "Drinks"};
            positions.Insert(new DZLTraderPosition("6337.460938 301.036987 7681.634766", "165 0 0", catNames, "0 0 0"));

            catNames = {"Drug Dealer", "Food", "Drinks"};
            positions.Insert(new DZLTraderPosition("14298.921875 3.697711 13301.237305", "170 0 0", catNames, "0 0 0"));

            catNames = {"Clothing", "Medic", "Tools", "Food", "Meat", "Drinks", "Weapons", "Magazines", "Ammo", "Cars"};
            positions.Insert(new DZLTraderPosition("6573.415527 5.991199 2453.483154", "-25 0 0", catNames, "6590.140625 5.810940 2441.690674"));

            Save();
        }
    }

    private bool Load() {
        if(GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "traderPositions.json")) {
            JsonFileLoader<DZLTraderPositionCollection>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "traderPositions.json", this);
            return true;
        }
        return false;
    }

    private void Save() {
        if(GetGame().IsServer()) {
            CheckDZLConfigPath();
            JsonFileLoader<DZLTraderPositionCollection>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "traderPositions.json", this);
        }
    }


}
