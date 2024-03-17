class DZLPlayer: DZLFileSerializer {

    protected string version = "6";
    string dayZPlayerId = "";
    protected int money = 0;
    protected int bank = 0;
    protected ref map<string, bool> jobMap = new map<string, bool>;
    protected ref map<string, string> jobGradeMap = new map<string, string>;
    protected ref map<string, int> onlineTimeMap = new map<string, int>;

    // DEPRECATED remove 08.03.2025
    protected bool isCop = false;
    protected string lastCopRank = "";
    protected bool isMedic = false;
    protected string lastMedicRank = "";
    protected bool isArmy = false;
    protected string lastArmyRank = "";
    protected int onlineTimeCivil = 0;
    protected int onlineTimeMedic = 0;
    protected int onlineTimeCop = 0;
    // Deprecated end

    string playerName = "";
    protected int robtMoney = 0;
    string arrestReason = "";
    int arrestTimeInMinutes = 0;
    protected string activeJob = DAY_Z_LIFE_JOB_CIVIL;
    protected string activeJobGrade = "Rekrut";
    ref DZLDate lastLoginDate = new DZLDate;
    ref TStringArray licenceIds = new TStringArray;
    protected string deadState = DAY_Z_LIFE_DZL_PLAYER_DEAD_STATE_NONE;
    ref array<ref DZLStoreItem> itemsStore = new array<ref DZLStoreItem>;
    protected ref array<ref DZLTicket> openTickets = new array<ref DZLTicket>;
    protected string fractionId = "";
    protected ref array<string> fractionWherePlayerCanJoin = new array<string>;
    protected ref DZLFraction fraction = null;
    [NonSerialized()] PlayerBase player;


    bool IsPlayerInArrest() {
        return arrestTimeInMinutes != 0;
    }

    string GetActiveJob() {
        if(activeJob == "") {
            activeJob = DAY_Z_LIFE_JOB_CIVIL;
            Save();
        }
        return activeJob;
    }

    string GetLastJobRank(string job) {
        string rank = jobGradeMap.Get(job);
        if(rank) return rank;

        return "Rekrut";
    }

    string GetJobGrade() {
        return activeJobGrade;
    }

    bool IsActiveJobGrade(string grade) {
        return activeJobGrade == grade;
    }

    bool IsActiveJob(string job) {
        return activeJob == job;
    }

    bool IsActiveAsCivil() {
        return DAY_Z_LIFE_JOB_CIVIL == activeJob || activeJob == "";
    }

    bool CanUseJob(string job) {
        return jobMap.Contains(job) && jobMap.Get(job);
    }

    int GetActiveOnlineTime() {
        int onlineTime = onlineTimeMap.Get(activeJob);
        if(!onlineTime) onlineTime = 0;

        return onlineTime;
    }

    bool HasEnoughMoney(int amount) {
        if(DZLConfig.Get().bankConfig.useMoneyAsObject) {
            return DZLPlayerMoney.Get(player).HasEnoughMoney(amount);;
        }

        return money >= amount;
    }

    bool HasEnoughMoneyBank(int amount) {
        return bank >= amount;
    }

    bool HasMoney() {
        if(DZLConfig.Get().bankConfig.useMoneyAsObject) {
            return DZLPlayerMoney.Get(player).HasEnoughMoney(1);;
        }
        return money > 0;
    }

    bool HasBankMoney() {
        return bank > 0;
    }

    int GetBankMoney() {
        return bank;
    }

    int GetMoney() {
        if(DZLConfig.Get().bankConfig.useMoneyAsObject) {
            return DZLPlayerMoney.Get(player).GetMoneyAmount();;
        }
        return money;
    }

    int GetAllMoney() {
        return GetMoney() + GetBankMoney();
    }

    DZLStoreItem GetPlayerData() {
        return itemsStore.Get(0);
    }

    bool WillHealByMedic() {
        return deadState == DAY_Z_LIFE_DZL_PLAYER_DEAD_STATE_NEW_SPAWN_MEDIC;
    }

    bool WillHealByHospital() {
        return deadState == DAY_Z_LIFE_DZL_PLAYER_DEAD_STATE_NEW_SPAWN_HOSPITAL;
    }

    bool HasNoDieState() {
        return deadState == DAY_Z_LIFE_DZL_PLAYER_DEAD_STATE_NONE;
    }

    bool HasBetweenState() {
        return deadState == DAY_Z_LIFE_DZL_PLAYER_DEAD_STATE_IS_BETWEEN;
    }

    string CanBuyLicence(notnull DZLCraftLicence licenceToBuy, DZLCraftLicence depLicence) {
        if(!HasEnoughMoney(licenceToBuy.price)) return "#not_enough_money";
        if(HasLicense(licenceToBuy)) return "#your_already_have_the_licence";

        if(!depLicence) return "";

        if(depLicence && HasDependencyLicense(depLicence)) return "";

        return "#you_have_not_the_dependency_licence";
    }

    bool HasDependencyLicense(notnull DZLCraftLicence depLicence) {
        return HasLicense(depLicence);
    }

    bool HasLicense(DZLCraftLicence licenceToBuy) {
        foreach(string licenceId: licenceIds) {
            if(licenceId == licenceToBuy.GetId()) {
                return true;
            }
        }
        return false;
    }

    array<ref DZLTicket> GetTickets() {
        return openTickets;
    }

    bool HasTickets() {
        return 0 != openTickets.Count();
    }


    DZLTicket GetTicketById(string id) {
        foreach(int index, DZLTicket ticket: openTickets) {
            if(id == ticket.GetId()) return ticket;
        }
        return null;
    }

    bool IsFractionBoss() {
        return fractionId == dayZPlayerId;
    }

    bool IsInAnyFraction() {
        return "" != fractionId;
    }

    DZLFraction GetFraction() {
        return fraction;
    }

    DZLFractionMember GetFractionMember() {
        if(fractionId) {
            return GetFraction().GetMember(dayZPlayerId);
        }
        return null;
    }

    bool HasFractionRightCanAccessFractionGarage() {
        return GetFraction() && GetFractionMember().canAccessFractionGarage;
    }

    bool HasFractionRightCanAccessBankAccount() {
        return GetFraction() && GetFractionMember() && GetFractionMember().canAccessBankAccount;
    }

    bool HasFractionRightCanGetMoneyFromBankAccount() {
        return GetFraction() && GetFractionMember() && GetFractionMember().canGetMoneyFromBankAccount;
    }

    bool HasPotentialFraction(string _fractionId) {
        if(IsInAnyFraction()) return false;

        foreach(int key, string fractionIdCanJoin: fractionWherePlayerCanJoin) {
            if(_fractionId == fractionIdCanJoin) {
                return true;
            }
        }

        return false;
    }

    string GetFractionId() {
        return fractionId;
    }

    array<string> GetFractionIdsWherePlayerCanJoin() {
        return fractionWherePlayerCanJoin;
    }

    void AddToContact(DZLOnlinePlayer _player) {
        DZLMessageDB.Get().AddContact(_player);
    }

    void TransferFromPlayerToOtherPlayer(DZLPlayer playerTarget) {};
    void AddMoneyToPlayerBank(int moneyCount) {};
    void SetWillHealByMedic() {};
    void SaveItems(PlayerBase _player) {};
    bool AddMoneyToPlayer(int moneyCount) {};
    void RemovePotentialFraction(string _fractionId) {};
    void AddPotentialFraction(string _fractionId) {};
    void RemoveFraction(string _fractionId) {};
    void PlayerHasDied() {};
    void SetWillHealByHospital() {};
}
