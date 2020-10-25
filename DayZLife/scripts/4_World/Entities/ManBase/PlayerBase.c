modded class PlayerBase
{
    ref DZLBuyHouseMenu houseBuyMenu;
    ref DZLUpgradeHouseMenu houseUpgradeMenu;
    ref DZLBankingMenu bankingMenu;
    ref DZLConfig config;
	ref DZLPlayerHouse house;
	ref DZLPlayer dzlPlayer;
	ref DZLBank dzlBank;
	bool IsDZLBank = false;
	private int moneyPlayerIsDead = 0;
	bool IsRealPlayer = false;

	void ~PlayerBase() {
	    GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
	}

	override void Init() {
        super.Init();
        RegisterNetSyncVariableBool("IsDZLBank");
        RegisterNetSyncVariableBool("IsRealPlayer");
        RegisterNetSyncVariableInt("moneyPlayerIsDead", 0, 99999999999);
    }

    override void SetActions() {
        super.SetActions();

        AddAction(ActionOpenBuyHouseMenu);
        AddAction(ActionOpenUpgradeHouseMenu);
        AddAction(ActionOpenBankingMenu);
        AddAction(ActionRobMoney);
        AddAction(ActionRobBank);

        if (GetGame().IsClient()) {
            GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
            Param1<PlayerBase> paramGetConfig = new Param1<PlayerBase>(this);
            GetGame().RPCSingleParam(paramGetConfig.param1, DAY_Z_LIFE_EVENT_GET_CONFIG, paramGetConfig, true);
            GetGame().RPCSingleParam(paramGetConfig.param1, DAY_Z_LIFE_GET_PLAYER_BUILDING, paramGetConfig, true);
            GetGame().RPCSingleParam(paramGetConfig.param1, DAY_Z_LIFE_PLAYER_DATA, paramGetConfig, true);
            GetGame().RPCSingleParam(paramGetConfig.param1, DAY_Z_LIFE_PLAYER_BANK_DATA, paramGetConfig, true);
        }
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE) {
            Param1 <ref DZLConfig> configParam;
            DebugMessageDZL("Initialize DZLConfig");
            if (ctx.Read(configParam)){
                this.config = configParam.param1;
                IsRealPlayer = true;
            }
        } else if (rpc_type == DAY_Z_LIFE_GET_PLAYER_BUILDING_RESPONSE) {
            Param1 <ref DZLPlayerHouse> houseParam;
            DebugMessageDZL("Initialize DZLPlayerHouse");
            if (ctx.Read(houseParam)){
                this.house = houseParam.param1;
            }
        } else if (rpc_type == DAY_Z_LIFE_PLAYER_DATA_RESPONSE) {
            Param1 <ref DZLPlayer> dzlPlayerParam;
            DebugMessageDZL("Initialize DZLPlayer");
            if (ctx.Read(dzlPlayerParam)){
                this.dzlPlayer = dzlPlayerParam.param1;
            }
        } else if (rpc_type == DAY_Z_LIFE_PLAYER_BANK_DATA_RESPONSE) {
            Param1 <ref DZLBank> dzlBankParam;
            DebugMessageDZL("Initialize Bank");
            if (ctx.Read(dzlBankParam)){
                this.dzlBank = dzlBankParam.param1;
            }
        }
    }
	
	void CloseMenu() {
		if (houseBuyMenu && houseBuyMenu.IsVisible()) {
			houseBuyMenu.OnHide();
		} else if (houseUpgradeMenu && houseBuyMenu.IsVisible()) {
			houseUpgradeMenu.OnHide();
		} else if (bankingMenu && bankingMenu.IsVisible()) {
			bankingMenu.OnHide();
		}
	}

    DZLBuyHouseMenu GetHouseBuyMenu(DZLHouseDefinition definition, Building target) {
        DebugMessageDZL("Initialize house buy menu");
        houseBuyMenu = new DZLBuyHouseMenu;
        houseBuyMenu.SetConfig(config);
		houseBuyMenu.SetHouseDefinition(definition);
		houseBuyMenu.SetTarget(target);

        return houseBuyMenu;
    }

    DZLUpgradeHouseMenu GetHouseUpgradeMenu(DZLHouseDefinition definition, Building target) {
        DebugMessageDZL("Initialize house upgrade menu");
        houseUpgradeMenu = new DZLUpgradeHouseMenu;
        houseUpgradeMenu.SetConfig(config);
		houseUpgradeMenu.SetHouseDefinition(definition);
		houseUpgradeMenu.SetTarget(target);

        return houseUpgradeMenu;
    }
	
	DZLHouseDefinition FindHouseDefinition(Building building) {
		array<ref DZLHouseDefinition> houseConfigs = config.GetHouseDefinitions();
		foreach(DZLHouseDefinition definition: houseConfigs) {
                if (definition.houseType == building.GetType()) {
					return definition;
                }
            }
		return null;
	}
	
	DZLBankingMenu GetBankingMenu() {
		bankingMenu = DZLBankingMenu();
		bankingMenu.SetConfig(config);
		return bankingMenu;
	}

    void TransferFromDeadPlayer(DZLPlayer playerTarget) {
        playerTarget.AddMoneyToPlayer(moneyPlayerIsDead);
        moneyPlayerIsDead = 0;
    }

    float GetMoneyPlayerIsDead() {
        return moneyPlayerIsDead;
    }

    void SetMoneyPlayerIsDead(float money) {
        IsRealPlayer = false;
        moneyPlayerIsDead = money;
    }
}