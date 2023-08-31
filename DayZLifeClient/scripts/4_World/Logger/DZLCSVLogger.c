static void DZLLogMoneyTransaction(string playerId, string type, int oldMoney, int newMoney, int addMoney) {
    if (!DZLLoggerConfig.Get().logMoneyTransfer) return;
	string fileName = "money_log.csv";

	array<string> head = new array<string>;
	head.Insert("type");
	head.Insert("oldMoney");
	head.Insert("newMoney");
	head.Insert("addMoney");

	array<string> data = new array<string>;
	data.Insert(type);
	data.Insert(oldMoney.ToString());
	data.Insert(newMoney.ToString());
	data.Insert(addMoney.ToString());

	DZLCSVLog(playerId, fileName, head, data);
}

static void DZLLogTraderTransaction(string playerId, string tradeType, string itemType, int price) {
    if (!DZLLoggerConfig.Get().logTraderTransactions) return;
	string fileName = "trader_log.csv";

    array<string> head = new array<string>;
    head.Insert("tradeType");
    head.Insert("itemType");
    head.Insert("price");

    array<string> data = new array<string>;
    data.Insert(tradeType);
    data.Insert(itemType);
    data.Insert(price.ToString());

    DZLCSVLog(playerId, fileName, head, data);
}

static void DZLLogCrafting(string playerId, string craftType, string itemType) {
    if (!DZLLoggerConfig.Get().logCrafting) return;
	string fileName = "crafting_log.csv";

    array<string> head = new array<string>;
    head.Insert("craftType");
    head.Insert("itemType");

    array<string> data = new array<string>;
    data.Insert(craftType);
    data.Insert(itemType);

    DZLCSVLog(playerId, fileName, head, data);
}

static void DZLLogLoadOut(string playerId, string categoryName) {
    if (!DZLLoggerConfig.Get().logLoadOut) return;
	string fileName = "load_out_log.csv";

    array<string> head = new array<string>;
    head.Insert("categoryName");

    array<string> data = new array<string>;
    data.Insert(categoryName);

    DZLCSVLog(playerId, fileName, head, data);
}

static void DZLLogRaid(string playerId, string info, string target, vector position) {
    if (!DZLLoggerConfig.Get().logRaid) return;
	string fileName = "raid_log.csv";

    array<string> head = new array<string>;
    head.Insert("info");
    head.Insert("target");
    head.Insert("position");

    array<string> data = new array<string>;
    data.Insert(info);
    data.Insert(target);
    data.Insert(position.ToString(true));

    DZLCSVLog(playerId, fileName, head, data);
}

static void DZLLogStore(string playerId, string info, string target, vector position) {
    if (!DZLLoggerConfig.Get().logStore) return;
	string fileName = "store_log.csv";

    array<string> head = new array<string>;
    head.Insert("info");
    head.Insert("target");
    head.Insert("position");

    array<string> data = new array<string>;
    data.Insert(info);
    data.Insert(target);
    data.Insert(position.ToString(true));

    DZLCSVLog(playerId, fileName, head, data);
}

static void DZLLogArrest(string playerId, string info, int duration) {
    if (!DZLLoggerConfig.Get().logArrest) return;
	string fileName = "arrest_log.csv";

    array<string> head = new array<string>;
    head.Insert("info");
    head.Insert("duration");

    array<string> data = new array<string>;
    data.Insert(info);
    data.Insert(duration.ToString());

    DZLCSVLog(playerId, fileName, head, data);
}
static void DZLLogTicket(string playerId, string info, int value) {
    if (!DZLLoggerConfig.Get().logTicket) return;
	string fileName = "ticket_log.csv";

    array<string> head = new array<string>;
    head.Insert("info");
    head.Insert("value");

    array<string> data = new array<string>;
    data.Insert(info);
    data.Insert(value.ToString());

    DZLCSVLog(playerId, fileName, head, data);
}

static void DZLLogHouseTrade(string playerId, string info, int price, vector position) {
    if (!DZLLoggerConfig.Get().logHouseTrade) return;
	string fileName = "houseTrade_log.csv";

    array<string> head = new array<string>;
    head.Insert("info");
    head.Insert("price");
    head.Insert("duration");

    array<string> data = new array<string>;
    data.Insert(info);
    data.Insert(price.ToString());
    data.Insert(position.ToString(true));

    DZLCSVLog(playerId, fileName, head, data);
}


static void DZLCSVLog(string playerId, string fileName, array<string> head, array<string> data) {
    if (!FileExist(DAY_Z_LIFE_LOGS)) {
        MakeDirectory(DAY_Z_LIFE_LOGS);
    }

    string path = DAY_Z_LIFE_LOGS + playerId + "\\";

    if (!FileExist(path)) {
        MakeDirectory(path);
    }

    fileName = path + fileName;

    FileHandle handle;
    if (!FileExist(fileName)) {
        handle = OpenFile(fileName , FileMode.APPEND);
        if ( handle == 0 )
            return;

        string headLine = "time;";

        foreach(string headPart: head) {
            headLine += headPart + ";";
        }

        FPrintln(handle, headLine);
    }

    if (handle == 0) {
        handle = OpenFile(fileName , FileMode.APPEND);
    }

    if (handle == 0) return;

    DZLDate date = new DZLDate;

    string dataLine = date.ToDateString() + ";";

    foreach(string dataPart: data) {
        dataLine += dataPart + ";";
    }

    FPrintln(handle, dataLine);

    CloseFile(handle);
}

