class DZLFractionMenu : DZLBaseMenu
{
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

	private ButtonWidget fractionDelete;
	private CheckBoxWidget deleteAccept;

	private ref array<ref DZLFractionMember> fractionMembers;
	private ref array<ref DZLFractionMember> potentialMembers;
	private ref DZLFraction fraction;
	private ref array<ref DZLFractionMember> fractionNotMembers;
	private DZLFractionMember member;

	private TextListboxWidget fractionInvitationList;
	private ButtonWidget acceptInvitation;
	private ButtonWidget fractionLeave;
	private ButtonWidget createFaction;
	private EditBoxWidget fractionNameEdit;

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
		layoutPath = "DayZLife/layout/FractionMenu/DZL_Car.layout";
        super.Init();

        fractionMenuHeadLine = creator.GetTextWidget("fractionMenuHeadLine");
        fractionAccessPanel = creator.GetWidget("fractionAccessPanel");
        fractionAccessPanel.Show(false);
        fractionPanel = creator.GetWidget("fractionPanel");
        fractionPanel.Show(false);

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
		acceptInvitation.Show(false);
		fractionLeave = creator.GetButtonWidget("fractionLeave");
		fractionLeave.Show(false);
		createFaction = creator.GetButtonWidget("createFaction");
		createFaction.Show(false);
		fractionNameEdit = creator.GetEditBoxWidget("fractionNameEdit");
		fractionNameEdit.Show(false);

        myRightsWidget = creator.GetWidget("myRightsWidget");
        myRightsWidget.Show(false);
		displayBankAccessRight = creator.GetCheckBoxWidget("displayBankAccessRight");
		displayBankGetMoneyRight = creator.GetCheckBoxWidget("displayBankGetMoneyRight");
		displayAccessGarageRight = creator.GetCheckBoxWidget("displayAccessGarageRight");

		changRightsButton = creator.GetButtonWidget("fractionChangRightsButton");

