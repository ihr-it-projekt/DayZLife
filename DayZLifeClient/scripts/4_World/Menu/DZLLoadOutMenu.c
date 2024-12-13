class DZLLoadOutMenu: DZLBaseMenu {
    private ButtonWidget equipButton;
    private TextListboxWidget loadoutListbox;
    private XComboBoxWidget loadoutComboBox;
    private DZLLoadOutCategory currentCat;
    private ItemPreviewWidget preview;

    private EntityAI previewItem;
    private array<ref DZLLoadOutCategory> categories;
    private int lastSelectedItem;

    void DZLLoadOutMenu() {
        layoutPath = "DayZLifeClient/layout/LoadoutMenu/LoadoutMenu.layout";
    }

    void ~DZLLoadOutMenu() {
        if(previewItem) {
            g_Game.ObjectDelete(previewItem);
        }
    }

    override void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DZL_RPC.LOAD_OUT_RESPONSE) {
            OnHide();
        }
    }

    override Widget Init() {
        super.Init();

        if(config) {
            equipButton = creator.GetButtonWidget("equipButton");
            loadoutListbox = creator.GetTextListboxWidget("loadoutListbox");

            loadoutComboBox = creator.GetXComboBoxWidget("loadoutComboBox");

            preview = creator.GetItemPreviewWidget("itemPreview");
        }

        return layoutRoot;
    }

    void SetCategories(array<ref DZLLoadOutCategory> _categories) {
        this.categories = _categories;
    }

    override void OnShow() {
        if(!categories) {
            OnHide();
            return;
        }

        foreach(DZLLoadOutCategory category: categories) {
            loadoutComboBox.AddItem(category.name);
        }

        currentCat = categories.Get(0);
        UpdateCategory();
        super.OnShow();
    }

    override void Update(float timeslice) {
        super.Update(timeslice);
        int currentSelectedItem = loadoutListbox.GetSelectedRow();

        if(currentSelectedItem != lastSelectedItem) {
            UpdaterPreviewType(loadoutListbox);
            lastSelectedItem = currentSelectedItem;
        }
    }

    override bool OnClick(Widget w, int x, int y, int button) {
        if(super.OnClick(w, x, y, button)) return true;
        switch(w) {
            case equipButton:
                g_Game.RPCSingleParam(player, DZL_RPC.LOAD_OUT, new Param1<string>(currentCat.name), true);
                return true;
            case loadoutComboBox:
                int index = loadoutComboBox.GetCurrentItem();

                currentCat = categories.Get(index);
                UpdateCategory();
                return true;
            default:
                break;
        }

        return false;
    }

    private void UpdateCategory() {
        if(currentCat) {
            loadoutListbox.ClearItems();
            foreach(DZLLoadOutType type: currentCat.items) {
                if(type.displayName == "") {
                    type.displayName = DZLDisplayHelper.GetItemDisplayName(type.type);
                }

                loadoutListbox.AddItem(type.displayName, type, 0);
            }
        }
    }

    private void UpdaterPreviewType(TextListboxWidget widget) {
        int pos = widget.GetSelectedRow();
        if(pos == -1) {
            return;
        }
        DZLLoadOutType itemType;
        widget.GetItemData(pos, 0, itemType);

        if(itemType) {
            EntityAI currentItem = preview.GetItem();

            if(currentItem && currentItem.GetType() == itemType.type) return;

            if(previewItem) {
                g_Game.ObjectDelete(previewItem);
            }

            previewItem = EntityAI.Cast(g_Game.CreateObject(itemType.type, "0 0 0", true, false, false));

            preview.SetItem(previewItem);
            preview.SetModelPosition(Vector(0, 0, 0.5));
        }
    }
}
