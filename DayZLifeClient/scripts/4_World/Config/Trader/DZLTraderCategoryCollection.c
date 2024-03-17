class DZLTraderCategoryCollection {
    string version = "2";
    ref array<ref DZLTraderCategory> categories;

    DZLTraderCategory GetCatByName(string name) {
        foreach(DZLTraderCategory cat: categories) {
            if(cat.name == name) {
                return cat;
            }
        }

        return null;
    }

}
