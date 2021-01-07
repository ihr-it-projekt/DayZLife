class DZLBankListener
{
    ref DZLBankingConfig config;

    void DZLBankListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
        config = DZLConfig.Get().bankConfig;
    }

    void ~DZLBankListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
		if (!DZLLicenceCheck.Get().HasActiveLicence(sender)) return;
        if (rpc_type == DAY_Z_LIFE_PLAYER_DEPOSIT_AT_BANK_DATA) {
            autoptr Param2<PlayerBase, int> paramDeposit;
            string message = "";
            if (ctx.Read(paramDeposit)){
                DZLPlayer dzlPlayer = DZLDatabaseLayer.Get().GetPlayer(paramDeposit.param1.GetIdentity().GetId());
				DZLBank bank = DZLDatabaseLayer.Get().GetBank();
				if (!bank.CanUseBank(config.raidCoolDownTimeInSeconds)) {
					message = "#bank_can_not_be_used_in_moment";
				} else if(paramDeposit.param2 >= dzlPlayer.GetMoney() || paramDeposit.param2 <= dzlPlayer.GetBankMoney()) {
                    bank.AddMoney(paramDeposit.param2 * -1);
                    dzlPlayer.AddMoneyToPlayer(paramDeposit.param2);
                    dzlPlayer.AddMoneyToPlayerBank(paramDeposit.param2 * -1);

                    GetGame().RPCSingleParam(paramDeposit.param1, DAY_Z_LIFE_PLAYER_BANK_DATA_RESPONSE, new Param1<ref DZLBank>(bank), true);
                    GetGame().RPCSingleParam(paramDeposit.param1, DAY_Z_LIFE_EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, new Param1<ref DZLPlayer>(null), true, sender);
                    message = "#money_transfer_successful";
                } else {
                    message = "#error_not_enough_money_to_transfer";
                }
                DZLSendMessage(sender, message);
            }
        } else if (rpc_type == DAY_Z_LIFE_PLAYER_DEPOSIT_TO_PLAYER) {
            autoptr Param3<PlayerBase, DZLPlayerBankInfo, int> paramDepositPlayer;
            string messageDeposit = "";
            if (ctx.Read(paramDepositPlayer)){
                DZLPlayer dzlPlayerSender = DZLDatabaseLayer.Get().GetPlayer(paramDepositPlayer.param1.GetIdentity().GetId());
                DZLPlayer dzlPlayerReciver = DZLDatabaseLayer.Get().GetPlayer(paramDepositPlayer.param2.id);
				
				array<Man> allPlayers = new array<Man>;
            	GetGame().GetPlayers(allPlayers);

				Man playerFound;
				foreach(Man player: allPlayers) {
					if (player.GetIdentity().GetId() == paramDepositPlayer.param2.id) {
						playerFound = player;
						break;
					}
				}
				
				if (!playerFound) {
					messageDeposit = "#reciver_for_deposit_is_not_longer_online";
				}
				
				DZLBank bankTransfer = DZLDatabaseLayer.Get().GetBank();
				if (!bankTransfer.CanUseBank(config.raidCoolDownTimeInSeconds)) {
					messageDeposit = "#bank_can_not_be_used_in_moment";
				} else if ("" == messageDeposit) {
					if(dzlPlayerSender.GetAllMoney() >= paramDepositPlayer.param3) {
						int moneyBankAdd = dzlPlayerSender.DepositMoneyToOtherPlayer(dzlPlayerReciver, paramDepositPlayer.param3);

						bankTransfer.AddMoney(moneyBankAdd);
						
						GetGame().RPCSingleParam(paramDepositPlayer.param1, DAY_Z_LIFE_PLAYER_BANK_DATA_RESPONSE, new Param1<ref DZLBank>(bankTransfer), true);
                    	GetGame().RPCSingleParam(paramDepositPlayer.param1, DAY_Z_LIFE_EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, new Param1<ref DZLPlayer>(null), true, sender);
                    	GetGame().RPCSingleParam(playerFound, DAY_Z_LIFE_EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, new Param1<ref DZLPlayer>(null), true, playerFound.GetIdentity());
					} else {
						messageDeposit = "#error_not_enough_money_to_transfer";
					}
					
					messageDeposit = "#money_transfer_successful";
                }
                GetGame().RPCSingleParam(paramDepositPlayer.param1, DAY_Z_LIFE_PLAYER_DEPOSIT_TO_PLAYER_RESPONSE, new Param3<ref DZLPlayer, ref DZLBank, string>(dzlPlayerSender, bankTransfer, messageDeposit), true, sender);
            }
        } else if (rpc_type == DAY_Z_LIFE_MONEY_TRANSFER) {
            autoptr Param3<PlayerBase, PlayerBase, int> paramDepositPlayerPlayer;
            string messageDepositPP = "";
            if (ctx.Read(paramDepositPlayerPlayer)){
                DZLPlayer dzlPlayerSenderPP = DZLDatabaseLayer.Get().GetPlayer(paramDepositPlayerPlayer.param1.GetIdentity().GetId());
                DZLPlayer dzlPlayerReciverPP = DZLDatabaseLayer.Get().GetPlayer(paramDepositPlayerPlayer.param2.GetIdentity().GetId());

				if(dzlPlayerSenderPP.GetMoney() >= paramDepositPlayerPlayer.param3) {
				    messageDepositPP = "#money_transfer_successful";
                    dzlPlayerSenderPP.DepositMoneyFromPlayerToOtherPlayer(dzlPlayerReciverPP, paramDepositPlayerPlayer.param3);
                    GetGame().RPCSingleParam(paramDepositPlayerPlayer.param1, DAY_Z_LIFE_EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, new Param1<ref DZLPlayer>(null), true, sender);
                    GetGame().RPCSingleParam(paramDepositPlayerPlayer.param2, DAY_Z_LIFE_EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, new Param1<ref DZLPlayer>(null), true, paramDepositPlayerPlayer.param2.GetIdentity());
                } else {
                    messageDepositPP = "#error_not_enough_money_to_transfer";
                }
				GetGame().RPCSingleParam(paramDepositPlayerPlayer.param1, DAY_Z_LIFE_MONEY_TRANSFER_RESPONSE, new Param1<string>(messageDepositPP), true, sender);
            }
        } else if (rpc_type == DAY_Z_LIFE_PLAYER_BANK_DATA) {
            autoptr Param1<PlayerBase> paramGetBankData;
            if (ctx.Read(paramGetBankData)){
                GetGame().RPCSingleParam(paramGetBankData.param1, DAY_Z_LIFE_PLAYER_BANK_DATA_RESPONSE, new Param1<ref DZLBank>(DZLDatabaseLayer.Get().GetBank()), true, sender);
            }
        } else if (rpc_type == DAY_Z_LIFE_ALL_PLAYER_IDENT_DATA) {
			array<Man> _players = new array<Man>;
            GetGame().GetPlayers(_players);
			
			array<ref DZLPlayerBankInfo> collection = new array<ref DZLPlayerBankInfo>;
			
			if (_players) {
				foreach(Man _player: _players) {
					collection.Insert(new DZLPlayerBankInfo(_player.GetIdentity().GetId(), _player.GetIdentity().GetName()));
				}
			}
			
			GetGame().RPCSingleParam(target, DAY_Z_LIFE_ALL_PLAYER_IDENT_DATA_RESPONSE, new Param1<ref array<ref DZLPlayerBankInfo>>(collection), true, sender);
        }
    }
}
