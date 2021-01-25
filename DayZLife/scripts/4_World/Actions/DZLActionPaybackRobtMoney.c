class DZLActionPaybackRobtMoney: ActionInteractBase
{
    ref DZLBankingConfig config;

    DZLBankingConfig GetConfig() {
        if (!config) {
            config = DZLConfig.Get().bankConfig;
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
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item ) {
		PlayerBase other_player = PlayerBase.Cast(target.GetObject());

		return player.GetDZLPlayer().IsActiveAsCop() && other_player && other_player.IsDZLBank;
	}

	override void OnEndServer(ActionData action_data) {
		DZLPlayer dzlPlayer = action_data.m_Player.GetDZLPlayer();
		PLayerIdentity ident = action_data.m_Player.GetIdentity();
		if (!DZLLicenceCheck.Get().HasActiveLicence(player.GetIdentity())) return false;
		if (!dzlPlayer.IsActiveAsCop()) return;

		GetConfig();
		DZLBank bank = DZLDatabaseLayer.Get().GetBank();

		if (!bank.CanUseBank(config.raidCoolDownTimeInSeconds)) {
			DZLSendMessage(ident, "#bank_can_not_be_used_in_moment");
			return;
		}
		if (!bank.CanPaybackRobtMoney()) {
			DZLSendMessage(ident, "#error_not_enough_money_payback " + bank.GetLastRaidMoney());
			return;
		}

		DZLSendMessage(ident, "#payback_was_successful " + bank.PaybackRobtMoney(dzlPlayer));
    }
};
