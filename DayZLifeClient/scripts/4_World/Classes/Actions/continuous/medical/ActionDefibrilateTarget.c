modded class ActionDefibrilateTarget {

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        Defibrillator defib = Defibrillator.Cast(item);
        if(!defib) return false;

        PlayerBase targetPlayer = PlayerBase.Cast(target.GetObject());
        if(!targetPlayer) return false;
        if(targetPlayer == player) return false;
        if(targetPlayer.IsAlive()) return false;

        DZLPlayer dzlPlayer = player.GetDZLPlayer();
        if(!dzlPlayer) return false;
        if(!dzlPlayer.IsActiveJob(DAY_Z_LIFE_JOB_MEDIC)) return false;

        return CanDefibrillate(defib);
    }
}
