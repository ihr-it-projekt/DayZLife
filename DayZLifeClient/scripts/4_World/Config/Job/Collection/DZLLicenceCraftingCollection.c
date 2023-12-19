class DZLLicenceCraftingCollection {
    ref array<ref DZLCraftLicence> collection;

    void DZLLicenceCraftingCollection() {
        collection = new array<ref DZLCraftLicence>;
    }

    DZLCraftLicence FindById(string id) {
        foreach(DZLCraftLicence licence: collection) {
            if (licence.GetId() == id) return licence;
        }

        return null;
    }

    DZLCraftLicence FindByName(string name) {
        foreach(DZLCraftLicence licence: collection) {
            if (licence.name == name) return licence;
        }

        return null;
    }
}