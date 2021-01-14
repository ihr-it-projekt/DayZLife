modded class DayZPlayerImplement
{
    override bool HandleDeath(int pCurrentCommandID) {
		bool isDead = super.HandleDeath(pCurrentCommandID);

        if (isDead && GetGame().IsServer()) {
            PlayerBase player = PlayerBase.Cast(this);

            if (player && player.GetIdentity() && DZLDatabaseLayer.Get().GetPlayer(player.GetIdentity().GetId())) {
                DZLPlayer dzlPlayer = DZLDatabaseLayer.Get().GetPlayer(player.GetIdentity().GetId());

                if (dzlPlayer.WillDie() && dzlPlayer.HasMoney()) {
                    player.SetMoneyPlayerIsDead(dzlPlayer.GetMoney());
                    dzlPlayer.PlayerHasDied();
                }
            }
            player.Delete();
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(Delete, 2500);
        }
		
		return isDead;
    }

    
	override void ShowDeadScreen(bool show, float duration) {
		PlayerBase player = PlayerBase.Cast(this);
		
		string text = "#dayz_implement_dead";
		
		if (player) {
			DZLPlayer dzlPlayer = player.dzlPlayer;
			DebugMessageDZL("2");	
			if (dzlPlayer) {
				if (dzlPlayer.WillHealByMedic()) {
					text = "#you_will_healed";
				} else if (dzlPlayer.WillHealByHospital()) {
					text = "#you_will_healed_and_transport_to_hospital";
				}
			}
		}

        #ifndef NO_GUI
            if (show && IsPlayerSelected()) {
                GetGame().GetUIManager().ScreenFadeIn(0, text, FadeColors.BLACK, FadeColors.WHITE);
            } else {
                GetGame().GetUIManager().ScreenFadeOut(0);
            }

            if (duration > 0)
                GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(StopDeathDarkeningEffect, duration * 1000, false);
            else
                GetGame().GetCallQueue(CALL_CATEGORY_GUI).Call(StopDeathDarkeningEffect);
        #endif
	}

}
