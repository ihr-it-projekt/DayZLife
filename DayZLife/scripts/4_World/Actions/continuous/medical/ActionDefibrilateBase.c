modded class ActionDefibrilateBase
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        PlayerBase targetPlayer = PlayerBase.Cast(target.GetObject());
        if (!targetPlayer) return false;

        if (GetGame().IsClient() && player.GetDZLPlayer() && player.GetDZLPlayer().IsActiveAsMedic()) {
			return !targetPlayer.IsAlive();
		} else if(GetGame().IsServer() && !targetPlayer.IsAlive()) {
		    
            PlayerIdentity targetIdent = targetPlayer.GetIdentity();

            if (!targetIdent) return false;
		    DZLEmergencies emergencies = DZLDatabaseLayer.Get().GetEmergencies();
		    string targetId = targetIdent.GetId();
		    
		    if (!emergencies.HasEmergency(targetId)) return false;

			return super.ActionCondition(player, target, item);
		}
		
		return false;
    }
}
