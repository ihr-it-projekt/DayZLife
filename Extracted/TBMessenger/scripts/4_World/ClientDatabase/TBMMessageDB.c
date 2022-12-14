class TBMMessageDB
{
    private static ref TBMMessageDB messageDB;
    private string version = "2";
    private ref array<string> ids;
    private ref array<string> answerIds;
    private ref array<ref TBMMessage> messageMap;
    private ref array<ref TBMMessage> answersMap;
	private string fileName = "messageIndex.json";
	private ref array<ref TBMOnlinePlayer> contacts;

	static TBMMessageDB Get() {
	    if (!messageDB) {
	        messageDB = new TBMMessageDB;
	    }
	    return messageDB;
	}

	void TBMMessageDB() {
		if (!Load()) {
		    version = "1";
			ids = new array<string>;
			contacts = new array<ref TBMOnlinePlayer>;
            answerIds = new array<string>;
            ids = new array<string>;

		    Save();
		}

		if (version == "1") {
		    version = "2";
		    Save();
		}

        messageMap = new array<ref TBMMessage>;
        answersMap = new array<ref TBMMessage>;

		foreach(string id: ids) {
            messageMap.Insert(new TBMMessage(id));
		}

		foreach(string _id: answerIds) {
            answersMap.Insert(new TBMMessage(_id));
		}
	}

	void AddAnswer(PlayerBase sender, string receiver, string text, TBMMessage replayedMessage) {
        TBMMessage replay = new TBMMessage;
        replay.CreateAnswer(sender, receiver, text, replayedMessage);
        replay.Save();
        answersMap.Insert(replay);
        answerIds.Insert(replay.GetId());
        Save();
	}

	void AddMessage(TBMMessage message) {
	    message.Save();
        messageMap.Insert(message);
        ids.Insert(message.GetId());
        Save();
	}

	void RemoveMessage(TBMMessage message) {
		if (message) {
			message.Delete();
			ids.RemoveItem(message.GetId());
			messageMap.RemoveItem(message);
	    	Save();
		}
	}
	
	void RemoveAnswer(TBMMessage message) {
		if (message) {
			message.Delete();
			answerIds.RemoveItem(message.GetId());
			answersMap.RemoveItem(message);
	    	Save();
		}
	}

	void AddContact(TBMOnlinePlayer player) {
	    contacts.Insert(player);
	    Save();
	}

	void RemoveContact(TBMOnlinePlayer player) {
	    contacts.RemoveItem(player);
	    Save();
	}

    bool HasContact(TBMOnlinePlayer player) {
        foreach(TBMOnlinePlayer onlinePlayer: contacts) {
            if (onlinePlayer.id == player.id) return true;
        }
        return false;
    }
	
	array<ref TBMMessage> GetMessages() {
		return messageMap;
	}

	array<ref TBMMessage> GetAnswers() {
		return answersMap;
	}

    private bool Load(){
        if (GetGame().IsClient() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA + fileName)) {
            JsonFileLoader<TBMMessageDB>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA + fileName, this);
            return true;
        }
        return false;
    }

    private bool Save(){
        if (GetGame().IsClient()) {
			ref array<ref TBMMessage> messageMapTemp = messageMap;
			ref array<ref TBMMessage> answerMapTemp = answersMap;
			messageMap = null;
			answersMap = null;
            CheckTBMDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA);
            TBMJsonFileHandler<TBMMessageDB>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA + fileName, this);
			messageMap = messageMapTemp;
			answersMap = answerMapTemp;
			return true;
        }
		return false;
    }

}
