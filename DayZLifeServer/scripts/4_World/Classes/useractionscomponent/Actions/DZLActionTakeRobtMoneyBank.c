modded class DZLActionTakeRobtMoneyBank {


    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if(!super.ActionCondition(player, target, item)) return false;

        DZLBank bank = DZLDatabaseLayer.Get().GetBank();
        if(bank.RaidRuns()) {
            DZLSendMessage(player.GetIdentity(), "#raid_has_not_finished (" + bank.GetCountDownRaid() + "s)");
            return false;
        }

        if(!bank.HasMoneyToRaid()) {
            DZLSendMessage(player.GetIdentity(), "#dzl_safe_is_closed");
            return false;
        }

        if(vector.Distance(bank.GetRaidPosition(), player.GetPosition()) <= config.maximumRaidDistanceToBank) return true;

        DZLSendMessage(player.GetIdentity(), "#not_in_near_of_raided_bank");
        return false;
    }

    override void OnStartServer(ActionData action_data) {
        PlayerBase player = action_data.m_Player;

        if(!player) return;
        DZLBank bank = DZLDatabaseLayer.Get().GetBank();
        int money = bank.PlayerRaidBank(player.GetDZLPlayer(), config.percentOfMoneyWhenRaid);
        DZLSendMessage(null, "#bank_rob_was_successful " + money.ToString());
        DZLLogRaid(player.GetPlayerId(), "bank raid finished", "bank", player.GetPosition());

        g_Game.RPCSingleParam(null, DZL_RPC.PLAYER_BANK_DATA_RESPONSE, new Param1<ref DZLBank>(bank), true);
    }
};
