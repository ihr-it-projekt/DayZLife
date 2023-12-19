class DZLTraderCategory {
    string name;
    ref array<ref DZLTraderType> items;

    void DZLTraderCategory(string name, array<ref DZLTraderType> items) {
        this.name = name;
        this.items = items;
    }

}