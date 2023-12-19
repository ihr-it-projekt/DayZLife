class DZLPreviewWindow extends Managed {
    private ItemPreviewWidget widget;
    private MultilineTextWidget description;
    private EntityAI previewItem;

    void DZLPreviewWindow(ItemPreviewWidget widget, MultilineTextWidget description = null) {
        this.widget = widget;
        this.description = description;
    }

    bool UpdatePreview(string type) {
        Object itemObject = GetGame().CreateObject(type, "0 0 0", true);

        previewItem = EntityAI.Cast(itemObject);

        if (!previewItem) {
            widget.Show(false);
            if (description)description.Show(false);
            return false;
        }

        Update(previewItem);

        return true;
    }

    private void Update(EntityAI previewItem) {
        widget.SetItem(previewItem);
        widget.SetModelPosition(Vector(0,0,0.5));

        widget.Show(true);
        if (description) description.Show(true);
    }
}
