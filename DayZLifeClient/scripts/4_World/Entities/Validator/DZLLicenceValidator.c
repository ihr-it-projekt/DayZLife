class DZLLicenceValidator {

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
            int quantity = DZLTraderHelper.GetQuantity(item);
            if(IsNeededCraftItem(item, itemType)) continue;

            IsNeededToolItem(item, itemType);
        }
        CheckTools();

        map<string, int> craftMap = licence.craftItems.GetTypeCountMap();
        if(craftItems.Count() >= craftMap.Count() && tools.Count() >= toolMap.Count()) {
            foreach(string type, int count: craftMap) {
                int countFound = 0;
                if(craftItems.Find(type, countFound)) {
                    if(countFound < count) {
                        return "#not_enough_items_to_craft";
                    }
                } else {
                    return "#missing_craft_item";
                }
            }


        } else {
            message = "#has_not_found_all_items_that_is_needed_to_craft";
        }

        return message;
    }

    private void CheckTools() {
        map<string, int> toolMap = licence.toolItems.GetTypeCountMap();

        foreach(string typeTool, int countTool: toolMap) {
            int countFoundTool = 0;
            if(tools.Find(typeTool, countFoundTool)) {
                if(countFoundTool < countTool) errors.Insert("#missing_tool_quantity: " + typeTool + "#needed: " + countTool + "#found: " + countFoundTool);
                continue;
            }
            return errors.Insert("#missing_tool: " + typeTool);
        }
    }

    private bool IsNeededToolItem(EntityAI item, string itemType) {
        foreach(DZLLicenceToolItem toolItem: licence.toolItems.collection) {
            if(IsNeededItem(toolItem, item, itemType)) {
                int countTools = 0;
                if(tools.Find(itemType, countTools)) {
                    tools.Set(itemType, countTools + quantity);

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
                    craftItems.Set(itemType, countCraft + quantity);

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
}