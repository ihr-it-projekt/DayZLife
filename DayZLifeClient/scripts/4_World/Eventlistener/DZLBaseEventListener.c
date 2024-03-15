class DZLBaseEventListener {
    void DZLBaseEventListener() {
        GetDayZGame().Event_OnRPC.Insert(OnRPC);
    }

    void ~DZLBaseEventListener() {
        GetDayZGame().Event_OnRPC.Remove(OnRPC);
    }

    void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {}
}