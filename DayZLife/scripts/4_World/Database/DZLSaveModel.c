class DZLSaveModel
{
	protected bool mustSave = false;

	protected bool DoSave() {

	    return false;
	}

	void Save() {
	    if (mustSave && DoSave()) {
            mustSave = false;
	    }
	}
}
