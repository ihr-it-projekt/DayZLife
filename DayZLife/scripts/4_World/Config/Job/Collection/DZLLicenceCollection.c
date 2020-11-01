class DZLLicenceCollection
{
    ref array<ref DZLLicence> collection;

    void DZLLicenceCollection() {
        collection = new array<ref DZLLicence>
    }

    DZLLicence FindById(string id) {
        foreach(DZLLicence licence: collection) {
			DebugMessageDZL("licence ids" + id + licence.id);
			if (licence.id == id) return licence;
		}
		
		return null;
    }
}