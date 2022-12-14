class TBMMessage: TBMIdModel
{
    static string TYPE_GLOBAL = "global";
    static string TYPE_PRIVATE = "private";

    private string type;
    private string sender;
    private string senderId;
    private string receiver;
    private string text;
    private vector position;
    private bool isRead = false;
    private bool isAnswered = false;
    private ref TBMDate date;
    private string replayedMessage;

    void TBMMessage(string _id = ""){
        if (GetGame().IsClient() && _id != "" && FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA + GetFileName(_id))) {
            JsonFileLoader<TBMMessage>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA + GetFileName(_id), this);

            if (!senderId) {
                senderId = "";
            }
            return;
        }
        return;
    }

    void CreateAndSend(PlayerBase _sender, PlayerIdentity _receiver, string _text, string _type, vector _position = "0 0 0", bool senderVisible = true) {
        sender = "";
        if (senderVisible) {
            sender = _sender.GetIdentity().GetName();
			senderId = _sender.GetIdentity().GetId();
        }
        receiver = _receiver.GetId();
        type = _type;
        text = _text;

        SetId();

        date = new TBMDate;
        GetGame().RPCSingleParam(null, DAY_Z_LIFE_SEND_MESSAGE_SERVER, new Param1<ref TBMMessage>(this), true, _receiver);
    }

    void CreateAnswer(PlayerBase sender, string receiver, string text, TBMMessage replayedMessage) {
        this.sender = sender.GetIdentity().GetName();
        this.senderId = sender.GetIdentity().GetId();
        this.receiver = receiver;
        this.type = TYPE_PRIVATE;
        this.text = text;
        this.SetId();
        this.date = new TBMDate;
        this.replayedMessage = replayedMessage.text;

        Save();
    }

    string GetShortText() {
		if (text.Length() < 20) {
			return text;
		}

        return text.Substring(0,20);
    }

    string GetText() {
        return text;
    }

    string GetSender() {
        return sender;
    }

    vector GetPosition() {
        return position;
    }

    TBMDate GetDate() {
        return date;
    }

    bool IsRead() {
        return isRead;
    }

    void Read() {
        isRead = true;
        Save();
    }

    bool IsAnswered() {
        return isAnswered;
    }

    void Answer() {
        isAnswered = true;
        Save();
    }
	
	string GetType() {
		return type;
	}

	string GetSenderId() {
	    return senderId;
	}

	string GetReplay() {
	    if (replayedMessage) {
	        return replayedMessage;
	    }
	    return "";
	}

	string GetFileName(string _id) {
		return _id + ".json";
	}

    void Delete() {
        DeleteFile(DAY_Z_LIFE_SERVER_FOLDER_DATA + GetFileName(id));
    }

    bool Save(){
        if (GetGame().IsClient()) {
            CheckTBMDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA);
            TBMJsonFileHandler<TBMMessage>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA + GetFileName(id), this);
            return true;
        }
        return false;
    }
}
