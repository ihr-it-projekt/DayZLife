class DZLRaidListener {
    void DZLRaidListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
    }

    void ~DZLRaidListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DAY_Z_LIFE_RAID_DOOR) {
            autoptr Param2<int, EntityAI> paramRaidDoor;
            if(ctx.Read(paramRaidDoor)) {
                Building raidedBuilding = Building.Cast(target);

                DZLJobHouseDefinition definitionRaided = DZLConfig.Get().houseConfig.GetJobHouseDefinition(raidedBuilding, DAY_Z_LIFE_JOB_COP);
                DZLJobHouseDefinition transportdefinitionRaided = DZLConfig.Get().houseConfig.GetJobHouseDefinition(raidedBuilding, DAY_Z_LIFE_JOB_TRANSPORT);
                DZLJobHouseDefinition medicDefinitionRaided = DZLConfig.Get().houseConfig.GetJobHouseDefinition(raidedBuilding, DAY_Z_LIFE_JOB_MEDIC);
                DZLJobHouseDefinition armyDefinitionRaided = DZLConfig.Get().houseConfig.GetJobHouseDefinition(raidedBuilding, DAY_Z_LIFE_JOB_ARMY);
                if(!definitionRaided && !medicDefinitionRaided && !armyDefinitionRaided && !transportdefinitionRaided) {
                    DZLHouse dzlHouse = DZLDatabaseLayer.Get().GetHouse(raidedBuilding);
                    dzlHouse.UnLookDoor(paramRaidDoor.param1);
                    DZLLockedHouses houses = DZLDatabaseLayer.Get().GetLockedHouses();
                    houses.Remove(dzlHouse);
                }

                if(raidedBuilding.IsDoorLocked(paramRaidDoor.param1)) {
                    raidedBuilding.UnlockDoor(paramRaidDoor.param1);
                }

                raidedBuilding.OpenDoor(paramRaidDoor.param1);

                paramRaidDoor.param2.SetHealth(0);
                DZLLogRaid(sender.GetId(), "end raid", raidedBuilding.GetType(), raidedBuilding.GetPosition());
            }
        } else if(rpc_type == DAY_Z_LIFE_GET_DZL_BUILDING_RAID_DOOR) {
            autoptr Param1<Building> paramRaidDoorDZLBuilding;
            if(ctx.Read(paramRaidDoorDZLBuilding)) {
                PlayerBase raider = PlayerBase.Cast(target);
                Building building = paramRaidDoorDZLBuilding.param1;

                DZLJobHouseDefinition definition = DZLConfig.Get().houseConfig.GetJobHouseDefinition(building, DAY_Z_LIFE_JOB_COP);
                DZLJobHouseDefinition transportdefinition = DZLConfig.Get().houseConfig.GetJobHouseDefinition(building, DAY_Z_LIFE_JOB_TRANSPORT);
                DZLJobHouseDefinition medicDefinition = DZLConfig.Get().houseConfig.GetJobHouseDefinition(building, DAY_Z_LIFE_JOB_MEDIC);
                DZLJobHouseDefinition armyDefinition = DZLConfig.Get().houseConfig.GetJobHouseDefinition(building, DAY_Z_LIFE_JOB_ARMY);

                int raidTime = 9999999999;

                if (definition)
				{
                    raidTime = definition.raidTimeInSeconds;
                }
				else if (transportdefinition)
				{
                    raidTime = transportdefinition.raidTimeInSeconds;
                }
				else if (medicDefinition)
				{
                    raidTime = medicDefinition.raidTimeInSeconds;
                }
				else if (armyDefinition)
				{
                    raidTime = armyDefinition.raidTimeInSeconds;
                }
				else
				{
                    DZLHouse dzlHouseRaid = DZLDatabaseLayer.Get().GetHouse(building);

                    if(dzlHouseRaid.HasAlarmSystem() && dzlHouseRaid.GetHouseAlarm().message) {
                        array<Man> players = new array<Man>;
                        GetGame().GetPlayers(players);

                        DZLHouseExtension extension = dzlHouseRaid.GetHouseAlarm();
                        if(extension.level == 4) {
                            string copMessage = extension.GetCopMessage();
                            DZLMessageListener.SendMessage(raider, "", copMessage, DZLMessage.TYPE_COP, dzlHouseRaid.GetPosition(), false);
                        }

                        if(players) {
                            foreach(Man player: players) {
                                PlayerBase currentPlayer = PlayerBase.Cast(player);
                                if(raider == currentPlayer) continue;

                                if(dzlHouseRaid.IsOwner(currentPlayer)) {
                                    GetGame().RPCSingleParam(currentPlayer, DAY_Z_LIFE_HOUSE_RAID_ALARM, new Param3<ref DZLHouseExtension, string, PlayerBase>(extension, dzlHouseRaid.GetName(), raider), true, currentPlayer.GetIdentity());
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
