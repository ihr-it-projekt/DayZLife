modded class PlayerBase
{
    ref DZLBuyHouseMenu houseBuyMenu;
    ref DZLUpgradeHouseMenu houseUpgradeMenu;
    ref DZLConfig config;

	void ~PlayerBase() {
	    GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
	}

    override void SetActions() {
        super.SetActions();
        DebugMessageDZL("Create Player");
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
        Param1<PlayerBase> paramGetConfig = new Param1<PlayerBase>(this);
        GetGame().RPCSingleParam(paramGetConfig.param1, DAY_Z_LIFE_EVENT_GET_CONFIG, paramGetConfig, true);

        AddAction(ActionOpenBuyHouseMenu);
        AddAction(ActionOpenUpgradeHouseMenu);
    }


    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE) {
            DebugMessageDZL("GET config");
            Param1 <ref DZLConfig> configParam;

            if (ctx.Read(configParam)){
                this.config = configParam.param1;
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
        DebugMessageDZL("Initialize house buy menu");
        houseUpgradeMenu = new DZLUpgradeHouseMenu;
        houseUpgradeMenu.SetConfig(config);
		houseUpgradeMenu.SetHouseDefinition(definition);
		houseUpgradeMenu.SetTarget(target);

        return houseUpgradeMenu;
    }
}