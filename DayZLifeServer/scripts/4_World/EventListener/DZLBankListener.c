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
        if (rpc_type == DAY_Z_LIFE_PLAYER_DEPOSIT_AT_BANK_DATA) {
            autoptr Param2<int, bool> paramDeposit;
            string message = "";
            if (ctx.Read(paramDeposit)){
                DZLPlayer dzlPlayer = PlayerBase.Cast(target).GetDZLPlayer();
				DZLBank bank = DZLDatabaseLayer.Get().GetBank();
				if (!bank.CanUseBank(config.raidCoolDownTimeInSeconds)) {
					message = "#bank_can_not_be_used_in_moment";
				} else if(!paramDeposit.param2 && paramDeposit.param1 >= dzlPlayer.GetMoney() || !paramDeposit.param2 && paramDeposit.param1 <= dzlPlayer.GetBankMoney()) {
                    bank.AddMoney(paramDeposit.param1 * -1);
                    dzlPlayer.AddMoneyToPlayer(paramDeposit.param1);
                    dzlPlayer.AddMoneyToPlayerBank(paramDeposit.param1 * -1);

                    GetGame().RPCSingleParam(target, DAY_Z_LIFE_PLAYER_BANK_DATA_RESPONSE, new Param1<ref DZLBank>(bank), true);
                    GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, null, true, sender);
                    message = "#money_transfer_successful";
                } else if(paramDeposit.param2 && dzlPlayer.HasFractionRightCanAccessBankAccount() && paramDeposit.param1 >= dzlPlayer.GetMoney() || dzlPlayer.HasFractionRightCanGetMoneyFromBankAccount() && paramDeposit.param2 && paramDeposit.param1 <= dzlPlayer.GetFraction().GetBankAccount()) {
                    bank.AddMoney(paramDeposit.param1 * -1);
                    dzlPlayer.AddMoneyToPlayer(paramDeposit.param1);
                    dzlPlayer.GetFraction().AddMoney(paramDeposit.param1 * -1);

                    GetGame().RPCSingleParam(target, DAY_Z_LIFE_PLAYER_BANK_DATA_RESPONSE, new Param1<ref DZLBank>(bank), true);
                    GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, null, true, sender);
                    message = "#money_transfer_successful";
                } else {
                    message = "#error_not_enough_money_to_transfer";
                }
                DZLSendMessage(sender, message);
            }
        } else if (rpc_type == DAY_Z_LIFE_PLAYER_DEPOSIT_TO_PLAYER) {
            autoptr Param3<DZLPlayerBankInfo, int, bool> paramDepositPlayer;
            string messageDeposit = "";
            if (ctx.Read(paramDepositPlayer)){
                DZLPlayer dzlPlayerSender = PlayerBase.Cast(target).GetDZLPlayer();
                DZLPlayer dzlPlayerReceiver = DZLDatabaseLayer.Get().GetPlayer(paramDepositPlayer.param1.id);
				
				array<Man> allPlayers = new array<Man>;
            	GetGame().GetPlayers(allPlayers);

				Man playerFound;
				foreach(Man player: allPlayers) {
					if (player.GetIdentity().GetId() == paramDepositPlayer.param1.id) {
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
				    int money = dzlPlayerSender.GetAllMoney();
				    bool isFractionTransaction = false;

                    if (paramDepositPlayer.param3 && dzlPlayerSender.HasFractionRightCanGetMoneyFromBankAccount()) {
                        money = dzlPlayerSender.GetFraction().GetBankAccount();
                        isFractionTransaction = true;
                    }

					if(money >= paramDepositPlayer.param2) {
					    if (isFractionTransaction) {
					        dzlPlayerSender.GetFraction().DepositMoneyFromFractionToOtherPlayer(dzlPlayerReceiver, paramDepositPlayer.param2);
					    } else {
						    int moneyBankAdd = dzlPlayerSender.DepositMoneyToOtherPlayer(dzlPlayerReceiver, paramDepositPlayer.param2);
						    bankTransfer.AddMoney(moneyBankAdd);
					    }

						GetGame().RPCSingleParam(target, DAY_Z_LIFE_PLAYER_BANK_DATA_RESPONSE, new Param1<ref DZLBank>(bankTransfer), true);
                    	GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, null, true, sender);
                    	GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, null, true, playerFound.GetIdentity());
					} else {
						messageDeposit = "#error_not_enough_money_to_transfer";
					}
					
					messageDeposit = "#money_transfer_successful";
                }
                GetGame().RPCSingleParam(target, DAY_Z_LIFE_PLAYER_DEPOSIT_TO_PLAYER_RESPONSE, new Param3<ref DZLPlayer, ref DZLBank, string>(dzlPlayerSender, bankTransfer, messageDeposit), true, sender);
            }
        } else if (rpc_type == DAY_Z_LIFE_MONEY_TRANSFER) {
            autoptr Param2<PlayerBase, int> paramDepositPlayerPlayer;
            string messageDepositPP = "";
            if (ctx.Read(paramDepositPlayerPlayer)){
                PlayerBase moneyGiverPlayer = PlayerBase.Cast(target);
                PlayerBase moneyReceiverPlayer = paramDepositPlayerPlayer.param1;
                DZLPlayer dzlPlayerSenderPP = moneyGiverPlayer.GetDZLPlayer();
                DZLPlayer dzlPlayerReceiverPP = moneyReceiverPlayer.GetDZLPlayer();

				if(dzlPlayerSenderPP.GetMoney() >= paramDepositPlayerPlayer.param2) {
				    messageDepositPP = "#money_transfer_successful";
                    dzlPlayerSenderPP.DepositMoneyFromPlayerToOtherPlayer(dzlPlayerReceiverPP, paramDepositPlayerPlayer.param2);
                    GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, null, true, sender);
                    GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, null, true, moneyReceiverPlayer.GetIdentity());
                } else {
                    messageDepositPP = "#error_not_enough_money_to_transfer";
                }
				DZLSendMessage(sender, messageDepositPP);
            }
        } else if (rpc_type == DAY_Z_LIFE_PLAYER_BANK_DATA) {
            GetGame().RPCSingleParam(PlayerBase.Cast(target), DAY_Z_LIFE_PLAYER_BANK_DATA_RESPONSE, new Param1<ref DZLBank>(DZLDatabaseLayer.Get().GetBank()), true, sender);
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
