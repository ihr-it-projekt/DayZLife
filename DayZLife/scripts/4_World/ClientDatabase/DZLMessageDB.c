class DZLMessageDB
{
    private static ref DZLMessageDB messageDB;

    private ref array<string> ids;
    private ref map<string, ref DZLMessage> messageMap;
	private string fileName = "messageIndex.json";
	private ref array<ref DZLOnlinePlayer> contacts;

	static DZLMessageDB Get() {
	    if (!messageDB) {
	        messageDB = new DZLMessageDB;
	    }
	    return messageDB;
	}

	void DZLMessageDB() {
		if (!Load()) {
			ids = new array<string>;
			contacts = new array<ref DZLOnlinePlayer>;
		}

        messageMap = new map<string, ref DZLMessage>;
		foreach(string id: ids) {
            messageMap.Insert(id, new DZLMessage(id));
		}
	}

	void AddMessage(DZLMessage message) {
	    message.Save();
        messageMap.Insert(message.id, message);
        ids.Insert(message.id);
        Save();
	}

	void RemoveMessage(DZLMessage message) {
		if (message) {
			message.Delete();
			ids.RemoveItem(message.GetId());
	    	Save();
		}
	}

	void AddContact(DZLOnlinePlayer player) {
	    contacts.Insert(player);
	    Save();
	}

	void RemoveContact(DZLOnlinePlayer player) {
	    contacts.RemoveItem(player);
	    Save();
	}

    bool HasContact(DZLOnlinePlayer player) {
        foreach(DZLOnlinePlayer onlinePlayer: contacts) {
            if (onlinePlayer.id == player.id) return true;
        }
        return false;
    }
	
	map<string, ref DZLMessage> GetMessages() {
		return messageMap;
	}

    private bool Load(){
        if (GetGame().IsClient() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA + fileName)) {
            JsonFileLoader<DZLMessageDB>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA + fileName, this);
            return true;
        }
        return false;
    }

    private bool Save(){
        if (GetGame().IsClient()) {
			ref map<string, ref DZLMessage> messageMapTemp = messageMap;
			messageMap = null;
            CheckDZLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA);
            DZLJsonFileHandler<DZLMessageDB>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA + fileName, this);
			messageMap = messageMapTemp;
			return true;
        }
		return false;
    }

}
