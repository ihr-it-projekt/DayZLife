class DZLLicencePosition
{
    vector position;
	vector orientation
    string survivor;
    ref array<string> attachments;

    void DZLLicencePosition(vector position, vector orientation, string survivor, array<string> attachments) {
        Init(position, orientation, survivor, attachments);
    }

    protected void Init(vector position, vector orientation, string survivor, array<string> attachments) {
        this.position = position;
        this.orientation = orientation;
        this.survivor = survivor;
        this.attachments = attachments;
    }
}
