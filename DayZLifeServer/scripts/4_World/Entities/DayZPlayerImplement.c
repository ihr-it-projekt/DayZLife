modded class DayZPlayerImplement {
    override bool HandleDeath(int pCurrentCommandID) {
        bool isDead = super.HandleDeath(pCurrentCommandID);
        PlayerBase player = PlayerBase.Cast(this);

        if(!player) return isDead;
        if(!player.GetIdentity()) return isDead;

        DZLPlayer dzlPlayer = player.GetDZLPlayer();
        if(!dzlPlayer) return isDead;

        if(isDead && dzlPlayer.HasMoney()) {
            player.SetMoneyPlayerIsDead(dzlPlayer.GetMoney());
            dzlPlayer.PlayerHasDied();
            return isDead;
        }

        return isDead;
    }
}
