class ActionStopRobBank: ActionInteractBase {
    ref DZLBankingConfig config;

    DZLBankingConfig GetConfig() {
        if (!config) {
            config = DZLConfig.Get().bankConfig;
        }

        return config;
    }

    void ActionStopRobBank() {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
        m_HUDCursorIcon = CursorIcons.None;
    }

    override string GetText() {
        return "#stop_rob_bank";
    }

    override void CreateConditionComponents() {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new DZL_CCTActionObject;
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item ) {
        if (GetGame().IsClient()) {
            if (!player.GetConfig()) return false;
            config = player.GetConfig().bankConfig;
        } else {
            GetConfig();
        }

        DZLBaseActionObject objectTarget = DZLBaseActionObject.Cast(target.GetObject());

        if (!objectTarget || !objectTarget.IsBank()) return false;

        if (GetGame().IsServer()) {
            if (DZLDatabaseLayer.Get().GetBank().RaidRuns() || DZLDatabaseLayer.Get().GetBank().HasMoneyToRaid()) {
                return true;
            }
            DZLSendMessage(player.GetIdentity(), "#no_raid_has_started");
            return false;
        }
        return true;
    }

    override void OnStartServer(ActionData action_data) {
        GetConfig();
        PlayerBase player = action_data.m_Player;

        if (player) {
            vector playerPosition = action_data.m_Player.GetPosition();
            DZLBank bank = DZLDatabaseLayer.Get().GetBank();
            if (bank && bank.GetRaidPosition() && vector.Distance(bank.GetRaidPosition(), playerPosition) <= config.maximumRaidDistanceToBank) {
                bank.StopRaid();
                DZLSendMessage(null, "#bank_rob_was_stopped");
                DZLLogRaid(player.GetPlayerId(), "stop bank raid", "bank", player.GetPosition());
                return;
            }
        }
    }
};
