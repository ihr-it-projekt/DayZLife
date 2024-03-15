class DZLTraderCategory {
    string name;
    ref array<ref DZLTraderType> items;

    void DZLTraderCategory(string _name, array<ref DZLTraderType> _items) {
        this.name = _name;
        this.items = _items;
    }

}