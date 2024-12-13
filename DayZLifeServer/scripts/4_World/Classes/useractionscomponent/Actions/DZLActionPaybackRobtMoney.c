modded class DZLActionPaybackRobtMoney {

    override void OnEndServer(ActionData action_data) {
        DZLPlayer dzlPlayer = action_data.m_Player.GetDZLPlayer();
        PlayerIdentity ident = action_data.m_Player.GetIdentity();
        ref DZLBankingConfig config = DZLConfig.Get().bankConfig;
        DZLBank bank = DZLDatabaseLayer.Get().GetBank();

        if(!bank.CanUseBank(config.raidCoolDownTimeInSeconds / 10)) {
            DZLSendMessage(ident, "#bank_can_not_be_used_in_moment");
            return;
        }

        if(!bank.CanPaybackRobtMoney(dzlPlayer)) {
            DZLSendMessage(ident, "#error_not_enough_money_payback " + bank.GetLastRaidMoney());
            return;
        }

        int moneyPaidBack = bank.PaybackRobtMoney(dzlPlayer);
        int bonus = moneyPaidBack / 100 * config.bonusPerCopWhenRobtMoneyWillPaidBackInPercent;

        array<Man> allPlayers = new array<Man>;
        g_Game.GetPlayers(allPlayers);

        foreach(Man playerMan: allPlayers) {
            PlayerBase player = PlayerBase.Cast(playerMan);
            PlayerIdentity playerIdentity = player.GetIdentity();
            if(!player) continue;

            DZLPlayer dzlPlayerCop = player.GetDZLPlayer();

            if(!dzlPlayerCop.IsActiveJob(DAY_Z_LIFE_JOB_COP)) continue;

            dzlPlayerCop.AddMoneyToPlayerBank(bonus);
        }

        g_Game.RPCSingleParam(null, DZL_RPC.PLAYER_BANK_DATA_RESPONSE, new Param1<ref DZLBank>(bank), true);
        DZLSendMessage(ident, "#payback_was_successful " + moneyPaidBack);
    }
};
