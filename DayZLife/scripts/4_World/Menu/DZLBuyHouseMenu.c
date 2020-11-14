class DZLBuyHouseMenu : DZLBaseHouseMenu
{
	private MapWidget mapWidget;

	void DZLBuyHouseMenu(){
	    layoutPath = "DayZLife/layout/Housing/Housing.layout";
        Construct();
	}
	
	void ~DZLBuyHouseMenu(){
        Destruct();
	}

	override Widget Init(){
        super.Init();
		mapWidget = creator.GetMapWidget("Map");

	    return layoutRoot;
    }

	override void OnShow() {
	    if (actualHouseDef) {
	        super.OnShow();

	        priceBuyTextWidget.SetText(actualHouseDef.buyPrice.ToString());
            priceSellTextWidget.SetText(actualHouseDef.sellPrice.ToString());
            storageTextWidget.SetText(actualHouseDef.GetMaxStorage().ToString());
			vector mapPos;
			float scale;

			preview.UpdatePreview(actualHouseDef.houseType);
			
			if(player && !player.GetLastMapInfo(scale, mapPos)) {
                mapPos = GetGame().GetCurrentCameraPosition();
                scale = 0.1;
			}

			mapWidget.SetScale(scale);
			mapWidget.SetMapPos(mapPos);
			mapWidget.AddUserMark(target.GetPosition(), "", ARGB(255,0,255,0), "set:dayz_gui image:cartridge_pistol");
        }
	}
	
	override bool OnClick(Widget w, int x, int y, int button) {
		if(super.OnClick(w, x, y, button)) return true;
	
		switch(w){
            case buyButton:
                if (actualHouseDef) {
                    if (dzlPlayer.HasEnoughMoney(actualHouseDef.buyPrice)) {
                        Param2<PlayerBase, ref Building> paramBuyHouse = new Param2<PlayerBase, ref Building>(PlayerBaseHelper.GetPlayer(), target);
                        GetGame().RPCSingleParam(paramBuyHouse.param1, DAY_Z_LIFE_OPEN_BUY_BUILDING, paramBuyHouse, true);
                    } else {
                        player.DisplayMessage("#error_not_enough_money");
                    }
				} else {
				    player.DisplayMessage("#error_please_reopen_menu");
				}
                return true;
            case sellButton:
                if (house && house.HasOwner() && house.IsOwner(PlayerBaseHelper.GetPlayer())) {
                    Param2<PlayerBase, ref Building> paramSellHouse = new Param2<PlayerBase, ref Building>(PlayerBaseHelper.GetPlayer(), target);
                    GetGame().RPCSingleParam(paramSellHouse.param1, DAY_Z_LIFE_OPEN_SELL_BUILDING, paramSellHouse, true);
                }
                return true;
            default:
                break;
		}
		return false;
	}

	override void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
	    super.HandleEventsDZL(sender, target, rpc_type, ctx);
        if (rpc_type == DAY_Z_LIFE_OPEN_BUY_BUILDING_RESPONSE || rpc_type == DAY_Z_LIFE_OPEN_SELL_BUILDING_RESPONSE) {
            autoptr Param2<ref DZLBuilding, string> paramBuyHouse;
            if (ctx.Read(paramBuyHouse)){
				house = paramBuyHouse.param1;
				UpdateGUI(paramBuyHouse.param2);
	        }
        }
    }
	
	override void UpdateGUI(string message = "") {
	    super.UpdateGUI(message);
		if (house && house.HasOwner() && house.IsOwner(PlayerBaseHelper.GetPlayer())) {
			sellButton.Show(true);
			buyButton.Show(false);
		} else if (house && house.HasOwner() && !house.IsOwner(PlayerBaseHelper.GetPlayer())) {
			sellButton.Show(false);
			buyButton.Show(false);
			player.DisplayMessage("#building_has_already_an_owner");
		} else if (house && !house.HasOwner()) {
			sellButton.Show(false);
			buyButton.Show(true);
		} else if (!house) {
			sellButton.Show(false);
			buyButton.Show(false);
		}
	}

}