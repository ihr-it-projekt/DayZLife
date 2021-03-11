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
            autoptr Param2<int, EntityAI> paramRaidDoor;
            if (ctx.Read(paramRaidDoor)){
				Building raidedBuilding = Building.Cast(target);
				
				DZLJobHouseDefinition definitionRaided = DZLConfig.Get().houseConfig.GetCopHouseDefinition(raidedBuilding);
				DZLJobHouseDefinition medicDefinitionRaided = DZLConfig.Get().houseConfig.GetMedicHouseDefinition(raidedBuilding);
				if (!definitionRaided && !medicDefinitionRaided) {
					DZLHouse dzlHouse = DZLDatabaseLayer.Get().GetHouse(raidedBuilding);
	                dzlHouse.UnLookDoor(paramRaidDoor.param1);
	                DZLLockedHouses houses = DZLDatabaseLayer.Get().GetLockedHouses();
	                houses.Remove(dzlHouse);
				}

				if (raidedBuilding.IsDoorLocked(paramRaidDoor.param1)) {
					raidedBuilding.UnlockDoor(paramRaidDoor.param1);
				}
				
				raidedBuilding.OpenDoor(paramRaidDoor.param1);
				
                paramRaidDoor.param2.SetHealth(0);
                DZLLogRaid(sender.GetId(), "end raid", raidedBuilding.GetType(), raidedBuilding.GetPosition());
            }
        } else if (rpc_type == DAY_Z_LIFE_GET_DZL_BUILDING_RAID_DOOR) {
            autoptr Param1<Building> paramRaidDoorDZLBuilding;
            if (ctx.Read(paramRaidDoorDZLBuilding)){
                PlayerBase raider = PlayerBase.Cast(target);
                Building building = paramRaidDoorDZLBuilding.param1;
				
				DZLJobHouseDefinition definition = DZLConfig.Get().houseConfig.GetCopHouseDefinition(building);
				DZLJobHouseDefinition medicDefinition = DZLConfig.Get().houseConfig.GetMedicHouseDefinition(building);

				int raidTime = 9999999999;
				
				if (definition) {
					raidTime = definition.raidTimeInSeconds;
				} else if(medicDefinition) {
				    raidTime = medicDefinition.raidTimeInSeconds;
				} else {
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
					raidTime = dzlHouseRaid.GetRaidTime();
				}
                DZLLogRaid(sender.GetId(), "start raid", building.GetType(), building.GetPosition());
                GetGame().RPCSingleParam(raider, DAY_Z_LIFE_GET_DZL_BUILDING_RAID_DOOR_RESPONSE, new Param1<int>(raidTime), true, sender);
            }
        }
    }
}
