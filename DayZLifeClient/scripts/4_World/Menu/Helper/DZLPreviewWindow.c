class DZLPreviewWindow extends Managed {
    private ItemPreviewWidget widget;
    private MultilineTextWidget description;
    private EntityAI previewItem;

    void DZLPreviewWindow(ItemPreviewWidget _widget, MultilineTextWidget _description = null) {
        this.widget = _widget;
        this.description = _description;
    }

    bool UpdatePreview(string type) {
        Object itemObject = GetGame().CreateObject(type, "0 0 0", true);

        previewItem = EntityAI.Cast(itemObject);

        if(!previewItem) {
            widget.Show(false);
            if(description)description.Show(false);
            return false;
        }

        Update(previewItem);

        return true;
    }

    private void Update(EntityAI _previewItem) {
        widget.SetItem(_previewItem);
        widget.SetModelPosition(Vector(0, 0, 0.5));

        widget.Show(true);
        if(description) description.Show(true);
    }
}
