class DZLLoadOutListener: DZLBaseEventListener {
    // A map to store the last access time of each player
    private ref map<string, float> playerLoadoutAccessTimes;

    void DZLLoadOutListener() {
        playerLoadoutAccessTimes = new map<string, float>();
    }

    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DZL_RPC.LOAD_OUT) {
            autoptr Param1<string> paramLoadOut;
            if(ctx.Read(paramLoadOut)) {
                PlayerBase player = PlayerBase.Cast(target);
                DZLPlayer dzlPlayer = player.GetDZLPlayer();
                string categoryName = paramLoadOut.param1;

                string job = dzlPlayer.GetActiveJob();
                if(DAY_Z_LIFE_JOB_CIVIL == job) {
                    DZLSendMessage(sender, "#error_category_not_found");
                    return;
                }

                if (IsCooldownActive(player)) {
                    DZLSendMessage(sender, "You need to wait one hour to pickup Loadout again");
                    return;
                }

                DZLLoadOuts loadOut = DZLConfig.Get().jobConfig.GetLoadOuts(job);
                if (SearchLoadOutAndEquip(categoryName, loadOut.loadOutCategories, sender, player)) {
                    UpdatePlayerAccessTime(player);
                }
            }
        }
    }

    private bool SearchLoadOutAndEquip(string categoryName, array<ref DZLLoadOutCategory> categories, PlayerIdentity sender, PlayerBase player) {
        foreach(DZLLoadOutCategory category: categories) {
            if(categoryName == category.name) {
                DZLLogLoadOut(sender.GetId(), categoryName);
                player.RemoveAllItems();
                foreach(DZLLoadOutType type: category.items) {
                    Add(player, type);
                }
                GetGame().RPCSingleParam(null, DZL_RPC.LOAD_OUT_RESPONSE, null, true, sender);
                return true;
            }
        }

        return false;
    }

    private void Add(PlayerBase player, DZLLoadOutType type) {
        EntityAI item;
        InventoryLocation inventoryLocation = new InventoryLocation;

        if(player.GetInventory().FindFirstFreeLocationForNewEntity(type.type, FindInventoryLocationType.ANY, inventoryLocation)) {
            item = player.GetHumanInventory().CreateInInventory(type.type);
        } else if(!player.GetHumanInventory().GetEntityInHands()) {
            item = player.GetHumanInventory().CreateInHands(type.type);
        }

        if(!item) {
            item = player.SpawnEntityOnGroundPos(type.type, player.GetPosition());
        }

        if(item && type.attachments) {
            AddAttachments(type, item);
        }

        if(item && type.quickBarEntityShortcut != -1) {
            player.SetQuickBarEntityShortcut(item, type.quickBarEntityShortcut, true);
        }
    }

    private void AddAttachments(DZLLoadOutType type, EntityAI item) {
        if(!item) return;

        foreach(DZLLoadOutType attachment: type.attachments) {
            if(item.GetInventory()) {
                EntityAI itemAttachment = item.GetInventory().CreateInInventory(attachment.type);

                if(!itemAttachment) {
                    itemAttachment = item.GetInventory().CreateEntityInCargo(attachment.type);
                    if(!itemAttachment) {
                        itemAttachment = item.GetInventory().CreateAttachment(attachment.type);
                    }
                }

                if(itemAttachment && attachment.attachments) {
                    AddAttachments(attachment, itemAttachment);
                }
            }
        }
    }

    private bool IsCooldownActive(PlayerBase player) {
        string playerId = player.GetIdentity().GetId();
        float currentTime = GetGame().GetTime() / 1000.0; // Get the current time in seconds
        if (playerLoadoutAccessTimes.Contains(playerId)) {
            float lastAccessTime = playerLoadoutAccessTimes.Get(playerId);
            // Check if 1 hour (3600 seconds) has passed
            if (currentTime - lastAccessTime < 3600) {
                return true;
            }
        }
        return false;
    }

    private void UpdatePlayerAccessTime(PlayerBase player) {
        string playerId = player.GetIdentity().GetId();
        float currentTime = GetGame().GetTime() / 1000.0; // Get the current time in seconds
        playerLoadoutAccessTimes.Set(playerId, currentTime);
    }
}
