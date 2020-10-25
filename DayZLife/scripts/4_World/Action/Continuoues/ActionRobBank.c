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
    bool done = false;

    DZLBankingConfig GetConfig() {
        if (!config) {
            config = new DZLBankingConfig;
        }

        return config;
    }

	void ActionRobBank() {
		m_CallbackClass = ActionRobBankTargetCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_RESTRAINTARGET;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
		done = false;
	}

	override void CreateConditionComponents() {
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
		m_ConditionItem = new CCINonRuined;
		done = false;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (player.GetInstanceType() == DayZPlayerInstanceType.INSTANCETYPE_SERVER) {
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

	override string GetText()
	{
		return "#rob_bank";
	}
	
	override void OnUpdate(ActionData action_data) {
		super.OnUpdate(action_data);
		PlayerBase target_player = PlayerBase.Cast(action_data.m_Target.GetObject());
		if (action_data.m_State == UA_FINISHED && done == false) {
		    DZLBank bank = new DZLBank;
		    done = true;
            bank.RaidIsFinished();
			DZLPlayer dzlPlayer = new DZLPlayer(action_data.m_Player.GetIdentity().GetId());
            
			float money = bank.PlayerRaidBank(dzlPlayer, GetConfig().percentOfMoneyWhenRaid);
            GetGame().RPCSingleParam(action_data.m_Player, ERPCs.RPC_USER_ACTION_MESSAGE, new Param1<string>("#bank_rob_was_successful " + money.ToString()), true);
            GetGame().RPCSingleParam(action_data.m_Player, DAY_Z_LIFE_PLAYER_BANK_DATA_RESPONSE, new Param1<ref DZLBank>(bank), true);
			GetGame().RPCSingleParam(action_data.m_Player, DAY_Z_LIFE_PLAYER_DATA_RESPONSE, new Param1<ref DZLPlayer>(new DZLPlayer(action_data.m_Player.GetIdentity().GetId())), true, action_data.m_Player.GetIdentity());
			bank = null;
		} else if ((action_data.m_State == UA_CANCEL || action_data.m_State == UA_INTERRUPT || action_data.m_State == UA_FAILED) && done == false) {
		    done = true;
		    DZLBank bank_cancel = new DZLBank;
			bank_cancel.CancelRaid();
			GetGame().RPCSingleParam(action_data.m_Player, ERPCs.RPC_USER_ACTION_MESSAGE, new Param1<string>("#bank_rob_was_canceled"), true);
		}
	}

	override void OnStartServer(ActionData action_data) {
	    done = false;
		DZLBank bank = new DZLBank;
		bank.StartRaid();
		GetGame().RPCSingleParam(action_data.m_Player, ERPCs.RPC_USER_ACTION_MESSAGE, new Param1<string>("#bank_rob_was_started"), true);
	}

};
