class DZLLicenceMenu : DZLBaseMenu {
    TextListboxWidget playerListbox;

    ButtonWidget buyButton;

    TextListboxWidget licenceListBox;

    EditBoxWidget inputDeposit;

    void DZLLicenceMenu() {
        layoutPath = "DayZLifeClient/layout/Licence/Licence_Menu.layout";
        Construct();
    }

    void ~DZLLicenceMenu() {
        Destruct();
    }

    override void UpdateGUI(string message = "") {
        super.UpdateGUI(message);

        DZLLicenceCraftingCollection licences = config.licenceConfig.licenceCollection;
        licenceListBox.ClearItems();
        foreach(DZLCraftLicence licence: licences.collection) {
            string hasLicenseText = "x";
            if(!dzlPlayer.HasLicense(licence)) {
                hasLicenseText = "";
            }

            int pos = licenceListBox.AddItem(licence.name, licence, 0);
            licenceListBox.SetItem(pos, licence.dependencyLicence, licence, 1);
            licenceListBox.SetItem(pos, licence.price.ToString(), licence, 2);
            licenceListBox.SetItem(pos, hasLicenseText, licence, 3);
        }
    }

    override void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DAY_Z_LIFE_BUY_LICENCE_RESPONSE) {
            autoptr Param1<string> paramGetResponse;
            if(ctx.Read(paramGetResponse)) {
                UpdateGUI(paramGetResponse.param1);
            }
        }
    }

    override Widget Init() {
        super.Init();

        buyButton = creator.GetButtonWidget("Button_Buy");
        buyButton.Show(false);
        licenceListBox = creator.GetTextListboxWidget("Licence_ListBox");

        return layoutRoot;
    }

    override void OnShow() {
        if(config) {
            super.OnShow();
            buyButton.Show(false);

            UpdateGUI();
        } else {
            OnHide();
        }
    }

    override bool OnClick(Widget w, int x, int y, int button) {
        if(super.OnClick(w, x, y, button)) return true;
        switch(w) {
            case buyButton:
                int position = licenceListBox.GetSelectedRow();

                if(-1 == position) return true;
                DZLCraftLicence licence;
                licenceListBox.GetItemData(position, 0, licence);

                if(!licence) return true;

                DZLCraftLicence depLicence;
                if(licence.dependencyLicence) {
                    depLicence = config.licenceConfig.licenceCollection.FindByName(licence.dependencyLicence);
                }

                string message = dzlPlayer.CanBuyLicence(licence, depLicence);

                if(!message) {
                    buyButton.Show(false);
                    GetGame().RPCSingleParam(player, DAY_Z_LIFE_BUY_LICENCE, new Param1<string>(licence.GetId()), true);
                } else {
                    UpdateGUI(message);
                }

                return true;
            case licenceListBox:
                int positionBox = licenceListBox.GetSelectedRow();

                if(-1 == positionBox) return true;
                DZLCraftLicence licenceBox;
                licenceListBox.GetItemData(positionBox, 0, licenceBox);

                if(!licenceBox) {
                    buyButton.Show(false);
                    return true;
                }

                string hasLicenceText;
                licenceListBox.GetItemText(positionBox, 3, hasLicenceText);

                if(hasLicenceText == "x") {
                    buyButton.Show(false);
                    return true;
                }

                buyButton.Show(true);
                return true;
            default:
                break;
        }
        return false;
    }
}
