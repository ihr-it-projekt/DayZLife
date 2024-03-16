modded class DZLActionOpenLoadOutMenu: ActionInteractBase {

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if(!super.ActionCondition(player, target, item)) return false;

        DZLBaseActionObject objectTarget = DZLBaseActionObject.Cast(target.GetObject());
        DZLLoadoutActionObject loadOutObject = DZLLoadoutActionObject.Cast(objectTarget);

        DZLPlayer dzlPlayer = player.GetDZLPlayer();
        string job = dzlPlayer.GetActiveJob();
        if(loadOutObject.IsLoadOut(job)) return true;

        DZLSendMessage(player.GetIdentity(), "#wrong_job");
        return false;
    }
}
