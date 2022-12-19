class TBLOLoadOutMenu: TBLOBaseMenu
{
	private ButtonWidget equipButton;
	private TextListboxWidget loadoutListbox;
	private XComboBoxWidget loadoutComboBox;
	private TBLOLoadOutCategory currentCat;
	private ItemPreviewWidget preview;

	private EntityAI previewItem;
	private ref array<ref TBLOLoadOutCategory> categories;
	private int lastSelectedItem;
	
    void TBLOLoadOutMenu() {
        layoutPath = "TBLoadOut/layout/LoadoutMenu/LoadoutMenu.layout";
        Construct();
        categories = new ref array<ref TBLOLoadOutCategory>;
    }

    void ~TBLOLoadOutMenu() {
        if (previewItem){
            GetGame().ObjectDelete(previewItem);
        }
        Destruct();
    }

    override void HandleEventsTBLO(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == TB_LOAD_OUT_RESPONSE) {
            OnHide();
        } else if (rpc_type == TB_LOAD_OUT_CONFIG_TIMEOUT_RESPONSE) {
            autoptr Param1<int> paramLoadOut;
            if (ctx.Read(paramLoadOut)){
                equipButton.SetText(paramLoadOut.param1.ToString() + " #seconds")
            }
        }
    }

    override Widget Init() {
        super.Init();
		
		equipButton = creator.GetButtonWidget("equipButton");
		loadoutListbox = creator.GetTextListboxWidget("loadoutListbox");
		loadoutComboBox = creator.GetXComboBoxWidget("loadoutComboBox");
		preview = creator.GetItemPreviewWidget("itemPreview");

		return layoutRoot;
    }

    void AddCategory(ref TBLOLoadOutCategory category) {
        this.categories.Insert(category);
    }

    override void OnShow() {
        if (categories.Count() == 0) {
            OnHide();
            return;
        }

        foreach(TBLOLoadOutCategory category: categories) {
            loadoutComboBox.AddItem(category.name);
        }

        currentCat = categories.Get(0);
        UpdateCategory();
        super.OnShow();
    }

    override void Update(float timeslice) {
        super.Update(timeslice);
        int currentSelectedItem = loadoutListbox.GetSelectedRow();

        if (currentSelectedItem != lastSelectedItem) {
            UpdaterPreviewType(loadoutListbox);
            lastSelectedItem = currentSelectedItem;
        }
    }
	
	override bool OnClick(Widget w, int x, int y, int button){
		if(super.OnClick(w, x, y, button)) return true;
		switch(w){
            case equipButton:
                GetGame().RPCSingleParam(player, TB_LOAD_OUT, new Param1<string>(currentCat.name), true);
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
			foreach(TBLOLoadOutType type: currentCat.items) {
				if (type.displayName == "") {
					type.displayName = TBLODisplayHelper.GetItemDisplayName(type.type);
				}
				
				loadoutListbox.AddItem(type.displayName, type, 0);
			}
		}
	}

	private void UpdaterPreviewType(TextListboxWidget widget) {
        int pos = widget.GetSelectedRow();
        if (pos == -1) {
            return;
        }
        TBLOLoadOutType itemType;
        widget.GetItemData(pos, 0, itemType);

        if (itemType) {
            EntityAI currentItem = preview.GetItem();

            if (currentItem && currentItem.GetType() == itemType.type) return;

            if (previewItem) {
                GetGame().ObjectDelete(previewItem);
            }

            previewItem = EntityAI.Cast(GetGame().CreateObject(itemType.type, "0 0 0", true, false, false));

            preview.SetItem(previewItem);
            preview.SetModelPosition(Vector(0,0,0.5));
        }
    }
}
