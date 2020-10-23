class DZLPlayerInventory
{
	bool PlayerHasEnoughMoney(PlayerBase player, int money) {
        int amount = GetPlayerMoneyAmount(player);
        return money <= amount;
    }

    float GetPlayerMoneyAmount(PlayerBase player)
    {
        if (!player) {
            return 0;
        }
        if (!DayZGame().IsClient()) {
            DZLPlayer playerConfig = new DZLPlayer(player.GetIdentity().GetId());
            return playerConfig.money;
        } else {
            return player.dzlPlayer.money;
        }
	}

    void AddMoneyToPlayer(PlayerBase player, float moneyCount) {
        if (!DayZGame().IsClient()) {
			DZLPlayer playerConfig = new DZLPlayer(player.GetIdentity().GetId());
			playerConfig.AddMoneyToPlayer(moneyCount);
		    GetGame().RPCSingleParam(player, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(playerConfig), true, player.GetIdentity());
		}
    }
        
};