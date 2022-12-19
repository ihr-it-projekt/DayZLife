class TBLOLoadOutListener
{
    ref map<string, ref TBLDate> playerLoadOutAction;
    ref TBLOLoadOuts config;

    void TBLOLoadOutListener() {
        config = TBLOConfig.Get().loadOuts;
        GetDayZGame().Event_OnRPC.Insert(HandleEventsTBLO);
		playerLoadOutAction = new map<string, ref TBLDate>;
    }

    void ~TBLOLoadOutListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsTBLO);
    }

    void HandleEventsTBLO(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == TB_LOAD_OUT) {
            autoptr Param1<string> paramLoadOut;
            if (ctx.Read(paramLoadOut)){
				string senderId = sender.GetId();
				
				TBLDate nextAction = playerLoadOutAction.Get(senderId);
				
				if (nextAction && !nextAction.IsInPast()) {
				    GetGame().RPCSingleParam(null, TB_LOAD_OUT_CONFIG_TIMEOUT_RESPONSE, new Param1<int>(nextAction.GetRemainingSeconds()), true, sender);
				    return
				}

				playerLoadOutAction.Set(senderId, new TBLDate(config.coolDownUsageInSeconds));
				
				PlayerBase player = PlayerBase.Cast(target);
				string categoryName = paramLoadOut.param1;

                SearchLoadOutAndEquip(categoryName, TBLOConfig.Get().loadOuts.loadOutCategories, sender, player);
            }
        }
    }

    private bool SearchLoadOutAndEquip(string categoryName, array<ref TBLOLoadOutCategory> categories, PlayerIdentity sender, PlayerBase player) {
        foreach(TBLOLoadOutCategory category: categories) {
            if (categoryName == category.name) {
                player.RemoveAllItems();
                foreach(TBLOLoadOutType type: category.items) {
                    Add(player, type);
                }
                GetGame().RPCSingleParam(null, TB_LOAD_OUT_RESPONSE, null, true, sender);
                return true;;
            }
        }

        return false;
    }

    private void Add(PlayerBase player, TBLOLoadOutType type) {
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

        if (item) {
            item.SetHealth(Math.RandomIntInclusive(type.minHealth, type.maxHealth));
        }

		if (item && type.attachments) {
			AddAttachments(type, item);
		}
		
        if (item && type.quickBarEntityShortcut != -1) {
            player.SetQuickBarEntityShortcut(item, type.quickBarEntityShortcut, true);
        }
    }

    private void AddAttachments(TBLOLoadOutType type, EntityAI item) {
		if (!item) return;
		
        foreach(TBLOLoadOutType attachment: type.attachments) {
            if (item.GetInventory()) {
                EntityAI itemAttachment = item.GetInventory().CreateInInventory(attachment.type);

                if (!itemAttachment) {
                    itemAttachment = item.GetInventory().CreateEntityInCargo(attachment.type);
					if (!itemAttachment) {
						itemAttachment = item.GetInventory().CreateAttachment(attachment.type);
					}
                }

                if (itemAttachment) {
                    itemAttachment.SetHealth(Math.RandomIntInclusive(type.minHealth, type.maxHealth));
                }

				if(itemAttachment && attachment.attachments) {
					AddAttachments(attachment, itemAttachment);
				}
            }
        }
    }
}
