class DZLArrestConfig {
    string version = "3";

    bool shouldDeleteAllItemsOnPrissoner = true;
    bool shouldDeleteAllItemsOnExPrissoner = true;
    bool teleportArrestedIntoJail = false;
    string teleportPosition = "0 0 0";
    ref array<string> prisonerItems;
    ref array<string> exPrisonerItems;
    ref array<vector> arrestAreas;
    ref array<vector> exPrisonerAreas;
    int arrestAreaRadius = 110;
}
