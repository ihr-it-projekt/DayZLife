class DZLBankListener
{
    ref DZLBank bank;

    void DZLBankListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
        bank = new DZLBank;
    }

    void ~DZLBankListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_PLAYER_DEPOSIT_AT_BANK_DATA) {
            autoptr Param2<PlayerBase, float> paramDeposit;
            string message = "";
            if (ctx.Read(paramDeposit)){
                DZLPlayer dzlPlayer = new DZLPlayer(paramDeposit.param1);
                if(paramDeposit.param2 >= dzlPlayer.money || paramDeposit.param2 <= dzlPlayer.bank) {
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
        } else if (rpc_type == DAY_Z_LIFE_PLAYER_BANK_DATA) {
            autoptr Param1<PlayerBase> paramGetBankData;
            if (ctx.Read(paramGetBankData)){
                GetGame().RPCSingleParam(paramGetBankData.param1, DAY_Z_LIFE_PLAYER_BANK_DATA_RESPONSE, new Param1<ref DZLBank>(bank), true);
            }
        }
    }
}