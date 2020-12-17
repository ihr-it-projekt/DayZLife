class ActionHarvestItemCB : ActionContinuousBaseCB
{
	override void CreateActionComponent() {}
}

class ActionHarvestItem: ActionContinuousBase
{
    ref DZLJobConfig config;

    DZLJobConfig GetConfig() {
        if (!config) {
            config = DZLConfig.Get().jobConfig;
        }

        return config;
    }

	void ActionHarvestItem() {
		m_CallbackClass = ActionHarvestItemCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_RESTRAINTARGET;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
	}

	override void Start(ActionData action_data) {
		GetConfig();
		vector playerPosition = action_data.m_Player.GetPosition();
		
		DZLWorkZone zone = FindZone(playerPosition, config);
		if (zone) {
			action_data.m_ActionComponent = new CAContinuousTime(zone.timeToHarvestPerItemInSeconds);
		}

		super.Start(action_data);
	}

	override void CreateConditionComponents() {
		m_ConditionTarget = new CCTNone;
		m_ConditionItem = new CCINonRuined;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item )
	{
		if(GetGame().IsServer()) {
			config = GetConfig();
		} else if(player && player.config) {
		    config = player.config.jobConfig;
		}

		if (!config) return false;

		vector playerPosition = player.GetPosition();
		
		DZLWorkZone zone = FindZone(playerPosition, config);
		if (zone) {
		    m_CommandUID = zone.m_CommandUID;

		    EntityAI item_in_hands_source = player.GetHumanInventory().GetEntityInHands();

            if (item_in_hands_source) {
                string handItemType = item_in_hands_source.GetType();
                handItemType.ToLower();
            }

			foreach(DZLHarvestItemToolRelation relation: zone.harvestItemToolRelation) {
			    if (0 == relation.itemsThatNeededForHarvest.Count()) return true;

			    if (!handItemType) return false;

                foreach(string _item: relation.itemsThatNeededForHarvest) {
					_item.ToLower();
                    if (handItemType == _item) {
						if (GetGame().IsServer()){
						    return 0 < item_in_hands_source.GetHealth();
                        } 
                        return true;
                    }
				}
			}
		}

		return false;
	}

	override string GetText(){
		return "#start_work";
	}
	
	override void OnUpdateServer(ActionData action_data) {
        if (action_data.m_State == UA_FINISHED && action_data.m_Player.isOnHarvest == true) {
            DZLWorkZone zone = FindZone(action_data.m_Player.GetPosition(), GetConfig());
            if (zone) {
                EntityAI item_in_hands_source = action_data.m_Player.GetHumanInventory().GetEntityInHands();
                array<DZLHarvestItemToolRelation> matchedRelations = new array<DZLHarvestItemToolRelation>;
                if(item_in_hands_source) {
                    string handItemType = item_in_hands_source.GetType();
                    handItemType.ToLower();
                }

                foreach(DZLHarvestItemToolRelation relation: zone.harvestItemToolRelation) {
                    if (0 == relation.itemsThatNeededForHarvest.Count()) {
                        matchedRelations.Insert(relation);
                        continue;
                    }
                    foreach(string _item: relation.itemsThatNeededForHarvest) {
                        _item.ToLower();
                         if (item_in_hands_source && handItemType == _item) {
                            if (0 < item_in_hands_source.GetHealth()) {
                                matchedRelations.Insert(relation);
                            }
                        }
                    }
                }

                if (matchedRelations.Count() == 0) return;

                DZLHarvestItemToolRelation randRelation = matchedRelations.GetRandomElement();

                if (!randRelation) return;

                string randomItemType = randRelation.itemsThatCanHarvest.GetRandomElement();

                InventoryLocation inventoryLocation = new InventoryLocation;
                EntityAI item;

                if (action_data.m_Player.GetInventory().FindFirstFreeLocationForNewEntity(randomItemType, FindInventoryLocationType.ANY, inventoryLocation)) {
                    item = action_data.m_Player.GetHumanInventory().CreateInInventory(randomItemType);
                } else if (!action_data.m_Player.GetHumanInventory().GetEntityInHands()) {
                    item = action_data.m_Player.GetHumanInventory().CreateInHands(randomItemType);
                } else {
                    DZLSendMessage(action_data.m_Player.GetIdentity(), "#no_space_left_in_inventory");
                }

                if (item) {
                    DZLSendMessage(action_data.m_Player.GetIdentity(), "#you_got: " + DZLDisplayHelper.GetItemDisplayName(randomItemType));
                    action_data.m_Player.isOnHarvest = false;
                }

                if (item_in_hands_source) {
                    item_in_hands_source.SetHealth(item_in_hands_source.GetHealth() - zone.damagePerHarvestItem);
                }
            }
        } else if ((action_data.m_State == UA_CANCEL || action_data.m_State == UA_INTERRUPT || action_data.m_State == UA_FAILED) && action_data.m_Player.isOnHarvest == true) {
            action_data.m_Player.isOnHarvest = false;
        }
        super.OnUpdateServer(action_data);
	}

	override void OnStartServer(ActionData action_data) {
	    action_data.m_Player.isOnHarvest = true;
	}

	private DZLWorkZone FindZone(vector playerPosition, DZLJobConfig config) {
	    if (!playerPosition) {
            return null;
        }

	    foreach(DZLWorkZone zone: config.workZones) {
            if(vector.Distance(zone.position, playerPosition) <= zone.range) {
                return zone;
            }
        }
        return null;
    }

};
