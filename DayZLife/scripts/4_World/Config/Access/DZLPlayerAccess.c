class DZLPlayerAccess
{
    private bool canManageCops = true;
    private bool canManagePlayers = true;
    private string ident;

    void DZLPlayerAccess(string ident) {
        this.ident = ident;
        canManageCops = true;
        canManagePlayers = true;
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
}
