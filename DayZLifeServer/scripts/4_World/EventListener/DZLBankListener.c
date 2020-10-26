class DZLBankListener
{
    ref DZLBankingConfig config;

    void DZLBankListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
        config = new DZLBankingConfig;
    }

    void ~DZLBankListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_PLAYER_DEPOSIT_AT_BANK_DATA) {
            autoptr Param2<PlayerBase, int> paramDeposit;
            string message = "";
            if (ctx.Read(paramDeposit)){
                DZLPlayer dzlPlayer = new DZLPlayer(paramDeposit.param1.GetIdentity().GetId());
				DZLBank bank = new DZLBank;
				if (!bank.CanUseBank(config.raidCoolDownTimeInSeconds)) {
					message = "#bank_can_not_be_used_in_moment";
				} else if(paramDeposit.param2 >= dzlPlayer.money || paramDeposit.param2 <= dzlPlayer.bank) {
                    bank.AddMoney(paramDeposit.param2 * -1);
                    dzlPlayer.AddMoneyToPlayer(paramDeposit.param2);
                    dzlPlayer.AddMoneyToPlayerBank(paramDeposit.param2 * -1);

                    GetGame().RPCSingleParam(paramDeposit.param1, DAY_Z_LIFE_PLAYER_BANK_DATA_RESPONSE, new Param1<ref DZLBank>(bank), true);
                    GetGame().RPCSingleParam(paramDeposit.param1, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(dzlPlayer), true, sender);
                    message = "#money_transfer_successful";
                } else {
                    message = "#error_not_enough_money_to_transfer";
                }
                GetGame().RPCSingleParam(paramDeposit.param1, DAY_Z_LIFE_PLAYER_DEPOSIT_AT_BANK_DATA_RESPONSE, new Param3<ref DZLPlayer, ref DZLBank, string>(dzlPlayer, bank, message), true, sender);
            }
        } else if (rpc_type == DAY_Z_LIFE_PLAYER_DEPOSIT_TO_PLAYER) {
            autoptr Param3<PlayerBase, DZLPlayerBankInfo, int> paramDepositPlayer;
            string messageDeposit = "";
            if (ctx.Read(paramDepositPlayer)){
                DZLPlayer dzlPlayerSender = new DZLPlayer(paramDepositPlayer.param1.GetIdentity().GetId());
                DZLPlayer dzlPlayerReciver = new DZLPlayer(paramDepositPlayer.param2.id);
				
				array<Man> allPlayers;
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
				
				DZLBank bankTransfer = new DZLBank;
				if (!bankTransfer.CanUseBank(config.raidCoolDownTimeInSeconds)) {
					messageDeposit = "#bank_can_not_be_used_in_moment";
				} else if ("" == messageDeposit) {
					if(dzlPlayerSender.money + dzlPlayerSender.bank >= paramDepositPlayer.param3) {
						dzlPlayerSender.DepositMoneyToOtherPlayer(dzlPlayerReciver, paramDepositPlayer.param3);
						
						GetGame().RPCSingleParam(paramDepositPlayer.param1, DAY_Z_LIFE_PLAYER_BANK_DATA_RESPONSE, new Param1<ref DZLBank>(bankTransfer), true);
                    	GetGame().RPCSingleParam(paramDepositPlayer.param1, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(new DZLPlayer(paramDepositPlayer.param1.GetIdentity().GetId())), true, sender);
                    	GetGame().RPCSingleParam(playerFound, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(new DZLPlayer(paramDepositPlayer.param2.id)), true, playerFound.GetIdentity());
					} else {
						messageDeposit = "#error_not_enough_money_to_transfer";
					}
					
					messageDeposit = "#money_transfer_successful";
                }
                GetGame().RPCSingleParam(paramDepositPlayer.param1, DAY_Z_LIFE_PLAYER_DEPOSIT_TO_PLAYER_RESPONSE, new Param3<ref DZLPlayer, ref DZLBank, string>(dzlPlayerSender, bankTransfer, messageDeposit), true, sender);
            }
        } else if (rpc_type == DAY_Z_LIFE_PLAYER_BANK_DATA) {
            autoptr Param1<PlayerBase> paramGetBankData;
            if (ctx.Read(paramGetBankData)){
                GetGame().RPCSingleParam(paramGetBankData.param1, DAY_Z_LIFE_PLAYER_BANK_DATA_RESPONSE, new Param1<ref DZLBank>(new DZLBank), true);
            }
        } else if (rpc_type == DAY_Z_LIFE_ALL_PLAYER_IDENT_DATA) {
			array<Man> _players;
            GetGame().GetPlayers(_players);
			
			array<ref DZLPlayerBankInfo> collection = new array<ref DZLPlayerBankInfo>;
			
			foreach(Man _player: _players) {
				collection.Insert(new DZLPlayerBankInfo(_player.GetIdentity().GetId(), _player.GetIdentity().GetName()));
				DebugMessageDZL(_player.GetIdentity().GetName());
			}
			
			GetGame().RPCSingleParam(target, DAY_Z_LIFE_ALL_PLAYER_IDENT_DATA_RESPONSE, new Param1<ref array<ref DZLPlayerBankInfo>>(collection), true, sender);
        }
    }
}