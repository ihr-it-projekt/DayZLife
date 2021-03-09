class ActionTakeRobtMoneyShop: ActionInteractBase
{
    ref DZLCrimeConfig config;

    DZLCrimeConfig GetConfig() {
        if (!config) {
            config = DZLConfig.Get().crimeConfig;
        }

        return config;
    }

	void ActionTakeRobtMoneyBank() {
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
        m_HUDCursorIcon = CursorIcons.None;
	}

	override string GetText() {
        return "#take_robt_money";
    }

	override void CreateConditionComponents() {
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new DZL_CCTActionObject;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (GetGame().IsClient()) {
		    if (!player.GetConfig()) return false;
			config = player.GetConfig().crimeConfig;
		} else {
		    if (!DZLLicenceCheck.Get().HasActiveLicence(player.GetIdentity())) return false;
			GetConfig();
		}

		DZLBaseActionObject objectTarget = DZLBaseActionObject.Cast(target.GetObject());

		if (!objectTarget || !objectTarget.IsShopActionPoint()) return false;


		return true;
	}

    override void OnStartClient(ActionData action_data) {
        PlayerBase player = action_data.m_Player;

        if (player) {
            GetGame().RPCSingleParam(player, DAY_Z_LIFE_PAY_ROB_MONEY_FROM_SHOP, null, true);
        }
    }
};
