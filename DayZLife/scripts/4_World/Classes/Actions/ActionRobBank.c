class ActionRobBank: ActionInteractBase
{
    ref DZLBankingConfig config;

    DZLBankingConfig GetConfig() {
        if (!config) {
            config = DZLConfig.Get().bankConfig;
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
		m_ConditionTarget = new DZL_CCTActionObject;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (GetGame().IsClient()) {
		    if (!player.GetConfig()) return false;
			config = player.GetConfig().bankConfig;
		} else {
		    if (!DZLLicenceCheck.Get().HasActiveLicence(player.GetIdentity())) return false;
			GetConfig();
		}

		DZLBaseActionObject objectTarget = DZLBaseActionObject.Cast(target.GetObject());

		if (!objectTarget || !objectTarget.IsBank()) return false;
		
		if (config) {
			EntityAI item_in_hands_source = player.GetHumanInventory().GetEntityInHands();

			if(!item_in_hands_source) return false;

			bool hasItem = false;
			foreach (string itemForRaid: config.itemsCanUsedToRaidBank) {
			    if (item_in_hands_source.GetType() == itemForRaid) {
			        hasItem = true;
			        break;
			    }
			}

			if(!hasItem) return false;

			if (!isInNearOfBankAndLocationIsEnabled(player)) return false;

            if (GetGame().IsServer()){
                if (!config.canStartRaidIfShopRaidRuns && DZLDatabaseLayer.Get().GetCrimeData().ShopRaidRuns()) {
                    DZLSendMessage(player.GetIdentity(), "#one_shop_rob_is_already_started");
                    return false;
                }

                if (config.raidIsCopControlled && config.minCountCopsForRaid > 0) {
                    if (DZLDatabaseLayer.Get().GetCopCount() < config.minCountCopsForRaid) {
                        DZLSendMessage(player.GetIdentity(), "#raid_can_not_start_to_less_players");
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
				DZLBank bank = DZLDatabaseLayer.Get().GetBank();
				if(bank.RaidRuns()) {
                    DZLSendMessage(player.GetIdentity(), "#raid_all_ready_started (" + bank.GetCountDownRaid() + "s)");
                    return false;
                }
				
				if(bank.HasMoneyToRaid()) {
                    DZLSendMessage(player.GetIdentity(), "#safe_is_open");
                    return false;
                }
            }

			return true;
		}

		return false;
	}

    override void OnStartServer(ActionData action_data) {
        GetConfig();
        PlayerBase player = action_data.m_Player;

        if (player) {
            vector playerPosition = action_data.m_Player.GetPosition();
            foreach(DZLBankingPosition position: config.positionOfBankingPoints) {
                if (position && position.position && vector.Distance(position.position, playerPosition) <= config.maximumRaidDistanceToBank){
					DZLBank bank = DZLDatabaseLayer.Get().GetBank();
										
                    bank.StartRaid(position.position, config.raidTimeBankInSeconds);
                    DZLSendMessage(null, "#bank_rob_was_started");
                    DZLLogRaid(player.GetPlayerId(), "start bank raid", "bank", player.GetPosition());
                    return;
                }
            }
        }
    }

    private bool isInNearOfBankAndLocationIsEnabled(PlayerBase player) {
        if (!player) {
            return false;
        }
        vector playerPosition = player.GetPosition();
        if (!playerPosition) {
            return false;
        }
        foreach(DZLBankingPosition position: config.positionOfBankingPoints) {
            if (position && position.position && vector.Distance(position.position, playerPosition) <= config.maximumRaidDistanceToBank){
                return position.raidIsEnabled;
            }
        }
        return false;
    }

};
