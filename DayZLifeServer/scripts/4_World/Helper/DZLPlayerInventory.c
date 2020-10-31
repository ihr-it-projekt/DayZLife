class DZLPlayerInventory
{
	bool PlayerHasEnoughMoney(PlayerBase player, int money) {
        DZLPlayer dzlPlayer = new DZLPlayer(player.GetIdentity().GetId());
        return dzlPlayer.HasEnoughMoney(money);
    }

    int GetPlayerMoneyAmount(PlayerBase player) {
        if (!player) {
            return 0;
        }
        DZLPlayer dzlPlayer = new DZLPlayer(player.GetIdentity().GetId());
        return dzlPlayer.money;
	}

    void AddMoneyToPlayer(PlayerBase player, float moneyCount) {
        DZLPlayer dzlPlayer = new DZLPlayer(player.GetIdentity().GetId());
        dzlPlayer.AddMoneyToPlayer(moneyCount);
        GetGame().RPCSingleParam(player, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(dzlPlayer), true, player.GetIdentity());
    }
};