class DZLPlayerInventory
{
	bool PlayerHasEnoughMoney(PlayerBase player, int money) {
        int amount = GetPlayerMoneyAmount(player);

        DebugMessageDZL("Has money: " + amount.ToString());
        DebugMessageDZL("must have money: " + money.ToString());

        return money <= amount;
    }

    float GetPlayerMoneyAmount(PlayerBase player)
    {
        if (!player) {
            return 0;
        }
        if (!DayZGame().IsClient()) {
            DZLPlayer playerConfig = new DZLPlayer(player);
            return playerConfig.money;
        } else {
            return player.dzlPlayer.money;
        }
	}

    void AddMoneyToPlayer(PlayerBase player, float moneyCount) {
        if (!DayZGame().IsClient()) {
			DZLPlayer playerConfig = new DZLPlayer(player);
			playerConfig.AddMoneyToPlayer(moneyCount);
		    GetGame().RPCSingleParam(player, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(playerConfig), true, player.GetIdentity());
		}
    }
        
};