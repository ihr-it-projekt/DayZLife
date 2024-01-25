class DZLFractionMenu : DZLBaseMenu {
    private Widget fractionAccessPanel;
    private Widget fractionPanel;

    private TextWidget fractionMenuHeadLine;
    private TextListboxWidget fractionPanelOnlinePlayerList;
    private TextListboxWidget fractionPanelPlayerList;
    private TextListboxWidget openInvitations;
    private ButtonWidget changRightsButton;
    private ButtonWidget fractionSaveButton;
    private ButtonWidget fractionSearchButton;
    private EditBoxWidget fractionSearchInput;
    private CheckBoxWidget accessBankAccountCheckbox;
    private CheckBoxWidget accessBankGetMoneyCheckbox;
    private CheckBoxWidget accessFractionGarage;
    private Widget wrapperBankRight;
    private Widget wrapperBankMoneyRight;
    private Widget wrapperGarageRight;
    private Widget wrapperFractionPlayer;
    private TextWidget fractionPlayer;

    private ButtonWidget fractionDelete;
    private CheckBoxWidget deleteAccept;

    private ref array<ref DZLFractionMember> fractionMembers;
    private ref array<ref DZLFractionMember> potentialMembers;
    private ref DZLFraction fraction;
    private ref array<ref DZLFractionMember> fractionNotMembers;
    private DZLFractionMember selectedMember;

    private TextListboxWidget fractionInvitationList;
    private ButtonWidget acceptInvitation;
    private ButtonWidget fractionLeave;
    private ButtonWidget createFaction;
    private EditBoxWidget fractionNameEdit;

    private Widget wrapperName;
    private Widget wrapperCreate;
    private Widget wrapperLeave;
    private Widget wrapperInvite;

    private Widget myRightsWidget;
    private CheckBoxWidget displayBankAccessRight;
    private CheckBoxWidget displayBankGetMoneyRight;
    private CheckBoxWidget displayAccessGarageRight;


    void DZLFractionMenu() {
        Construct();
    }
    void ~DZLFractionMenu() {
        Destruct();
    }

    override Widget Init() {
        layoutPath = "DayZLifeClient/layout/FractionMenu/DZL_FractionMenu.layout";
        super.Init();

        fractionMenuHeadLine = creator.GetTextWidget("fractionMenuHeadLine");
        fractionAccessPanel = creator.GetWidget("fractionAccessPanel");
        fractionAccessPanel.Show(false);
        fractionPanel = creator.GetWidget("fractionPanel");
        fractionPanel.Show(false);
        wrapperBankRight = creator.GetWidget("wrapperBankRight");
        wrapperBankRight.Show(false);
        wrapperBankMoneyRight = creator.GetWidget("wrapperBankMoneyRight");
        wrapperBankMoneyRight.Show(false);
        wrapperGarageRight = creator.GetWidget("wrapperGarageRight");
        wrapperGarageRight.Show(false);
        wrapperFractionPlayer = creator.GetWidget("wrapperFractionPlayer");
        wrapperFractionPlayer.Show(false);
        fractionPlayer = creator.GetTextWidget("fractionPlayer");

        fractionPanelOnlinePlayerList = creator.GetTextListboxWidget("playerList");
        fractionPanelPlayerList = creator.GetTextListboxWidget("fractionMembers");
        openInvitations = creator.GetTextListboxWidget("openInvitations");
        fractionSaveButton = creator.GetButtonWidget("fractionSafeMembers");
        fractionSearchButton = creator.GetButtonWidget("searchButton");
        fractionSearchInput = creator.GetEditBoxWidget("search_input");
        accessBankAccountCheckbox = creator.GetCheckBoxWidget("accessBankAccountCheckbox");
        accessBankGetMoneyCheckbox = creator.GetCheckBoxWidget("accessBankGetMoneyCheckbox");
        accessFractionGarage = creator.GetCheckBoxWidget("accessFractionGarage");

        fractionDelete = creator.GetButtonWidget("fractionDelete");
        deleteAccept = creator.GetCheckBoxWidget("deleteAccept");

        fractionInvitationList = creator.GetTextListboxWidget("fractionInvitationList");
        fractionInvitationList.Show(false);
        acceptInvitation = creator.GetButtonWidget("acceptInvitation");
        fractionLeave = creator.GetButtonWidget("fractionLeave");
        createFaction = creator.GetButtonWidget("createFaction");
        fractionNameEdit = creator.GetEditBoxWidget("fractionNameEdit");

        wrapperName = creator.GetWidget("wrapperName");
        wrapperName.Show(false);
        wrapperCreate = creator.GetWidget("wrapperCreate");
        wrapperCreate.Show(false);
        wrapperLeave = creator.GetWidget("wrapperLeave");
        wrapperLeave.Show(false);
        wrapperInvite = creator.GetWidget("wrapperInvite");
        wrapperInvite.Show(false);

        myRightsWidget = creator.GetWidget("myRightsWidget");
        myRightsWidget.Show(false);
        displayBankAccessRight = creator.GetCheckBoxWidget("displayBankAccessRight");
        displayBankGetMoneyRight = creator.GetCheckBoxWidget("displayBankGetMoneyRight");
        displayAccessGarageRight = creator.GetCheckBoxWidget("displayAccessGarageRight");

        changRightsButton = creator.GetButtonWidget("fractionChangRightsButton");

        GetGame().RPCSingleParam(null, DAY_Z_LIFE_GET_FRACTION, null, true);

        return layoutRoot;
    }


    override bool OnDoubleClick(Widget w, int x, int y, int button) {
        if(w == fractionPanelPlayerList) {
            MoveDZLFractionMemberFromListWidgetToListWidget(fractionPanelPlayerList, fractionPanelOnlinePlayerList);
            ResetSelectedMember();
        } else if(w == openInvitations) {
            MoveDZLFractionMemberFromListWidgetToListWidget(openInvitations, fractionPanelOnlinePlayerList);
            ResetSelectedMember();
        } else if(w == fractionPanelOnlinePlayerList) {
            int pos = fractionPanelOnlinePlayerList.GetSelectedRow();
            if(pos == -1) {
                return true;
            }
            DZLFractionMember member;
            fractionPanelOnlinePlayerList.GetItemData(pos, 0, member);

            if(member) {
                TextListboxWidget targetWidget = openInvitations;
                if(member.isMember) {
                    targetWidget = fractionPanelOnlinePlayerList;
                }
                fractionPanelOnlinePlayerList.RemoveRow(pos);
                targetWidget.AddItem(member.name, member, 0);
            }
            ResetSelectedMember();
        }

        return false;
    }

    override bool OnClick(Widget w, int x, int y, int button) {
        if(super.OnClick(w, x, y, button)) return true;
        bool wasDone = false;
        if(w == fractionSaveButton) {
            fractionMembers = DZLDisplayHelper.GetDZLFractionMemberFromList(fractionPanelPlayerList);
            potentialMembers = DZLDisplayHelper.GetDZLFractionMemberFromList(openInvitations);
            GetGame().RPCSingleParam(player, DAY_Z_LIFE_GET_UPDATE_FRACTION_MEMBERS, new Param2<ref array<ref DZLFractionMember>, ref array<ref DZLFractionMember>>(fractionMembers, potentialMembers), true);
            fractionSearchInput.SetText("");
            wasDone = true;
            ResetSelectedMember();
        } else if(w == fractionSearchButton) {
            DZLDisplayHelper.SearchFractionMembersSingleWiget(fractionSearchInput.GetText(), fractionPanelOnlinePlayerList, fractionNotMembers);
            wasDone = true;
            ResetSelectedMember();
        } else if(w == fractionPanelPlayerList) {
            LoadDZLFractionMemberAndFillRightsWidget();
            wasDone = true;
        } else if(w == accessBankAccountCheckbox) {
            if(selectedMember) {
                selectedMember.canAccessBankAccount = !selectedMember.canAccessBankAccount;
            }
            wasDone = true;
        } else if(w == accessBankGetMoneyCheckbox) {
            if(selectedMember) {
                selectedMember.canGetMoneyFromBankAccount = !selectedMember.canGetMoneyFromBankAccount;
            }
            wasDone = true;
        } else if(w == accessFractionGarage) {
            if(selectedMember) {
                selectedMember.canAccessFractionGarage = !selectedMember.canAccessFractionGarage;
            }
            wasDone = true;
        } else if(w == deleteAccept) {
            ResetSelectedMember();
            fractionDelete.Enable(deleteAccept.IsChecked());
            wasDone = true;
        } else if(w == fractionDelete && deleteAccept.IsChecked()) {
            ResetSelectedMember();
            GetGame().RPCSingleParam(player, DAY_Z_LIFE_DELETE_FRACTION, null, true);
            wasDone = true;
        } else if(w == fractionLeave) {
            GetGame().RPCSingleParam(player, DAY_Z_LIFE_FRACTION_MEMBER_LEAVE, null, true);
            wasDone = true;
        } else if(w == acceptInvitation) {
            DZLFractionMember member = GetMarkedMember(fractionInvitationList);

            GetGame().RPCSingleParam(player, DAY_Z_LIFE_FRACTION_MEMBER_JOIN, new Param1<ref DZLFractionMember>(member), true);
            wasDone = true;
        } else if(w == createFaction) {
            string fractionName = fractionNameEdit.GetText();

            if(fractionName && fractionName != "") {
                GetGame().RPCSingleParam(player, DAY_Z_LIFE_FRACTION_CREATE_FRACTION, new Param1<string>(fractionName), true);
            }
            wasDone = true;
        }

        return wasDone;
    }

    override void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DAY_Z_LIFE_GET_FRACTION_RESPONSE_FRACTION_OWNER) {
            autoptr Param2<ref DZLFraction, ref array<ref DZLFractionMember>> paramFractionOwner;
            if(ctx.Read(paramFractionOwner)) {
                fraction = paramFractionOwner.param1;
                fractionMembers = fraction.GetMembers();
                potentialMembers = fraction.GetPotentialMembers();
                fractionNotMembers = paramFractionOwner.param2;
                UpdateList();
            }
        } else if(rpc_type == DAY_Z_LIFE_GET_UPDATE_FRACTION_MEMBERS_RESPONSE) {
            OnHide();
        } else if(rpc_type == DAY_Z_LIFE_FRACTION_MEMBER_LEAVE_RESPONSE) {
            OnHide();
        } else if(rpc_type == DAY_Z_LIFE_FRACTION_MEMBER_JOIN_RESPONSE) {
            OnHide();
        } else if(rpc_type == DAY_Z_LIFE_DELETE_FRACTION_RESPONSE) {
            OnHide();
        } else if(rpc_type == DAY_Z_LIFE_GET_FRACTION_RESPONSE_FRACTION_MEMBER) {
            autoptr Param1<ref DZLFractionMember> paramFractionMember;
            if(ctx.Read(paramFractionMember)) {
                DZLFractionMember member = paramFractionMember.param1;
                fractionMenuHeadLine.SetText(member.fractionName);
                displayBankAccessRight.SetChecked(member.canAccessBankAccount);
                displayBankGetMoneyRight.SetChecked(member.canGetMoneyFromBankAccount);
                displayAccessGarageRight.SetChecked(member.canAccessFractionGarage);
                myRightsWidget.Show(true);
                fractionPanel.Show(true);
                wrapperLeave.Show(true);
            }
        } else if(rpc_type == DAY_Z_LIFE_GET_FRACTION_RESPONSE_NOT_A_FRACTION_MEMBER) {
            autoptr Param1<ref array<ref DZLFractionMember>> paramNotFractionMember;
            if(ctx.Read(paramNotFractionMember)) {
                fractionInvitationList.ClearItems();
                foreach(DZLFractionMember potentialMember: paramNotFractionMember.param1) {
                    fractionInvitationList.AddItem(potentialMember.fractionName, potentialMember, 0);
                }

                fractionInvitationList.Show(true);
                wrapperInvite.Show(true);
                wrapperName.Show(true);
                wrapperCreate.Show(true);
                fractionPanel.Show(true);
            }
        }
    }

    private void UpdateList() {
        fractionAccessPanel.Show(true);
        fractionPanelPlayerList.ClearItems();
        openInvitations.ClearItems();
        fractionPanelOnlinePlayerList.ClearItems();
        ResetSelectedMember();

        foreach(DZLFractionMember fractionNotMember: fractionNotMembers) {
            fractionPanelOnlinePlayerList.AddItem(fractionNotMember.name, fractionNotMember, 0);
        }

        foreach(DZLFractionMember potentialMember: potentialMembers) {
            openInvitations.AddItem(potentialMember.name, potentialMember, 0);
        }

        foreach(DZLFractionMember fractionMember: fractionMembers) {
            fractionPanelPlayerList.AddItem(fractionMember.name, fractionMember, 0);
        }
    }

    private void MoveDZLFractionMemberFromListWidgetToListWidget(TextListboxWidget sourceWidget, TextListboxWidget targetWidget) {
        int pos = sourceWidget.GetSelectedRow();
        if(pos == -1) {
            return;
        }
        DZLFractionMember member;
        sourceWidget.GetItemData(pos, 0, member);

        if(member && !member.IsFractionBoss()) {
            sourceWidget.RemoveRow(pos);
            targetWidget.AddItem(member.name, member, 0);
        }
    }

    private DZLFractionMember GetMarkedMember(TextListboxWidget sourceWidget) {
        int pos = sourceWidget.GetSelectedRow();
        if(pos == -1) {
            return null;
        }
        DZLFractionMember member;
        sourceWidget.GetItemData(pos, 0, member);

        return member;
    }

    private void LoadDZLFractionMemberAndFillRightsWidget() {
        selectedMember = GetMarkedMember(fractionPanelPlayerList);

        if(selectedMember) {
            fractionPlayer.SetText(selectedMember.name);
            accessBankAccountCheckbox.SetChecked(selectedMember.canAccessBankAccount);
            accessBankGetMoneyCheckbox.SetChecked(selectedMember.canGetMoneyFromBankAccount);
            accessFractionGarage.SetChecked(selectedMember.canAccessFractionGarage);
            wrapperFractionPlayer.Show(true);
            wrapperBankRight.Show(true);
            wrapperBankMoneyRight.Show(true);
            wrapperGarageRight.Show(true);
        }
    }

    private void ResetSelectedMember() {
        wrapperFractionPlayer.Show(false);
        wrapperBankRight.Show(false);
        wrapperBankMoneyRight.Show(false);
        wrapperGarageRight.Show(false);
        selectedMember = null;
    }
}
