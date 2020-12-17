class DZLLoadOutMenu: DZLBaseMenu
{
	private ButtonWidget equipButton;
	private TextListboxWidget loadoutListbox;
	private XComboBoxWidget loadoutComboBox;
	private DZLLoadOutCategory currentCat;
	
	private array<ref DZLLoadOutCategory> categories;
	
    void DZLLoadOutMenu() {
        layoutPath = "DayZLife/layout/LoadoutMenu/LoadoutMenu.layout";
        Construct();
    }

    void ~DZLLoadOutMenu() {
        Destruct();
    }

    override void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {

    }

    override Widget Init() {
        super.Init();
		
		if (config){
			equipButton = creator.GetButtonWidget("equipButton");
			loadoutListbox = creator.GetTextListboxWidget("loadoutListbox");
			
			loadoutComboBox = creator.GetXComboBoxWidget("loadoutComboBox");
			
			categories = DZLConfig.Get().jobConfig.loadOutCategories;
			
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
}
