static void CheckTBLOBasePath() {
    if (!FileExist(TB_SERVER_FOLDER_BASE)) {
        MakeDirectory(TB_SERVER_FOLDER_BASE);
    }
}

static void CheckTBLOConfigPath() {
    CheckTBLOBasePath();
    if (!FileExist(TB_SERVER_FOLDER_CONFIG)) {
        MakeDirectory(TB_SERVER_FOLDER_CONFIG);
    }
}

static void CheckTBLODataSubPath(string path) {
    CheckTBLOBasePath();
    if (!FileExist(path)) {
        MakeDirectory(path);
    }
}


