modded class PlayerBase
{
    private ref DZLLicenceMenu licenceMenu;
    private ref DZLLicenceProgressBar progressBarLicence;
    private ref DZLDoorRaidProgressBar progressBarRaid;
    private ref DZLCarRaidProgressBar progressBarRaidCar;
    private ref DZLHarvestProgressBar progressBarHarvest;
    private ref DZLMessageMenu messageMenu;
    private ref DZLPlayerMoneyTransferMenu moneyTransferMenu;
    private ref DZLSpawnPositionMenu spawnPositionMenu;
    private ref DZLLoadOutMenu loadOutMenu;
    private ref DZLPlayerArrestMenu arrestMenu;
    private ref DZLCarMenu carMenu;
    private ref DZLCarStorageMenu carStorageMenu;
    private ref DZLMedicHelpMenu healMenu;
    private ref DZLMessageSystemMenu messageSystemMenu;
    private ref DZLHouseMenu houseMenu;
    private ref DZLBankingMenu bankingMenu;
    private ref DZLTraderMenu traderMenu;
    private ref DZLAlmanacMenu almanacMenu;

	bool willHeal = false;
	bool willDie = false;
	int moneyPlayerIsDead = 0;
	bool isOnHarvest = false;
	bool isPolice = false;
	bool medicHelpMenuWasShown = false;
	private ref Timer resetCanSpawn;
	private ref Timer enableToHospital;
	bool canHealInHospital = false;
	bool canSeeKillButton = false;
	int waitForHospital = 0;
	int medicCount = 0;

	int timeAskForTraderConfig = 0;
	int timeAskForBankingConfig = 0;
	bool hasBankingConfig = false;
	float deltaTimeLastUpdate = 0;

	private string playerUID;

	override void Init() {
        super.Init();
        RegisterNetSyncVariableInt("moneyPlayerIsDead", 0, 99999999999);
	}

	void SetIsSpawned() {
	    int time = DZLPlayerClientDB.Get().GetConfig().civilSpawnPoints.blockTimeForJobChange;
		DZLPlayer dzlPlayer = GetDZLPlayer();
	    if (dzlPlayer.IsCop()) {
	        time = DZLPlayerClientDB.Get().GetConfig().copSpawnPoints.blockTimeForJobChange;
	    } else if (dzlPlayer.IsMedic()) {
	        time = DZLPlayerClientDB.Get().GetConfig().medicSpawnPoints.blockTimeForJobChange;
	    }
	    resetCanSpawn = new Timer;
        resetCanSpawn.Run(time, this, "ResetSpawned");
	}

	void EnableTimerEnableHospital() {
	    enableToHospital = new Timer;
	    enableToHospital.Run(1, this, "EnableToHospital", null, true);
	    waitForHospital = 0;
	}

	void EnableToHospital() {
	    ++waitForHospital;
	    if (GetWaitTimeForHospital() < 1) {
	        canHealInHospital = true;
	    }
	    if (GetWaitTimeForKill() < 1) {
	        canSeeKillButton = true;
	    }

	    if(canHealInHospital && canSeeKillButton) {
	        enableToHospital.Stop();
	    }
	}

	int IsKillButtonOn() {
	    return waitForHospital;
	}

	int GetWaitTimeForHospital() {
		DZLConfig config = GetConfig();
	    if (medicCount >= config.medicConfig.minMedicCountForHospitalTimer) {
	        return config.medicConfig.minTimeBeforeHospital - waitForHospital;
	    }
	    return config.medicConfig.minTimeBeforeHospitalWhenMinMedicNotOnline - waitForHospital;
	}

	int GetWaitTimeForKill() {
	    return GetConfig().medicConfig.minTimeBeforeKillButton - waitForHospital;
	}

	void ResetSpawned() {
	    resetCanSpawn.Stop();
	    resetCanSpawn = null;
	}

	bool CanReSpawn() {
	    return !resetCanSpawn;
	}
	
	string GetPlayerId() {
		if (!playerUID) {
			playerUID = GetIdentity().GetId();
		}
		
		return playerUID;
	}

	bool IsDZLPlayer() {
        return !!GetIdentity();
    }

    override void SetActions(out TInputActionMap InputActionMap) {
        super.SetActions(InputActionMap);

        AddAction(ActionOpenHouseMenu, InputActionMap);
        AddAction(ActionRobMoney, InputActionMap);
        AddAction(ActionRobMoneyFromDead, InputActionMap);
        AddAction(DZLActionHarvestItem, InputActionMap);
        AddAction(DZLActionLockDoors, InputActionMap);
        AddAction(DZLActionRaidDoors, InputActionMap);
        AddAction(DZLActionUnLockDoors, InputActionMap);
        AddAction(DZLActionTransferMoney, InputActionMap);
        AddAction(ActionOpenArrestMenu, InputActionMap);
    }
	
	override void CheckDeath()
	{
		if(IsPlayerSelected() && !IsAlive())
		{
			if (!medicHelpMenuWasShown) {
			    ShowHealMenu();
			    EnableTimerEnableHospital();
			    PPEffects.SetUnconsciousnessVignette(1000);
			} else if (willDie) {
                SimulateDeath(true);
                m_DeathCheckTimer.Stop();
			}
		}
	}

    void RequestUpdateDZLPlayer() {
        GetGame().RPCSingleParam(this, DAY_Z_LIFE_PLAYER_DATA, null, true);
        GetGame().RPCSingleParam(this, DAY_Z_LIFE_PLAYER_BANK_DATA, null, true);
    }

    void DisplayMessage(string message) {
        GetMessageMenu();
        messageMenu.SetText(message);
        messageMenu.Init();
        messageMenu.Show();
    }

    void UpdatePlayerAtDependencies() {
        if (houseMenu && houseMenu.IsVisible()) {
            houseMenu.UpdatePlayer(this);
        } else if (bankingMenu && bankingMenu.IsVisible()) {
            bankingMenu.UpdatePlayer(this);
        } else if (traderMenu && traderMenu.IsVisible()) {
            traderMenu.UpdatePlayer(this);
        } else if (licenceMenu && licenceMenu.IsVisible()) {
            licenceMenu.UpdatePlayer(this);
        } else if (progressBarLicence && progressBarLicence.IsVisible()) {
            progressBarLicence.UpdatePlayer(this);
        } else if (loadOutMenu && loadOutMenu.IsVisible()) {
            loadOutMenu.UpdatePlayer(this);
        } else if (arrestMenu && arrestMenu.IsVisible()) {
            arrestMenu.UpdatePlayer(this);
        } else if (carMenu && carMenu.IsVisible()) {
            carMenu.UpdatePlayer(this);
        } else if (carStorageMenu && carStorageMenu.IsVisible()) {
            carStorageMenu.UpdatePlayer(this);
        } else if (healMenu && healMenu.IsVisible()) {
            healMenu.UpdatePlayer(this);
        }else if (messageSystemMenu && messageSystemMenu.IsVisible()) {
            messageSystemMenu.UpdatePlayer(this);
        }
    }

    DZLHouseMenu GetHouseMenu(DZLHouseDefinition definition, Building target) {
        houseMenu = new DZLHouseMenu;
        InitMenu(houseMenu);

		houseMenu.SetHouseDefinition(definition);
		houseMenu.SetTarget(target);

        return houseMenu;
    }
	
    DZLCarMenu GetCarMenu(CarScript car) {
        carMenu = new DZLCarMenu;
        InitMenu(carMenu);
		carMenu.SetCar(car);
		
        return carMenu;
    }

    DZLMedicHelpMenu GetMedicHealMenu() {
        healMenu = new DZLMedicHelpMenu;
        InitMenu(healMenu);

        return healMenu;
    }

    DZLCarStorageMenu GetCarStorageMenu() {
        carStorageMenu = new DZLCarStorageMenu;
        InitMenu(carStorageMenu);

        return carStorageMenu;
    }
	
    private void InitMenu(DZLBaseMenu menu) {
        menu.SetConfig(GetConfig());
        menu.SetPlayer(this);
    }

	DZLMessageMenu GetMessageMenu() {
		messageMenu = new DZLMessageMenu();
		return messageMenu;
	}

	DZLAlmanacMenu GetAlmanacMenu() {
		almanacMenu = new DZLAlmanacMenu();
		InitMenu(almanacMenu);
		return almanacMenu;
	}
	
	DZLTraderMenu GetTraderMenu(DZLTraderPosition position) {
		traderMenu = new DZLTraderMenu(position);
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

	DZLLoadOutMenu GetLoadOutMenu() {
		loadOutMenu = new DZLLoadOutMenu();
		InitMenu(loadOutMenu);
		return loadOutMenu;
	}

	DZLPlayerArrestMenu GetArrestMenu() {
		arrestMenu = new DZLPlayerArrestMenu();
		InitMenu(arrestMenu);
		return arrestMenu;
	}

	DZLPlayerMoneyTransferMenu GetPlayerMoneyTransferMenu() {
		moneyTransferMenu = new DZLPlayerMoneyTransferMenu();
		InitMenu(moneyTransferMenu);
		return moneyTransferMenu;
	}

    DZLLicenceProgressBar GetLicenceProgressBar() {
        progressBarLicence = new DZLLicenceProgressBar();
        progressBarLicence.SetPlayer(this);
        return progressBarLicence;
    }

    DZLHarvestProgressBar GetHarvestProgressBar() {
        progressBarHarvest = new DZLHarvestProgressBar();
        progressBarHarvest.SetPlayer(this);
        return progressBarHarvest;
    }

    DZLDoorRaidProgressBar GetRaidProgressBar() {
        progressBarRaid = new DZLDoorRaidProgressBar();
        progressBarRaid.SetPlayer(this);
        return progressBarRaid;
    }

    DZLCarRaidProgressBar GetRaidCarProgressBar() {
        progressBarRaidCar = new DZLCarRaidProgressBar();
        progressBarRaidCar.SetPlayer(this);
        return progressBarRaidCar;
    }
	
	DZLSpawnPositionMenu GetSpawnPositionMenu() {
		spawnPositionMenu = new DZLSpawnPositionMenu();
		InitMenu(spawnPositionMenu);
		return spawnPositionMenu;
	}

	DZLMessageSystemMenu GetMessageSystemMenu() {
		messageSystemMenu = new DZLMessageSystemMenu();
		InitMenu(messageSystemMenu);
		return messageSystemMenu;
	}

	void RefreshMessageSystem() {
	    if (messageSystemMenu) {
	        messageSystemMenu.RefreshMessageSystem();
	    }
	}

	void CloseMenu() {
		if (houseMenu && houseMenu.IsVisible()) {
			houseMenu.OnHide();
		} else if (bankingMenu && bankingMenu.IsVisible()) {
			bankingMenu.OnHide();
		} else if (traderMenu && traderMenu.IsVisible()) {
			traderMenu.OnHide();
		} else if (licenceMenu && licenceMenu.IsVisible()) {
			licenceMenu.OnHide();
		} else if (loadOutMenu && loadOutMenu.IsVisible()) {
			loadOutMenu.OnHide();
		} else if (arrestMenu && arrestMenu.IsVisible()) {
			arrestMenu.OnHide();
		} else if (progressBarLicence && progressBarLicence.IsVisible()) {
			progressBarLicence.OnHide();
		} else if (almanacMenu && almanacMenu.IsVisible()) {
			almanacMenu.OnHide();
		} else if (progressBarRaid && progressBarRaid.IsVisible()) {
			progressBarRaid.OnHide();
		} else if (progressBarRaidCar && progressBarRaidCar.IsVisible()) {
			progressBarRaidCar.OnHide();
		} else if (moneyTransferMenu && moneyTransferMenu.IsVisible()) {
			moneyTransferMenu.OnHide();
		} else if (carMenu && carMenu.IsVisible()) {
			carMenu.OnHide();
		} else if (carStorageMenu && carStorageMenu.IsVisible()) {
			carStorageMenu.OnHide();
		} else if (healMenu && healMenu.IsVisible()) {
			healMenu.OnHide();
		} else if (spawnPositionMenu && spawnPositionMenu.IsVisible()) {
			spawnPositionMenu.OnHide();
		} else if (messageSystemMenu && messageSystemMenu.IsVisible()) {
		    messageSystemMenu.OnHide();
		}
	}

	DZLHouseDefinition FindHouseDefinition(Building building) {
		array<ref DZLHouseDefinition> houseConfigs = GetConfig().GetHouseDefinitions();
		if (!houseConfigs) return null;
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
        moneyPlayerIsDead = money;
        money = 0;
    }
	
	DZLCraftLicence GetLicenceByPosition() {
	    if(!GetDZLPlayer() || !GetConfig() || !GetConfig().licenceConfig) return null;

        vector playerPosition = GetPosition();
        if (!playerPosition) {
            return null;
        }
		
        foreach(string licenceId: GetDZLPlayer().licenceIds) {
			DZLCraftLicence licence = GetConfig().licenceConfig.licenceCollection.FindById(licenceId);
			
			if(!licence) continue;
			
            if (vector.Distance(licence.position, playerPosition) <= 3){
                return licence;
            }
        }
        if (GetGame().IsServer()) {
            DZLSendMessage(GetIdentity(), "#you_have_not_the_dependency_licence");
        }
        return null;
    }

    DZLTraderPosition GetTraderByPosition(int distance = 3) {
		vector playerPosition = GetPosition();
        if (!playerPosition || !GetConfig() || !GetConfig().traderConfig) {
            return null;
        }
		
		array<ref DZLTraderPosition> positions = GetConfig().traderConfig.positions.positions;
		
		foreach(DZLTraderPosition position: positions) {
			float distanceToPos = vector.Distance(position.position, playerPosition);
			if (distanceToPos <= distance){
                return position;
            }
		}
		
		return null;
    }

	string CanUseLicence(notnull DZLCraftLicence licence) {
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

	void UseLicence(DZLCraftLicence licence) {
        array<EntityAI> items = GetPlayerItems();
        map<string, int> craftMap = licence.craftItems.GetTypeCountMap();
        map<string, int> toolMap = licence.toolItems.GetTypeCountMap();
		
		array<DZLLicenceToolItem> tools = new array<DZLLicenceToolItem>;
		
		foreach(DZLLicenceToolItem tool: licence.toolItems.collection) {
			tools.Insert(tool);
		}
		
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
							DZLLogCrafting(GetPlayerId(), "licence crafting delete resource", item.GetType());
							countFoundCraft -= 1;
							craftMap.Set(itemType, countFoundCraft);
						} else if (quantity > countFoundCraft) {
							ItemBase.Cast(item).SetQuantity(quantity - countFoundCraft);
							countFoundCraft = 0;
						} else {
							countFoundCraft -= quantity;
							GetGame().ObjectDelete(item);
							DZLLogCrafting(GetPlayerId(), "licence crafting delete resource", item.GetType());
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

			foreach(int index, DZLLicenceToolItem toolItem: tools) {
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
							DZLLogCrafting(GetPlayerId(), "licence crafting tool reduce health", item.GetType());
						}
						tools.Remove(index);
						break;
					}
				}
			}
        }

		
        InventoryLocation inventoryLocation = new InventoryLocation;
        EntityAI itemSpawn;
		DZLLicenceCraftedItem itemToCraft = licence.craftedItem;
		
		if (itemToCraft.spawnOnGround) {
			itemSpawn = SpawnEntityOnGroundPos(itemToCraft.type, itemToCraft.positionIfSpawnOnGround.ToVector());
		} else {
			if (GetInventory().FindFirstFreeLocationForNewEntity(itemToCraft.type, FindInventoryLocationType.ANY, inventoryLocation)) {
			    itemSpawn = GetHumanInventory().CreateInInventory(itemToCraft.type);
			} else if (GetHumanInventory().GetEntityInHands()) {
			    itemSpawn = GetHumanInventory().CreateInHands(itemToCraft.type);
			} else {
			    itemSpawn = SpawnEntityOnGroundPos(itemToCraft.type, GetPosition());
			}
		}
		
		if (itemSpawn) {
		    DZLLogCrafting(GetPlayerId(), "licence crafting get item", itemToCraft.type);
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

    bool HasInInventory(string type) {
        array<EntityAI> items = GetPlayerItems();
        foreach(EntityAI item: items) {
            if (item.GetType() == type) {
                return true;
            }
        }
		return false;
    }
	
	override void RemoveAllItems() {
		array<EntityAI> itemsArray = new array<EntityAI>;
		ItemBase item;
		GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
		
		for (int i = 0; i < itemsArray.Count(); i++) {
			Class.CastTo(item, itemsArray.Get(i));
			if (item && !item.IsInherited(SurvivorBase)) {
				GetGame().ObjectDelete(item);
			}	
		}
	}
	
	void ShowHealMenu() {
        if (GetGame().IsClient()){
            if (!healMenu && medicHelpMenuWasShown == false){
                if (g_Game.GetUIManager().GetMenu()) {
                    g_Game.GetUIManager().GetMenu().Close();
                }
				DZLConfig config = GetConfig();
                if (config && config.medicConfig && medicHelpMenuWasShown == false) {
                    GetGame().GetUIManager().ShowScriptedMenu(GetMedicHealMenu(), NULL);
                    medicHelpMenuWasShown = true;
                }
            }
        }
	}

	void ShowHealMenuFromMission() {
	    if (GetGame().IsClient() && medicHelpMenuWasShown){
	        medicHelpMenuWasShown = false;
	        ShowHealMenu();
	    }
	}

    DZLConfig GetConfig() {
        if (GetGame().IsServer()) {
            return DZLConfig.Get();
        }
        return DZLPlayerClientDB.Get().GetConfig();
    }

    DZLPlayer GetDZLPlayer() {
        if (GetGame().IsServer()) {
            return DZLDatabaseLayer.Get().GetPlayer(GetPlayerId());
        }
        return DZLPlayerClientDB.Get().GetDZLPlayer();
    }

    DZLPlayerHouse GetPlayerHouse() {
        if (GetGame().IsServer()) {
            return DZLDatabaseLayer.Get().GetPlayerHouse(GetPlayerId());
        }
        return DZLPlayerClientDB.Get().GetPlayerHouse();
    }

    DZLBank GetBank() {
        if (GetGame().IsServer()) {
            return DZLDatabaseLayer.Get().GetBank();
        }
        return DZLPlayerClientDB.Get().GetBank();
    }

    void ResetDZLPlayer() {
        if (GetGame().IsServer()) {
            GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, null, true, GetIdentity());
        }
    }
}
