class DZLStorageTypeBought 
{
    DZLStorageType storageType;
    vector position;
    int paidPrice;
    int sellPrice;
	string type;

    void DZLStorageTypeBought(DZLStorageType storageType, vector position, int paidPrice) {
        this.storageType = storageType;
        this.position = position;
        this.paidPrice = paidPrice;
        this.sellPrice = paidPrice / 2;
		this.type = storageType.type;
    }
}