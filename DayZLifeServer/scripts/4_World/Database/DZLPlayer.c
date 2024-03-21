modded class DZLPlayer {

    void DZLPlayer(string playerId, int moneyToAdd = 0) {
        if(!playerId) {
            Print("Can not create DZLPlayer without playerId");
            return;
        }

        Init(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER, playerId);
        if(LoadJSON(playerId)) {
            Init(DAY_Z_LIFE_SERVER_FOLDER_DATA_PLAYER, playerId);
            Save();
        }

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
    }

    override protected bool Read(FileSerializer ctx) {
        if(!ctx.Read(version)) return false;
        if(!ctx.Read(dayZPlayerId)) return false;
        if(!ctx.Read(money)) return false;
        if(!ctx.Read(bank)) return false;
        if(!ctx.Read(jobMap)) return false;
        if(!ctx.Read(jobGradeMap)) return false;
        if(!ctx.Read(onlineTimeMap)) return false;
        if(!ctx.Read(playerName)) return false;
        if(!ctx.Read(robtMoney)) return false;
        if(!ctx.Read(arrestReason)) return false;
        if(!ctx.Read(arrestTimeInMinutes)) return false;
        if(!ctx.Read(activeJob)) return false;
        if(!ctx.Read(activeJobGrade)) return false;
        if(!ctx.Read(lastLoginDate)) return false;
        if(!ctx.Read(licenceIds)) return false;
        if(!ctx.Read(itemsStore)) return false;
        if(!ctx.Read(openTickets)) return false;
        if(!ctx.Read(fractionId)) return false;
        if(!ctx.Read(fractionWherePlayerCanJoin)) return false;
        if(!ctx.Read(fraction)) return false;

        return true;
    }

    override protected void Write(FileSerializer ctx) {
        ctx.Write(version);
        ctx.Write(dayZPlayerId);
        ctx.Write(money);
        ctx.Write(bank);
        ctx.Write(jobMap);
        ctx.Write(jobGradeMap);
        ctx.Write(onlineTimeMap);
        ctx.Write(playerName);
        ctx.Write(robtMoney);
        ctx.Write(arrestReason);
        ctx.Write(arrestTimeInMinutes);
        ctx.Write(activeJob);
        ctx.Write(activeJobGrade);
        ctx.Write(lastLoginDate);
        ctx.Write(licenceIds);
        ctx.Write(itemsStore);
        ctx.Write(openTickets);
        ctx.Write(fractionId);
        ctx.Write(fractionWherePlayerCanJoin);
        ctx.Write(fraction);
    }

    void IncreaseOnlineTime() {
        int onlineTime = onlineTimeMap.Get(activeJob);
        if(!onlineTime) onlineTime = 0;

        onlineTimeMap.Set(activeJob, onlineTime + 1);
    }

    void ArrestCountDown() {
        --arrestTimeInMinutes;
    }

    void ArrestPlayer(string reason, int time) {
        arrestTimeInMinutes = time;
        arrestReason = reason;
    }

    override string GetActiveJob() {
        if(activeJob == "") {
            activeJob = DAY_Z_LIFE_JOB_CIVIL;
            Save();
        }
        return activeJob;
    }

    void SetJobGrade(string grade) {
        activeJobGrade = grade;
        jobGradeMap.Set(activeJob, grade);
    }

    void UpdateActiveJob(string job) {
        activeJob = job;
        activeJobGrade = GetLastJobRank(job);
    }

    void UpdateOnlineTime() {
        int onlineTime = onlineTimeMap.Get(activeJob);
        if(!onlineTime) onlineTime = 0;

        onlineTimeMap.Set(activeJob, onlineTime + 1);
    }

    void ResetOnlineTime() {
        onlineTimeMap.Set(activeJob, 0);
    }

    void UpdateJob(string jobName, bool isJob, string rank) {
        jobMap.Set(jobName, isJob);
        jobGradeMap.Set(jobName, rank);

        if(IsActiveJob(jobName)) {
            this.activeJobGrade = rank;
        }

        ResetJobCivil();
    }

    private void ResetJobCivil() {
        if(!IsActiveAsCivil()) return;
        this.activeJobGrade = "Rekrut";
    }

    void UpdateName(string _playerName) {
        this.playerName = _playerName;
        lastLoginDate = new DZLDate();
    }

    void LoosPlayerInventoryMoney() {
        money = 0;
    }

    bool AddMoneyToPlayer(int moneyCount) {
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

        money += moneyCount;

        return true;
    }

    void AddMoneyToPlayerBank(int moneyCount) {
        DZLLogMoneyTransaction(dayZPlayerId, "bank", bank, bank + moneyCount, moneyCount);
        bank += moneyCount;
    }

    void PlayerHasDied() {
        DZLLogMoneyTransaction(dayZPlayerId, "has died", money, 0, money * -1);
        money = 0;
    }

    void SaveItems(PlayerBase _player) {
        itemsStore = new array<ref DZLStoreItem>;
        DZLStoreItem items = new DZLStoreItem;
        items.Init(_player, _player.GetPosition(), true, false);

        itemsStore.Insert(items);
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

        return moneyBankAdd;
    }

    void BuyLicence(DZLCraftLicence licenceToBuy) {
        AddMoneyToPlayer(-licenceToBuy.price);
        licenceIds.Insert(licenceToBuy.GetId());
    }

    void AddTicket(int value, string reason) {
        openTickets.Insert(new DZLTicket(value, reason));
    }

    void RemoveTicketById(string id) {
        foreach(int index, DZLTicket ticket: openTickets) {
            if(id == ticket.GetId()) {
                openTickets.Remove(index);
                Save();
                return;
            }
        }
    }

    override DZLFraction GetFraction() {
        fraction = DZLDatabaseLayer.Get().GetFraction(fractionId);

        return fraction;
    }

    void RemoveFraction(string _fractionId) {
        if(this.fractionId == _fractionId) {
            this.fractionId = "";
            fraction = null;
        }
    }

    void SetFraction(DZLFraction _fraction) {
        this.fraction = _fraction;
        this.fractionId = fraction.GetId();
        fractionWherePlayerCanJoin = new array<string>;
    }

    void UpdateFraction(DZLFraction _fraction) {
        if(fractionId != _fraction.GetId()) return;

        this.fraction = _fraction;
        this.fractionId = fraction.GetId();
    }

    void RemovePotentialFraction(string _fractionId) {
        foreach(int key, string fractionIdCanJoin: fractionWherePlayerCanJoin) {
            if(_fractionId == fractionIdCanJoin) {
                fractionWherePlayerCanJoin.Remove(key);
                break;
            }
        }
    }

    void AddPotentialFraction(string _fractionId) {
        if(IsInAnyFraction()) return;

        foreach(int key, string fractionIdCanJoin: fractionWherePlayerCanJoin) {
            if(_fractionId == fractionIdCanJoin) {
                return;
            }
        }

        fractionWherePlayerCanJoin.Insert(_fractionId);
    }

    void ResetPotentialFractions() {
        fractionWherePlayerCanJoin = new array<string>;
    }

    protected bool LoadJSON(string tmpFileName) {
        if(FileExist(path + tmpFileName + ".json")) {
            JsonFileLoader<DZLPlayer>.JsonLoadFile(path + tmpFileName + ".json", this);
            DeleteFile(path + tmpFileName + ".json");
            return true;
        }
        return false;
    }

}
