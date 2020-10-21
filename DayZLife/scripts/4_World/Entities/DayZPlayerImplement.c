modded class DayZPlayerImplement
{
    override bool HandleDeath(int pCurrentCommandID) {
        bool isDead = super.HandleDeath(pCurrentCommandID);

        if (isDead && GetGame().IsServer()) {
            PlayerBase player = PlayerBase.Cast(this);

            DZLPlayer dzlPlayer = new DZLPlayer(player);

            player.moneyPlayerIsDead = dzlPlayer.money;

            dzlPlayer.PlayerHasDied();

            GetGame().RPCSingleParam(player, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(dzlPlayer), true, player.GetIdentity());
        }
		
		return isDead;
    }

}