		return layoutRoot;
    }

	override void OnShow() {
		super.OnShow();
		
        GetGame().RPCSingleParam(null, DAY_Z_LIFE_GET_FRACTION, null, true);
	}
	
	override bool OnDoubleClick(Widget w, int x, int y, int button) {
		if (w == fractionPanelOnlinePlayerList) {
		    MoveDZLFractionMemberFromListWidgetToListWidget(fractionPanelOnlinePlayerList, fractionPanelPlayerList);
		} else if (w == openInvitations) {
		    MoveDZLFractionMemberFromListWidgetToListWidget(openInvitations, fractionPanelOnlinePlayerList);
		} else if (w == fractionPanelPlayerList) {
		    int pos = fractionPanelPlayerList.GetSelectedRow();
            if (pos == -1) {
                return true;
            }
            DZLFractionMember member;
            fractionPanelPlayerList.GetItemData(pos, 0, member);

		    if (member) {
		        TextListboxWidget targetWidget = openInvitations;
		        if (member.isMember) {
		            targetWidget = fractionPanelOnlinePlayerList;
		        }
                fractionPanelPlayerList.RemoveRow(pos);
                targetWidget.AddItem(member.name, member, 0);
            }
		}
		
		return false;
	}
	
	override bool OnClick(Widget w, int x, int y, int button) {
		if (super.OnClick(w, x, y, button)) return true;
        bool wasDone = false;
		if (w == fractionSaveButton) {
            GetGame().RPCSingleParam(player, DAY_Z_LIFE_GET_UPDATE_FRACTION_MEMBERS, new Param2<ref array<ref DZLFractionMember>, ref array<ref DZLFractionMember>>(DZLDisplayHelper.GetDZLFractionMemberFromList(fractionPanelPlayerList), DZLDisplayHelper.GetDZLFractionMemberFromList(openInvitations)), true);
			fractionSearchInput.SetText("");
			wasDone = true;
		} else if (w == fractionSearchButton) {
			DZLDisplayHelper.SearchFractionMembersSingleWiget(fractionSearchInput.GetText(), fractionPanelOnlinePlayerList, fractionNotMembers);
			wasDone = true;
		} else if (w == fractionMembers) {
            LoadDZLFractionMemberAndFillRightsWidget();
            wasDone = true;
		} else if (w == accessBankAccountCheckbox) {
            if (member) {
                member.canAccessBankAccount = !member.canAccessBankAccount;
            }
            wasDone = true;
		} else if (w == accessBankGetMoneyCheckbox) {
            if (member) {
                member.canGetMoneyFromBankAccount = !member.canGetMoneyFromBankAccount;
            }
            wasDone = true;
		} else if (w == accessFractionGarage) {
            if (member) {
                member.canAccessFractionGarage = !member.canAccessFractionGarage;
            }
            wasDone = true;
		} else if (w == deleteAccept) {
		    fractionDelete.Enable(deleteAccept.IsChecked());
		    wasDone = true;
		} else if (w == fractionDelete && deleteAccept.IsChecked()) {
		    GetGame().RPCSingleParam(player, DAY_Z_LIFE_DELETE_FRACTION, null, true);
		    wasDone = true;
		} else if (w == fractionLeave) {
            GetGame().RPCSingleParam(player, DAY_Z_LIFE_FRACTION_MEMBER_LEAVE, null, true);
		    wasDone = true;
		} else if (w == acceptInvitation) {
		    DZLFractionMember member = GetMarkedMember(fractionInvitationList);

            GetGame().RPCSingleParam(player, DAY_Z_LIFE_FRACTION_MEMBER_JOIN, new Param1<ref DZLFractionMember>(member), true);
		    wasDone = true;
		} else if (w == createFaction) {
		    string fractionName = fractionNameEdit.GetText();

		    if (fractionName && fractionName != "") {
                GetGame().RPCSingleParam(player, DAY_Z_LIFE_FRACTION_CREATE_FRACTION, new Param1<string>(fractionName), true);
		    }
		    wasDone = true;
		}

		return wasDone;
	}

	override void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_GET_FRACTION_RESPONSE_FRACTION_OWNER) {
            autoptr Param2<ref DZLFraction, ref array<ref DZLFractionMember>> paramFractionOwner;
            if (ctx.Read(paramFractionOwner)){
                fraction = paramFractionOwner.param1;
                fractionMembers = fraction.GetMembers();
                potentialMembers = fraction.GetPotentialMembers();
                fractionNotMembers = paramFractionOwner.param2;
                UpdateList();
            }
        } else if (rpc_type == DAY_Z_LIFE_GET_UPDATE_FRACTION_MEMBERS_RESPONSE || rpc_type == DAY_Z_LIFE_FRACTION_MEMBER_LEAVE_RESPONSE || DAY_Z_LIFE_FRACTION_MEMBER_JOIN_RESPONSE) {
           OnHide();
        } else if (rpc_type == DAY_Z_LIFE_GET_FRACTION_RESPONSE_FRACTION_MEMBER) {
            autoptr Param1<ref DZLFractionMember> paramFractionMember;
            if (ctx.Read(paramFractionMember)){
                DZLFractionMember member = paramFractionMember.param1;
                fractionMenuHeadLine.SetText(member.fractionName);
                displayBankAccessRight.SetChecked(member.canAccessBankAccount);
                displayBankGetMoneyRight.SetChecked(member.canGetMoneyFromBankAccount);
                displayAccessGarageRight.SetChecked(member.canAccessFractionGarage);
                myRightsWidget.Show(true);
                fractionPanel.Show(true);
                fractionLeave.Show(true);
            }
        } else if (rpc_type == DAY_Z_LIFE_GET_FRACTION_RESPONSE_NOT_A_FRACTION_MEMBER) {
            autoptr Param1<ref array<ref DZLFractionMember>> paramNotFractionMember;
            if (ctx.Read(paramNotFractionMember)){
                fractionInvitationList.ClearItems();
                foreach(DZLFractionMember potentialMember: paramNotFractionMember.param1) {
                    fractionInvitationList.AddItem(potentialMember.fractionName, potentialMember, 0);
                }

                fractionInvitationList.Show(true);
                acceptInvitation.Show(true);
                fractionNameEdit.Show(true);
                createFaction.Show(true);
                fractionPanel.Show(true);
            }
        }
	}

	private void UpdateList() {
	    fractionAccessPanel.Show(true);
        fractionPanelPlayerList.ClearItems();
        openInvitations.ClearItems();
        fractionPanelOnlinePlayerList.ClearItems();

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
        if (pos == -1) {
            return;
        }
        DZLFractionMember member;
        sourceWidget.GetItemData(pos, 0, member);

        if (member) {
            sourceWidget.RemoveRow(pos);
            targetWidget.AddItem(member.name, member, 0);
        }
    }

    private DZLFractionMember GetMarkedMember(TextListboxWidget sourceWidget) {
        int pos = sourceWidget.GetSelectedRow();
        if (pos == -1) {
            return null;
        }
        DZLFractionMember member;
        sourceWidget.GetItemData(pos, 0, member);
		
		return member;
    }

    private void LoadDZLFractionMemberAndFillRightsWidget() {
        DZLFractionMember member = GetMarkedMember(fractionPanelPlayerList);

        if (member) {
            accessBankAccountCheckbox.SetChecked(member.canAccessBankAccount);
            accessBankGetMoneyCheckbox.SetChecked(member.canGetMoneyFromBankAccount);
            accessFractionGarage.SetChecked(member.canAccessFractionGarage);
        }
    }
}
