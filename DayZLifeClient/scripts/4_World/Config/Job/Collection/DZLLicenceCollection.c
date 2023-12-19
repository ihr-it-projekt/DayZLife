class DZLLicenceCollection {
    ref array<ref DZLLicence> collection;

    void DZLLicenceCollection() {
        collection = new array<ref DZLLicence>;
    }

    DZLLicence FindById(string id) {
        foreach(DZLLicence licence: collection) {
            if (licence.GetId() == id) return licence;
        }

        return null;
    }

    DZLLicence FindByName(string name) {
        foreach(DZLLicence licence: collection) {
            if (licence.name == name) return licence;
        }

        return null;
    }
}