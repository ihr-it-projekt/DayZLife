class DZLLicencePosition
{
    vector position;
	vector orientation
    string type;

    void DZLLicencePosition(vector position, vector orientation, string type) {
        Init(position, orientation, type);
    }

    protected void Init(vector position, vector orientation, string type) {
        this.position = position;
        this.orientation = orientation;
        this.type = type;
    }
}
