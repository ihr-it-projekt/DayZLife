class DZLTraderPosition: DZLLicencePosition
{
    ref array<string> categoryNames;
    vector spawnPositionOfVehicles;
    void DZLTraderPosition(vector position, vector orientation, string survivor, array<string> attachments, array<string> categoryNames, vector spawnPositionOfVehicles) {
        Init(position, orientation, survivor, attachments);
        this.categoryNames = categoryNames;
        this.spawnPositionOfVehicles = spawnPositionOfVehicles;
    }

}