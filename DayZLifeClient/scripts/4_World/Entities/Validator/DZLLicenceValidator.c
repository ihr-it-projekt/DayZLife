class DZLLicenceValidator {
    // TODO: check tool und item health
    PlayerBase player;
    DZLCraftLicence licence;

    ref array<string> errors = new array<string>;

    ref map<string, ref DZLFoundLicenseCraftItems> craftEntities = new map<string, ref DZLFoundLicenseCraftItems>;
    ref map<string, ref DZLFoundLicenseCraftItems> toolEntities = new map<string, ref DZLFoundLicenseCraftItems>;

    ref array<EntityAI> items = new array<EntityAI>;

    void DZLLicenceValidator(notnull PlayerBase _player, notnull DZLCraftLicence _licence) {
        this.licence = _licence;
        this.player = _player;

        items = player.GetPlayerItems();

        craftEntities = licence.craftItems.GetLicenceCraftItems();
        toolEntities = licence.toolItems.GetLicenceCraftItems();
    }

    string CanUseLicence() {
        foreach(EntityAI item: items) {
            if(AddCraftItem(item)) continue;
            AddToolItem(item);
        }

        CheckTools();
        CheckItems();

        string error = "";
        foreach(string err: errors) {
            error += err + " ";
        }

        return error;
    }

    private bool AddCraftItem(EntityAI item) {
        foreach(string type, ref DZLFoundLicenseCraftItems cItems: craftEntities) {
            if(cItems.AddItem(item)) return true;
        }

        return false;
    }

    private bool AddToolItem(EntityAI item) {
        foreach(string type, ref DZLFoundLicenseCraftItems tItems: toolEntities) {
            if(tItems.AddItem(item)) return true;
        }

        return false;
    }

    private void CheckItems() {
        foreach(string index, ref DZLFoundLicenseCraftItems item: craftEntities) {
            if(item.CanUsed()) continue;
            errors.Insert("#missing_craft_item_quantity: " + item.GetErrorMessage());
        }
    }

    private void CheckTools() {
        foreach(string index, ref DZLFoundLicenseCraftItems item: toolEntities) {
            if(item.CanUsed()) continue;
            errors.Insert("#missing_craft_item_quantity: " + item.GetErrorMessage());
        }
    }

    private void UseItems() {
        foreach(string index, ref DZLFoundLicenseCraftItems item: craftEntities) {
            item.Use(player.GetIdentity());
        }
    }

    private void UseTools() {
        foreach(string index, ref DZLFoundLicenseCraftItems item: toolEntities) {
            item.Use(player.GetIdentity());
        }
    }

    void UseLicence() {
        UseItems();
        UseTools();
    }

}