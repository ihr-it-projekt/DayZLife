modded class DayZPlayerImplement
{
    override bool HandleDeath(int pCurrentCommandID) {
		bool isDead = super.HandleDeath(pCurrentCommandID);

        if (isDead && GetGame().IsServer() && DZLDatabaseLayer.Get()) {
            PlayerBase player = PlayerBase.Cast(this);

            if (player && player.GetIdentity() && DZLDatabaseLayer.Get().GetPlayer(player.GetIdentity().GetId())) {
                DZLPlayer dzlPlayer = DZLDatabaseLayer.Get().GetPlayer(player.GetIdentity().GetId());

                if (dzlPlayer.WillDie() && dzlPlayer.HasMoney()) {
                    player.SetMoneyPlayerIsDead(dzlPlayer.GetMoney());
                    dzlPlayer.PlayerHasDied();
                }
            }
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLaterByName(player, "DeleteSave", 3000, false);
        }
		
		return isDead;
    }

    
	override void ShowDeadScreen(bool show, float duration) {
		PlayerBase player = PlayerBase.Cast(this);
		
		show = false;
		
		if (player) {
			DZLPlayer dzlPlayer = player.dzlPlayer;
			
			if (dzlPlayer && !dzlPlayer.WillHealByMedic() && !dzlPlayer.WillHealByHospital()) {
				show = true;
			}
		}
		
		super.ShowDeadScreen(show, duration);
	}

}
