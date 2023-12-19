class ActionGetOwnerName: ActionInteractBase {
    void ActionGetOwnerName() {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
        m_HUDCursorIcon = CursorIcons.CloseHood;
    }

    override void CreateConditionComponents() {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new DZL_CCTCar;
    }

    override string GetText() {
        return "#show_owner";
    }

    override void OnStartClient(ActionData action_data) {
        CarScript car = CarScript.Cast(action_data.m_Target.GetParent());
        if (car) {
            action_data.m_Player.DisplayMessage("#owner_is: " + car.ownerName);
        }
    }
};
