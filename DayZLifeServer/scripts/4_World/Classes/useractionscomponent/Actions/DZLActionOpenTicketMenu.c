modded class DZLActionOpenTicketMenu {

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if(!super.ActionCondition(player, target, item)) return false;

        PlayerBase targetPlayer = PlayerBase.Cast(target.GetObject());
        if(!targetPlayer.IsDZLPlayer()) return false;

        if(!targetPlayer || !targetPlayer.GetIdentity()) return false;

        DZLPlayer dzlPlayerPrisoner = targetPlayer.GetDZLPlayer();
        if(dzlPlayerPrisoner.IsActiveJob(DAY_Z_LIFE_JOB_COP)) return false;

        return true;
    }
}
