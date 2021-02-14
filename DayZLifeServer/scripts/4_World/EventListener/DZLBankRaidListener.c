class DZLBankRaidListener : Managed 
{
    void DZLBankRaidListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
    }

    void ~DZLBankRaidListener() {
       GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

	void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
		if (!DZLLicenceCheck.Get().HasActiveLicence(sender)) return;
        if (rpc_type == DAY_Z_LIFE_BANK_RAID_CANCELED) {
            DZLDatabaseLayer.Get().GetBank().StopRaid();
            DZLSendMessage(null, "#bank_rob_was_canceled");
        } else if (rpc_type == DAY_Z_LIFE_BANK_RAID_FINISHED) {
            DZLBank bank = DZLDatabaseLayer.Get().GetBank();
            bank.RaidIsFinished();
			PlayerBase _player = PlayerBase.Cast(target);
            DZLPlayer dzlPlayer = _player.GetDZLPlayer();
			DZLBankingConfig config = DZLConfig.Get().bankConfig;

            int money = bank.PlayerRaidBank(dzlPlayer, config.percentOfMoneyWhenRaid);
            DZLSendMessage(null, "#bank_rob_was_successful " + money.ToString());
            DZLLogRaid(_player.GetPlayerId(), "bank raid finished", "bank", _player.GetPosition());

            array<Man> allPlayers = new array<Man>;
            GetGame().GetPlayers(allPlayers);

            foreach(Man playerMan: allPlayers) {
                PlayerBase player = PlayerBase.Cast(playerMan);
                PlayerIdentity playerIdentity = player.GetIdentity();
                if (!player || !playerIdentity)  continue;

                GetGame().RPCSingleParam(null, DAY_Z_LIFE_PLAYER_BANK_DATA_RESPONSE, new Param1<ref DZLBank>(bank), true, playerIdentity);
                GetGame().RPCSingleParam(null, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(player.GetDZLPlayer()), true, playerIdentity);
            }
        }

    }



}
