class DZLBankListener: DZLBaseEventListener {
    ref DZLBankingConfig config;

    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        config = DZLConfig.Get().bankConfig;
        if(rpc_type == DZL_RPC.PLAYER_DEPOSIT_AT_BANK_DATA) {
            Param2<int, bool> paramDeposit;
            string message = "";
            if(ctx.Read(paramDeposit)) {
                DZLPlayer dzlPlayer = PlayerBase.Cast(target).GetDZLPlayer();
                if(!dzlPlayer || !dzlPlayer.dayZPlayerId) return;

                DZLBank bank = DZLDatabaseLayer.Get().GetBank();
                message = "#error_not_enough_money_to_transfer";
                if(!bank.CanUseBank(config.raidCoolDownTimeInSeconds)) {
                    message = "#bank_can_not_be_used_in_moment";
                } else if(!paramDeposit.param2) {
                    bool canSendMoney = paramDeposit.param1 >= dzlPlayer.GetMoney();
                    bool canTakeMoney = paramDeposit.param1 <= dzlPlayer.GetBankMoney();
                    if(canTakeMoney || canSendMoney) {
                        if(!dzlPlayer.AddMoneyToPlayer(paramDeposit.param1)) return;

                        bank.AddMoney(paramDeposit.param1 * -1);
                        dzlPlayer.AddMoneyToPlayerBank(paramDeposit.param1 * -1);

                        g_Game.RPCSingleParam(target, DZL_RPC.PLAYER_BANK_DATA_RESPONSE, new Param1<ref DZLBank>(bank), true);
                        g_Game.RPCSingleParam(null, DZL_RPC.EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, null, true, sender);
                        message = "#money_transfer_successful";
                    }
                } else if(paramDeposit.param2) {
                    bool canSendMoneyToFraction = dzlPlayer.HasFractionRightCanAccessBankAccount() && paramDeposit.param1 <= dzlPlayer.GetMoney();
                    bool canTakeMoneyToFraction = dzlPlayer.HasFractionRightCanGetMoneyFromBankAccount() && paramDeposit.param1 <= dzlPlayer.GetFraction().GetBankAccount();

                    if(canTakeMoneyToFraction || canSendMoneyToFraction) {
                        if(!dzlPlayer.AddMoneyToPlayer(paramDeposit.param1)) return;
                        bank.AddMoney(paramDeposit.param1 * -1);
                        dzlPlayer.GetFraction().AddMoney(paramDeposit.param1 * -1);

                        g_Game.RPCSingleParam(target, DZL_RPC.PLAYER_BANK_DATA_RESPONSE, new Param1<ref DZLBank>(bank), true);
                        g_Game.RPCSingleParam(null, DZL_RPC.EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, null, true, sender);
                        message = "#money_transfer_successful";
                    }
                }

                DZLSendMessage(sender, message);
            }
        } else if(rpc_type == DZL_RPC.PLAYER_DEPOSIT_TO_PLAYER) {
            Param3<DZLPlayerBankInfo, int, bool> paramDepositPlayer;
            string messageDeposit = "";
            if(ctx.Read(paramDepositPlayer)) {
                DZLPlayer dzlPlayerSender = PlayerBase.Cast(target).GetDZLPlayer();
                DZLPlayer dzlPlayerReceiver = DZLDatabaseLayer.Get().GetPlayer(paramDepositPlayer.param1.id);

                array<Man> allPlayers = new array<Man>;
                g_Game.GetPlayers(allPlayers);

                Man playerFound;
                foreach(Man player: allPlayers) {
                    if(player.GetIdentity().GetId() == paramDepositPlayer.param1.id) {
                        playerFound = player;
                        break;
                    }
                }

                if(!playerFound) {
                    messageDeposit = "#reciver_for_deposit_is_not_longer_online";
                }

                DZLBank bankTransfer = DZLDatabaseLayer.Get().GetBank();
                if(!bankTransfer.CanUseBank(config.raidCoolDownTimeInSeconds)) {
                    messageDeposit = "#bank_can_not_be_used_in_moment";
                } else if("" == messageDeposit) {
                    int money = dzlPlayerSender.GetAllMoney();
                    bool isFractionTransaction = false;

                    if(paramDepositPlayer.param3 && dzlPlayerSender.HasFractionRightCanGetMoneyFromBankAccount()) {
                        money = dzlPlayerSender.GetFraction().GetBankAccount();
                        isFractionTransaction = true;
                    }

                    if(money >= paramDepositPlayer.param2) {
                        if(isFractionTransaction) {
                            dzlPlayerSender.GetFraction().DepositMoneyFromFractionToOtherPlayer(dzlPlayerReceiver, paramDepositPlayer.param2);
                        } else {
                            int moneyBankAdd = dzlPlayerSender.DepositMoneyToOtherPlayer(dzlPlayerReceiver, paramDepositPlayer.param2);
                            bankTransfer.AddMoney(moneyBankAdd);
                        }

                        g_Game.RPCSingleParam(target, DZL_RPC.PLAYER_BANK_DATA_RESPONSE, new Param1<ref DZLBank>(bankTransfer), true);
                        g_Game.RPCSingleParam(null, DZL_RPC.EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, null, true, sender);
                        g_Game.RPCSingleParam(null, DZL_RPC.EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, null, true, playerFound.GetIdentity());
                    } else {
                        messageDeposit = "#error_not_enough_money_to_transfer";
                    }

                    messageDeposit = "#money_transfer_successful";
                }
                g_Game.RPCSingleParam(target, DZL_RPC.PLAYER_DEPOSIT_TO_PLAYER_RESPONSE, new Param3<ref DZLPlayer, ref DZLBank, string>(dzlPlayerSender, bankTransfer, messageDeposit), true, sender);
            }
        } else if(rpc_type == DZL_RPC.MONEY_TRANSFER) {
            Param2<PlayerBase, int> paramDepositPlayerPlayer;
            string messageDepositPP = "";
            if(ctx.Read(paramDepositPlayerPlayer)) {
                PlayerBase moneyGiverPlayer = PlayerBase.Cast(target);
                PlayerBase moneyReceiverPlayer = paramDepositPlayerPlayer.param1;
                DZLPlayer dzlPlayerSenderPP = moneyGiverPlayer.GetDZLPlayer();
                DZLPlayer dzlPlayerReceiverPP = moneyReceiverPlayer.GetDZLPlayer();

                if(dzlPlayerSenderPP.GetMoney() >= paramDepositPlayerPlayer.param2) {
                    messageDepositPP = "#money_transfer_successful";
                    dzlPlayerSenderPP.DepositMoneyFromPlayerToOtherPlayer(dzlPlayerReceiverPP, paramDepositPlayerPlayer.param2);
                    g_Game.RPCSingleParam(null, DZL_RPC.EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, null, true, sender);
                    g_Game.RPCSingleParam(null, DZL_RPC.EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, null, true, moneyReceiverPlayer.GetIdentity());
                } else {
                    messageDepositPP = "#error_not_enough_money_to_transfer";
                }
                DZLSendMessage(sender, messageDepositPP);
            }
        } else if(rpc_type == DZL_RPC.PLAYER_BANK_DATA) {
            g_Game.RPCSingleParam(PlayerBase.Cast(target), DZL_RPC.PLAYER_BANK_DATA_RESPONSE, new Param1<ref DZLBank>(DZLDatabaseLayer.Get().GetBank()), true, sender);
        } else if(rpc_type == DZL_RPC.ALL_PLAYER_IDENT_DATA) {
            array<Man> _players = new array<Man>;
            g_Game.GetPlayers(_players);

            array<ref DZLPlayerBankInfo> collection = new array<ref DZLPlayerBankInfo>;

            if(_players) {
                foreach(Man _player: _players) {
                    collection.Insert(new DZLPlayerBankInfo(_player.GetIdentity().GetId(), _player.GetIdentity().GetName()));
                }
            }

            g_Game.RPCSingleParam(target, DZL_RPC.ALL_PLAYER_IDENT_DATA_RESPONSE, new Param1<ref array<ref DZLPlayerBankInfo>>(collection), true, sender);
        }
    }
}
