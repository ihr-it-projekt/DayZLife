class DZLSaveModel
{
	protected bool mustSave = false;

	protected void DoSave() {}

	void Save() {
	    if (mustSave) {
	        mustSave = false;

	        DoSave();
	    }
	}
}
