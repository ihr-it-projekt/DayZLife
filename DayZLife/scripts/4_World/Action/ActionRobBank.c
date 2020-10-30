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
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (GetGame().IsClient()) {
		    if (!player.config) return false;

			config = player.config.bankConfig;
		} else {
			GetConfig();
		}
		
		if (config) {
			PlayerBase other_player = PlayerBase.Cast(target.GetObject());
			EntityAI item_in_hands_source = player.GetHumanInventory().GetEntityInHands();

			if(!item_in_hands_source) return false;
			if(!other_player) return false;

			bool hasItem = false;
			foreach (string itemForRaid: player.config.bankConfig.itemsCanUsedToRaidBank) {
			    if (item_in_hands_source.GetType() == itemForRaid) {
			        hasItem = true;
			        break;
			    }
			}

			if(!hasItem) return false;
			if(!isInNearOfBankAndLocationIsEnabled(player)) return false;

			return other_player.IsDZLBank;
		}

		return false;
	}

	override void OnStartClient(ActionData action_data) {
	    super.OnStartClient(action_data);
		DebugMessageDZL("Start raid from client");
        GetGame().RPCSingleParam(action_data.m_Player, DAY_Z_LIFE_START_BANK_RAID, new Param1<ref PlayerBase>(action_data.m_Player), true, action_data.m_Player.GetIdentity());
    }

    private bool isInNearOfBankAndLocationIsEnabled(PlayerBase playerWhoStartedRaid) {
        if (!playerWhoStartedRaid) {
            return false;
        }
        vector playerPosition = playerWhoStartedRaid.GetPosition();
        if (!playerPosition) {
            return false;
        }
        foreach(DZLBankingPosition position: config.positionOfBankingPoints) {
            if (vector.Distance(position.position, playerPosition) <= config.maximumRaidDistanceToBank){
                return position.raidIsEnabled;
            }
        }
        return false;
    }

};
