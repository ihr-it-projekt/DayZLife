class DZLAlmanacListener {
    ref DZLConfig config;
    private ref DZLHouseFinder houseFinder;

    void DZLAlmanacListener() {
        config = DZLConfig.Get();
        houseFinder = new DZLHouseFinder;
        houseFinder.SetConfig(config);

        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
    }

    void ~DZLAlmanacListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DAY_Z_LIFE_PLAYER_SERVER_RESET_AT_PLAYER_BASE) {
            PlayerBase.Cast(target).ResetDZLPlayer();
        } else if(rpc_type == DAY_Z_LIFE_ALL_PLAYER_ONLINE_PLAYERS) {
            SendUpdateListCops(PlayerBase.Cast(target));
        } else if(rpc_type == DAY_Z_LIFE_ALL_PLAYER_GET_MEDIC_PLAYERS) {
            SendUpdateListMedic(PlayerBase.Cast(target));
        } else if(rpc_type == DAY_Z_LIFE_ALL_PLAYER_UPDATE_TRANSPORT_PLAYERS) {
            SendUpdateListTransport(PlayerBase.Cast(target));
        } else if(rpc_type == DAY_Z_LIFE_ALL_PLAYER_GET_ARMY_PLAYERS) {
            SendUpdateListArmy(PlayerBase.Cast(target));
        } else if(rpc_type == DAY_Z_LIFE_GET_ALL_PLAYERS) {
            SendAllPlayerList(sender);
        } else if(rpc_type == DAY_Z_LIFE_DELETE_PLAYER) {
            if(!config.adminIds.CanManagePlayers(sender.GetId())) return;
            autoptr Param1<string> paramDeletePlayer;
            if(ctx.Read(paramDeletePlayer)) {
                string identString = paramDeletePlayer.param1;
                if(DZLDatabaseLayer.Get().HasPlayer(identString)) {
                    DZLPlayer dzlPlayer = DZLDatabaseLayer.Get().GetPlayer(identString);
                    DZLPlayerHouse dzlPlayerHouse = DZLDatabaseLayer.Get().GetPlayerHouse(identString);

                    DZLHouse house;
                    foreach(string fileNameHouse: dzlPlayerHouse.playerHouseCollection) {
                        house = DZLDatabaseLayer.Get().GetHouse(null, fileNameHouse);

                        array<ref DZLStorageTypeBought> storages = house.GetStorage();
                        if(storages && storages.Count() > 0) {
                            foreach(DZLStorageTypeBought storage: storages) {
                                if(!storage) continue;
                                houseFinder.objectFinder.DeleteContainerAt(storage.position, storage.position, storage.type);
                            }
                        }

                        DZLDatabaseLayer.Get().RemoveHouseInventory(house.GetOwner(), house.GetPosition());
                        house.RemoveOwner();

                        DZLDatabaseLayer.Get().RemoveHouse(house.GetFileName());
                        DZLDatabaseLayer.Get().GetLockedHouses().Remove(house);
                    }

                    DZLDatabaseLayer.Get().GetBank().AddMoney(dzlPlayer.GetBankMoney() * -1);

                    foreach(string fileHouseAccess: dzlPlayerHouse.playerHouseKeyCollection) {
                        house = DZLDatabaseLayer.Get().GetHouse(null, fileHouseAccess);
                        if(house) house.RemovePlayerAccess(identString);
                    }

                    DZLDatabaseLayer.Get().RemovePlayer(identString);
                    DZLDatabaseLayer.Get().RemovePlayerHouse(identString);
                    DZLDatabaseLayer.Get().RemovePlayerCars(identString);
                    DZLDatabaseLayer.Get().GetPlayerIds().RemovePlayer(identString);
                }

                array<Man> _players = new array<Man>;
                GetGame().GetPlayers(_players);

                if(_players) {
                    foreach(Man _player: _players) {
                        if(_player.GetIdentity().GetId() == identString) {
                            PlayerBase.Cast(_player).ResetDZLPlayer();
                            break;
                        }
                    }
                }

                DZLSendMessage(sender, "#player_data_was_deleted");
                SendAllPlayerList(sender);
            }
        } else if(rpc_type == DAY_Z_LIFE_ALL_PLAYER_UPDATE_COP_PLAYERS) {
            if(!config.adminIds.CanManageCops(sender.GetId())) return;
            autoptr Param1<ref array<DZLOnlinePlayer>> paramUpdateCops;
            if(ctx.Read(paramUpdateCops)) {
                DZLPlayerIdentities dzlPlayerIdentities = DZLDatabaseLayer.Get().GetPlayerIds();
                dzlPlayerIdentities.UpdateCops(paramUpdateCops.param1);
                DZLSendMessage(sender, "#update_cop_list_successful");
            }
        } else if(rpc_type == DAY_Z_LIFE_ALL_PLAYER_UPDATE_TRANSPORT_PLAYERS) {
            if(!config.adminIds.CanManageTransport(sender.GetId())) return;
            autoptr Param1<ref array<DZLOnlinePlayer>> paramUpdateTransports;
            if(ctx.Read(paramUpdateTransports)) {
                DZLPlayerIdentities dzlPlayerIdentitiesTransport = DZLDatabaseLayer.Get().GetPlayerIds();
                dzlPlayerIdentitiesTransport.UpdateTransports(paramUpdateTransports.param1);
                DZLSendMessage(sender, "update transport list");
            }
        } else if(rpc_type == DAY_Z_LIFE_ALL_PLAYER_UPDATE_MEDIC_PLAYERS) {
            if(!config.adminIds.CanManageMedic(sender.GetId())) return;
            autoptr Param1<ref array<DZLOnlinePlayer>> paramUpdateMedics;
            if(ctx.Read(paramUpdateMedics)) {
                DZLPlayerIdentities dzlPlayerIdentitiesMedic = DZLDatabaseLayer.Get().GetPlayerIds();
                dzlPlayerIdentitiesMedic.UpdateMedics(paramUpdateMedics.param1);
                DZLSendMessage(sender, "#update_medic_list_successful");
            }
        } else if(rpc_type == DAY_Z_LIFE_ALL_PLAYER_UPDATE_ARMY_PLAYERS) {
            if(!config.adminIds.CanManageArmy(sender.GetId())) return;
            autoptr Param1<ref array<DZLOnlinePlayer>> paramUpdateArmy;
            if(ctx.Read(paramUpdateArmy)) {
                DZLPlayerIdentities dzlPlayerIdentitiesArmy = DZLDatabaseLayer.Get().GetPlayerIds();
                dzlPlayerIdentitiesArmy.UpdateArmy(paramUpdateArmy.param1);
                DZLSendMessage(sender, "#update_army_list_successful");
            }
        } else if(rpc_type == DAY_Z_LIFE_MONEY_TRANSFER_ADMIN) {
            if(!config.adminIds.CanManagePlayers(sender.GetId())) return;
            autoptr Param3<string, int, bool> paramDepositAdminPlayer;
            string messageDepositPP = "";
            if(ctx.Read(paramDepositAdminPlayer)) {
                PlayerIdentity identMoney = sender;
                if(!config.adminIds.CanManagePlayers(identMoney.GetId())) return;

                DZLPlayer dzlPlayerReciverPP = DZLDatabaseLayer.Get().GetPlayer(paramDepositAdminPlayer.param1);

                if(!paramDepositAdminPlayer.param3) {
                    dzlPlayerReciverPP.AddMoneyToPlayer(paramDepositAdminPlayer.param2);
                } else {
                    DZLDatabaseLayer.Get().GetBank().AddMoney(paramDepositAdminPlayer.param2);
                    dzlPlayerReciverPP.AddMoneyToPlayerBank(paramDepositAdminPlayer.param2);
                }
                DZLSendMessage(identMoney, "#money_transfer_successful");
            }
        }
    }

    void SendUpdateListCops(PlayerBase player) {
        if(!config.adminIds.CanManageCops(player.GetPlayerId())) return;

        array<Man> _players = new array<Man>;
        GetGame().GetPlayers(_players);
        array<ref DZLOnlinePlayer> collection = new array<ref DZLOnlinePlayer>;

        DZLPlayerIdentities dzlPlayerIdentities = DZLDatabaseLayer.Get().GetPlayerIds();
        array<ref DZLOnlinePlayer> copIdents = dzlPlayerIdentities.GetCopPlayerCollection();

        if(_players) {
            foreach(Man _player: _players) {
                string ident = _player.GetIdentity().GetId();
                DZLPlayer dzlPlayer = PlayerBase.Cast(_player).GetDZLPlayer();

                if(!dzlPlayer.IsCop()) {
                    collection.Insert(new DZLOnlinePlayer(ident, _player.GetIdentity().GetName(), dzlPlayer.GetLastJobRank(DAY_Z_LIFE_JOB_COP)));
                }
            }
        }

        GetGame().RPCSingleParam(null, DAY_Z_LIFE_ALL_PLAYER_ONLINE_PLAYERS_RESPONSE, new Param2<ref array<ref DZLOnlinePlayer>, ref array<ref DZLOnlinePlayer>>(collection, copIdents), true, player.GetIdentity());
    }

    void SendUpdateListTransport(PlayerBase player) {
        if(!config.adminIds.CanManageTransport(player.GetPlayerId())) return;

        array<Man> _players = new array<Man>;
        GetGame().GetPlayers(_players);
        array<ref DZLOnlinePlayer> collection = new array<ref DZLOnlinePlayer>;

        DZLPlayerIdentities dzlPlayerIdentities = DZLDatabaseLayer.Get().GetPlayerIds();
        array<ref DZLOnlinePlayer> transportIdents = dzlPlayerIdentities.GetTransportPlayerCollection();

        if(_players) {
            foreach(Man _player: _players) {
                string ident = _player.GetIdentity().GetId();
                DZLPlayer dzlPlayer = PlayerBase.Cast(_player).GetDZLPlayer();

                if(!dzlPlayer.IsTransport()) {
                    collection.Insert(new DZLOnlinePlayer(ident, _player.GetIdentity().GetName(), dzlPlayer.GetLastJobRank(DAY_Z_LIFE_JOB_TRANSPORT)));
                }
            }
        }

        GetGame().RPCSingleParam(null, DAY_Z_LIFE_ALL_PLAYER_ONLINE_PLAYERS_RESPONSE, new Param2<ref array<ref DZLOnlinePlayer>, ref array<ref DZLOnlinePlayer>>(collection, transportIdents), true, player.GetIdentity());
    }

    void SendUpdateListMedic(PlayerBase player) {
        if(!config.adminIds.CanManageMedic(player.GetPlayerId())) return;

        array<Man> _players = new array<Man>;
        GetGame().GetPlayers(_players);
        array<ref DZLOnlinePlayer> collection = new array<ref DZLOnlinePlayer>;

        DZLPlayerIdentities dzlPlayerIdentities = DZLDatabaseLayer.Get().GetPlayerIds();
        array<ref DZLOnlinePlayer> medicIdents = dzlPlayerIdentities.GetMedicPlayerCollection();

        if(_players) {
            foreach(Man _player: _players) {
                DZLPlayer dzlPlayer = PlayerBase.Cast(_player).GetDZLPlayer();
                if(!dzlPlayer.IsMedic()) {
                    collection.Insert(new DZLOnlinePlayer(_player.GetIdentity().GetId(), _player.GetIdentity().GetName(), ""));
                }
            }
        }

        GetGame().RPCSingleParam(player, DAY_Z_LIFE_ALL_NOT_MEDIC_PLAYER_ONLINE_PLAYERS_RESPONSE, new Param2<ref array<ref DZLOnlinePlayer>, ref array<ref DZLOnlinePlayer>>(collection, medicIdents), true, player.GetIdentity());
    }

    void SendUpdateListArmy(PlayerBase player) {
        if(!config.adminIds.CanManageArmy(player.GetPlayerId())) return;

        array<Man> _players = new array<Man>;
        GetGame().GetPlayers(_players);
        array<ref DZLOnlinePlayer> collection = new array<ref DZLOnlinePlayer>;

        DZLPlayerIdentities dzlPlayerIdentities = DZLDatabaseLayer.Get().GetPlayerIds();
        array<ref DZLOnlinePlayer> armyIdents = dzlPlayerIdentities.GetArmyPlayerCollection();

        if(_players) {
            foreach(Man _player: _players) {
                DZLPlayer dzlPlayer = PlayerBase.Cast(_player).GetDZLPlayer();
                if(!dzlPlayer.IsArmy()) {
                    collection.Insert(new DZLOnlinePlayer(_player.GetIdentity().GetId(), _player.GetIdentity().GetName(), dzlPlayer.GetLastJobRank(DAY_Z_LIFE_JOB_ARMY)));
                }
            }
        }

        GetGame().RPCSingleParam(player, DAY_Z_LIFE_ALL_PLAYER_GET_ARMY_PLAYERS_RESPONSE, new Param2<ref array<ref DZLOnlinePlayer>, ref array<ref DZLOnlinePlayer>>(collection, armyIdents), true, player.GetIdentity());
    }

    void SendAllPlayerList(PlayerIdentity player) {
        if(!config.adminIds.CanManagePlayers(player.GetId())) return;

        array<ref DZLPlayer> collection = new array<ref DZLPlayer>;
        DZLPlayerIdentities dzlPlayerIdentities = DZLDatabaseLayer.Get().GetPlayerIds();

        array<string> allPlayer = dzlPlayerIdentities.playerIdentities;
        foreach(string ident: allPlayer) {
            DZLPlayer _player = DZLDatabaseLayer.Get().GetPlayer(ident);
            collection.Insert(_player);
        }

        GetGame().RPCSingleParam(null, DAY_Z_LIFE_GET_ALL_PLAYERS_RESPONSE, new Param1<ref array<ref DZLPlayer>>(collection), true, player);
    }
}
