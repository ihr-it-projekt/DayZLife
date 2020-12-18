class DZLRaidListener
{
    void DZLRaidListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
    }

    void ~DZLRaidListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_RAID_DOOR) {
            autoptr Param4<PlayerBase, Building, int, EntityAI> paramRaidDoor;
            if (ctx.Read(paramRaidDoor)){
                DZLHouse dzlHouse = DZLDatabaseLayer.Get().GetHouse(paramRaidDoor.param2);
                dzlHouse.UnLookDoor(paramRaidDoor.param3);
                DZLLockedHouses houses = DZLDatabaseLayer.Get().GetLockedHouses();
                houses.Remove(dzlHouse);

                paramRaidDoor.param4.SetHealth(0);
            }
        } else if (rpc_type == DAY_Z_LIFE_GET_DZL_BUILDING_RAID_DOOR) {
            autoptr Param2<PlayerBase, Building> paramRaidDoorDZLBuilding;
            if (ctx.Read(paramRaidDoorDZLBuilding)){
                PlayerBase raider = paramRaidDoorDZLBuilding.param1;
                Building building = paramRaidDoorDZLBuilding.param2;
                DZLHouse dzlHouseRaid = DZLDatabaseLayer.Get().GetHouse(building);

                if (dzlHouseRaid.HasAlarmSystem() && dzlHouseRaid.GetHouseAlarm().message) {
                    array<Man> players = new array<Man>;
                    GetGame().GetPlayers(players);

                    if (players) {
                        foreach(Man player: players) {
							PlayerBase currentPlayer = PlayerBase.Cast(player);
                            if (raider == currentPlayer) continue;

                            if (dzlHouseRaid.IsOwner(currentPlayer)) {
                                GetGame().RPCSingleParam(currentPlayer, DAY_Z_LIFE_HOUSE_RAID_ALARM, new Param3<ref DZLHouseExtension, string, PlayerBase>(dzlHouseRaid.GetHouseAlarm(), dzlHouseRaid.GetName(), raider), true, currentPlayer.GetIdentity());
                            }
                        }
                    }
                }

                GetGame().RPCSingleParam(raider, DAY_Z_LIFE_GET_DZL_BUILDING_RAID_DOOR_RESPONSE, new Param1<ref DZLHouse>(dzlHouseRaid), true, sender);
            }
        }
    }
}
