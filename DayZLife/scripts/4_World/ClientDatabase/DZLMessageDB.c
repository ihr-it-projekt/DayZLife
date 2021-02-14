class DZLMessageDB
{
    private static ref DZLMessageDB messageDB;

    private ref array<string> ids;
    private ref array<ref DZLMessage> messageMap;
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

        messageMap = new array<ref DZLMessage>;

		foreach(string id: ids) {
            messageMap.Insert(new DZLMessage(id));
		}
	}

	void AddMessage(DZLMessage message) {
	    message.Save();
        messageMap.Insert(message);
        ids.Insert(message.GetId());
        Save();
	}

	void RemoveMessage(DZLMessage message) {
		if (message) {
			message.Delete();
			ids.RemoveItem(message.GetId());
			messageMap.RemoveItem(message);
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
	
	array<ref DZLMessage> GetMessages() {
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
			ref array<ref DZLMessage> messageMapTemp = messageMap;
			messageMap = null;
            CheckDZLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA);
            DZLJsonFileHandler<DZLMessageDB>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA + fileName, this);
			messageMap = messageMapTemp;
			return true;
        }
		return false;
    }

}
