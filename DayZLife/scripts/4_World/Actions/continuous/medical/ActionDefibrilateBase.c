modded class ActionDefibrilateBase
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if (GetGame().IsClient() && player.dzlPlayer && player.dzlPlayer.IsActiveAsMedic()) {
			return super.ActionCondition(player, target, item);
		}
		
		return false;
    }
}
