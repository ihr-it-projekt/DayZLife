class DZLCrimeData: DZLFileSerializer {
    private string version = "1";
    private DZLDate lastRaidTime;
    private bool shopRaidRuns = false;

    void DZLCrimeData() {
        Init(DAY_Z_LIFE_SERVER_FOLDER_DATA, "crimeData");
        Load();
    }

    void SetLastRaidTime(DZLDate date) {
        lastRaidTime = date;
        Save();
    }

    void SetShopRaid(bool raidRuns) {
        shopRaidRuns = raidRuns;
    }

    bool ShopRaidRuns() {
        return shopRaidRuns;
    }

    DZLDate GetLastRaidTime() {
        return lastRaidTime;
    }

    override protected bool Read(FileSerializer ctx) {
        if(!ctx.Read(version)) return false;
        if(!ctx.Read(lastRaidTime)) return false;

        return true;
    }
    override protected void Write(FileSerializer ctx) {
        ctx.Write(version);
        ctx.Write(lastRaidTime);
    }
}