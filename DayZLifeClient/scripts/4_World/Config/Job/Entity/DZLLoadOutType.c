class DZLLoadOutType {
    string type;
    string displayName = "";
    ref array<ref DZLLoadOutType> attachments;
    int quickBarEntityShortcut;

    void DZLLoadOutType(string _type, array<ref DZLLoadOutType> _attachments = null, int _quickBarEntityShortcut = -1) {
        this.type = _type;
        this.attachments = _attachments;
        this.quickBarEntityShortcut = _quickBarEntityShortcut;
    }
}
