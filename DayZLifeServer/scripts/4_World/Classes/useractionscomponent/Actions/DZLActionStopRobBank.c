modded class DZLActionStopRobBank {
    ref DZLBankingConfig config;

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if(!super.ActionCondition(player, target, item)) return false;

        if(DZLDatabaseLayer.Get().GetBank().RaidRuns() || DZLDatabaseLayer.Get().GetBank().HasMoneyToRaid()) return true;

        DZLSendMessage(player.GetIdentity(), "#no_raid_has_started");
        return false;
    }

    override void OnStartServer(ActionData action_data) {
        PlayerBase player = action_data.m_Player;
        if(!player) return;

        vector playerPosition = action_data.m_Player.GetPosition();
        DZLBank bank = DZLDatabaseLayer.Get().GetBank();
        if(!bank) return;
        vector raidPosition = bank.GetRaidPosition();
        if(!raidPosition) return;

        if(vector.Distance(raidPosition, playerPosition) > config.maximumRaidDistanceToBank) return;

        bank.StopRaid();
        DZLSendMessage(null, "#bank_rob_was_stopped");
        DZLLogRaid(player.GetPlayerId(), "stop bank raid", "bank", player.GetPosition());
    }
};
