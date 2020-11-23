class DZLIdModel
{
    string id;

    bool HasCorrectId() {
        return id != "";
    }

    void SetId() {
        id = Math.RandomInt(0, 100000000000).ToString();
    }
}