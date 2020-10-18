modded class PlayerBase
{
    ref DZLBuyHouseMenu houseBuyMenu;
    ref DZLUpgradeHouseMenu houseUpgradeMenu;
    ref DZLConfig config;
	ref DZLPlayerHouse house;

	void ~PlayerBase() {
	    GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
	}

    override void SetActions() {
        super.SetActions();
        DebugMessageDZL("Create Player");
		
		if (GetGame().IsClient()) {
			GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
        	Param1<PlayerBase> paramGetConfig = new Param1<PlayerBase>(this);
        	GetGame().RPCSingleParam(paramGetConfig.param1, DAY_Z_LIFE_EVENT_GET_CONFIG, paramGetConfig, true);
        	GetGame().RPCSingleParam(paramGetConfig.param1, DAY_Z_LIFE_GET_PLAYER_BUILDING, paramGetConfig, true);
		}
        

        AddAction(ActionOpenBuyHouseMenu);
        AddAction(ActionOpenUpgradeHouseMenu);
    }


    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE) {
            Param1 <ref DZLConfig> configParam;
            DebugMessageDZL("Initialize DZLConfig");
            if (ctx.Read(configParam)){
                this.config = configParam.param1;
            }
        } else if (rpc_type == DAY_Z_LIFE_GET_PLAYER_BUILDING_RESPONSE) {
            Param1 <ref DZLPlayerHouse> houseParam;
            DebugMessageDZL("Initialize DZLPlayerHouse");
            if (ctx.Read(houseParam)){
                this.house = houseParam.param1;
            }
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
}