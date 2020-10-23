class ActionRobBankTargetCB : ActionContinuousBaseCB
{
	ref DZLBankingConfig config;
	ref DZLBank bank;

    DZLBankingConfig GetConfig() {
        if (!config) {
            config = new DZLBankingConfig;
        }

        return config;
    }
	DZLBank GetBank() {
        if (!bank) {
            bank = new DZLBank;
        }

        return bank;
    }

    override bool CancelCondition() {
        if (!super.CancelCondition() && GetConfig().raidIsEnabled) {

			return false;
        }
		
		GetBank().CancelRaid();
		
        return true;
    }

	override void CreateActionComponent() {
		float time = 30;

		if (GetConfig().raidTimeBankInSeconds){
			time = GetConfig().raidTimeBankInSeconds;
		}

		m_ActionData.m_ActionComponent = new CAContinuousTime(time);
	}
};

class ActionRobBank: ActionContinuousBase
{
    ref DZLBankingConfig config;
    ref DZLBank bank;

    DZLBankingConfig GetConfig() {
        if (!config) {
            config = new DZLBankingConfig;
        }

        return config;
    }

	DZLBank GetBank() {
        if (!bank) {
            bank = new DZLBank;
        }

        return bank;
    }

	void ActionRobBank() {
		m_CallbackClass = ActionRobBankTargetCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_RESTRAINTARGET;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
	}

	override void CreateConditionComponents() {
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
		m_ConditionItem = new CCINonRuined;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (player.GetInstanceType() == DayZPlayerInstanceType.INSTANCETYPE_SERVER) {
		    DebugMessageDZL("ActionCondition ActionRobBank");
			PlayerBase other_player = PlayerBase.Cast(target.GetObject());
			EntityAI item_in_hands_source = player.GetHumanInventory().GetEntityInHands();

			if(!item_in_hands_source) return false;

			bool hasItem = false;
			foreach (string itemForRaid: GetConfig().itemsCanUsedToRaidBank) {
			    if (item_in_hands_source.GetType() == itemForRaid) {
			        hasItem = true;
			        break;
			    }
			}

			if(!hasItem) return false;


			return other_player.IsDZLBank;
		}

		return true;
	}

	override void Interrupt(ActionData action_data)
	{
		PlayerBase target_player = PlayerBase.Cast(action_data.m_Target.GetObject());

		GetBank().CancelRaid();
		
		GetGame().RPCSingleParam(action_data.m_Player, ERPCs.RPC_USER_ACTION_MESSAGE, new Param1<string>("#bank_rob_was_canceled"), true);
	}

	override string GetText()
	{
		return "#rob_bank";
	}
	
	override void OnEndServer(ActionData action_data) {
		PlayerBase target_player = PlayerBase.Cast(action_data.m_Target.GetObject());
		if (target_player && target_player.IsDZLBank) {
            GetBank().RaidIsFinished();
			DZLPlayer dzlPlayer = new DZLPlayer(action_data.m_Player.GetIdentity().GetId());
            
			float money = GetBank().PlayerRaidBank(dzlPlayer, GetConfig().percentOfMoneyWhenRaid);
			GetGame().RPCSingleParam(action_data.m_Player, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(dzlPlayer), true, action_data.m_Player.GetIdentity());
            GetGame().RPCSingleParam(action_data.m_Player, ERPCs.RPC_USER_ACTION_MESSAGE, new Param1<string>("#bank_rob_was_successfull " + money.ToString()), true);
		}
	}

	override void OnStartServer(ActionData action_data) {
		GetBank().StartRaid();
		GetGame().RPCSingleParam(action_data.m_Player, ERPCs.RPC_USER_ACTION_MESSAGE, new Param1<string>("#bank_rob_was_started"), true);
	}

};
