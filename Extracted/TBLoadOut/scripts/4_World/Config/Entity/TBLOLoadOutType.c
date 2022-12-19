class TBLOLoadOutType
{
    string type;
    string displayName = "";
    int quickBarEntityShortcut;
    float minHealth = 100;
    float maxHealth = 100;
    ref array<ref TBLOLoadOutType> attachments;

    void TBLOLoadOutType(string type, array<ref TBLOLoadOutType> attachments = null, int quickBarEntityShortcut = -1) {
        this.type = type;
		this.attachments = attachments;
		this.quickBarEntityShortcut = quickBarEntityShortcut;
    }

    void UpdateV3() {
        minHealth = 100;
        maxHealth = 100;

        if (attachments) {
            foreach(TBLOLoadOutType item: attachments) {
                item.UpdateV3();
            }
        }
     }
}
