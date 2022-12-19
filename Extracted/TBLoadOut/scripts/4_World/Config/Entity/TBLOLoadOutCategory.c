class TBLOLoadOutCategory
{
    string name;
    ref array<ref TBLOLoadOutType> items;

    void TBLOLoadOutCategory(string name, array<ref TBLOLoadOutType> items) {
       this.name = name;
       this.items = items;
    }
	
	void UpdateV3() {
       foreach(TBLOLoadOutType item: items) {
           item.UpdateV3();
       }
    }

}
