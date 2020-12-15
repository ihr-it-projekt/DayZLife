modded class DayZPlayerImplement
{
    override bool HandleDeath(int pCurrentCommandID) {
        bool isDead = super.HandleDeath(pCurrentCommandID);

        if (isDead && GetGame().IsServer()) {
            PlayerBase player = PlayerBase.Cast(this);

            if (player) {
                DZLPlayer dzlPlayer = new DZLPlayer(player.GetIdentity().GetId());

                if (dzlPlayer.money > 0) {
                    player.SetMoneyPlayerIsDead(dzlPlayer.money);
                    dzlPlayer.PlayerHasDied();
                    GetGame().RPCSingleParam(player, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(dzlPlayer), true, player.GetIdentity());
                }
            }
        }
		
		return isDead;
    }

}
