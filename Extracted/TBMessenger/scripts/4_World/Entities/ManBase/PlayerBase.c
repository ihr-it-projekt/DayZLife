modded class PlayerBase
{
    private ref TBMMessageMenu messageMenu;
    private ref TBMMessageSystemMenu messageSystemMenu;

	private string playerUID;

	string GetPlayerId() {
		if (!playerUID) {
			playerUID = GetIdentity().GetId();
		}
		
		return playerUID;
	}

    override void SetActions(out TInputActionMap InputActionMap) {
        super.SetActions(InputActionMap);

        AddAction(TBMActionGiveNumber, InputActionMap);
    }
	
    void DisplayMessage(string message) {
        GetMessageMenu();
        messageMenu.SetText(message);
        messageMenu.Init();
        messageMenu.Show();
    }

    void UpdatePlayerAtDependencies() {
        if (messageSystemMenu && messageSystemMenu.IsVisible()) {
            messageSystemMenu.UpdatePlayer(this);
        }
    }

    private void InitMenu(TBMBaseMenu menu) {
        menu.SetConfig(GetConfig());
        menu.SetPlayer(this);
    }

	TBMMessageMenu GetMessageMenu() {
		messageMenu = new TBMMessageMenu();
		return messageMenu;
	}

	TBMMessageSystemMenu GetMessageSystemMenu() {
		messageSystemMenu = new TBMMessageSystemMenu();
		InitMenu(messageSystemMenu);
		return messageSystemMenu;
	}

	void RefreshMessageSystem() {
	    if (messageSystemMenu) {
	        messageSystemMenu.RefreshMessageSystem();
	    }
	}

	bool CloseMenu() {
	    bool hasDoAction = false;

		if (messageSystemMenu && messageSystemMenu.IsVisible()) {
		    messageSystemMenu.OnHide();
			hasDoAction = true;
		}
		
		return hasDoAction;
	}

	array<EntityAI> GetPlayerItems() {
        array<EntityAI> itemsArray = new array<EntityAI>;
        GetInventory().EnumerateInventory(InventoryTraversalType.INORDER, itemsArray);

        return itemsArray;
    }

    bool HasInInventory(string type) {
        array<EntityAI> items = GetPlayerItems();
        foreach(EntityAI item: items) {
            if (item.GetType() == type) {
                return true;
            }
        }
		return false;
    }

    array<EntityAI> GetItemsByTypeFromInventory(string type) {
        array<EntityAI> items = GetPlayerItems();
        array<EntityAI> itemsFound = new array<EntityAI>;
        foreach(EntityAI item: items) {
            if (item.GetType() == type) {
                itemsFound.Insert(item);
            }
        }
        return itemsFound;
    }

    TBMConfig GetConfig() {
        if (GetGame().IsServer()) {
            return TBMConfig.Get();
        }
        return TBMPlayerClientDB.Get().GetConfig();
    }

    bool CanOpenMessageMenu() {
        if (IsRestrained()) return false;
        if (IsUnconscious()) return false;
        if (!GetConfig()) return false;
        if (!GetConfig().messageConfig) {
			GetGame().RPCSingleParam(TBMPlayerBaseHelper.GetPlayer(), DAY_Z_LIFE_EVENT_GET_CONFIG, null, true);
            return false;
        }


        if (!GetConfig().messageConfig.mustHavePersonalRadio) return true;

        array<EntityAI> radios = GetItemsByTypeFromInventory("PersonalRadio");

        if (radios.Count() < 1) return false;

        if (!GetConfig().messageConfig.radioMustHaveBattery) return true;

        foreach(EntityAI radio: radios) {
            if (radio.GetInventory()) {
                for(int i = 0; i < radio.GetInventory().AttachmentCount(); i++ ) {
                    EntityAI attachment = radio.GetInventory().GetAttachmentFromIndex(i);
                    if(attachment && attachment.GetType() == "Battery9V") {
						Battery9V itemCast = Battery9V.Cast(attachment);

						if (itemCast && itemCast.GetQuantity() > 0) {
							float energy = itemCast.GetCompEM().GetEnergy();
							
							if (energy > 0) return true;
						}                        
                    }
                }
            }
        }

        return false;
    }

}
