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
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLaterByName(GetGame(), "ObjectDelete", 3000, false, new Param1<DayZPlayerImplement>(this));
        }
		
		return isDead;
    }

    

}
