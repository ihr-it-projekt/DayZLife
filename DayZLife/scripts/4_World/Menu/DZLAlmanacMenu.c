class DZLAlmanacMenu : DZLBaseMenu
{
    private Widget licenceWidget;
	private MapWidget licenceMap;
	private TextListboxWidget licenceList;
	private TextListboxWidget licenceCraftItemList;
	private ItemPreviewWidget licenceYieldPreview;
	private EntityAI licenceYieldPreviewItem;
	private EntityAI licenceHaverestPreviewItem;
	private ItemPreviewWidget licenceHarvestPreview;
	private TextWidget licenceToolsList;
	private TextWidget licenceItemCraftedName;

    private Widget workzoneWidget;
	private MapWidget workingZoneMap;
	private TextListboxWidget workzoneYieldList;
	private TextListboxWidget workingZoneToolsList;
	private ItemPreviewWidget workzoneToolPreview;
	private ItemPreviewWidget workzoneYieldPreview;
	private EntityAI workZobeToolPreviewItem;
	private EntityAI workZobeYieldPreviewItem;
	private TextListboxWidget workingZoneList;

    private Widget escapedWidget;
	private TextListboxWidget escapedPlayers;
	private PlayerPreviewWidget escapedPlayerPreview;

    private Widget copPanelWidget;
	private TextListboxWidget copPanelOnlinePlayerList;
	private TextListboxWidget copPanelCopsList;
	private ButtonWidget copPanelSave;
	
    private Widget medicPanelWidget;
	private TextListboxWidget medicPanelOnlinePlayerList;
	private TextListboxWidget medicPanelCopsList;
	private ButtonWidget medicPanelSave;

    private Widget adminPanelWidget;
	private TextListboxWidget adminPlayers;
	private ButtonWidget adminDeletePlayerButton;
	private EditBoxWidget adminAddMoneyToPlayerInput;
	private ButtonWidget adminAddMoneyToPlayerButton;
	private ButtonWidget adminAddMoneyToPlayerButtonBank;
	private ButtonWidget adminSearchPlayer;
	private EditBoxWidget adminSearchPlayerInput;
	private TextWidget adminPlayerId;
	private TextWidget adminMoneyCash;
	private TextWidget adminMoneyBank;
	private TextWidget adminJob;
	private TextWidget adminArrestTime;
	private TextWidget adminCanCop;
	private TextListboxWidget adminLicenseTextListbox

	private Widget medicWidget;
	private TextListboxWidget playerNeedMedicList;
	private MapWidget medicMap;

    private TextWidget countCivil;
    private TextWidget countMedic;
    private TextWidget countCop;
	private ButtonWidget syncButton;

	private XComboBoxWidget toggleViewWidget;
	
	private int copPaneId = -1;
	private int adminPanelId = -1;
	private int medicPanelId = -1;
	private int medicManagePanelId = -1;

	private ref array<ref DZLPlayer> allPlayers;

	void DZLAlmanacMenu() {
	    Construct();
	}
	void ~DZLAlmanacMenu() {
	    Destruct();
	}

    override Widget Init() {
		layoutPath = "DayZLife/layout/Almanac/DZL_Almanac.layout";
        super.Init();
        
		licenceWidget = creator.GetWidget("lizenze_panel");
		licenceList = creator.GetTextListboxWidget("lizenzelist");
		licenceToolsList = creator.GetTextWidget("tool_list");
		licenceCraftItemList = creator.GetTextListboxWidget("craft_itembox");
		licenceHarvestPreview = creator.GetItemPreviewWidget("harvestPreview");
		licenceYieldPreview = creator.GetItemPreviewWidget("yield_ItemPreview");
		licenceItemCraftedName = creator.GetTextWidget("Item_Crafted");
		licenceMap = creator.GetMapWidget("lizenzemap");
		
		workzoneWidget = creator.GetWidget("workzone_panel");
		workingZoneList = creator.GetTextListboxWidget("workzonelist");
		workingZoneToolsList = creator.GetTextListboxWidget("tool_listbox");
		workzoneToolPreview = creator.GetItemPreviewWidget("tool_preview");
		workzoneYieldList = creator.GetTextListboxWidget("yield_listbox");
		workzoneYieldPreview = creator.GetItemPreviewWidget("yield_preview");
		workingZoneMap = creator.GetMapWidget("workzonemap");

		copPanelWidget = creator.GetWidget("cop_panel");
		copPanelOnlinePlayerList = creator.GetTextListboxWidget("playerlist_CopPanel");
		copPanelCopsList = creator.GetTextListboxWidget("coplist_CopPanel");
		copPanelSave = creator.GetButtonWidget("saveButton_CopPanel");
		
		medicPanelWidget = creator.GetWidget("medicjob_panel");
		medicPanelOnlinePlayerList = creator.GetTextListboxWidget("playerlist_MedicPanel");
		medicPanelCopsList = creator.GetTextListboxWidget("medicListbox");
		medicPanelSave = creator.GetButtonWidget("saveButton_MedicPanel");
		
		escapedWidget = creator.GetWidget("escaped_panel");
        escapedPlayers = creator.GetTextListboxWidget("escaped_TextListbox");
		escapedPlayerPreview = creator.GetPlayerPreview("escaped_PlayerPreview");

		adminPanelWidget = creator.GetWidget("admin_Panel");
		adminPlayers = creator.GetTextListboxWidget("players");
		adminDeletePlayerButton = creator.GetButtonWidget("delete_Button");
		adminAddMoneyToPlayerButton = creator.GetButtonWidget("giveMoneyButton");
		adminAddMoneyToPlayerButtonBank = creator.GetButtonWidget("giveMoneyButtonBank");
		adminSearchPlayer = creator.GetButtonWidget("searchButton");
		adminAddMoneyToPlayerInput = creator.GetEditBoxWidget("moneyInput");
		adminSearchPlayerInput = creator.GetEditBoxWidget("search_input");
		adminPlayerId = creator.GetTextWidget("playerID");
		adminMoneyCash = creator.GetTextWidget("moneyCash");
		adminMoneyBank = creator.GetTextWidget("moneyBank");
		adminJob = creator.GetTextWidget("job");
		adminArrestTime = creator.GetTextWidget("arrestTime");
		adminCanCop = creator.GetTextWidget("copValue");
		adminLicenseTextListbox = creator.GetTextListboxWidget("licenseTextListbox");
		
		
		medicWidget = creator.GetWidget("medic_Panel");
		playerNeedMedicList = creator.GetTextListboxWidget("player_Listbox");
		medicMap = creator.GetMapWidget("medic_Map");
		
		toggleViewWidget = creator.GetXComboBoxWidget("almanac_box");

		countCivil = creator.GetTextWidget("countCivil");
		countMedic = creator.GetTextWidget("countMedic");
		countCop = creator.GetTextWidget("countCop");
		
		syncButton = creator.GetButtonWidget("sync_Button");

		return layoutRoot;
    }
	
	override void OnShow() {
		super.OnShow();
		string ident = player.GetIdentity().GetId();
		
		if (player.dzlPlayer.IsActiveAsMedic()) {
			toggleViewWidget.AddItem("#emergencies");
			GetGame().RPCSingleParam(player, DAY_Z_LIFE_GET_EMERGENCY_CALLS, new Param1<PlayerBase>(null), true);
			medicPanelId = toggleViewWidget.GetNumItems() - 1;
		}
		
		if (config.adminIds.CanManageCops(ident)) {
			toggleViewWidget.AddItem("#manage_cops");
			GetGame().RPCSingleParam(player, DAY_Z_LIFE_ALL_PLAYER_ONLINE_PLAYERS, new Param1<PlayerBase>(player), true);
			copPaneId = toggleViewWidget.GetNumItems() - 1;
		}
		
		if (config.adminIds.CanManageMedic(ident)) {
			toggleViewWidget.AddItem("#manage_medics");
			GetGame().RPCSingleParam(player, DAY_Z_LIFE_ALL_PLAYER_GET_MEDIC_PLAYERS, new Param1<PlayerBase>(player), true);
			medicManagePanelId = toggleViewWidget.GetNumItems() - 1;
		}

		if (config.adminIds.CanManagePlayers(ident)) {
			toggleViewWidget.AddItem("#admin_Panel");
			GetGame().RPCSingleParam(player, DAY_Z_LIFE_GET_ALL_PLAYERS, new Param1<PlayerBase>(player), true);
			adminPanelId = toggleViewWidget.GetNumItems() - 1;
		}

        GetGame().RPCSingleParam(player, DAY_Z_LIFE_GET_ESCAPED_PLAYERS, new Param1<PlayerBase>(player), true);

	    workzoneWidget.Show(true);
		
		array<ref DZLWorkZone> workZones = config.jobConfig.workZones.workZones;
		DZLLicenceCollection licences = config.licenceConfig.licences;
		
		int index;
		workingZoneList.ClearItems();
		foreach(DZLWorkZone zone: workZones) {
			index = workingZoneList.AddItem(zone.zoneDisplayName, zone, 0);
			workingZoneList.SetItem(index, zone.damagePerHarvestItem.ToString(), zone, 1);
		}
		
		licenceList.ClearItems();
		foreach(DZLLicence licence: licences.collection) {
			licenceList.AddItem(licence.name, licence, 0);
		}
	}
	
	override bool OnDoubleClick(Widget w, int x, int y, int button) {
		if (w == copPanelOnlinePlayerList) {
		    DZLDisplayHelper.MoveDZLOnlinePlayerFromListWidgetToListWidget(copPanelOnlinePlayerList, copPanelCopsList);
		} else if (w == copPanelCopsList) {
		    DZLDisplayHelper.MoveDZLOnlinePlayerFromListWidgetToListWidget(copPanelCopsList, copPanelOnlinePlayerList);
		} else if (w == medicPanelOnlinePlayerList) {
		    DZLDisplayHelper.MoveDZLOnlinePlayerFromListWidgetToListWidget(medicPanelOnlinePlayerList, medicPanelCopsList);
		} else if (w == medicPanelCopsList) {
		    DZLDisplayHelper.MoveDZLOnlinePlayerFromListWidgetToListWidget(medicPanelCopsList, medicPanelOnlinePlayerList);
		}
		
		return false;
	}
	
	override bool OnClick(Widget w, int x, int y, int button) {
		if (super.OnClick(w, x, y, button)) return true;
		
		string name;
		int index;
		
		if (w == workingZoneList) {
			index = workingZoneList.GetSelectedRow();
			
			if (index == -1) return true;
			
			DZLWorkZone zoneWZL
			workingZoneList.GetItemData(index, 0, zoneWZL);
			
			if (!zoneWZL) return true;

			DZLDisplayHelper.UpdateMap(workingZoneMap, zoneWZL.position);
			
			workingZoneToolsList.ClearItems();
			workzoneYieldList.ClearItems();

			string itemUpdatePreview = "";

			foreach(DZLHarvestItemToolRelation relation: zoneWZL.harvestItemToolRelation) {
				foreach(string itemThatNeededForHarvest: relation.itemsThatNeededForHarvest) {
					map<string, DZLHarvestItemToolRelation> mapRelation = new map<string, DZLHarvestItemToolRelation>();
					mapRelation.Set(itemThatNeededForHarvest, relation);
					name = DZLDisplayHelper.GetItemDisplayName(itemThatNeededForHarvest);

					if (itemUpdatePreview == "") {
					    itemUpdatePreview = itemThatNeededForHarvest;
					}

					workingZoneToolsList.AddItem(name, mapRelation, 0);
				}
			}

			if (itemThatNeededForHarvest) {
                workingZoneToolsList.SelectRow(0);

                UpdaterPreview(itemThatNeededForHarvest, workzoneToolPreview, workZobeToolPreviewItem);
            }

            ResetPreview(workZobeYieldPreviewItem);
			
			return true;
			
		} else if (w == workingZoneToolsList) {
			index = workingZoneToolsList.GetSelectedRow();
			
			if (index == -1) return true;
			
			map<string, DZLHarvestItemToolRelation> mapRelationTool;
			workingZoneToolsList.GetItemData(index, 0, mapRelationTool);
			
			if (!mapRelationTool) return true;
			
			DZLHarvestItemToolRelation relationTool = mapRelationTool.GetElement(0);
			string itemName = mapRelationTool.GetKey(0);
			
			workzoneYieldList.ClearItems();
			
			foreach(string itemThatCanHarvest: relationTool.itemsThatCanHarvest) {
				name = DZLDisplayHelper.GetItemDisplayName(itemThatCanHarvest);
				array<string> data = new array<string>;
				data.Insert(itemThatCanHarvest);
				workzoneYieldList.AddItem(name, data, 0);
			}

			if (workzoneYieldList.GetNumItems() > 0) {
                workzoneYieldList.SelectRow(0);
                UpdaterPreviewListBox(workzoneYieldList, workzoneYieldPreview, workZobeYieldPreviewItem);
            }

			UpdaterPreview(itemName, workzoneToolPreview, workZobeToolPreviewItem);
			
			return true;
		} else if(w == workzoneYieldList) {
			UpdaterPreviewListBox(workzoneYieldList, workzoneYieldPreview, workZobeYieldPreviewItem);
			
			return true;
		 }else if(w == licenceCraftItemList) {
			UpdaterPreviewListBoxCraftItem(licenceCraftItemList, licenceHarvestPreview, licenceHaverestPreviewItem);
			
			return true;
		} else if (w == licenceList) {
			index = licenceList.GetSelectedRow();
			
			if (index == -1) return true;
			
			DZLLicence licence;
			licenceList.GetItemData(index, 0, licence);
			
			if (!licence) return true;
			
			DZLDisplayHelper.UpdateMap(licenceMap, licence.position);

			name = "#no_tool_required";
			
			foreach(DZLLicenceToolItem licenceTool: licence.toolItems.collection) {
				if (name != "#no_tool_required") {
					name +=", ";
				} else {
				    name = "";
				}
				name += DZLDisplayHelper.GetItemDisplayName(licenceTool.type);
			}
			
			licenceToolsList.SetText(name);
			
			licenceCraftItemList.ClearItems();
			foreach(DZLLicenceCraftItem craftItem: licence.craftItems.collection) {
				index = licenceCraftItemList.AddItem(DZLDisplayHelper.GetItemDisplayName(craftItem.type), craftItem, 0);
				licenceCraftItemList.SetItem(index, craftItem.quantity.ToString(), craftItem, 1);
			}
			
			UpdaterPreview(licence.craftedItem.type, licenceYieldPreview, licenceYieldPreviewItem);
			
			licenceItemCraftedName.SetText(DZLDisplayHelper.GetItemDisplayName(licence.craftedItem.type));
			
			if (licenceCraftItemList.GetNumItems() > 0) {
				licenceCraftItemList.SelectRow(0);
				UpdaterPreviewListBoxCraftItem(licenceCraftItemList, licenceHarvestPreview, licenceHaverestPreviewItem);
			}
			
			return true;
		} else if(w == toggleViewWidget) {
			int item = toggleViewWidget.GetCurrentItem();

			workzoneWidget.Show(0 == item);
		 	licenceWidget.Show(1 == item);
		 	escapedWidget.Show(2 == item);
			copPanelWidget.Show(copPaneId == item);
			adminPanelWidget.Show(adminPanelId == item);
			medicWidget.Show(medicPanelId == item);
			medicPanelWidget.Show(medicManagePanelId == item);
		} else if (w == copPanelSave) {
            GetGame().RPCSingleParam(player, DAY_Z_LIFE_ALL_PLAYER_UPDATE_COP_PLAYERS, new Param2<PlayerBase, ref array<string>>(player, DZLDisplayHelper.GetPlayerIdsFromList(copPanelCopsList)), true);
		} else if (w == medicPanelSave) {
            GetGame().RPCSingleParam(player, DAY_Z_LIFE_ALL_PLAYER_UPDATE_MEDIC_PLAYERS, new Param2<PlayerBase, ref array<string>>(player, DZLDisplayHelper.GetPlayerIdsFromList(medicPanelCopsList)), true);
		} else if (w == escapedPlayers) {
			int posEscaped = escapedPlayers.GetSelectedRow();
	   		if (posEscaped == -1) {
	   			return true;
	   		}
			
	   		DayZPlayer escaped;
	   		escapedPlayers.GetItemData(posEscaped, 0, escaped);
			
			if (escaped) {
				escapedPlayerPreview.SetPlayer(escaped);
			}
			
			return true;
		} else if (w == adminDeletePlayerButton) {
		    DZLPlayer _dzlPlayer = DZLDisplayHelper.GetDZLPlayerFromList(adminPlayers);

            if (_dzlPlayer) {
		        GetGame().RPCSingleParam(player, DAY_Z_LIFE_DELETE_PLAYER, new Param1<string>(_dzlPlayer.dayZPlayerId), true);
            } else {
                player.DisplayMessage("#no_player_selected");
            }
		} else if (w == adminAddMoneyToPlayerButton) {
		    DZLPlayer __dzlPlayer = DZLDisplayHelper.GetDZLPlayerFromList(adminPlayers);

            if (__dzlPlayer) {
                int deposit = adminAddMoneyToPlayerInput.GetText().ToInt();
		        GetGame().RPCSingleParam(player, DAY_Z_LIFE_MONEY_TRANSFER_ADMIN, new Param4<PlayerBase, string, int, bool>(player, __dzlPlayer.dayZPlayerId, deposit, false), true);
            } else {
                player.DisplayMessage("#no_player_selected");
            }
		} else if (w == adminAddMoneyToPlayerButtonBank) {
		    DZLPlayer ___dzlPlayer = DZLDisplayHelper.GetDZLPlayerFromList(adminPlayers);

            if (___dzlPlayer) {
                int depositBank = adminAddMoneyToPlayerInput.GetText().ToInt();
		        GetGame().RPCSingleParam(player, DAY_Z_LIFE_MONEY_TRANSFER_ADMIN, new Param4<PlayerBase, string, int, bool>(player, ___dzlPlayer.dayZPlayerId, depositBank, true), true);
            } else {
                player.DisplayMessage("#no_player_selected");
            }
		} else if (w == adminPlayers) {
		    DZLPlayer selectedAdminPlayer = DZLDisplayHelper.GetDZLPlayerFromList(adminPlayers);

            if (selectedAdminPlayer) {
                adminPlayerId.SetText(selectedAdminPlayer.dayZPlayerId);
				adminMoneyCash.SetText(selectedAdminPlayer.GetMoney().ToString());
				adminMoneyBank.SetText(selectedAdminPlayer.GetBankMoney().ToString());
				adminJob.SetText(selectedAdminPlayer.GetActiveJob());
				adminArrestTime.SetText(selectedAdminPlayer.arrestTimeInMinutes.ToString());
				adminCanCop.SetText(selectedAdminPlayer.IsCop().ToString());
				adminLicenseTextListbox.ClearItems();
				TStringArray licenceIds = selectedAdminPlayer.licenceIds;

				if (licenceIds.Count() > 0) {
					array<ref DZLLicence> licences = player.config.licenceConfig.licences.collection;
					foreach(DZLLicence configLicence: licences) {
						foreach(string licenceId: licenceIds) {
							if (licenceId == configLicence.id) {
								adminLicenseTextListbox.AddItem(configLicence.name, configLicence, 0);
							}
						}
					}
				}
				
            } else {
                player.DisplayMessage("#no_player_selected");
            }
		} else if (w == syncButton) {
			
			Param1<PlayerBase> paramGetConfig = new Param1<PlayerBase>(player);
            GetGame().RPCSingleParam(player, DAY_Z_LIFE_EVENT_GET_CONFIG, paramGetConfig, true);
            GetGame().RPCSingleParam(player, DAY_Z_LIFE_GET_PLAYER_BUILDING, paramGetConfig, true);
            GetGame().RPCSingleParam(player, DAY_Z_LIFE_PLAYER_DATA, paramGetConfig, true);
            GetGame().RPCSingleParam(player, DAY_Z_LIFE_PLAYER_BANK_DATA, paramGetConfig, true);
			player.DisplayMessage("#player_was_manuel_synced");
			syncButton.Show(false);
		} else if (w == adminSearchPlayer) {
            DZLDisplayHelper.SearchOnlinePlayersSingleWiget(adminSearchPlayerInput.GetText(), adminPlayers, allPlayers);
		} else if (w == playerNeedMedicList) {
			int indexNeedHelp = playerNeedMedicList.GetSelectedRow();
			
			if (-1 != indexNeedHelp) {
				DZLOnlinePlayer emergencyPlayer;
				playerNeedMedicList.GetItemData(indexNeedHelp, 0, emergencyPlayer);
				
				if (emergencyPlayer) {
					DZLDisplayHelper.UpdateMap(medicMap, emergencyPlayer.position);
				}
				
			}
		}

		return false;
	}

	override void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_ALL_PLAYER_ONLINE_PLAYERS_RESPONSE) {
            autoptr Param2<ref array<ref DZLOnlinePlayer>, ref array<ref DZLOnlinePlayer>> paramCopPlayers;
            if (ctx.Read(paramCopPlayers)){

                copPanelOnlinePlayerList.ClearItems();
				
				array<ref DZLOnlinePlayer> onlinePlayers = paramCopPlayers.param1;
				
				foreach(DZLOnlinePlayer onlinePlayer: onlinePlayers) {
					copPanelOnlinePlayerList.AddItem(onlinePlayer.name, onlinePlayer, 0);
				}
				array<ref DZLOnlinePlayer> copPlayers = paramCopPlayers.param2;
				
				foreach(DZLOnlinePlayer copPlayer: copPlayers) {
					copPanelCopsList.AddItem(copPlayer.name, copPlayer, 0);
				}
            }
        } else if (rpc_type == DAY_Z_LIFE_ALL_NOT_MEDIC_PLAYER_ONLINE_PLAYERS_RESPONSE) {
            autoptr Param2<ref array<ref DZLOnlinePlayer>, ref array<ref DZLOnlinePlayer>> paramMedicPlayers;
            if (ctx.Read(paramMedicPlayers)){

                medicPanelOnlinePlayerList.ClearItems();
				
				array<ref DZLOnlinePlayer> onlinePlayersNotMedic = paramMedicPlayers.param1;
				
				foreach(DZLOnlinePlayer onlinePlayerMedic: onlinePlayersNotMedic) {
					medicPanelOnlinePlayerList.AddItem(onlinePlayerMedic.name, onlinePlayerMedic, 0);
				}
				array<ref DZLOnlinePlayer> medicPlayers = paramMedicPlayers.param2;
				
				foreach(DZLOnlinePlayer medicPlayer: medicPlayers) {
					medicPanelCopsList.AddItem(medicPlayer.name, medicPlayer, 0);
				}
            }
        } if (rpc_type == DAY_Z_LIFE_GET_ALL_PLAYERS_RESPONSE) {
            autoptr Param1<ref array<ref DZLPlayer>> paramAllPlayers;
            if (ctx.Read(paramAllPlayers)){
                adminPlayers.ClearItems();

				allPlayers = paramAllPlayers.param1;

				foreach(DZLPlayer _player: allPlayers) {
				    if (_player) {
					    int indexRow = adminPlayers.AddItem(_player.playerName, _player, 0);
					    adminPlayers.SetItem(indexRow, _player.lastLoginDate.ToDateString(), _player, 1);
					}
				}
            }
        } else if (rpc_type == DAY_Z_LIFE_GET_ESCAPED_PLAYERS_RESPONSE) {
            autoptr Param4<ref array<ref DZLEscapedPlayer>, int, int, int> paramEscaped;
            if (ctx.Read(paramEscaped)){
				countCop.SetText(paramEscaped.param2.ToString());
				countMedic.SetText(paramEscaped.param3.ToString());
				countCivil.SetText(paramEscaped.param4.ToString());
				
                escapedPlayers.ClearItems();

				array<ref DZLEscapedPlayer> escapedPlayersParam = paramEscaped.param1;

				foreach(DZLEscapedPlayer escapedPlayer: escapedPlayersParam) {
					int indexOfRow = escapedPlayers.AddItem(escapedPlayer.name, escapedPlayer.player, 0);
					if (player.dzlPlayer.IsActiveAsCop()) {
						escapedPlayers.SetItem(indexOfRow, escapedPlayer.arrestTime.ToString(), escapedPlayer.player, 1);
					} else {
						escapedPlayers.SetItem(indexOfRow, "#only_for_cops", escapedPlayer.player, 1);
					}
					
				}
            }
        } else if (rpc_type == DAY_Z_LIFE_GET_EMERGENCY_CALLS_RESPONSE) {
			autoptr Param1<ref array<ref DZLOnlinePlayer>> paramEmergencies;
            if (ctx.Read(paramEmergencies)){
				playerNeedMedicList.ClearItems();
				array<ref DZLOnlinePlayer> emergencies = paramEmergencies.param1;

				foreach(DZLOnlinePlayer emergency: emergencies) {
					playerNeedMedicList.AddItem(emergency.name, emergency, 0);
				}
			}
		}
	}

	private void UpdaterPreview(string itemType, ItemPreviewWidget preview, EntityAI previewItem) {
		if (itemType) {
			EntityAI currentItem = preview.GetItem();
			
			if (currentItem && currentItem.GetType() == itemType) return;
	
			if (previewItem) {
	            GetGame().ObjectDelete(previewItem);
	        }
	
	        previewItem = EntityAI.Cast(GetGame().CreateObject(itemType, "0 0 0", true, false, false));
	
			preview.SetItem(previewItem);
			preview.SetModelPosition(Vector(0,0,0.5));
		}
	}
	
	private void UpdaterPreviewListBox(TextListboxWidget widget, ItemPreviewWidget preview, EntityAI previewItem) {
		int pos = widget.GetSelectedRow();
   		if (pos == -1) {
   			return;
   		}
   		array<string> itemType;
   		widget.GetItemData(pos, 0, itemType);

   		UpdaterPreview(itemType.Get(0), preview, previewItem);
	}
	private void UpdaterPreviewListBoxCraftItem(TextListboxWidget widget, ItemPreviewWidget preview, EntityAI previewItem) {
		int pos = widget.GetSelectedRow();
   		if (pos == -1) {
   			return;
   		}
   		DZLLicenceCraftItem itemType;
   		widget.GetItemData(pos, 0, itemType);

   		UpdaterPreview(itemType.type, preview, previewItem);
	}

	private void ResetPreview(EntityAI previewItem) {
        if (previewItem) {
            GetGame().ObjectDelete(previewItem);
        }
	}

}
