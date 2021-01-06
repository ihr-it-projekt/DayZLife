modded class ActionCheckPulse
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item){
        if(!target.GetObject()) return false;

        if (!PlayerBase.Cast(target.GetObject()).IsDZLPlayer()) {
            return false;
        }

        return super.ActionCondition(player, target, item);
	}
}
