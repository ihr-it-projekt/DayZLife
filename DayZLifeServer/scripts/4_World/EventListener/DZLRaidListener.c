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
                paramRaidDoor.param2.UnlockDoor(paramRaidDoor.param3);
                paramRaidDoor.param4.SetHealth(0);
            }
        }else if (rpc_type == DAY_Z_LIFE_GET_DZL_BUILDING_RAID_DOOR) {
            autoptr Param2<PlayerBase, Building> paramRaidDoorDZLBuilding;
            if (ctx.Read(paramRaidDoorDZLBuilding)){
                GetGame().RPCSingleParam(paramRaidDoorDZLBuilding.param1, DAY_Z_LIFE_GET_DZL_BUILDING_RAID_DOOR_RESPONSE, new Param1<ref DZLHouse>(new DZLHouse(paramRaidDoorDZLBuilding.param2)), true, sender);
            }
        }
    }
}