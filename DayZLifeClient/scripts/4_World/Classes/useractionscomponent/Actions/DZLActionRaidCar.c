class DZLActionRaidCar: ActionInteractBase {
    ref DZLCarConfig config;

    void DZLActionRaidCar() {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
        m_HUDCursorIcon = CursorIcons.OpenDoors;

        if(g_Game.IsServer()) {
            config = DZLConfig.Get().carConfig;
        }
    }

    override string GetText() {
        return "#break_door";
    }

    override void CreateConditionComponents() {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new DZL_CCTCar(false);
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        CarScript car = CarScript.Cast(target.GetParent());
        if(!car) return false;
        if(!car.CanRaidDoor(player)) return false;

        item = player.GetItemInHands();
        if(!item) return false;
        if(item.IsRuined()) return false;

        config = DZLConfig.Get().carConfig;
        if(!config) return false;

        foreach(string itemType: config.carRaidTools) {
            if(item.GetType() == itemType) return true;
        }

        return false;
    }

    override void OnEndClient(ActionData action_data) {
        if(g_Game.GetUIManager().GetMenu() != NULL) return;
        CarScript car = CarScript.Cast(action_data.m_Target.GetParent());
        EntityAI item = action_data.m_Player.GetItemInHands();

        DZLCarRaidProgressBar bar = action_data.m_Player.GetRaidCarProgressBar();
        bar.SetCar(car);
        bar.SetRaidItem(item);
        bar.SetDuration(DZLConfig.Get().carConfig.carRaidTimeInSeconds);

        g_Game.GetUIManager().ShowScriptedMenu(bar, NULL);
    }
    override bool IsLockTargetOnUse() {
        return false;
    }
};
