class ActionRobShop: ActionInteractBase
{
    DZLCrimeConfig config;

    DZLCrimeConfig GetConfig() {
        if (!config) {
            config = DZLConfig.Get().crimeConfig;
        }

        return config;
    }

	void ActionRobShop() {
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
        m_HUDCursorIcon = CursorIcons.None;
	}

	override string GetText() {
        return "#rob_shop";
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
			GetConfig();
		}

		DZLBaseActionObject objectTarget = DZLBaseActionObject.Cast(target.GetObject());

		if (!objectTarget || !objectTarget.IsShopActionPoint()) return false;
		
		if (config) {
			EntityAI item_in_hands_source = player.GetHumanInventory().GetEntityInHands();

			if(!item_in_hands_source) return false;

			bool hasItem = false;
			foreach (string itemForRaid: config.robTools) {
			    if (item_in_hands_source.GetType() == itemForRaid) {
			        hasItem = true;
			        break;
			    }
			}

			if(!hasItem) return false;

            if (GetGame().IsServer()){
                if (config.raidIsCopControlled && config.minCountCopsForRaid > 0) {
                    if (DZLDatabaseLayer.Get().GetCopCount() < config.minCountCopsForRaid) {
                        DZLSendMessage(player.GetIdentity(), "#raid_can_not_start_to_less_cops");
                        return false;
                    }
                }

                if (config.raidTimeControlled) {
                    DZLDate date = new DZLDate;

                    if (date.hour < config.raidStartTimeHour || date.hour > config.raidEndTimeHour) {
                        DZLSendMessage(player.GetIdentity(), "#raid_can_not_start_wrong_time");
                        return false;
                    } else if ((date.hour == config.raidEndTimeHour && date.minute > config.raidEndTimeMinute) || (date.hour == config.raidStartTimeHour && date.minute < config.raidStartTimeMinute)) {
                        DZLSendMessage(player.GetIdentity(), "#raid_can_not_start_wrong_time");
                        return false;
                    } 
                }
            }

			return true;
		}

		return false;
	}

    override void OnStartClient(ActionData action_data) {
        PlayerBase player = action_data.m_Player;

        if (player) {
            GetGame().RPCSingleParam(player, DAY_Z_LIFE_START_ROB_MONEY_FROM_SHOP, null, true);
        }
    }
};
