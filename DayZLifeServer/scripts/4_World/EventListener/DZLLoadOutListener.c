class DZLLoadOutListener : DZLBaseEventListener {

    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DZL_RPC.LOAD_OUT) {
            autoptr Param1<string> paramLoadOut;
            if (ctx.Read(paramLoadOut)) {
                PlayerBase player = PlayerBase.Cast(target);
                DZLPlayer dzlPlayer = player.GetDZLPlayer();
                string categoryName = paramLoadOut.param1;

                string job = dzlPlayer.GetActiveJob();
                if (DAY_Z_LIFE_JOB_CIVIL == job) {
                    DZLSendMessage(sender, "#error_category_not_found");
                    return;
                }

                DZLLoadOuts loadOut = DZLConfig.Get().jobConfig.GetLoadOuts(job);
                SearchLoadOutAndEquip(categoryName, loadOut.loadOutCategories, sender, player);
            }
        }
    }

    private bool SearchLoadOutAndEquip(string categoryName, array<ref DZLLoadOutCategory> categories, PlayerIdentity sender, PlayerBase player) {
        foreach (DZLLoadOutCategory category : categories) {
            if (categoryName == category.name) {
                DZLLogLoadOut(sender.GetId(), categoryName);
                player.RemoveAllItems();
                ScheduleItemAddition(player, category.items, 0);
                GetGame().RPCSingleParam(null, DZL_RPC.LOAD_OUT_RESPONSE, null, true, sender);
                return true;
            }
        }
        return false;
    }

    private void ScheduleItemAddition(PlayerBase player, array<ref DZLLoadOutType> items, int index) {
        if (index < items.Count()) {
            Add(player, items[index]);
            // Schedule the next item addition
            DZLSleep(1000 * 60 * 180, this, "ScheduleItemAdditionCallback", new Param3<PlayerBase, array<ref DZLLoadOutType>, int>(player, items, index + 1));
        }
    }

    void ScheduleItemAdditionCallback(PlayerBase player, array<ref DZLLoadOutType> items, int index) {
        ScheduleItemAddition(player, items, index);
    }

    private void Add(PlayerBase player, DZLLoadOutType type) {
        EntityAI item;
        InventoryLocation inventoryLocation = new InventoryLocation;

        if (player.GetInventory().FindFirstFreeLocationForNewEntity(type.type, FindInventoryLocationType.ANY, inventoryLocation)) {
            item = player.GetHumanInventory().CreateInInventory(type.type);
        } else if (!player.GetHumanInventory().GetEntityInHands()) {
            item = player.GetHumanInventory().CreateInHands(type.type);
        }

        if (!item) {
            item = player.SpawnEntityOnGroundPos(type.type, player.GetPosition());
        }

        if (item && type.attachments) {
            AddAttachments(type, item);
        }

        if (item && type.quickBarEntityShortcut != -1) {
            player.SetQuickBarEntityShortcut(item, type.quickBarEntityShortcut, true);
        }
    }

    private void AddAttachments(DZLLoadOutType type, EntityAI item) {
        if (!item) return;

        foreach (DZLLoadOutType attachment : type.attachments) {
            if (item.GetInventory()) {
                EntityAI itemAttachment = item.GetInventory().CreateInInventory(attachment.type);

                if (!itemAttachment) {
                    itemAttachment = item.GetInventory().CreateEntityInCargo(attachment.type);
                    if (!itemAttachment) {
                        itemAttachment = item.GetInventory().CreateAttachment(attachment.type);
                    }
                }

                if (itemAttachment && attachment.attachments) {
                    AddAttachments(attachment, itemAttachment);
                }
            }
        }
    }

    void DZLSleep(int milliseconds, Class callbackClass, string callbackMethod, Param param = null) {
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(callbackClass, callbackMethod, milliseconds, false, param);
    }
}
