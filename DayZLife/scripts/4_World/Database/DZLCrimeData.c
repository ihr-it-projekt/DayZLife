class DZLCrimeData: DZLFileStore
{
	private string version = "1";
    private DZLDate lastRaidTime;
    private bool shopRaidRuns = false;

    void DZLCrimeData() {
        fileName = "crimeData.json";
        folder = DAY_Z_LIFE_SERVER_FOLDER_DATA;
        shopRaidRuns = false;
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

    override protected bool DoSave() {
        DZLJsonFileHandler<DZLCrimeData>.JsonSaveFile(folder + fileName, this);
        return true;
    };

    override protected bool DoLoad() {
        JsonFileLoader<DZLCrimeData>.JsonLoadFile(folder + fileName, this);
        return true;
    };
}