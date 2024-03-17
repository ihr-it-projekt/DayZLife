modded class DayZPlayerImplement {
    override bool HandleDeath(int pCurrentCommandID) {
        bool isDead = super.HandleDeath(pCurrentCommandID);
        PlayerBase player = PlayerBase.Cast(this);

        if(player && player.GetIdentity() && player.GetDZLPlayer()) {
            DZLPlayer dzlPlayer = player.GetDZLPlayer();

            if(dzlPlayer) {
                if(dzlPlayer.WillHealByMedic()) {
                    GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(Delete, DZLConfig.Get().medicConfig.deleteDeadBodyTimeWhenHealedByMedic * 1000);
                    player.RemoveAllItems();
                } else if(dzlPlayer.WillHealByHospital()) {
                    GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(Delete, 2500);
                    player.RemoveAllItems();
                } else if(isDead && dzlPlayer.HasMoney()) {
                    player.SetMoneyPlayerIsDead(dzlPlayer.GetMoney());
                    dzlPlayer.PlayerHasDied();
                }
            }
        }
        return isDead;
    }
}
