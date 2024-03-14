class DZLPlayer {

    private string version = "6";
    string fileName = "";
    string dayZPlayerId = "";
    private int money = 0;
    private int bank = 0;

    private ref map<string, bool> jobMap = new map<string, bool>;
    private ref map<string, string> jobGradeMap = new map<string, string>;
    private ref map<string, int> onlineTimeMap = new map<string, int>;

    // DEPRECATED remove 08.03.2025
    private bool isCop = false;
    private string lastCopRank = "";
    private bool isMedic = false;
    private string lastMedicRank = "";
    private bool isArmy = false;
    private string lastArmyRank = "";
    private int onlineTimeCivil = 0;
    private int onlineTimeMedic = 0;
    private int onlineTimeCop = 0;

    // Deprecated end

    string playerName = "";
    private int robtMoney = 0;
    string arrestReason = "";
    int arrestTimeInMinutes = 0;
    private string activeJob = DAY_Z_LIFE_JOB_CIVIL;
    private string activeJobGrade = "Rekrut";
    ref DZLDate lastLoginDate;
    ref TStringArray licenceIds;
    private string deadState = DAY_Z_LIFE_DZL_PLAYER_DEAD_STATE_NONE;
    ref array<ref DZLStoreItem> itemsStore;
    private ref array<ref DZLTicket> openTickets;
    private string fractionId = "";
    private ref array<string> fractionWherePlayerCanJoin;
    private ref DZLFraction fraction = null;
    [NonSerialized()] PlayerBase player;

    void IncreaseOnlineTime() {
        int onlineTime = onlineTimeMap.Get(activeJob);
        if(!onlineTime) onlineTime = 0;

        onlineTimeMap.Set(activeJob, onlineTime + 1);
    }

    void DZLPlayer(string playerId, int moneyToAdd = 0) {
        if(!playerId) {
            Print("Can not create DZLPlayer without playerId");
            return;
        }

        fileName = playerId + ".json";
        if(!Load()) {
            bank = moneyToAdd;
            this.dayZPlayerId = playerId;
            licenceIds = new TStringArray;

            DZLDatabaseLayer.Get().GetBank().AddMoney(bank);
            openTickets = new array<ref DZLTicket>;
        }

        DZLPlayerIdentities idents = DZLDatabaseLayer.Get().GetPlayerIds();
        idents.AddPlayer(playerId);


        DZLPaycheck payCheck = DZLRankHelper.getCurrentPayCheck(this, DZLConfig.Get().jobConfig.paycheck);

        if(payCheck.rank != activeJobGrade) {
            activeJobGrade = payCheck.rank;
        }

        if(IsInAnyFraction()) {
            fraction = DZLDatabaseLayer.Get().GetFraction(fractionId);

            if(!fraction) {
                fractionId = "";
            }
        }

        if("5" == version) {
            jobMap = new map<string, bool>;
            jobMap.Insert(DAY_Z_LIFE_JOB_CIVIL, true);
            jobMap.Insert(DAY_Z_LIFE_JOB_MEDIC, isMedic);
            jobMap.Insert(DAY_Z_LIFE_JOB_COP, isCop);
            jobMap.Insert(DAY_Z_LIFE_JOB_ARMY, isArmy);

            jobGradeMap = new map<string, string>;
            jobGradeMap.Insert(DAY_Z_LIFE_JOB_CIVIL, "Rekrut");
            jobGradeMap.Insert(DAY_Z_LIFE_JOB_MEDIC, lastMedicRank);
            jobGradeMap.Insert(DAY_Z_LIFE_JOB_COP, lastCopRank);
            jobGradeMap.Insert(DAY_Z_LIFE_JOB_ARMY, lastArmyRank);

            onlineTimeMap = new map<string, int>;
            onlineTimeMap.Insert(DAY_Z_LIFE_JOB_CIVIL, onlineTimeCivil);
            onlineTimeMap.Insert(DAY_Z_LIFE_JOB_MEDIC, onlineTimeMedic);
            onlineTimeMap.Insert(DAY_Z_LIFE_JOB_COP, onlineTimeCop);

            version = "6";
        }

        Save();
    }

    bool IsPlayerInArrest() {
        return arrestTimeInMinutes != 0;
    }

    void ArrestCountDown() {
        --arrestTimeInMinutes;
        Save();
    }

    void ArrestPlayer(string reason, int time) {
        arrestTimeInMinutes = time;
        arrestReason = reason;
        Save();
    }

    string GetActiveJob() {
        if(activeJob == "") {
            activeJob = DAY_Z_LIFE_JOB_CIVIL;
            Save();
        }
        return activeJob;
    }

    void SetJobGrade(string grade) {
        activeJobGrade = grade;
        jobGradeMap.Set(activeJob, grade);

        Save();
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

    void UpdateActiveJob(string job) {
        activeJob = job;
        activeJobGrade = GetLastJobRank(job);

        Save();
    }

    void UpdateOnlineTime() {
        int onlineTime = onlineTimeMap.Get(activeJob);
        if(!onlineTime) onlineTime = 0;

        onlineTimeMap.Set(activeJob, onlineTime + 1);

        Save();
    }

    void ResetOnlineTime() {
        onlineTimeMap.Set(activeJob, 0);
        Save();
    }

    int GetActiveOnlineTime() {
        int onlineTime = onlineTimeMap.Get(activeJob);
        if(!onlineTime) onlineTime = 0;

        return onlineTime;
    }

    void UpdateJob(string jobName, bool isJob, string rank) {
        jobMap.Set(jobName, isJob);
        jobGradeMap.Set(jobName, rank);

        if(IsActiveJob(jobName)) {
            this.activeJobGrade = rank;
        }

        ResetJobCivil();

        Save();
    }

    private void ResetJobCivil() {
        if(!IsActiveAsCivil()) return;
        this.activeJobGrade = "Rekrut";
    }

    void UpdateName(string playerName) {
        this.playerName = playerName;
        lastLoginDate = new DZLDate();
        Save();
    }

    void LoosPlayerInventoryMoney() {
        money = 0;
        Save();
    }

    bool AddMoneyToPlayer(int moneyCount) {
        if(GetDayZGame().IsServer()) {
            DZLLogMoneyTransaction(dayZPlayerId, "player", money, money + moneyCount, moneyCount);

            if(DZLConfig.Get().bankConfig.useMoneyAsObject) {
                moneyCount = DZLPlayerMoney.Get(player).AddMoney(moneyCount);

                if(moneyCount != 0 && player && player.GetIdentity()) {
                    Error("Error: Can't add/remove money to/from player transaction stopped!");
                    Error("Player ID" + dayZPlayerId);
                    DZLSendMessage(player.GetIdentity(), "#pls_restart_your_dayz");
                }
                return moneyCount == 0;
            }
        }

        money += moneyCount;
        Save();

        return true;
    }

    void AddMoneyToPlayerBank(int moneyCount) {
        if(GetDayZGame().IsServer()) {
            DZLLogMoneyTransaction(dayZPlayerId, "bank", bank, bank + moneyCount, moneyCount);
            bank += moneyCount;
            Save();
        }
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

    void PlayerHasDied() {
        DZLLogMoneyTransaction(dayZPlayerId, "has died", money, 0, money * -1);
        money = 0;
        Save();
    }

    void SetWillHealByMedic() {
        deadState = DAY_Z_LIFE_DZL_PLAYER_DEAD_STATE_NEW_SPAWN_MEDIC;
        Save();
    }

    void SetWillHealByHospital() {
        deadState = DAY_Z_LIFE_DZL_PLAYER_DEAD_STATE_NEW_SPAWN_HOSPITAL;
        Save();
    }

    void SetBetweenState() {
        deadState = DAY_Z_LIFE_DZL_PLAYER_DEAD_STATE_IS_BETWEEN;
        Save();
    }

    void ResetDeadState() {
        deadState = DAY_Z_LIFE_DZL_PLAYER_DEAD_STATE_NONE;
        itemsStore = new array<ref DZLStoreItem>;;
        Save();
    }

    void SaveItems(PlayerBase player) {
        itemsStore = new array<ref DZLStoreItem>;
        DZLStoreItem items = new DZLStoreItem;
        items.Init(player, player.GetPosition(), true, false);

        itemsStore.Insert(items);
        Save();
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

    void TransferFromPlayerToOtherPlayer(DZLPlayer playerTarget) {
        DZLLogMoneyTransaction(dayZPlayerId, "player", money, 0, money * -1);
        playerTarget.AddMoneyToPlayer(money);

        AddMoneyToPlayer(-money);
    }

    void DepositMoneyFromPlayerToOtherPlayer(DZLPlayer playerTarget, int moneyToTransfer) {
        DZLLogMoneyTransaction(dayZPlayerId, "player", money, money - moneyToTransfer, moneyToTransfer * -1);
        playerTarget.AddMoneyToPlayer(moneyToTransfer);

        AddMoneyToPlayer(-moneyToTransfer);
    }

    int DepositMoneyToOtherPlayer(DZLPlayer playerTarget, int moneyToTransfer) {
        int moneyBankAdd = moneyToTransfer;

        playerTarget.AddMoneyToPlayerBank(moneyToTransfer);

        if(money > 0) {
            if(money < moneyToTransfer) {
                DZLLogMoneyTransaction(dayZPlayerId, "player", money, money, 0);

                if(DZLConfig.Get().bankConfig.useMoneyAsObject) {
                    DZLPlayerMoney.Get(player).AddMoney(-DZLPlayerMoney.Get(player).GetMoneyAmount());
                }

                moneyToTransfer -= money;
                money = 0;
            } else {
                DZLLogMoneyTransaction(dayZPlayerId, "player", money, money - moneyToTransfer, moneyToTransfer * -1);

                if(DZLConfig.Get().bankConfig.useMoneyAsObject) {
                    DZLPlayerMoney.Get(player).AddMoney(-moneyToTransfer);
                } else {
                    money -= moneyToTransfer;
                }

                moneyToTransfer = 0;
            }
        }

        if(moneyToTransfer > 0) {
            DZLLogMoneyTransaction(dayZPlayerId, "bank", bank, bank - moneyToTransfer, moneyToTransfer * -1);
            bank -= moneyToTransfer;
            moneyBankAdd -= moneyToTransfer;
        }

        Save();
        return moneyBankAdd;
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

    void BuyLicence(DZLCraftLicence licenceToBuy) {
        AddMoneyToPlayer(-licenceToBuy.price);

        licenceIds.Insert(licenceToBuy.GetId());
        Save();
    }

    void AddTicket(int value, string reason) {
        openTickets.Insert(new DZLTicket(value, reason));
        Save();
    }

    array<ref DZLTicket> GetTickets() {
        return openTickets;
    }

    bool HasTickets() {
        return 0 != openTickets.Count();
    }

    void RemoveTicketById(string id) {
        if(!GetGame().IsServer()) return;

        foreach(int index, DZLTicket ticket: openTickets) {
            if(id == ticket.GetId()) {
                openTickets.Remove(index);
                Save();
                return;
            }
        }
    }

    DZLTicket GetTicketById(string id) {
        foreach(int index, DZLTicket ticket: openTickets) {
            if(id == ticket.GetId()) {
                return ticket;
            }
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
        if(GetGame().IsServer()) {
            fraction = DZLDatabaseLayer.Get().GetFraction(fractionId);
        }

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

    void RemoveFraction(string fractionId) {
        if(this.fractionId == fractionId) {
            this.fractionId = "";
            fraction = null;

            Save();
        }
    }

    void SetFraction(DZLFraction fraction) {
        this.fraction = fraction;
        this.fractionId = fraction.GetId();
        fractionWherePlayerCanJoin = new array<string>;

        Save();
    }

    void UpdateFraction(DZLFraction fraction) {
        if(fractionId != fraction.GetId()) return;

        this.fraction = fraction;
        this.fractionId = fraction.GetId();

        Save();
    }

    void RemovePotentialFraction(string fractionId) {
        foreach(int key, string fractionIdCanJoin: fractionWherePlayerCanJoin) {
            if(fractionId == fractionIdCanJoin) {
                fractionWherePlayerCanJoin.Remove(key);
                break;
            }
        }

        Save();
    }

    void AddPotentialFraction(string fractionId) {
        if(IsInAnyFraction()) return;

        foreach(int key, string fractionIdCanJoin: fractionWherePlayerCanJoin) {
            if(fractionId == fractionIdCanJoin) {
                return;
            }
        }

        fractionWherePlayerCanJoin.Insert(fractionId);

        Save();
    }

    bool HasPotentialFraction(string fractionId) {
        if(IsInAnyFraction()) return false;

        foreach(int key, string fractionIdCanJoin: fractionWherePlayerCanJoin) {
            if(fractionId == fractionIdCanJoin) {
                return true;
            }
        }

        return false;
    }

    string GetFractionId() {
        return fractionId;
    }

    void ResetPotentialFractions() {
        fractionWherePlayerCanJoin = new array<string>;
        Save();
    }

    array<string> GetFractionIdsWherePlayerCanJoin() {
        return fractionWherePlayerCanJoin;
    }

    void AddToContact(DZLOnlinePlayer player) {
        DZLMessageDB.Get().AddContact(player);
    }

    private bool Load() {
        if(GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName)) {
            JsonFileLoader<DZLPlayer>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName, this);
            return true;
        }
        return false;
    }

    private bool Save() {
        if(GetGame().IsServer() && dayZPlayerId) {
            if(dayZPlayerId + ".json" != fileName) {
                LogMessageDZL("Can not save PlayerData. There are inconsistent in your player database: Please check file:" + fileName);
                return false;
            }
            DZLFraction fractionTemp = fraction;
            fraction = null;

            CheckDZLDataSubPath(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER);
            DZLJsonFileHandler<DZLPlayer>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER + fileName, this);
            fraction = fractionTemp;

            return true;
        }
        return false;
    }
}
