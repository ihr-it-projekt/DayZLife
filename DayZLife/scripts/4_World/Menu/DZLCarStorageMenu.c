class DZLCarStorageMenu: DZLBaseMenu
{
	private TextListboxWidget carToStoreList;
	private TextListboxWidget carInStoreList;
	private ButtonWidget inStoreButton;
	private ButtonWidget outStoreButton;
	private DZLStoragePosition position;
	private CheckBoxWidget hasInsuranceWidget;
	private TextWidget insuranceText;

    void DZLCarStorageMenu() {
        Construct();
        GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_GET_CAR_DATA_FROM_STORAGE, null, true);
    }

    void ~DZLCarStorageMenu() {
        Destruct();
    }

    override Widget Init() {
        layoutPath = "DayZLife/layout/Grage/DZLGarage.layout";
        super.Init();
		
		carToStoreList = creator.GetTextListboxWidget("tostoreTextListbox");
		carInStoreList = creator.GetTextListboxWidget("isstoredTextListbox");
		
		inStoreButton = creator.GetButtonWidget("storeinButton");
		outStoreButton = creator.GetButtonWidget("storeoutButton");
		
		hasInsuranceWidget = creator.GetCheckBoxWidget("insuranceCheckBox");
		insuranceText = creator.GetTextWidget("insurranceTextBox");

        return layoutRoot;
    }
	
	override void UpdateGUI(string message = "") {
		super.UpdateGUI(message);
		carToStoreList.ClearItems();
		array<string> carTypes = player.config.carConfig.carTypesToStore;
		foreach(string carType: carTypes) {
			CarScript playerCar = DZLObjectFinder.GetCar(position.spawnPositionOfVehicles, position.spawnOrientationOfVehicles, carType, player.GetPlayerId(), true);
			if (playerCar && !playerCar.isSold) {
				string name = "";
            	GetGame().ObjectGetDisplayName(playerCar, name);
	            carToStoreList.AddItem(name, playerCar, 0);
	        }
		}
	}

    override void OnShow() {
        super.OnShow();
        insuranceText.SetText("#out_parking_with_insurance (" + config.carConfig.carInsurancePrice + ")");
       
		if (!position) {
		    position = player.config.carConfig.GetStorageByPosition(player.GetPosition());
		}

		if (!position) {
		    OnHide();
		    LogMessageDZL("No Storage position found.");
		    return;
		}

		UpdateGUI();
	}

    override bool OnClick(Widget w, int x, int y, int button) {
		if (w == inStoreButton) {
			int index = carToStoreList.GetSelectedRow();
			
			if (-1 == index) {
				player.DisplayMessage("#no_car_selected");
				return true;
			}
			
			CarScript car = null;
			carToStoreList.GetItemData(index, 0, car);
			
			if (car) {
			    bool carIsEmpty = true;
                for (int seat = 0; seat < car.CrewSize(); seat++){
                    if (car.CrewMember(seat)) {
                        player.DisplayMessage("#car_is_not_empty");
                        return true;
                    }
                }

                CargoBase cargo = car.GetInventory().GetCargo();
                if (!player.config.carConfig.canStoreCarsWithGoods && cargo.GetItemCount() > 0) {
                    player.DisplayMessage("#car_is_not_empty");
                    return true;
                }

				GetGame().RPCSingleParam(car, DAY_Z_LIFE_EVENT_STORE_CAR, new Param1<vector>(player.GetPosition()), true);
			    car.isSold = true;
			}
		} else if (w == outStoreButton) {
			int indexOut = carInStoreList.GetSelectedRow();

            if (-1 == indexOut) {
                player.DisplayMessage("#no_car_selected");
                return true;
            }

            DZLCarStoreItem carOut = null;
			carInStoreList.GetItemData(indexOut, 0, carOut);

            if (carOut) {
                array<Object> excludedObjects = new array<Object>;
                array<Object> nearbyObjects = new array<Object>;
				
                if (GetGame().IsBoxColliding(position.spawnPositionOfVehicles, position.spawnOrientationOfVehicles, "2 2 0", excludedObjects, nearbyObjects)){
                    player.DisplayMessage("#car_spwan_place_is_blocked");
                    return true;
                }
				
				if(hasInsuranceWidget.IsChecked() && !dzlPlayer.HasEnoughMoney(config.carConfig.carInsurancePrice)) {
					player.DisplayMessage("#error_not_enough_money");
				}

                GetGame().RPCSingleParam(player, DAY_Z_LIFE_EVENT_GET_CAR_FROM_STORAGE, new Param2<string, bool>(carOut.id, hasInsuranceWidget.IsChecked()), true);
            }
		} else if (w == closeButton){
		    OnHide();
            return true;
		}

		return true;
    }
	
    override void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_EVENT_GET_CAR_DATA_FROM_STORAGE_RESPONSE) {
           autoptr Param1<ref DZLCarStorage> paramGetCarDataResponse;
           if (ctx.Read(paramGetCarDataResponse)){
                DZLCarStorage carStorage = paramGetCarDataResponse.param1;
				array<ref DZLCarStoreItem> items = carStorage.items;
				
				carInStoreList.ClearItems();
				
				foreach(DZLCarStoreItem item: items) {
					carInStoreList.AddItem(GetItemDisplayName(item.type), item, 0);
				}
           }
           UpdateGUI();
        }
    }

    string GetItemDisplayName(string itemClassname){
        string cfg;
        string displayName;

        cfg = CFG_VEHICLESPATH + " " + itemClassname + " displayName";

        GetGame().ConfigGetText(cfg, displayName);
        

        if (displayName == "") {
            displayName = itemClassname;
        }

        return displayName;
    }
	
}
