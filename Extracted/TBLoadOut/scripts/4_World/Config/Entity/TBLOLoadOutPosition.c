class TBLOLoadOutPosition
{
	vector position;
	vector orientation
	
    void TBLOLoadOutPosition(vector position, vector orientation) {
        Init(position, orientation);
    }

    protected void Init(vector position, vector orientation) {
        this.position = position;
        this.orientation = orientation;
    }

}
