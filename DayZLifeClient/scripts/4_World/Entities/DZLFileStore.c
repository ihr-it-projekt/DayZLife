class DZLFileStore
{
	protected string folder;
	protected string fileName;
	
    protected bool Load(){
        if (GetGame().IsServer() && FileExist(folder + fileName)) {
            return DoLoad();
        }
        return false;
    }

    protected bool Save(){
        if (GetGame().IsServer()) {
            CheckDZLDataSubPath(folder);
            return DoSave();
        }
        return false;
    }

    protected bool DoSave() { return false; };
    protected bool DoLoad() { return false; };
}