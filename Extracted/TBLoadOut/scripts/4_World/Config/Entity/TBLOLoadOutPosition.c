class TBLOLoadOutPosition
{
	vector position;
	vector orientation
	ref array<string> categories;
	
    void TBLOLoadOutPosition(vector position, vector orientation) {
        Init(position, orientation);
        categories = new array<string>;
    }

    protected void Init(vector position, vector orientation) {
        this.position = position;
        this.orientation = orientation;
    }

    void AddCategory(string cat) {
        if (!categories) {
            categories = new array<string>;
        }

        categories.Insert(cat);
    }

    bool IsLoadOut(vector searchPos) {
        return this.position == searchPos;
    }

    bool HasCategory(string searchCat) {
        return -1 != categories.Find(searchCat);
    }

}
