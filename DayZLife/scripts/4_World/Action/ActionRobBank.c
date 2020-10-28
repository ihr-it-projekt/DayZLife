class ActionRobBank: ActionInteractBase
{
    ref DZLBankingConfig config;

    DZLBankingConfig GetConfig() {
        if (!config) {
            config = new DZLBankingConfig;
        }

        return config;
    }

	void ActionRobBank() {
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
        m_HUDCursorIcon = CursorIcons.None;
	}

	override string GetText() {
        return "#rob_bank";
    }

	override void CreateConditionComponents() {
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNone;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (player.GetInstanceType() == DayZPlayerInstanceType.INSTANCETYPE_SERVER) {
			PlayerBase other_player = PlayerBase.Cast(target.GetObject());
			EntityAI item_in_hands_source = player.GetHumanInventory().GetEntityInHands();

			if(!item_in_hands_source || !other_player) return false;

			bool hasItem = false;
			foreach (string itemForRaid: GetConfig().itemsCanUsedToRaidBank) {
			    if (item_in_hands_source.GetType() == itemForRaid) {
			        hasItem = true;
			        break;
			    }
			}

			if(!hasItem) return false;

			return other_player.IsDZLBank;
		}

		return true;
	}

	override void OnStartClient(ActionData action_data) {
	    super.OnStartClient(action_data);
		DebugMessageDZL("Start raid from client");
        GetGame().RPCSingleParam(action_data.m_Player, DAY_Z_LIFE_START_BANK_RAID, new Param1<ref PlayerBase>(action_data.m_Player), true, action_data.m_Player.GetIdentity());
    }

};
