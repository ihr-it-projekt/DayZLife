class DZLCarStoreItem: DZLStoreItem
{
	ref array<string> playerAccess;
	
	void DZLCarStoreItem(CarScript item, vector storagePosition) {
		Init(item, storagePosition, false);
		isCar = true;
		this.playerAccess = item.playerAccess;
	}
}
