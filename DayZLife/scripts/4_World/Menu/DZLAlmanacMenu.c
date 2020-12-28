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

    private Widget adminPanelWidget;
	private TextListboxWidget adminPlayers;
	private ButtonWidget adminDeletePlayerButton;

    private TextWidget countCivil;
    private TextWidget countMedic;
    private TextWidget countCop;
	private ButtonWidget syncButton;

	private XComboBoxWidget toggleViewWidget;

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
		
		escapedWidget = creator.GetWidget("escaped_panel");
        escapedPlayers = creator.GetTextListboxWidget("escaped_TextListbox");
		escapedPlayerPreview = creator.GetPlayerPreview("escaped_PlayerPreview");

		adminPanelWidget = creator.GetWidget("admin_Panel");
		adminPlayers = creator.GetTextListboxWidget("players");
		adminDeletePlayerButton = creator.GetButtonWidget("delete_Button");

		toggleViewWidget = creator.GetXComboBoxWidget("almanac_box");

		countCivil = creator.GetTextWidget("countCivil");
		countMedic = creator.GetTextWidget("countMedic");
		countCop = creator.GetTextWidget("countCop");
		
		syncButton = creator.GetButtonWidget("sync_Button");

		return layoutRoot;
    }
	
	override void OnShow() {
		super.OnShow();
		
		if (config.IsAdmin(player.GetIdentity())) {
			toggleViewWidget.AddItem("#manage_cops");
			toggleViewWidget.AddItem("#admin_Panel");
			GetGame().RPCSingleParam(player, DAY_Z_LIFE_ALL_PLAYER_ONLINE_PLAYERS, new Param1<PlayerBase>(player), true);
			GetGame().RPCSingleParam(player, DAY_Z_LIFE_GET_ALL_PLAYERS, new Param1<PlayerBase>(player), true);
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
			copPanelWidget.Show(3 == item);
			adminPanelWidget.Show(4 == item);
		} else if (w == copPanelSave) {
            GetGame().RPCSingleParam(player, DAY_Z_LIFE_ALL_PLAYER_UPDATE_COP_PLAYERS, new Param2<PlayerBase, ref array<string>>(player, DZLDisplayHelper.GetPlayerIdsFromList(copPanelCopsList)), true);
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
		} else if (w == syncButton) {
			
			Param1<PlayerBase> paramGetConfig = new Param1<PlayerBase>(player);
            GetGame().RPCSingleParam(player, DAY_Z_LIFE_EVENT_GET_CONFIG, paramGetConfig, true);
            GetGame().RPCSingleParam(player, DAY_Z_LIFE_GET_PLAYER_BUILDING, paramGetConfig, true);
            GetGame().RPCSingleParam(player, DAY_Z_LIFE_PLAYER_DATA, paramGetConfig, true);
            GetGame().RPCSingleParam(player, DAY_Z_LIFE_PLAYER_BANK_DATA, paramGetConfig, true);
			player.DisplayMessage("#player_was_manuel_synced");
			syncButton.Show(false);
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
        } if (rpc_type == DAY_Z_LIFE_GET_ALL_PLAYERS_RESPONSE) {
            autoptr Param1<ref array<ref DZLPlayer>> paramAllPlayers;
            if (ctx.Read(paramAllPlayers)){
                adminPlayers.ClearItems();

				array<ref DZLPlayer> allPlayers = paramAllPlayers.param1;

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
