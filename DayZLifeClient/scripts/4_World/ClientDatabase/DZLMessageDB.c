class DZLMessageDB
{
    private static ref DZLMessageDB messageDB;
    private string version = "2";
    private ref array<string> ids;
    private ref array<string> answerIds;
    private ref array<ref DZLMessage> messageMap;
    private ref array<ref DZLMessage> answersMap;
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
		    version = "1";
			ids = new array<string>;
			contacts = new array<ref DZLOnlinePlayer>;
            answerIds = new array<string>;
            ids = new array<string>;

		    Save();
		}

		if (version == "1") {
		    version = "2";
		    Save();
		}

        messageMap = new array<ref DZLMessage>;
        answersMap = new array<ref DZLMessage>;

		foreach(string id: ids) {
            messageMap.Insert(new DZLMessage(id));
		}

		foreach(string _id: answerIds) {
            answersMap.Insert(new DZLMessage(_id));
		}
	}

	void AddAnswer(PlayerBase sender, string receiver, string text, DZLMessage replayedMessage) {
        DZLMessage replay = new DZLMessage;
        replay.CreateAnswer(sender, receiver, text, replayedMessage);
        replay.Save();
        answersMap.Insert(replay);
        answerIds.Insert(replay.GetId());
        Save();
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
	
	void RemoveAnswer(DZLMessage message) {
		if (message) {
			message.Delete();
			answerIds.RemoveItem(message.GetId());
			answersMap.RemoveItem(message);
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

	array<ref DZLMessage> GetAnswers() {
		return answersMap;
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
			ref array<ref DZLMessage> answerMapTemp = answersMap;
			messageMap = null;
			answersMap = null;
            CheckDZLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA);
            DZLJsonFileHandler<DZLMessageDB>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA + fileName, this);
			messageMap = messageMapTemp;
			answersMap = answerMapTemp;
			return true;
        }
		return false;
    }

}
