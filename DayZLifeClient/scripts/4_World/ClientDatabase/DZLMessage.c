class DZLMessage: DZLIdModel {
    static string TYPE_COP = "cop";
    static string TYPE_MEDIC = "medic";
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
    private ref DZLDate date;
    private string replayedMessage;

    void DZLMessage(string _id = "") {
        if(g_Game.IsClient() && _id != "" && FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA + GetFileName(_id))) {
            JsonFileLoader<DZLMessage>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA + GetFileName(_id), this);

            if(!senderId) senderId = "";
            return;
        }
        return;
    }

    void CreateAndSend(PlayerBase _sender, PlayerIdentity _receiver, string _text, string _type, vector _position = "0 0 0", bool senderVisible = true) {
        sender = "";
        if(senderVisible) {
            sender = _sender.GetIdentity().GetName();
            senderId = _sender.GetIdentity().GetId();
        }
        receiver = _receiver.GetId();
        type = _type;
        text = _text;
        if(type == TYPE_COP) {
            position = _sender.GetPosition();
            if(_position != "0 0 0") {
                position = _position;
            }
        }
        SetId();

        date = new DZLDate;
        g_Game.RPCSingleParam(null, DZL_RPC.SEND_MESSAGE_SERVER, new Param1<ref DZLMessage>(this), true, _receiver);
    }

    void CreateAnswer(PlayerBase _sender, string _receiver, string _text, DZLMessage _replayedMessage) {
        this.sender = _sender.GetIdentity().GetName();
        this.senderId = _sender.GetIdentity().GetId();
        this.receiver = _receiver;
        this.type = TYPE_PRIVATE;
        this.text = _text;
        this.SetId();
        this.date = new DZLDate;
        this.replayedMessage = _replayedMessage.text;

        Save();
    }

    string GetShortText() {
        if(text.Length() < 30) {
            return text;
        }

        string shortText = text;
        if(g_Game.IsClient()) shortText = Widget.TranslateString(text);

        if(!shortText) return text.Substring(0, 30);

        return shortText.Substring(0, 30);
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

    DZLDate GetDate() {
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
        if(replayedMessage) {
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

    bool Save() {
        if(g_Game.IsClient()) {
            DZLJsonFileHandler<DZLMessage>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA + GetFileName(id), this);
            return true;
        }
        return false;
    }
}
