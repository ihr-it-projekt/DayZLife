class DZLLoadOutListener
{
    ref DZLJobConfig config;

    void DZLLoadOutListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
        config = DZLConfig.Get().jobConfig;
    }

    void ~DZLLoadOutListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
		if (!DZLLicenceCheck.Get().HasActiveLicence(sender)) return;
        if (rpc_type == DAY_Z_LIFE_LOAD_OUT) {
            autoptr Param1<string> paramLoadOut;
            if (ctx.Read(paramLoadOut)){
				PlayerBase player = PlayerBase.Cast(target);
                DZLPlayer dzlPlayer = player.GetDZLPlayer();
				string categoryName = paramLoadOut.param1;

                if ((dzlPlayer.IsActiveAsCop() && !SearchLoadOutAndEquip(categoryName, config.loadOutsCops.loadOutCategories, sender, player)) || (dzlPlayer.IsActiveAsMedic() && !SearchLoadOutAndEquip(categoryName, config.loadOutsMedics.loadOutCategories, sender, player))) {
					DZLSendMessage(sender, "#error_category_not_found");
				}
            }
        }
    }

    private bool SearchLoadOutAndEquip(string categoryName, array<ref DZLLoadOutCategory> categories, PlayerIdentity sender, PlayerBase player) {
        foreach(DZLLoadOutCategory category: categories) {
            if (categoryName == category.name) {
                DZLLogLoadOut(sender.GetId(), categoryName);
                player.RemoveAllItems();
                foreach(DZLLoadOutType type: category.items) {
                    Add(player, type);
                }
                GetGame().RPCSingleParam(null, DAY_Z_LIFE_LOAD_OUT_RESPONSE, null, true, sender);
                return true;;
            }
        }

        return false;
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
		
        foreach(DZLLoadOutType attachment: type.attachments) {
            if (item.GetInventory()) {
                EntityAI itemAttachment = item.GetInventory().CreateInInventory(attachment.type);

                if (!itemAttachment) {
                    itemAttachment = item.GetInventory().CreateEntityInCargo(attachment.type);
					if (!itemAttachment) {
						itemAttachment = item.GetInventory().CreateAttachment(attachment.type);
					}
                }

				if(itemAttachment && attachment.attachments) {
					AddAttachments(attachment, itemAttachment);
				}
            }
        }
    }
}
