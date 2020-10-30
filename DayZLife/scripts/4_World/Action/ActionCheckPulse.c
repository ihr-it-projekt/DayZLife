modded class ActionCheckPulse
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item){
        if(!target.GetObject()) return false;

        if (PlayerBase.Cast(target.GetObject()).IsDZLBank || PlayerBase.Cast(target.GetObject()).IsLicencePoint) {
            return false;
        }

        return super.ActionCondition(player, target, item);
	}
}