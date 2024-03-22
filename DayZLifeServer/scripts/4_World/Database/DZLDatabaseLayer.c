class DZLDatabaseLayer {
    private static ref DZLDatabaseLayer databaseLayer;

    private ref map<string, ref DZLPlayer> dzlPlayers = new map<string, ref DZLPlayer>;
    private ref map<string, ref DZLFraction> dzlFractions = new map<string, ref DZLFraction>;
    private ref DZLPlayerIdentities dzlPlayerIdentities = new DZLPlayerIdentities;
    private ref DZLBank bank = new DZLBank;
    private ref map<string, ref DZLCarStorage> storageCars = new map<string, ref DZLCarStorage>;
    private ref map<string, ref DZLCarStorage> fractionStorageCars = new map<string, ref DZLCarStorage>;
    private ref DZLCrimeData crimeData = new DZLCrimeData;
    private ref DZLTraderStorage traderStorage = new DZLTraderStorage;
    private ref DZLDatabase database = new DZLDatabase;

    private int copCount = 0;
    private int civCount = 0;
    private int medicCount = 0;
    private int armyCount = 0;

    static DZLDatabaseLayer Get() {
        if(!databaseLayer) {
            databaseLayer = new DZLDatabaseLayer;
            databaseLayer.InitDB();
        }

        return databaseLayer;
    }

    static void Reload() {
        databaseLayer = new DZLDatabaseLayer;
        databaseLayer.InitDB();

        array<Man> allPlayers = new array<Man>;
        GetGame().GetPlayers(allPlayers);
        foreach(Man playerMan: allPlayers) {
            PlayerBase player = PlayerBase.Cast(playerMan);
            if(!player) continue;
            player.Reload();
        }
    }

    void InitDB() {
        database.Init(this);
    }

    DZLBank GetBank() {
        return bank;
    }

    DZLPlayerIdentities GetPlayerIds() {
        return dzlPlayerIdentities;
    }

    bool HasPlayer(string playerId) {
        return database.HasPlayer(playerId);
    }

    DZLPlayer GetPlayerFromFiles(string playerId) {
        if("" == playerId) return null;
        DZLPlayer player;
        if(!dzlPlayers.Find(playerId, player)) {
            player = new DZLPlayer(playerId, DZLConfig.Get().bankConfig.startCapital);
            dzlPlayers.Insert(playerId, player);
        }

        return player;
    }

    DZLPlayer GetPlayer(string playerId) {
        return database.GetPlayer(playerId);
    }

    DZLFraction GetFraction(string playerId) {
        DZLFraction fraction;
        if(!dzlFractions.Find(playerId, fraction)) {
            fraction = new DZLFraction(playerId);
			
			if (fraction.GetId() != playerId) {
			    DZLPlayer boss = GetPlayer(playerId);
			    if (boss && !boss.IsInAnyFraction()) {
			        return null;
			    }
			}
			
            dzlFractions.Insert(playerId, fraction);
        }

        return fraction;
    }

    DZLCarStorage GetPlayerCarStorage(string playerId) {
        DZLCarStorage storageCar;
        if(!storageCars.Find(playerId, storageCar)) {
            storageCar = new DZLCarStorage(playerId);
            storageCars.Insert(playerId, storageCar);
        }
        return storageCar;
    }

    DZLCarStorage GetFractionCarStorage(string fractionId) {
        DZLCarStorage storageCar;
        fractionId = fractionId + "fraction";
        if(!fractionStorageCars.Find(fractionId, storageCar)) {
            storageCar = new DZLCarStorage(fractionId);
            fractionStorageCars.Insert(fractionId, storageCar);
        }
        return storageCar;
    }

    void RemoveFraction(string fractionId) {
        DZLFraction fraction = GetFraction(fractionId);
        if(!fraction) return;

        DZLPlayer currentPlayer;
        array<ref DZLFractionMember>potentialMembers = fraction.GetPotentialMembers();
        foreach(DZLFractionMember potentialMember: potentialMembers) {
            currentPlayer = database.GetPlayer(potentialMember.playerId);
            currentPlayer.RemovePotentialFraction(fraction.GetId());
        }

        currentPlayer = null;
        array<ref DZLFractionMember>members = fraction.GetMembers();
        foreach(DZLFractionMember member: members) {
            currentPlayer = database.GetPlayer(member.playerId);
            currentPlayer.RemoveFraction(fraction.GetId());
        }

        fraction.Delete();
        dzlFractions.Remove(fraction.GetId());
    }

    void RemovePlayerCars(string playerId) {
        DZLCarStorage storageCar = GetPlayerCarStorage(playerId);;
        if(storageCars.Find(playerId, storageCar)) {
            storageCars.Remove(playerId);
        }

        DeleteFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_CAR + storageCar.fileName);
    }

    void RemovePlayer(string playerId) {
        database.RemovePlayer(playerId);
    }

    DZLDatabaseLayer SetCopCount(int count) {
        copCount = count;
        return this;
    }

    DZLDatabaseLayer SetMedicCount(int count) {
        medicCount = count;
        return this;
    }

    DZLDatabaseLayer SetArmyCount(int count) {
        armyCount = count;
        return this;
    }


    DZLDatabaseLayer SetCivCount(int count) {
        civCount = count;
        return this;
    }

    int GetCopCount() {
        return copCount;
    }

    int GetMedicCount() {
        return medicCount;
    }

    int GetArmyCount() {
        return armyCount;
    }

    int GetCivCount() {
        return civCount;
    }

    DZLCrimeData GetCrimeData() {
        return crimeData;
    }

    DZLTraderStorage GetTraderStorage() {
        return traderStorage;
    }
}
