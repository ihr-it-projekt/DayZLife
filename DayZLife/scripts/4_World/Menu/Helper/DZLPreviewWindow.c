class DZLPreviewWindow extends Managed
{
    private ItemPreviewWidget widget;
    private MultilineTextWidget description;
    private EntityAI previewItem;

    void DZLPreviewWindow(ItemPreviewWidget widget, MultilineTextWidget description) {
        this.widget = widget;
        this.description = description;
    }

	bool UpdatePreview(string type) {
		Object itemObject = GetGame().CreateObject(type, "0 0 0", true);
		
		previewItem = EntityAI.Cast(itemObject);
		
		if (!previewItem) {
			widget.Show(false);
			description.Show(false);
			return false;
		}
		
		Update(previewItem);
		
		return false;
	}
	
	private void Update(EntityAI previewItem){
		widget.SetItem(previewItem);
		widget.SetModelPosition(Vector(0,0,0.5));

		InventoryItem itemCast = InventoryItem.Cast(previewItem);

//		if (itemCast) {
//			this.description.SetText(item.GetTranslation() + " "+ itemCast.GetTooltip());
//		} else {
//			this.description.SetText("");
//		}
		
		widget.Show(true);
		description.Show(true);
    }
}