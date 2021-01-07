class DZLPlayerInventory
{
	bool PlayerHasEnoughMoney(PlayerBase player, int money) {
        DZLPlayer dzlPlayer = DZLDatabaseLayer.Get().GetPlayer(player.GetIdentity().GetId());
        return dzlPlayer.HasEnoughMoney(money);
    }

    int GetPlayerMoneyAmount(PlayerBase player) {
        if (!player) {
            return 0;
        }
        DZLPlayer dzlPlayer = DZLDatabaseLayer.Get().GetPlayer(player.GetIdentity().GetId());
        return dzlPlayer.GetMoney();
	}

    void AddMoneyToPlayer(PlayerBase player, float moneyCount) {
        DZLPlayer dzlPlayer = DZLDatabaseLayer.Get().GetPlayer(player.GetIdentity().GetId());
        dzlPlayer.AddMoneyToPlayer(moneyCount);
        GetGame().RPCSingleParam(player, DAY_Z_LIFE_EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, new Param1<ref DZLPlayer>(null), true, player.GetIdentity());
    }
};
