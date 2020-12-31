class DZLCarEventListener
{
    void DZLCarEventListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
    }

    void ~DZLCarEventListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_UPDATE_CAR) {
            Param5<CarScript, int, ref array<string>, string, string> carParam;
            if (ctx.Read(carParam) && carParam.param1) {
                carParam.param1.dzlCarId = carParam.param2;
                carParam.param1.playerAccess = carParam.param3;
                carParam.param1.ownerId = carParam.param4;
                carParam.param1.ownerName = carParam.param5;
                carParam.param1.isSync = true;
            }
        }
    }
}
