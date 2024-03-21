class DZLAlmanacMenu : DZLBaseMenu {
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

    private Widget playerOpenTicketsWidget;
    private TextListboxWidget playerOpenTicketsList;

    private string selectedJob;
    private Widget jobPanelWidget;
    private TextListboxWidget jobPanelOnlinePlayerList;
    private TextListboxWidget jobPanelRankList;
    private TextListboxWidget jobPanelJobsList;
    private ButtonWidget jobPanelSave;

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
    private TextListboxWidget adminLicenseTextListbox;

    private Widget medicWidget;
    private TextListboxWidget playerNeedMedicList;
    private MapWidget medicMap;

    private TextWidget countCivil;
    private TextWidget countMedic;
    private TextWidget countCop;
    private TextWidget countArmy;
    private ButtonWidget syncButton;
    private ButtonWidget reloadConfig;

    private XComboBoxWidget toggleViewWidget;

    private ref map<int, string> jobPanelIds = new map<int, string>();
    private int adminPanelId = -1;
    private int medicPanelId = -1;
    private int internalCopPanelId = -1;

    private ref array<ref DZLPlayer> allPlayers;

    private ref map<string, ref array<ref DZLOnlinePlayer>> jobPlayers = new map<string, ref array<ref DZLOnlinePlayer>>();
    private ref map<string, ref array<ref DZLOnlinePlayer>> jobOnlinePlayers = new map<string, ref array<ref DZLOnlinePlayer>>();

    void DZLAlmanacMenu() {
        Construct();
    }
    void ~DZLAlmanacMenu() {
        Destruct();
    }

    override Widget Init() {
        layoutPath = "DayZLifeClient/layout/Almanac/DZL_Almanac.layout";
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

        jobPanelWidget = creator.GetWidget("job_panel");
        jobPanelOnlinePlayerList = creator.GetTextListboxWidget("playerlist_JobPanel");
        jobPanelJobsList = creator.GetTextListboxWidget("jobListbox");
        jobPanelRankList = creator.GetTextListboxWidget("job_RankList");
        jobPanelSave = creator.GetButtonWidget("saveButton_JobPanel");

        escapedWidget = creator.GetWidget("escaped_panel");
        escapedPlayers = creator.GetTextListboxWidget("escaped_TextListbox");
        escapedPlayerPreview = creator.GetPlayerPreview("escaped_PlayerPreview");

        playerOpenTicketsWidget = creator.GetWidget("playerOpenTicketsWidget");
        playerOpenTicketsList = creator.GetTextListboxWidget("playerOpenTicketsList");

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
        countArmy = creator.GetTextWidget("countArmy");

        syncButton = creator.GetButtonWidget("sync_Button");
        reloadConfig = creator.GetButtonWidget("reloadConfig");

        return layoutRoot;
    }

    override void OnShow() {
        super.OnShow();
        string ident = player.GetPlayerId();

        array<string>jobs = config.jobConfig.paycheck.jobNames;
        foreach(string job: jobs) {
            if(!config.adminIds.HasAccess(job, ident)) continue;

            GetGame().RPCSingleParam(player, DZL_RPC.ALL_PLAYER_ONLINE_PLAYERS, new Param1<string>(job), true);
            toggleViewWidget.AddItem("#manage #" + job);
            jobPanelIds.Set(toggleViewWidget.GetNumItems() - 1, job);

        }

        if(player.GetDZLPlayer().IsActiveJob(DAY_Z_LIFE_JOB_MEDIC)) {
            toggleViewWidget.AddItem("#emergencies");
            GetGame().RPCSingleParam(player, DZL_RPC.GET_EMERGENCY_CALLS, null, true);
            medicPanelId = toggleViewWidget.GetNumItems() - 1;
        }

        if(config.adminIds.HasAccess(DAY_Z_LIFE_ACCESS_PLAYERS, ident)) {
            toggleViewWidget.AddItem("#admin_Panel");
            GetGame().RPCSingleParam(null, DZL_RPC.GET_ALL_PLAYERS, null, true);
            adminPanelId = toggleViewWidget.GetNumItems() - 1;
        }

        GetGame().RPCSingleParam(null, DZL_RPC.GET_ESCAPED_PLAYERS, null, true);
        if(player.GetDZLPlayer().IsActiveJob(DAY_Z_LIFE_JOB_COP)) {
            toggleViewWidget.AddItem("#cop_panel");
            GetGame().RPCSingleParam(null, DZL_RPC.GET_OPEN_TICKET_PLAYERS, null, true);
            internalCopPanelId = toggleViewWidget.GetNumItems() - 1;
        }

        workzoneWidget.Show(true);

        array<ref DZLWorkZone> workZones = config.jobConfig.workZones.workZones;
        DZLLicenceCraftingCollection licences = config.licenceConfig.licenceCollection;

        int index;
        workingZoneList.ClearItems();
        foreach(DZLWorkZone zone: workZones) {
            index = workingZoneList.AddItem(zone.zoneDisplayName, zone, 0);
            workingZoneList.SetItem(index, zone.damagePerHarvestItem.ToString(), zone, 1);
        }

        licenceList.ClearItems();
        foreach(DZLCraftLicence licence: licences.collection) {
            licenceList.AddItem(licence.name, licence, 0);
        }
    }

    override bool OnDoubleClick(Widget w, int x, int y, int button) {
        if(w == jobPanelOnlinePlayerList) {
            DZLDisplayHelper.MoveDZLOnlinePlayerFromListWidgetToListWidget(jobPanelOnlinePlayerList, jobPanelJobsList, selectedJob);
        } else if(w == jobPanelJobsList) {
            DZLDisplayHelper.MoveDZLOnlinePlayerFromListWidgetToListWidget(jobPanelJobsList, jobPanelOnlinePlayerList, DAY_Z_LIFE_JOB_CIVIL);
        }

        return false;
    }

    override bool OnClick(Widget w, int x, int y, int button) {
        if(super.OnClick(w, x, y, button)) return true;

        string name;
        int index;

        if(w == jobPanelRankList) {
            DZLDisplayHelper.ChangeRankFromPlayer(jobPanelRankList, jobPanelJobsList);
        } else if(w == reloadConfig) {
            GetGame().RPCSingleParam(null, DZL_RPC.RELOAD_CONFIG, null, true);
            GetGame().GetUIManager().HideScriptedMenu(this);
        } else if(w == jobPanelJobsList) {
            DZLDisplayHelper.LoadDZLOnlinePlayerAndFillRankListWidget(jobPanelJobsList, jobPanelRankList, selectedJob);
        } else if(w == workingZoneList) {
            index = workingZoneList.GetSelectedRow();

            if(index == -1) return true;

            DZLWorkZone zoneWZL
            workingZoneList.GetItemData(index, 0, zoneWZL);

            if(!zoneWZL) return true;

            if(!zoneWZL.showNotOnMapInAlmanac) {
                DZLDisplayHelper.UpdateMap(workingZoneMap, zoneWZL.position);
            } else {
                workingZoneMap.ClearUserMarks();
            }
            workingZoneMap.Show(!zoneWZL.showNotOnMapInAlmanac);

            workingZoneToolsList.ClearItems();
            workzoneYieldList.ClearItems();

            string itemUpdatePreview = "";

            foreach(DZLHarvestItemToolRelation relation: zoneWZL.harvestItemToolRelation) {
                foreach(string itemThatNeededForHarvest: relation.itemsThatNeededForHarvest) {
                    map<string, DZLHarvestItemToolRelation> mapRelation = new map<string, DZLHarvestItemToolRelation>();
                    mapRelation.Set(itemThatNeededForHarvest, relation);
                    name = DZLDisplayHelper.GetItemDisplayName(itemThatNeededForHarvest);

                    if(itemUpdatePreview == "") {
                        itemUpdatePreview = itemThatNeededForHarvest;
                    }

                    workingZoneToolsList.AddItem(name, mapRelation, 0);
                }
            }

            if(itemThatNeededForHarvest) {
                workingZoneToolsList.SelectRow(0);

                UpdaterPreview(itemThatNeededForHarvest, workzoneToolPreview, workZobeToolPreviewItem);
            }

            ResetPreview(workZobeYieldPreviewItem);

            return true;

        } else if(w == workingZoneToolsList) {
            index = workingZoneToolsList.GetSelectedRow();

            if(index == -1) return true;

            map<string, DZLHarvestItemToolRelation> mapRelationTool;
            workingZoneToolsList.GetItemData(index, 0, mapRelationTool);

            if(!mapRelationTool) return true;

            DZLHarvestItemToolRelation relationTool = mapRelationTool.GetElement(0);
            string itemName = mapRelationTool.GetKey(0);

            workzoneYieldList.ClearItems();

            foreach(string itemThatCanHarvest: relationTool.itemsThatCanHarvest) {
                name = DZLDisplayHelper.GetItemDisplayName(itemThatCanHarvest);
                array<string> data = new array<string>;
                data.Insert(itemThatCanHarvest);
                workzoneYieldList.AddItem(name, data, 0);
            }

            if(workzoneYieldList.GetNumItems() > 0) {
                workzoneYieldList.SelectRow(0);
                UpdaterPreviewListBox(workzoneYieldList, workzoneYieldPreview, workZobeYieldPreviewItem);
            }

            UpdaterPreview(itemName, workzoneToolPreview, workZobeToolPreviewItem);

            return true;
        } else if(w == workzoneYieldList) {
            UpdaterPreviewListBox(workzoneYieldList, workzoneYieldPreview, workZobeYieldPreviewItem);

            return true;
        } else if(w == licenceCraftItemList) {
            UpdaterPreviewListBoxCraftItem(licenceCraftItemList, licenceHarvestPreview, licenceHaverestPreviewItem);

            return true;
        } else if(w == licenceList) {
            index = licenceList.GetSelectedRow();

            if(index == -1) return true;

            DZLCraftLicence licence;
            licenceList.GetItemData(index, 0, licence);

            if(!licence) return true;

            if(!licence.showNotOnMapInAlmanac) {
                DZLDisplayHelper.UpdateMap(licenceMap, licence.position);
            } else {
                licenceMap.ClearUserMarks();
            }
            licenceMap.Show(!licence.showNotOnMapInAlmanac);

            name = "#no_tool_required";

            foreach(DZLLicenceToolItem licenceTool: licence.toolItems.collection) {
                if(name != "#no_tool_required") {
                    name += ", ";
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

            if(licenceCraftItemList.GetNumItems() > 0) {
                licenceCraftItemList.SelectRow(0);
                UpdaterPreviewListBoxCraftItem(licenceCraftItemList, licenceHarvestPreview, licenceHaverestPreviewItem);
            }

            return true;
        } else if(w == toggleViewWidget) {
            int item = toggleViewWidget.GetCurrentItem();

            workzoneWidget.Show(0 == item);
            licenceWidget.Show(1 == item);
            escapedWidget.Show(2 == item);
            adminPanelWidget.Show(adminPanelId == item);
            medicWidget.Show(medicPanelId == item);
            playerOpenTicketsWidget.Show(internalCopPanelId == item);

            jobPanelWidget.Show(false);
            if(jobPanelIds.Get(item)) {
                selectedJob = jobPanelIds.Get(item);
                jobPanelWidget.Show(true);

                jobPanelOnlinePlayerList.ClearItems();

                array<ref DZLOnlinePlayer> onlinePlayers = jobOnlinePlayers.Get(selectedJob);
                foreach(DZLOnlinePlayer onlinePlayer: onlinePlayers) {
                    jobPanelOnlinePlayerList.AddItem(onlinePlayer.name, onlinePlayer, 0);
                }

                array<ref DZLOnlinePlayer> jobPlayersList = jobPlayers.Get(selectedJob);
                jobPanelJobsList.ClearItems();
                foreach(DZLOnlinePlayer jobPlayer: jobPlayersList) {
                    int jobPlayerIndex = jobPanelJobsList.AddItem(jobPlayer.name, jobPlayer, 0);
                    jobPanelJobsList.SetItem(jobPlayerIndex, jobPlayer.rank, jobPlayer, 1);
                }

// jobPanelRankList.ClearItems();
// array<ref DZLPaycheck> paychecks = config.jobConfig.paycheck.GetPaycheckByJob(selectedJob);
// foreach(DZLPaycheck paycheck: paychecks) {
// jobPanelRankList.AddItem(paycheck.rank, paycheck, 0);
// }
            }
        } else if(w == jobPanelSave) {
            if(!config.adminIds.HasAccess(selectedJob, player.GetPlayerId())) return true;
            GetGame().RPCSingleParam(null, DZL_RPC.ALL_PLAYER_UPDATE_JOB_PLAYERS, new Param2<string, ref array<DZLOnlinePlayer>> (selectedJob, DZLDisplayHelper.GetPlayerIdsAndRanksFromList(jobPanelJobsList)), true);
        } else if(w == escapedPlayers) {
            int posEscaped = escapedPlayers.GetSelectedRow();
            if(posEscaped == -1) {
                return true;
            }

            DayZPlayer escaped;
            escapedPlayers.GetItemData(posEscaped, 0, escaped);

            if(escaped) {
                escapedPlayerPreview.SetPlayer(escaped);
            }

            return true;
        } else if(w == adminDeletePlayerButton) {
            if(!config.adminIds.HasAccess(DAY_Z_LIFE_ACCESS_PLAYERS, player.GetPlayerId())) return true;
            DZLPlayer _dzlPlayer = DZLDisplayHelper.GetDZLPlayerFromList(adminPlayers);

            if(_dzlPlayer) {
                GetGame().RPCSingleParam(null, DZL_RPC.DELETE_PLAYER, new Param1<string>(_dzlPlayer.dayZPlayerId), true);
            } else {
                player.DisplayMessage("#no_player_selected");
            }
        } else if(w == adminAddMoneyToPlayerButton) {
            if(!config.adminIds.HasAccess(DAY_Z_LIFE_ACCESS_PLAYERS, player.GetPlayerId())) return true;
            DZLPlayer __dzlPlayer = DZLDisplayHelper.GetDZLPlayerFromList(adminPlayers);

            if(__dzlPlayer) {
                int deposit = adminAddMoneyToPlayerInput.GetText().ToInt();
                GetGame().RPCSingleParam(null, DZL_RPC.MONEY_TRANSFER_ADMIN, new Param3<string, int, bool>(__dzlPlayer.dayZPlayerId, deposit, false), true);
            } else {
                player.DisplayMessage("#no_player_selected");
            }
        } else if(w == adminAddMoneyToPlayerButtonBank) {
            if(!config.adminIds.HasAccess(DAY_Z_LIFE_ACCESS_PLAYERS, player.GetPlayerId())) return true;
            DZLPlayer ___dzlPlayer = DZLDisplayHelper.GetDZLPlayerFromList(adminPlayers);

            if(___dzlPlayer) {
                int depositBank = adminAddMoneyToPlayerInput.GetText().ToInt();
                GetGame().RPCSingleParam(null, DZL_RPC.MONEY_TRANSFER_ADMIN, new Param3<string, int, bool>(___dzlPlayer.dayZPlayerId, depositBank, true), true);
            } else {
                player.DisplayMessage("#no_player_selected");
            }
        } else if(w == adminPlayers) {
            if(!config.adminIds.HasAccess(DAY_Z_LIFE_ACCESS_PLAYERS, player.GetPlayerId())) return true;
            DZLPlayer selectedAdminPlayer = DZLDisplayHelper.GetDZLPlayerFromList(adminPlayers);

            if(selectedAdminPlayer) {
                adminPlayerId.SetText(selectedAdminPlayer.dayZPlayerId);
                adminMoneyCash.SetText(selectedAdminPlayer.GetMoney().ToString());
                adminMoneyBank.SetText(selectedAdminPlayer.GetBankMoney().ToString());
                adminJob.SetText(selectedAdminPlayer.GetActiveJob());
                adminArrestTime.SetText(selectedAdminPlayer.arrestTimeInMinutes.ToString());
                adminCanCop.SetText(selectedAdminPlayer.IsActiveJob(DAY_Z_LIFE_JOB_COP).ToString());
                adminLicenseTextListbox.ClearItems();
                TStringArray licenceIds = selectedAdminPlayer.licenceIds;

                if(licenceIds.Count() > 0) {
                    array<ref DZLCraftLicence> licences = DZLConfig.Get().licenceConfig.licenceCollection.collection;
                    foreach(DZLCraftLicence configLicence: licences) {
                        foreach(string licenceId: licenceIds) {
                            if(licenceId == configLicence.GetId()) {
                                adminLicenseTextListbox.AddItem(configLicence.name, configLicence, 0);
                            }
                        }
                    }
                }

            } else {
                player.DisplayMessage("#no_player_selected");
            }
        } else if(w == syncButton) {
            GetGame().RPCSingleParam(player, DZL_RPC.PLAYER_SERVER_RESET_AT_PLAYER_BASE, null, true);
            player.DisplayMessage("#player_was_manuel_synced");
            syncButton.Show(false);
        } else if(w == adminSearchPlayer) {
            DZLDisplayHelper.SearchOnlinePlayersSingleWiget(adminSearchPlayerInput.GetText(), adminPlayers, allPlayers);
        } else if(w == playerNeedMedicList) {
            int indexNeedHelp = playerNeedMedicList.GetSelectedRow();
            if(-1 != indexNeedHelp) {
                DZLOnlinePlayer emergencyPlayer;
                playerNeedMedicList.GetItemData(indexNeedHelp, 0, emergencyPlayer);
                if(emergencyPlayer) {
                    DZLDisplayHelper.UpdateMap(medicMap, emergencyPlayer.position);
                }

            }
        }

        return false;
    }

    override void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DZL_RPC.ALL_PLAYER_ONLINE_PLAYERS_RESPONSE) {
            Param3<string, ref array<ref DZLOnlinePlayer>, ref array<ref DZLOnlinePlayer>> paramCopPlayers;
            if(ctx.Read(paramCopPlayers)) {
                jobOnlinePlayers.Set(paramCopPlayers.param1, paramCopPlayers.param2);
                jobPlayers.Set(paramCopPlayers.param1, paramCopPlayers.param3);
            }
        } else if(rpc_type == DZL_RPC.GET_ALL_PLAYERS_RESPONSE) {
            autoptr Param1<ref array<ref DZLPlayer>> paramAllPlayers;
            if(ctx.Read(paramAllPlayers)) {
                adminPlayers.ClearItems();

                allPlayers = paramAllPlayers.param1;

                foreach(DZLPlayer _player: allPlayers) {
                    if(_player) {
                        int indexRow = adminPlayers.AddItem(_player.playerName, _player, 0);
                        adminPlayers.SetItem(indexRow, _player.lastLoginDate.ToDateString(), _player, 1);
                    }
                }
            }
        } else if(rpc_type == DZL_RPC.GET_ESCAPED_PLAYERS_RESPONSE) {
            autoptr Param5<ref array<ref DZLEscapedPlayer>, int, int, int, int> paramEscaped;
            if(ctx.Read(paramEscaped)) {
                countCop.SetText(paramEscaped.param2.ToString());
                countMedic.SetText(paramEscaped.param3.ToString());
                countCivil.SetText(paramEscaped.param4.ToString());
                countArmy.SetText(paramEscaped.param5.ToString());

                escapedPlayers.ClearItems();

                array<ref DZLEscapedPlayer> escapedPlayersParam = paramEscaped.param1;

                foreach(DZLEscapedPlayer escapedPlayer: escapedPlayersParam) {
                    int indexOfRow = escapedPlayers.AddItem(escapedPlayer.name, escapedPlayer.player, 0);
                    escapedPlayers.SetItem(indexOfRow, escapedPlayer.arrestReason, escapedPlayer.player, 1);
                    if(player.GetDZLPlayer().IsActiveJob(DAY_Z_LIFE_JOB_COP)) {
                        escapedPlayers.SetItem(indexOfRow, escapedPlayer.arrestTime.ToString(), escapedPlayer.player, 2);
                    } else {
                        escapedPlayers.SetItem(indexOfRow, "#only_for_cops", escapedPlayer.player, 2);
                    }

                }
            }
        } else if(rpc_type == DZL_RPC.GET_OPEN_TICKET_PLAYERS_RESPONSE) {
            autoptr Param1<ref array<ref DZLOpenTicketPlayer>> paramUnpaidTickets;
            if(ctx.Read(paramUnpaidTickets)) {
                playerOpenTicketsList.ClearItems();

                array<ref DZLOpenTicketPlayer> openTicketPlayersParam = paramUnpaidTickets.param1;

                foreach(DZLOpenTicketPlayer openTicketPlayer: openTicketPlayersParam) {
                    int indexOfRowUnpaid = playerOpenTicketsList.AddItem(openTicketPlayer.name, openTicketPlayer, 0);
                    playerOpenTicketsList.SetItem(indexOfRowUnpaid, openTicketPlayer.countOfTickets.ToString(), openTicketPlayer, 1);
                    playerOpenTicketsList.SetItem(indexOfRowUnpaid, openTicketPlayer.valueOfTickets.ToString(), openTicketPlayer, 2);
                }
            }
        } else if(rpc_type == DZL_RPC.GET_EMERGENCY_CALLS_RESPONSE) {
            autoptr Param1<ref array<ref DZLOnlinePlayer>> paramEmergencies;
            if(ctx.Read(paramEmergencies)) {
                playerNeedMedicList.ClearItems();
                array<ref DZLOnlinePlayer> emergencies = paramEmergencies.param1;

                foreach(DZLOnlinePlayer emergency: emergencies) {
                    playerNeedMedicList.AddItem(emergency.name, emergency, 0);
                }
            }
        }
    }

    private void UpdaterPreview(string itemType, ItemPreviewWidget preview, EntityAI previewItem) {
        if(itemType) {
            EntityAI currentItem = preview.GetItem();

            if(currentItem && currentItem.GetType() == itemType) return;

            if(previewItem) {
                GetGame().ObjectDelete(previewItem);
            }

            previewItem = EntityAI.Cast(GetGame().CreateObject(itemType, "0 0 0", true, false, false));

            preview.SetItem(previewItem);
            preview.SetModelPosition(Vector(0, 0, 0.5));
        }
    }

    private void UpdaterPreviewListBox(TextListboxWidget widget, ItemPreviewWidget preview, EntityAI previewItem) {
        int pos = widget.GetSelectedRow();
        if(pos == -1) {
            return;
        }
        array<string> itemType;
        widget.GetItemData(pos, 0, itemType);

        UpdaterPreview(itemType.Get(0), preview, previewItem);
    }

    private void UpdaterPreviewListBoxCraftItem(TextListboxWidget widget, ItemPreviewWidget preview, EntityAI previewItem) {
        int pos = widget.GetSelectedRow();
        if(pos == -1) {
            return;
        }
        DZLLicenceCraftItem itemType;
        widget.GetItemData(pos, 0, itemType);

        UpdaterPreview(itemType.type, preview, previewItem);
    }

    private void ResetPreview(EntityAI previewItem) {
        if(previewItem) {
            GetGame().ObjectDelete(previewItem);
        }
    }

}
