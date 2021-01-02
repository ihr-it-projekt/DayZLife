static void LogMoneyTransaction(string playerId, string type, int oldMoney, int newMoney, int addMoney) {
    if (!FileExist(DAY_Z_LIFE_LOGS)) {
        MakeDirectory(DAY_Z_LIFE_LOGS);
    }
	
	FileHandle handle;

	string fileName = DAY_Z_LIFE_LOGS + "money_log_" + playerId + ".csv";
	
	if (!FileExist(fileName)) {
		handle = OpenFile(fileName , FileMode.APPEND);
		if ( handle == 0 )
        	return;
		
		FPrintln(handle, "time;type;oldMoney;newMoney;addMoney");
	}

	if (handle == 0) {
		handle = OpenFile(fileName , FileMode.APPEND);
	}
    
    if (handle == 0) return;

    DZLDate date = new DZLDate;

    FPrintln(handle, date.ToDateString() + ";" + type + ";" + oldMoney.ToString() + ";"+ newMoney.ToString() + ";"+ addMoney.ToString() + ";");

    CloseFile(handle);
}
