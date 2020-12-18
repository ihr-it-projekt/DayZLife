class DZLLoadOutType: DZLIdModel
{
    string type;
    string displayName = "";
    ref array<ref DZLLoadOutType> attachments;
    int quickBarEntityShortcut;

    void DZLLoadOutType(string type, array<ref DZLLoadOutType> attachments = null, int quickBarEntityShortcut = -1) {
        this.type = type;
		this.attachments = attachments;
		this.quickBarEntityShortcut = quickBarEntityShortcut;

        SetId();
    }
}
