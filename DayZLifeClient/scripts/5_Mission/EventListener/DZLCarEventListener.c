class DZLCarEventListener: DZLBaseEventListener {

    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DZL_RPC.UPDATE_CAR) {
            Param6<int, ref array<string>, string, string, bool, bool> carParam;
            CarScript car = CarScript.Cast(target);
            if(ctx.Read(carParam) && car) {
                car.dzlCarId = carParam.param1;
                car.playerAccess = carParam.param2;
                car.ownerId = carParam.param3;
                car.ownerName = carParam.param4;
                car.isRaided = carParam.param5;
                car.EnableInsuranceClient(carParam.param6);
                car.isSync = true;
            }
        }
    }
}
