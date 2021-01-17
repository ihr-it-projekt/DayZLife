class DZLPlayerInventory
{
	bool PlayerHasEnoughMoney(PlayerBase player, int money) {
        DZLPlayer dzlPlayer = player.GetDZLPlayer();
        return dzlPlayer.HasEnoughMoney(money);
    }

    int GetPlayerMoneyAmount(PlayerBase player) {
        if (!player) {
            return 0;
        }
        DZLPlayer dzlPlayer = player.GetDZLPlayer();
        return dzlPlayer.GetMoney();
	}

    void AddMoneyToPlayer(PlayerBase player, float moneyCount) {
        DZLPlayer dzlPlayer = player.GetDZLPlayer();
        dzlPlayer.AddMoneyToPlayer(moneyCount);
        GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, null, true, player.GetIdentity());
    }
};
