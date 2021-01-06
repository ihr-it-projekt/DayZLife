class DZLPlayerEventListener
{
    private PlayerBase player;
	private ScriptCallQueue queue;

    void DZLPlayerEventListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
    }

    void ~DZLPlayerEventListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        player = PlayerBaseHelper.GetPlayer();
        if (player) {
            if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_HOUSE) {
                Param1 <ref DZLHouseConfig> configParamHouse;
                if (ctx.Read(configParamHouse) && configParamHouse.param1) {
                    player.config.houseConfig = configParamHouse.param1;
                    player.IsRealPlayerDZL = true;
                }
            } else if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_HOUSE_EXTENSION) {
                Param1 <ref DZLHouseExtensions> configParamHouseExtension;
                if (ctx.Read(configParamHouseExtension) && configParamHouseExtension.param1) {
                    player.config.houseExtensions = configParamHouseExtension.param1;
                    player.IsRealPlayerDZL = true;
                }
            } else if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_BANKING) {
                Param1 <ref DZLBankingConfig> configParamBanking;
                if (ctx.Read(configParamBanking) && configParamBanking.param1) {
                    player.config.bankConfig = configParamBanking.param1;
                    player.IsRealPlayerDZL = true;
                    player.hasBankingConfig = true;
                }
            } else if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_JOB) {
                Param1 <ref DZLJobConfig> configParamJob;
                if (ctx.Read(configParamJob) && configParamJob.param1) {
                    player.config.jobConfig = configParamJob.param1;
                    player.IsRealPlayerDZL = true;
                }
            } else if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_LICENCE) {
                Param1 <ref DZLLicenceConfig> configParamLicence;
                if (ctx.Read(configParamLicence) && configParamLicence.param1) {
                    player.config.licenceConfig = configParamLicence.param1;
                    player.IsRealPlayerDZL = true;
                }
            } else if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_TRADER) {
                Param1 <ref DZLTraderConfig> configParamTrader;
                if (ctx.Read(configParamTrader) && configParamTrader.param1) {
                    player.config.traderConfig = configParamTrader.param1;
                    player.IsRealPlayerDZL = true;
                    player.hasTraderConfig = true;
                }
            } else if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_COP) {
                Param1 <ref DZLJobSpawnPoints> configParamCop;
                if (ctx.Read(configParamCop) && configParamCop.param1) {
                    player.config.copSpawnPoints = configParamCop.param1;
                    player.IsRealPlayerDZL = true;
                }
            } else if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_MEDIC) {
                Param1 <ref DZLJobSpawnPoints> configParamMedicSpawn;
                if (ctx.Read(configParamMedicSpawn) && configParamMedicSpawn.param1) {
                    player.config.medicSpawnPoints = configParamMedicSpawn.param1;
                    player.IsRealPlayerDZL = true;
                }
            } else if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_CIV) {
                Param1 <ref DZLJobSpawnPoints> configParamCiv;
                if (ctx.Read(configParamCiv) && configParamCiv.param1) {
                    player.config.civilSpawnPoints = configParamCiv.param1;
                    player.IsRealPlayerDZL = true;
                }
            } else if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_ADMIN_IDS) {
                Param1 <ref DZLAdmin> configParamAdmin;
                if (ctx.Read(configParamAdmin) && configParamAdmin.param1) {
                    player.config.adminIds = configParamAdmin.param1;
                    player.IsRealPlayerDZL = true;
                }
            } else if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_CAR_RESPONSE) {
                Param1 <ref DZLCarConfig> configParamCar;
                if (ctx.Read(configParamCar) && configParamCar.param1) {
                    player.config.carConfig = configParamCar.param1;
                    player.IsRealPlayerDZL = true;
                }
            } else if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_MEDIC_RESPONSE) {
                Param1 <ref DZLMedicConfig> configParamMedic;
                if (ctx.Read(configParamMedic) && configParamMedic.param1) {
                    player.config.medicConfig = configParamMedic.param1;
                    player.IsRealPlayerDZL = true;
                }
            } else if (rpc_type == DAY_Z_LIFE_GET_PLAYER_BUILDING_RESPONSE) {
                Param1 <ref DZLPlayerHouse> houseParam;
                if (ctx.Read(houseParam) && houseParam.param1){
                    player.house = houseParam.param1;
                }
            } else if (rpc_type == DAY_Z_LIFE_PLAYER_DATA_RESPONSE) {
                Param1 <ref DZLPlayer> dzlPlayerParam;
                if (ctx.Read(dzlPlayerParam) && dzlPlayerParam.param1){
                    player.dzlPlayer = dzlPlayerParam.param1;
                    player.UpdatePlayerAtDependencies();
                }
            } else if (rpc_type == DAY_Z_LIFE_PLAYER_BANK_DATA_RESPONSE) {
                Param1 <ref DZLBank> dzlBankParam;
                if (ctx.Read(dzlBankParam) && dzlBankParam.param1){
                    player.dzlBank = dzlBankParam.param1;
                }
            } else if (rpc_type == DAY_Z_LIFE_RECEIVE_MESSAGE) {
                Param1 <string> dzlMessage;
                if (ctx.Read(dzlMessage) && dzlMessage.param1){
                    player.DisplayMessage(dzlMessage.param1);
                }
            } else if (rpc_type == DAY_Z_LIFE_RECEIVE_MEDIC_MESSAGE) {
                Param1 <string> dzlMessageMedic;
                if (ctx.Read(dzlMessageMedic) && dzlMessageMedic.param1){
                    if (player && player.dzlPlayer && player.dzlPlayer.IsActiveAsMedic()) {
						player.DisplayMessage(dzlMessageMedic.param1);
					}
                }
            } else if(rpc_type == DAY_Z_LIFE_HOUSE_RAID_ALARM) {
                Param3<ref DZLHouseExtension, string, PlayerBase> dzlAlarm;
                if (ctx.Read(dzlAlarm) && dzlAlarm.param1 && dzlAlarm.param2 && dzlAlarm.param3){
                     player.DisplayMessage(dzlAlarm.param1.GetMessage(dzlAlarm.param3, dzlAlarm.param2));
                }
            } else if(rpc_type == DAY_Z_LIFE_EVENT_MEDIC_SYNC_PLAYER) {
                Param1<bool> paramDzlMedicPlayerSync
                if (ctx.Read(paramDzlMedicPlayerSync) && paramDzlMedicPlayerSync.param1){
                     player.ToggleHealMenu(paramDzlMedicPlayerSync.param1);
                }
            }
        }

        if (rpc_type == DAY_Z_LIFE_NEW_SPAWN_CLIENT) {
            queue = GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM);
            queue.CallLater(CreateSpawnMenu, 1750, true);
        }
    }

    void CreateSpawnMenu() {
        player = PlayerBaseHelper.GetPlayer();
        if (!player || !player.config|| !player.dzlPlayer) {
            return;
        }

        queue = GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM);
        queue.Remove(CreateSpawnMenu);

        GetGame().GetUIManager().CloseAll();
        GetGame().GetUIManager().ShowScriptedMenu(player.GetSpawnPositionMenu(), null);
    }

}
