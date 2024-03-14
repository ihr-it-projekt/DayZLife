modded class ActionDefibrilateTarget {
    override void CreateConditionComponents() {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new CCTNone;
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        PlayerBase targetPlayer = PlayerBase.Cast(target.GetObject());

        if(!targetPlayer) return false;

        if(targetPlayer == player) {
            return false;
        }

        if(GetGame().IsClient() && player.GetDZLPlayer() && player.GetDZLPlayer().IsActiveJob(DAY_Z_LIFE_JOB_MEDIC) && !targetPlayer.IsAlive()) {
            Defibrillator defib = Defibrillator.Cast(item);
            if(!defib) return false;
            return CanDefibrillate(defib);;
        } else if(GetGame().IsServer() && !targetPlayer.IsAlive()) {
            DZLEmergencies emergencies = DZLDatabaseLayer.Get().GetEmergencies();
            return emergencies.HasEmergency(targetPlayer.GetPlayerId()));
        }

        return false;
    }

    override void OnFinishProgressServer(ActionData action_data) {
        super.OnFinishProgressServer(action_data);
        DZLEmergencies emergencies = DZLDatabaseLayer.Get().GetEmergencies();

        PlayerBase target = PlayerBase.Cast(action_data.m_Target.GetObject());
        PlayerIdentity targetIdent = target.GetIdentity();

        if(!targetIdent) return;

        DZLPlayer dzlPlayer = target.GetDZLPlayer();
        string targetId = targetIdent.GetId();

        if(target && emergencies.HasEmergency(targetId)) {
            emergencies.Remove(targetId);
            dzlPlayer.AddMoneyToPlayerBank(DZLConfig.Get().medicConfig.priceMedicHeal * -1);
            dzlPlayer.SetWillHealByMedic();
            dzlPlayer.SaveItems(target);
            action_data.m_Player.GetDZLPlayer().AddMoneyToPlayerBank(DZLConfig.Get().medicConfig.priceMedicHeal);
            GetGame().RPCSingleParam(null, DZL_RPC.ALL_WAS_HEALED_RESPONSE, null, true, targetIdent);
            target.Delete();
            DZLSendMessage(action_data.m_Player.GetIdentity(), "#player_travels_between_worlds");
        }
    }

}
