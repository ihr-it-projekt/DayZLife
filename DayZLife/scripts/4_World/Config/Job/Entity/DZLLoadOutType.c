class DZLLoadOutType: DZLIdModel
{
    string type;
    string displayName = "";
    ref array<string> attachments;

    void DZLLoadOutType(string type, array<string> attachments) {
        this.type = type;
		this.attachments = attachments;
        SetId();
    }
}
