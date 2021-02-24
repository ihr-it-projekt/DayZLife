class DZLPlayerClientDB
{
    private static ref DZLPlayerClientDB db;


    private ref DZLConfig config;
    private ref DZLPlayerHouse house;
    private ref DZLPlayer dzlPlayer;
    private ref DZLBank dzlBank;

    static DZLPlayerClientDB Get() {
        if (!db) {
            db = new DZLPlayerClientDB;
            GetGame().RPCSingleParam(PlayerBaseHelper.GetPlayer(), DAY_Z_LIFE_EVENT_GET_CONFIG, null, true);
            GetGame().RPCSingleParam(PlayerBaseHelper.GetPlayer(), DAY_Z_LIFE_GET_PLAYER_BUILDING, null, true);
            GetGame().RPCSingleParam(PlayerBaseHelper.GetPlayer(), DAY_Z_LIFE_PLAYER_BANK_DATA, null, true);
            GetGame().RPCSingleParam(PlayerBaseHelper.GetPlayer(), DAY_Z_LIFE_PLAYER_DATA, null, true);
        }
        return db;
    }

    void DZLPlayerClientDB() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
    }

    void ~DZLPlayerClientDB() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    DZLConfig GetConfig(){
        if (!config) {
            GetGame().RPCSingleParam(PlayerBaseHelper.GetPlayer(), DAY_Z_LIFE_EVENT_GET_CONFIG, null, true);
            config = DZLConfig.Get();
        }

        return config;
    }

    DZLPlayerHouse GetPlayerHouse() {
        if (!house) {
            GetGame().RPCSingleParam(PlayerBaseHelper.GetPlayer(), DAY_Z_LIFE_GET_PLAYER_BUILDING, null, true);
        }

        return house;
    }

    DZLBank GetBank() {
        if (!dzlBank) {
            GetGame().RPCSingleParam(PlayerBaseHelper.GetPlayer(), DAY_Z_LIFE_PLAYER_BANK_DATA, null, true);
        }

        return dzlBank;
    }
   
    DZLPlayer GetDZLPlayer() {
        if (!dzlPlayer) {
            GetGame().RPCSingleParam(PlayerBaseHelper.GetPlayer(), DAY_Z_LIFE_PLAYER_DATA, null, true);
        }

        return dzlPlayer;
    }

    void SetDZLPlayer(DZLPlayer dzlPlayer, string playerId) {
        if (dzlPlayer.dayZPlayerId == playerId) {
            this.dzlPlayer = dzlPlayer;
        }
    }

   void RequestUpdateDZLPlayer() {
        GetGame().RPCSingleParam(PlayerBaseHelper.GetPlayer(), DAY_Z_LIFE_PLAYER_DATA, null, true);
        GetGame().RPCSingleParam(PlayerBaseHelper.GetPlayer(), DAY_Z_LIFE_PLAYER_BANK_DATA, null, true);
   }

   void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        PlayerBase player = PlayerBaseHelper.GetPlayer();
        if (player) {
            if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_HOUSE) {
                Param1 <ref DZLHouseConfig> configParamHouse;
                if (ctx.Read(configParamHouse) && configParamHouse.param1) {
                    config.houseConfig = configParamHouse.param1;
                }
            } else if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_HOUSE_EXTENSION) {
                Param1 <ref DZLHouseExtensions> configParamHouseExtension;
                if (ctx.Read(configParamHouseExtension) && configParamHouseExtension.param1) {
                    config.houseExtensions = configParamHouseExtension.param1;
                }
            } else if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_BANKING) {
                Param1 <ref DZLBankingConfig> configParamBanking;
                if (ctx.Read(configParamBanking) && configParamBanking.param1) {
                    config.bankConfig = configParamBanking.param1;
                }
            } else if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_BASE_BUILDING) {
                Param1 <ref DZLBaseBuildingConfig> configParamBaseBuilding;
                if (ctx.Read(configParamBaseBuilding) && configParamBaseBuilding.param1) {
                    config.baseBuildingConfig = configParamBaseBuilding.param1;
                }
            } else if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_JOB) {
                Param1 <ref DZLJobConfig> configParamJob;
                if (ctx.Read(configParamJob) && configParamJob.param1) {
                    config.jobConfig = configParamJob.param1;
                }
            } else if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_LICENCE) {
                Param1 <ref DZLLicenceConfig> configParamLicence;
                if (ctx.Read(configParamLicence) && configParamLicence.param1) {
                    config.licenceConfig = configParamLicence.param1;
                }
            } else if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_TRADER) {
                Param1 <ref DZLTraderConfig> configParamTrader;
                if (ctx.Read(configParamTrader) && configParamTrader.param1) {
                    config.traderConfig = configParamTrader.param1;
                }
            } else if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_COP) {
                Param1 <ref DZLJobSpawnPoints> configParamCop;
                if (ctx.Read(configParamCop) && configParamCop.param1) {
                    config.copSpawnPoints = configParamCop.param1;
                }
            } else if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_MEDIC) {
                Param1 <ref DZLJobSpawnPoints> configParamMedicSpawn;
                if (ctx.Read(configParamMedicSpawn) && configParamMedicSpawn.param1) {
                    config.medicSpawnPoints = configParamMedicSpawn.param1;
                }
            } else if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_CIV) {
                Param1 <ref DZLJobSpawnPoints> configParamCiv;
                if (ctx.Read(configParamCiv) && configParamCiv.param1) {
                    config.civilSpawnPoints = configParamCiv.param1;
                }
            } else if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE_ADMIN_IDS) {
                Param1 <ref DZLAdmin> configParamAdmin;
                if (ctx.Read(configParamAdmin) && configParamAdmin.param1) {
                    config.adminIds = configParamAdmin.param1;
                }
            } else if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_CAR_RESPONSE) {
                Param1 <ref DZLCarConfig> configParamCar;
                if (ctx.Read(configParamCar) && configParamCar.param1) {
                    config.carConfig = configParamCar.param1;
                }
            } else if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_MEDIC_RESPONSE) {
                Param1 <ref DZLMedicConfig> configParamMedic;
                if (ctx.Read(configParamMedic) && configParamMedic.param1) {
                    config.medicConfig = configParamMedic.param1;
                }
            } else if (rpc_type == DAY_Z_LIFE_GET_PLAYER_BUILDING_RESPONSE) {
                Param1 <ref DZLPlayerHouse> houseParam;
                if (ctx.Read(houseParam) && houseParam.param1){
                    house = houseParam.param1;
                }
            } else if (rpc_type == DAY_Z_LIFE_PLAYER_DATA_RESPONSE) {
                Param1 <ref DZLPlayer> dzlPlayerParam;
                if (ctx.Read(dzlPlayerParam) && dzlPlayerParam.param1){
                    SetDZLPlayer(dzlPlayerParam.param1, player.GetPlayerId());
                    player.UpdatePlayerAtDependencies();
                }
            } else if (rpc_type == DAY_Z_LIFE_PLAYER_BANK_DATA_RESPONSE) {
                Param1 <ref DZLBank> dzlBankParam;
                if (ctx.Read(dzlBankParam) && dzlBankParam.param1){
                    dzlBank = dzlBankParam.param1;
                }
            }  else if(rpc_type == DAY_Z_LIFE_EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE) {
                RequestUpdateDZLPlayer();
            }
        }
   }
}