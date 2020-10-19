class DZLStorageTypeBought 
{
    DZLStorageType storageType;
    vector position;
    vector relativePos;
    int paidPrice;
    int sellPrice;
	string type;

    void DZLStorageTypeBought(DZLStorageType storageType, vector position, int paidPrice, vector relativePos) {
        this.storageType = storageType;
        this.position = position;
        this.relativePos = relativePos;
        this.paidPrice = paidPrice;
        this.sellPrice = paidPrice / 2;
		this.type = storageType.type;
    }
}