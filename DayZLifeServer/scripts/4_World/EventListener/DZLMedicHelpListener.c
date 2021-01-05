class DZLMedicHelpListener
{

    void DZLMedicHelpListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
    }

    void ~DZLMedicHelpListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_EVENT_MEDIC_KILL_PLAYER) {
            autoptr Param1<PlayerBase>paramKill;
            if (ctx.Read(paramKill)){
                paramKill.param1.willDie = true;
                paramKill.param1.SetCanBeDestroyed(true);
            }
        } else if (rpc_type == DAY_Z_LIFE_EVENT_MEDIC_HEAL_PLAYER) {
            autoptr Param1<PlayerBase>paramHeal;
            if (ctx.Read(paramHeal)){
                paramHeal.param1.willHeal = true;
                paramHeal.param1.SetHealth(100);
            }
        }
    }
}