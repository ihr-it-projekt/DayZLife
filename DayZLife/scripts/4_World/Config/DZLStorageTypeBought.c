class DZLStorageTypeBought 
{
    DZLStorageType storageType;
    vector position;
    int paidPrice;
    int spelledPrice;

    void DZLStorageType(DZLStorageType storageType, vector position, int paidPrice, int spelledPrice) {
        this.storageType = storageType;
        this.position = position;
        this.paidPrice = paidPrice;
        this.spelledPrice = spelledPrice;
    }
}