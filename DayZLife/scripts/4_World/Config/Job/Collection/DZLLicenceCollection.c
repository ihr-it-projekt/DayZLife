class DZLLicenceCollection: array<ref DZLLicence>
{
    DZLLicence FindById(string id) {
        foreach(DZLLicence licence: this) {
			if (licence.id == id) return licence;
		}
		
		return null;
    }
}