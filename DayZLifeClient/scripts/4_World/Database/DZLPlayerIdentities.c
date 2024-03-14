class DZLPlayerIdentities {
    string fileName = "DZLPlayerIdentities.bin";
    ref array<string> playerIdentities;

    void DZLPlayerIdentities() {
        if(!Load()) {
            playerIdentities = new array<string>;
        }
    }

    void AddPlayer(string playerId) {
        if(-1 == playerIdentities.Find(playerId)) {
            playerIdentities.Insert(playerId);
            Save();
        }
    }
    void RemovePlayer(string playerId) {
        int index = playerIdentities.Find(playerId);
        if(-1 != index) {
            playerIdentities.Remove(index);
            Save();
        }
    }

    array<ref DZLOnlinePlayer> GetJobPlayerCollection(string jobName) {
        array<ref DZLOnlinePlayer> collection = new array<ref DZLOnlinePlayer>;

        foreach(string ident: playerIdentities) {
            DZLPlayer player = DZLDatabaseLayer.Get().GetPlayer(ident);

            if(player.CanUseJob(jobName)) {
                collection.Insert(new DZLOnlinePlayer(ident, player.playerName, player.GetLastJobRank(jobName)));
            }
        }

        return collection;
    }


    array<ref DZLOnlinePlayer> GetPlayerCollection(array<string> exclude) {
        array<ref DZLOnlinePlayer> collection = new array<ref DZLOnlinePlayer>;

        foreach(string ident: playerIdentities) {
            DZLPlayer player = DZLDatabaseLayer.Get().GetPlayer(ident);

            if(exclude.Count() == 0 || exclude.Find(ident) == -1) {
                collection.Insert(new DZLOnlinePlayer(ident, player.playerName, ""));
            }
        }

        return collection;
    }

    void UpdateJob(string job, ref array<DZLOnlinePlayer> players) {
        if(!players) return;

        foreach(string ident: playerIdentities) {
            DZLPlayer player = DZLDatabaseLayer.Get().GetPlayer(ident);
            bool hasFound = false;
            string newRank = "";
            foreach(DZLOnlinePlayer dzlPlayer: players) {
                if(ident == dzlPlayer.id) {
                    hasFound = true;
                    newRank = dzlPlayer.rank;
                    break;
                }
            }

            player.UpdateJob(job, hasFound, newRank);
        }
    }

    void UpdateCarKeys(PlayerIdentity player, CarScript car, ref array<DZLOnlinePlayer> players) {
        if(!players) return;

        array<ref DZLOnlinePlayer> collection = new array<ref DZLOnlinePlayer>;

        if(!car.IsOwner(player)) return;

        car.UpdatePlayerAccessByDZLOnlinePlayer(players);
    }

    private bool Load() {
        if(!GetGame().IsServer()) return false;
        if(!FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName)) {
            MigrateIdentities();
        };

        playerIdentities = new array<string>;
        FileSerializer serial = new FileSerializer();
        serial.Open(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName, FileMode.READ);

        if(!serial.CanRead()) return false;

        int count = 0;
        serial.Read(count);

        for(int i = 0; i < count; i++) {
            string value = "";
            serial.Read(value);
            playerIdentities.Insert(value);
        }

        serial.Close();
        return true;
    }

    private void Save() {
        if(!GetGame().IsServer()) return;

        if(FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName)) DeleteFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName);
        FileSerializer serial = new FileSerializer();
        serial.Open(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName, FileMode.WRITE);

        if(!serial.CanWrite()) return;

        serial.Write(playerIdentities.Count());
        foreach(string value : playerIdentities) {
            serial.Write(value);
        }

        serial.Close();
    }

    private void MigrateIdentities() {
        CheckDZLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER);
        if(FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + "DZLPlayerIdentities.json")) DeleteFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + "DZLPlayerIdentities.json");
        array<string> files = new array<string>;
        AssemblePathStructure(files, "*.json");

        playerIdentities = new array<string>;
        foreach(string file: files) {
            if(file.Contains("house")) continue;

            string playerId = file;
            playerId.Replace(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER, "");
            playerId.Replace(".json", "");
            playerId.Replace("/", "");

            playerIdentities.Insert(playerId);
        }
        Print("[DayZLife] Migrated " + playerIdentities.Count() + " player identities");
        Save();
    }

    private void AssemblePathStructure(out array<string> paths, string pattern, string pathToRead = "") {
        if("" == pathToRead) pathToRead = DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER;
        paths = {};
        string fileNameTmp;
        FileAttr fileAtts;
        FindFileFlags flags = FindFileFlags.ARCHIVES;

        FindFileHandle fHandle;
        bool complete;

        while(!complete) {
            if(!fHandle)
                fHandle = FindFile(pathToRead + pattern, fileNameTmp, fileAtts, flags); //init find file

            if(fileNameTmp != string.Empty || FileExist(fileNameTmp)) {
                if(fileAtts == FileAttr.DIRECTORY) {
                    array<string> subDirs = {};
                    AssemblePathStructure(subDirs, pattern, string.Format("%1/%2", pathToRead, fileNameTmp)); //recursive
                    if(subDirs && subDirs.Count() > 0) {
                        paths.InsertAll(subDirs); //we want these to be in order of AFTER the contents of themselves
                    }
                }
                paths.Insert(string.Format("%1/%2", pathToRead, fileNameTmp));
            }
            complete = !FindNextFile(fHandle, fileNameTmp, fileAtts);
        }
    }

}
