class ActionLicenceCrafting: ActionInteractBase
{
    void ActionLicenceCrafting() {
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ALL;
        m_HUDCursorIcon = CursorIcons.None;
	}

	override string GetText() {
        return "#start_crafting";
    }

	override void CreateConditionComponents() {
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNone;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item ) {
		DZLLicence licence = GetLicence();
		
		if (!licence) return false;

		return false;
	}

	override void OnStartClient(ActionData action_data) {
	    super.OnStartClient(action_data);
		
        
    }

    private DZLLicence GetLicence(PlayerBase player) {
        if (!player) {
            return false;
        }
        vector playerPosition = player.GetPosition();
        if (!playerPosition) {
            return false;
        }
		
        foreach(DZLLicence licence: player.dzlPlayer.licences) {
            if (vector.Distance(licence.position, playerPosition) <= licence.range){
                return licence;
            }
        }
        return null;
    }

};
