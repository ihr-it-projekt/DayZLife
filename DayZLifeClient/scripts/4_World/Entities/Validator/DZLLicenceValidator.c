class DZLLicenceValidator {
    // TODO: check tool und item health
    PlayerBase player;
    DZLCraftLicence licence;

    ref array<string> errors = new array<string>;
    map<string, int> craftItems = new map<string, int>;
    map<string, int> tools = new map<string, int>;

    map<string, ref array<EntityAI>> craftEntities = new map<string, ref array<EntityAI>>;
    map<string, ref array<EntityAI>> toolEntities = new map<string, ref array<EntityAI>>;

    array<EntityAI> items = new array<EntityAI>;

    void DZLLicenceValidator(notnull PlayerBase _player, notnull DZLCraftLicence _licence) {
        this.licence = _licence;
        this.player = _player;

        items = GetPlayerItems();
    }

    string CanUseLicence() {

        foreach(EntityAI item: items) {
            string itemType = item.GetType();
            itemType.ToLower();
            if(IsNeededCraftItem(item, itemType)) continue;

            IsNeededToolItem(item, itemType);
        }
        CheckTools();
        CheckItems();

        string error = "";
        foreach(string err: errors) {
            error += err + " ";
        }

        return error;
    }

    private void CheckItems() {
        // TODO: check item health
        map<string, int> craftMap = licence.craftItems.GetTypeCountMap();
        foreach(string type, int count: craftMap) {
            int countFound = 0;
            if(craftItems.Find(type, countFound)) {
                if(countFound < count) errors.Insert("#missing_craft_item_quantity: " + type + "#needed: " + count + "#found: " + countFound);
                continue;
            }
            errors.Insert("#missing_craft_item: " + type);
        }
    }

    private void CheckTools() {
        // TODO: check tool health
        map<string, int> toolMap = licence.toolItems.GetTypeCountMap();

        foreach(string typeTool, int countTool: toolMap) {
            int countFoundTool = 0;
            if(tools.Find(typeTool, countFoundTool)) {
                if(countFoundTool < countTool) errors.Insert("#missing_tool_quantity: " + typeTool + "#needed: " + countTool + "#found: " + countFoundTool);
                continue;
            }
            errors.Insert("#missing_tool: " + typeTool);
        }
    }

    private float GetQuantity(EntityAI item) {
        if(item.HasQuantity()) {
            return item.GetQuantity();
        }

        return 1.0;
    }

    private bool IsNeededToolItem(EntityAI item, string itemType) {
        foreach(DZLLicenceToolItem toolItem: licence.toolItems.collection) {
            if(IsNeededItem(toolItem, item, itemType)) {
                int countTools = 0;
                if(tools.Find(itemType, countTools)) {
                    tools.Set(itemType, countTools + GetQuantity(item));

                    array<EntityAI> items;
                    toolEntities.Find(itemType, items);
                    items.Insert(item);
                } else {
                    tools.Insert(itemType, quantity);

                    new array<EntityAI> items;
                    items.Insert(item);
                    toolEntities.Insert(itemType, items);
                }
                return true;
            }
        }

        return false;
    }

    private bool IsNeededCraftItem(EntityAI item, string itemType) {
        foreach(DZLLicenceCraftItem craftItem: licence.craftItems.collection) {
            if(IsNeededItem(craftItem, item, itemType)) {
                int countCraft = 0;
                if(craftItems.Find(itemType, countCraft)) {
                    craftItems.Set(itemType, countCraft + GetQuantity(item));

                    array<EntityAI> items;
                    craftEntities.Find(itemType, items);
                    items.Insert(item);
                } else {
                    craftItems.Insert(itemType, quantity);

                    new array<EntityAI> items;
                    items.Insert(item);
                    craftEntities.Insert(itemType, items);
                }
                return true;
            }
        }

        return false;
    }

    private bool IsNeededItem(DZLLicenceCraftItem item, EntityAI itemSearch, string ItemSearchType) {
        if(item.GetLowerCaseType() == ItemSearchType) {
            if(!GetGame().IsServer()) return true;
            if(itemSearch.GetHealth() >= item.health) return true;
        }

        return false;
    }

    void UseLicence(){
        ReduceQuantity(craftItems, craftEntities);
        ReduceQuantity(tools, toolEntities);
    }

    private void ReduceQuantity(map<string, int> searchedItems, map<string, ref array<EntityAI>> entities) {
        foreach(string type, int count: searchedItems) {
            array<EntityAI> items;
            Entities.Find(type, items);
            foreach(EntityAI item: items) {
                if(count <= 0) break;
                int quantity = GetQuantity(item);
                count -= quantity;
                if(count >= 0) {
                    item.Delete();
                    DZLLogCrafting(player.GetPlayerId(), "licence crafting delete resource", type);
                    continue;
                }
                if(count < 0) item.SetQuantity(quantity + count);
            }
        }
    }
}