class TBLOLoadOutType
{
    string type;
    string displayName = "";
    ref array<ref TBLOLoadOutType> attachments;
    int quickBarEntityShortcut;

    void TBLOLoadOutType(string type, array<ref TBLOLoadOutType> attachments = null, int quickBarEntityShortcut = -1) {
        this.type = type;
		this.attachments = attachments;
		this.quickBarEntityShortcut = quickBarEntityShortcut;
    }
}
