class TBMIdModel
{
    protected string id;

    bool HasCorrectId() {
        return id != "";
    }

    void SetId(string _id = "") {
        if (_id == "") {
            id = Math.RandomInt(0, 100000000000).ToString();
        } else {
            id = _id;
        }
    }
	
	string GetId() {
		return id;
	}
}