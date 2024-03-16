class DZLActionGiveNumber: ActionInteractBase {
    void DZLActionGiveNumber() {
        m_CommandUID = DayZPlayerConstants.CMD_GESTUREFB_COME;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
        m_HUDCursorIcon = CursorIcons.None;
    }

    override void CreateConditionComponents() {
        m_ConditionTarget = new CCTMan;
        m_ConditionItem = new CCINone;
    }

    override string GetText() {
        return "#send_contact";
    }
}
