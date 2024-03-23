modded class DZLActionOpenArrestMenu {

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if(!super.ActionCondition(player, target, item)) return false;

        DZLPlayer dzlPlayerCop = player.GetDZLPlayer();

        PlayerBase targetPlayer = PlayerBase.Cast(target.GetObject());
        if(!targetPlayer || !targetPlayer.GetIdentity()) return false;

        DZLPlayer dzlPlayerPrisoner = targetPlayer.GetDZLPlayer();

        if(true == dzlPlayerPrisoner.IsActiveJob(DAY_Z_LIFE_JOB_COP) && true == dzlPlayerCop.IsActiveJob(DAY_Z_LIFE_JOB_COP)) return false;
        if(true == dzlPlayerPrisoner.IsActiveJob(DAY_Z_LIFE_JOB_ARMY) && true == dzlPlayerCop.IsActiveJob(DAY_Z_LIFE_JOB_ARMY)) return false;

        return true;
    }

}
