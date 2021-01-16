class DZLLoadOutMenu: DZLBaseMenu
{
	private ButtonWidget equipButton;
	private TextListboxWidget loadoutListbox;
	private XComboBoxWidget loadoutComboBox;
	private DZLLoadOutCategory currentCat;
	private ItemPreviewWidget preview;

	private EntityAI previewItem;
	private array<ref DZLLoadOutCategory> categories;
	private int lastSelectedItem;
	
    void DZLLoadOutMenu() {
        layoutPath = "DayZLife/layout/LoadoutMenu/LoadoutMenu.layout";
        Construct();
    }

    void ~DZLLoadOutMenu() {
        if (previewItem){
            GetGame().ObjectDelete(previewItem);
        }
        Destruct();
    }

    override void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_LOAD_OUT_RESPONSE) {
            OnHide();
        }
    }

    override Widget Init() {
        super.Init();
		
		if (config){
			equipButton = creator.GetButtonWidget("equipButton");
			loadoutListbox = creator.GetTextListboxWidget("loadoutListbox");
			
			loadoutComboBox = creator.GetXComboBoxWidget("loadoutComboBox");
			
			preview = creator.GetItemPreviewWidget("itemPreview");
			
			categories = player.config.jobConfig.loadOutsCops.loadOutCategories;
			
			foreach(DZLLoadOutCategory category: categories) {
				loadoutComboBox.AddItem(category.name);
			}
			
			currentCat = categories.Get(0);
			UpdateCategory();
		}
		
		return layoutRoot;
    }

    override void OnShow() {
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
                GetGame().RPCSingleParam(player, DAY_Z_LIFE_LOAD_OUT, new Param1<string>(currentCat.name), true);
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
				if (type.displayName == "") {
					type.displayName = DZLDisplayHelper.GetItemDisplayName(type.type);
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
        DZLLoadOutType itemType;
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
