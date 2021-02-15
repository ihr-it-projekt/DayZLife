class DZLActionPaybackRobtMoney: ActionInteractBase
{
    ref DZLBankingConfig config;

    DZLBankingConfig GetConfig(PlayerBase player) {
        if (!config) {
			if (GetGame().IsServer()) {
				config = DZLConfig.Get().bankConfig;
			} else {
				config = player.config.bankConfig;
			}
            
        }

        return config;
    }

	void DZLActionPaybackRobtMoney() {
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
        m_HUDCursorIcon = CursorIcons.None;
	}

	override string GetText() {
        return "#payback_robt_money";
    }

	override void CreateConditionComponents() {
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTCursor;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
		if(!target) return false;
        if(!target.GetObject()) return false;

        DZLBaseActionObject objectTarget = DZLBaseActionObject.Cast(target.GetObject());
        if (!objectTarget || !objectTarget.IsBank()) return false;
		
		if (!player.GetDZLPlayer() || !player.GetDZLPlayer().IsActiveAsCop()) return false;

        DZLBank bank;
        if (GetGame().IsServer()) {
            bank = DZLDatabaseLayer.Get().GetBank();
        } else {
            bank  = player.dzlBank;
        }

        if(!bank || bank.GetLastRaidMoney() == 0)  return false;

        return true;
	}

	override void OnEndServer(ActionData action_data) {
		DZLPlayer dzlPlayer = action_data.m_Player.GetDZLPlayer();
		PlayerIdentity ident = action_data.m_Player.GetIdentity();
		if (!DZLLicenceCheck.Get().HasActiveLicence(ident)) return;
		if (!dzlPlayer.IsActiveAsCop()) return;

		GetConfig(action_data.m_Player);
		DZLBank bank = DZLDatabaseLayer.Get().GetBank();

		if (!bank.CanUseBank(config.raidCoolDownTimeInSeconds / 10)) {
			DZLSendMessage(ident, "#bank_can_not_be_used_in_moment");
			return;
		}
		if (!bank.CanPaybackRobtMoney(dzlPlayer)) {
			DZLSendMessage(ident, "#error_not_enough_money_payback " + bank.GetLastRaidMoney());
			return;
		}

		int moneyPaidBack = bank.PaybackRobtMoney(dzlPlayer);
		int bonus = moneyPaidBack / 100 * config.bonusPerCopWhenRobtMoneyWillPaidBackInPercent;

		array<Man> allPlayers = new array<Man>;
        GetGame().GetPlayers(allPlayers);

        foreach(Man playerMan: allPlayers) {
            PlayerBase player = PlayerBase.Cast(playerMan);
            PlayerIdentity playerIdentity = player.GetIdentity();
            if (!player)  continue;

            DZLPlayer dzlPlayerCop = player.GetDZLPlayer();

            if (dzlPlayerCop.IsActiveAsCop()) {
                dzlPlayerCop.AddMoneyToPlayerBank(bonus);
                GetGame().RPCSingleParam(null, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(dzlPlayerCop), true, playerIdentity);
            }
            
            GetGame().RPCSingleParam(null, DAY_Z_LIFE_PLAYER_BANK_DATA_RESPONSE, new Param1<ref DZLBank>(bank), true, playerIdentity);
        }

		DZLSendMessage(ident, "#payback_was_successful " + moneyPaidBack);
    }
};
