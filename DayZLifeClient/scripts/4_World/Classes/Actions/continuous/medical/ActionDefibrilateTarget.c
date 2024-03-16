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
}
