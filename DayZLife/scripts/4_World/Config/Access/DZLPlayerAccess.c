class DZLPlayerAccess
{
    private bool canManageCops = true;
    private bool canManagePlayers = true;
    private bool canManageMedic = true;
    private bool canManageCars = true;
    private string ident;

    void DZLPlayerAccess(string ident) {
        this.ident = ident;
        canManageCops = true;
        canManagePlayers = true;
		canManageMedic = true;
		canManageCars = true;
    }

    string GetIdent() {
        return ident;
    }

    bool CanManagePlayers() {
        return canManagePlayers;
    }

    bool CanManageCops() {
        return canManageCops;
    }
	
    bool CanManageMedic() {
        return canManageMedic;
    }

    bool CanManageCars() {
        return canManageCars;
    }
}
