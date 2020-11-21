modded class PlayerBase
{
    ref DZLBuyHouseMenu houseBuyMenu;
    ref DZLUpgradeHouseMenu houseUpgradeMenu;
    ref DZLBankingMenu bankingMenu;
    ref DZLTraderMenu traderMenu;
    ref DZLConfig config;
	ref DZLPlayerHouse house;
	ref DZLPlayer dzlPlayer;
	ref DZLBank dzlBank;
	ref DZLLicenceMenu licenceMenu;
	ref DZLLicenceProgressBar progressBarLicence;
	ref DZLDoorRaidProgressBar progressBarRaid;
	ref DZLMessageMenu messageMenu;

	bool IsDZLBank = false;
	bool IsLicencePoint = false;
	bool IsTrader = false;
	int moneyPlayerIsDead = 0;
	bool IsRealPlayer = false;

	void ~PlayerBase() {
	    GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
	}

	override void Init() {
        super.Init();
        RegisterNetSyncVariableBool("IsDZLBank");
        RegisterNetSyncVariableBool("IsRealPlayer");
        RegisterNetSyncVariableBool("IsLicencePoint");
        RegisterNetSyncVariableBool("IsTrader");
        RegisterNetSyncVariableInt("moneyPlayerIsDead", 0, 99999999999);
	}

	bool IsDZLPlayer() {
	    return !IsDZLBank && !IsLicencePoint && !IsTrader;
	}

    override void SetActions(out TInputActionMap InputActionMap) {
        super.SetActions(InputActionMap);

        AddAction(ActionOpenBuyHouseMenu, InputActionMap);
        AddAction(ActionOpenUpgradeHouseMenu, InputActionMap);
        AddAction(ActionOpenTraderMenu, InputActionMap);
        AddAction(ActionOpenBankingMenu, InputActionMap);
        AddAction(ActionRobMoney, InputActionMap);
        AddAction(ActionRobMoneyFromDead, InputActionMap);
        AddAction(ActionRobBank, InputActionMap);
        AddAction(ActionHarvestItem, InputActionMap);
        AddAction(ActionOpenLicenseMenu, InputActionMap);
        AddAction(ActionLicenceCrafting, InputActionMap);
        AddAction(DZLActionLockDoors, InputActionMap);
        AddAction(DZLActionRaidDoors, InputActionMap);
        AddAction(DZLActionUnLockDoors, InputActionMap);

        if (GetGame().IsClient() && IsDZLPlayer()) {
            GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
            Param1<PlayerBase> paramGetConfig = new Param1<PlayerBase>(this);
            GetGame().RPCSingleParam(paramGetConfig.param1, DAY_Z_LIFE_EVENT_GET_CONFIG, paramGetConfig, true);
            GetGame().RPCSingleParam(paramGetConfig.param1, DAY_Z_LIFE_GET_PLAYER_BUILDING, paramGetConfig, true);
            GetGame().RPCSingleParam(paramGetConfig.param1, DAY_Z_LIFE_PLAYER_DATA, paramGetConfig, true);
            GetGame().RPCSingleParam(paramGetConfig.param1, DAY_Z_LIFE_PLAYER_BANK_DATA, paramGetConfig, true);
        }
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_EVENT_GET_CONFIG_RESPONSE) {
            Param1 <ref DZLConfig> configParam;
            DebugMessageDZL("Initialize DZLConfig");
            if (ctx.Read(configParam)){
                this.config = configParam.param1;
                IsRealPlayer = true;
            }
        } else if (rpc_type == DAY_Z_LIFE_GET_PLAYER_BUILDING_RESPONSE) {
            Param1 <ref DZLPlayerHouse> houseParam;
            DebugMessageDZL("Initialize DZLPlayerHouse");
            if (ctx.Read(houseParam)){
                this.house = houseParam.param1;
            }
        } else if (rpc_type == DAY_Z_LIFE_PLAYER_DATA_RESPONSE) {
            Param1 <ref DZLPlayer> dzlPlayerParam;
            DebugMessageDZL("Initialize DZLPlayer");
            if (ctx.Read(dzlPlayerParam)){
                this.dzlPlayer = dzlPlayerParam.param1;
                UpdatePlayerAtDependencies();
            }
        } else if (rpc_type == DAY_Z_LIFE_PLAYER_BANK_DATA_RESPONSE) {
            Param1 <ref DZLBank> dzlBankParam;
            DebugMessageDZL("Initialize Bank");
            if (ctx.Read(dzlBankParam)){
                this.dzlBank = dzlBankParam.param1;
            }
        } else if (rpc_type == DAY_Z_LIFE_RECEIVE_MESSAGE) {
            Param1 <string> dzlMessage;
            DebugMessageDZL("Receive Message");
            if (ctx.Read(dzlMessage)){
                DisplayMessage(dzlMessage.param1);
            }
        }
    }

    void DisplayMessage(string message) {
        GetMessageMenu();
        messageMenu.SetText(message);
        messageMenu.Init();
        messageMenu.OnShow();
    }

    void UpdatePlayerAtDependencies() {
        if (houseBuyMenu && houseBuyMenu.IsVisible()) {
            houseBuyMenu.UpdatePlayer(this);;
        } else if (houseUpgradeMenu && houseUpgradeMenu.IsVisible()) {
            houseUpgradeMenu.UpdatePlayer(this);;
        } else if (bankingMenu && bankingMenu.IsVisible()) {
            bankingMenu.UpdatePlayer(this);;
        } else if (traderMenu && traderMenu.IsVisible()) {
            traderMenu.UpdatePlayer(this);;
        } else if (licenceMenu && licenceMenu.IsVisible()) {
            licenceMenu.UpdatePlayer(this);;
        } else if (progressBarLicence && progressBarLicence.IsVisible()) {
            progressBarLicence.UpdatePlayer(this);;
        }
    }

    DZLBuyHouseMenu GetHouseBuyMenu(DZLHouseDefinition definition, Building target) {
        DebugMessageDZL("Initialize house buy menu");
        houseBuyMenu = new DZLBuyHouseMenu;
        InitMenu(houseBuyMenu);

		houseBuyMenu.SetHouseDefinition(definition);
		houseBuyMenu.SetTarget(target);

        return houseBuyMenu;
    }

    DZLUpgradeHouseMenu GetHouseUpgradeMenu(DZLHouseDefinition definition, Building target) {
        DebugMessageDZL("Initialize house upgrade menu");
        houseUpgradeMenu = new DZLUpgradeHouseMenu;
        InitMenu(houseUpgradeMenu);

		houseUpgradeMenu.SetHouseDefinition(definition);
		houseUpgradeMenu.SetTarget(target);

        return houseUpgradeMenu;
    }

    private void InitMenu(DZLBaseMenu menu) {
        menu.SetConfig(config);
        menu.SetPlayer(this);
    }

	DZLMessageMenu GetMessageMenu() {
		messageMenu = new DZLMessageMenu();
		return messageMenu;
	}

	DZLTraderMenu GetTraderMenu() {
		traderMenu = new DZLTraderMenu();
		InitMenu(traderMenu);
		return traderMenu;
	}

	DZLBankingMenu GetBankingMenu() {
		bankingMenu = new DZLBankingMenu();
		InitMenu(bankingMenu);
		return bankingMenu;
	}

	DZLLicenceMenu GetLicenceMenu() {
		licenceMenu = new DZLLicenceMenu();
		InitMenu(licenceMenu);
		return licenceMenu;
	}

    DZLLicenceProgressBar GetLicenceProgressBar() {
        progressBarLicence = new DZLLicenceProgressBar();
        progressBarLicence.SetPlayer(this);
        return progressBarLicence;
    }

    DZLDoorRaidProgressBar GetRaidProgressBar() {
        progressBarRaid = new DZLDoorRaidProgressBar();
        progressBarRaid.SetPlayer(this);
        return progressBarRaid;
    }

	void CloseMenu() {
		if (houseBuyMenu && houseBuyMenu.IsVisible()) {
			houseBuyMenu.OnHide();
		} else if (houseUpgradeMenu && houseUpgradeMenu.IsVisible()) {
			houseUpgradeMenu.OnHide();
		} else if (bankingMenu && bankingMenu.IsVisible()) {
			bankingMenu.OnHide();
		} else if (traderMenu && traderMenu.IsVisible()) {
			traderMenu.OnHide();
		} else if (licenceMenu && licenceMenu.IsVisible()) {
			licenceMenu.OnHide();
		} else if (progressBarLicence && progressBarLicence.IsVisible()) {
			progressBarLicence.OnHide();
		} else if (progressBarRaid && progressBarRaid.IsVisible()) {
			progressBarRaid.OnHide();
		}
	}

	DZLHouseDefinition FindHouseDefinition(Building building) {
		array<ref DZLHouseDefinition> houseConfigs = config.GetHouseDefinitions();
		foreach(DZLHouseDefinition definition: houseConfigs) {
                if (definition.houseType == building.GetType()) {
					return definition;
                }
            }
		return null;
	}

    void TransferFromDeadPlayer(DZLPlayer playerTarget) {
        playerTarget.AddMoneyToPlayer(moneyPlayerIsDead);
        moneyPlayerIsDead = 0;
    }

    float GetMoneyPlayerIsDead() {
        return moneyPlayerIsDead;
    }

    void SetMoneyPlayerIsDead(float money) {
        IsRealPlayer = false;
        moneyPlayerIsDead = money;
    }
	
	DZLLicence GetLicenceByPosition() {
		
		if (GetGame().IsServer()) {
			dzlPlayer = new DZLPlayer(GetIdentity().GetId());
			config = new DZLConfig();
		}

	    if(!dzlPlayer) return null;

        vector playerPosition = GetPosition();
        if (!playerPosition) {
            return null;
        }
		
        foreach(string licenceId: dzlPlayer.licenceIds) {
			DZLLicence licence = config.licenceConfig.licences.FindById(licenceId);
			
			if(!licence) continue;
			
            if (vector.Distance(licence.position, playerPosition) <= licence.range){
                return licence;
            }
        }
        return null;
    }

    DZLTraderPosition GetTraderByPosition(int distance = 2) {
		vector playerPosition = GetPosition();
        if (!playerPosition) {
            return null;
        }
		
		array<ref DZLTraderPosition> positions = config.traderConfig.positions.positions;
		
		foreach(DZLTraderPosition position: positions) {
			float distanceToPos = vector.Distance(position.position, playerPosition);
			if (distanceToPos <= distance){
                return position;
            }
		}
		
		return null;
        
    }
	
	string CanUseLicence(notnull DZLLicence licence) {
        array<EntityAI> items = GetPlayerItems();
        map<string, int> craft = new map<string, int>;
        map<string, int> tools = new map<string, int>;
		string message = "";

        foreach(EntityAI item: items) {
            string itemType = item.GetType();
            itemType.ToLower();
			int quantity = item.GetQuantity();
			if (quantity == 0) {
                quantity = 1;
            }
			
			bool isCraft = false;

			foreach(DZLLicenceCraftItem craftItem: licence.craftItems.collection) {
                if(IsNeededItem(craftItem, item, itemType)) {
					int countCraft = 0;
					if (craft.Find(itemType, countCraft)) {
						craft.Set(itemType, countCraft + quantity);
					} else {
						craft.Insert(itemType, quantity);
					}
					isCraft = true;
					break;
				}
			}
			
			if(isCraft) continue;
			
			foreach(DZLLicenceToolItem toolItem: licence.toolItems.collection) {
                if(IsNeededItem(toolItem, item, itemType)) {
					int countTools = 0;
					if (tools.Find(itemType, countTools)) {
						tools.Set(itemType, countTools + quantity);
					} else {
						tools.Insert(itemType, quantity);
					}
					break;
				}
			}
        }
		
		map<string, int> craftMap = licence.craftItems.GetTypeCountMap();
		map<string, int> toolMap = licence.toolItems.GetTypeCountMap();

		if (craft.Count() >= craftMap.Count() && tools.Count() >= toolMap.Count()) {
		    foreach(string type, int count: craftMap) {
				int countFound = 0;
				if (craft.Find(type, countFound)) {
					if (countFound < count) {
						return "#not_enough_items_to_craft";
					}
				} else {
					return "#missing_craft_item";
				}
			}
			
			foreach(string typeTool, int countTool: toolMap) {
                int countFoundTool = 0;
                if (tools.Find(typeTool, countFoundTool)) {
                    if (countFoundTool < countTool) {
                        return "#not_enough_tools_to_craft";
                    }
                } else {
                    return "#missing_tool_item";
                }
            }
		} else {
			message = "#has_not_found_all_items_that_is_needed_to_craft";
		}
		
        return message;
	}

	void UseLicence(DZLLicence licence) {
        array<EntityAI> items = GetPlayerItems();
        map<string, int> craftMap = licence.craftItems.GetTypeCountMap();
        map<string, int> toolMap = licence.toolItems.GetTypeCountMap();

        foreach(EntityAI item: items) {
			if (craftMap.Count() == 0 && toolMap.Count() == 0) break;
			
            string itemType = item.GetType();
            itemType.ToLower();
            int quantity = item.GetQuantity();
            if (quantity == 0) {
                quantity = 1;
            }

			bool isCraft = false;
			foreach(DZLLicenceCraftItem craftItem: licence.craftItems.collection) {
				if (craftMap.Count() == 0) break;
				
                if(IsNeededItem(craftItem, item, itemType)) {
					int countFoundCraft = 0;
					if(craftMap.Find(itemType, countFoundCraft)) {
						if (quantity == 1) {
							GetGame().ObjectDelete(item);
							countFoundCraft -= 1;
							craftMap.Set(itemType, countFoundCraft);
						} else if (quantity > countFoundCraft) {
							ItemBase.Cast(item).SetQuantity(quantity - countFoundCraft);
							countFoundCraft = 0;
						} else {
							countFoundCraft -= quantity;
							GetGame().ObjectDelete(item);
							craftMap.Set(itemType, countFoundCraft);
						}

						if (0 == countFoundCraft) {
                            craftMap.Remove(itemType);
						}

						isCraft = true;
						break;
					}
				}
			}

			if(isCraft) continue;

			foreach(DZLLicenceToolItem toolItem: licence.toolItems.collection) {
				if (toolMap.Count() == 0) break;
				
                if(IsNeededItem(toolItem, item, itemType)) {
					int countFoundTool = 0;
					if(toolMap.Find(itemType, countFoundTool)) {
					    int health = item.GetHealth();
						
						if (health >= toolItem.health) {
						    if (quantity == 1) {
						        craftMap.Remove(itemType);
						    } else {
						        craftMap.Set(itemType, craftMap.Get(itemType) - 1);
						    }

							item.SetHealth(health - toolItem.health);
						}
						break;
					}
				}
			}
        }

		
        InventoryLocation inventoryLocation = new InventoryLocation;
        EntityAI itemSpawn;
		DZLLicenceCraftedItem itemToCraft = licence.craftedItem;
		
        if (GetInventory().FindFirstFreeLocationForNewEntity(itemToCraft.type, FindInventoryLocationType.ANY, inventoryLocation)) {
            itemSpawn = GetHumanInventory().CreateInInventory(itemToCraft.type);
        } else if (GetHumanInventory().GetEntityInHands()) {
            itemSpawn = GetHumanInventory().CreateInHands(itemToCraft.type);
        } else {
            itemSpawn = SpawnEntityOnGroundPos(itemToCraft.type, GetPosition());
        }
		
		if (itemSpawn) {
			itemSpawn.SetHealth(itemToCraft.health);
			ItemBase.Cast(itemSpawn).SetQuantity(itemToCraft.quantity);
		}
		
	}

	private bool IsNeededItem(DZLLicenceCraftItem item, EntityAI itemSearch, string ItemSearchType) {
        if(item.GetLowerCaseType() == ItemSearchType) {
            if(GetGame().IsServer()) {
                if (itemSearch.GetHealth() >= item.health){
					return true;
                }
            } else {
                return true;
            }
        }

        return false;
	}
		
	array<EntityAI> GetPlayerItems() {
        array<EntityAI> itemsArray = new array<EntityAI>;
        GetInventory().EnumerateInventory(InventoryTraversalType.INORDER, itemsArray);

        return itemsArray;
    }
}