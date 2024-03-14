class DZLCarStorageMenu: DZLBaseMenu {
    private TextListboxWidget carToStoreList;
    private TextListboxWidget carInStoreList;
    private ButtonWidget inStoreButton;
    private ButtonWidget storeInFractionButton;
    private ButtonWidget outStoreButton;
    private DZLStoragePosition position;
    private CheckBoxWidget hasInsuranceWidget;
    private TextWidget insuranceText;
    private Widget storeInFractionButtonWrapper;

    void DZLCarStorageMenu() {
        Construct();
        GetGame().RPCSingleParam(null, DZL_RPC.EVENT_GET_CAR_DATA_FROM_STORAGE, null, true);
    }

    void ~DZLCarStorageMenu() {
        Destruct();
    }

    override Widget Init() {
        layoutPath = "DayZLifeClient/layout/Grage/DZLGarage.layout";
        super.Init();

        carToStoreList = creator.GetTextListboxWidget("tostoreTextListbox");
        carInStoreList = creator.GetTextListboxWidget("isstoredTextListbox");

        inStoreButton = creator.GetButtonWidget("storeinButton");
        storeInFractionButton = creator.GetButtonWidget("storeinFractionButton");
        outStoreButton = creator.GetButtonWidget("storeoutButton");

        hasInsuranceWidget = creator.GetCheckBoxWidget("insuranceCheckBox");
        insuranceText = creator.GetTextWidget("insurranceTextBox");

        storeInFractionButtonWrapper = creator.GetWidget("storeInFractionButtonWrapper");

        return layoutRoot;
    }

    override void UpdateGUI(string message = "") {
        super.UpdateGUI(message);
        storeInFractionButtonWrapper.Show(dzlPlayer.HasFractionRightCanAccessFractionGarage());
        carToStoreList.ClearItems();
        array<string> carTypes = player.GetConfig().carConfig.carTypesToStore;
        foreach(string carType: carTypes) {
            CarScript playerCar = DZLObjectFinder.GetCar(position.spawnPositionOfVehicles, position.spawnOrientationOfVehicles, carType, dzlPlayer, false);
            if(playerCar && !playerCar.isSold) {
                string name = "";
                GetGame().ObjectGetDisplayName(playerCar, name);
                name += " (" + playerCar.ownerName + ")";
                carToStoreList.AddItem(name, playerCar, 0);
            }
        }
    }

    override void OnShow() {
        super.OnShow();
        insuranceText.SetText("#out_parking_with_insurance (" + config.carConfig.carInsurancePrice + " $)");

        if(!position) {
            position = player.GetConfig().carConfig.GetStorageByPosition(player.GetPosition());
        }

        if(!position) {
            OnHide();
            LogMessageDZL("No Storage position found.");
            return;
        }

        UpdateGUI();
    }

    override bool OnClick(Widget w, int x, int y, int button) {
        if(w == inStoreButton || w == storeInFractionButton) {
            if(w == storeInFractionButton && !dzlPlayer.HasFractionRightCanAccessFractionGarage()) return true;

            int index = carToStoreList.GetSelectedRow();

            if(-1 == index) {
                player.DisplayMessage("#no_car_selected");
                return true;
            }

            CarScript car = null;
            carToStoreList.GetItemData(index, 0, car);

            if(car) {
                bool carIsEmpty = true;
                for(int seat = 0; seat < car.CrewSize(); seat++) {
                    if(car.CrewMember(seat)) {
                        player.DisplayMessage("#car_is_not_empty");
                        return true;
                    }
                }

                CargoBase cargo = car.GetInventory().GetCargo();
                if(!player.GetConfig().carConfig.canStoreCarsWithGoods && cargo.GetItemCount() > 0) {
                    player.DisplayMessage("#car_is_not_empty");
                    return true;
                }

                if(w == inStoreButton && car.ownerId != dzlPlayer.dayZPlayerId) {
                    player.DisplayMessage("#car_can_only_stored_in_fraction_garage");
                    return true;
                }

                if(w == storeInFractionButton && !dzlPlayer.HasFractionRightCanAccessFractionGarage()) return true;

                GetGame().RPCSingleParam(car, DZL_RPC.EVENT_STORE_CAR, new Param2<vector, bool>(player.GetPosition(), w == storeInFractionButton), true);
                car.isSold = true;
            }
        } else if(w == outStoreButton) {
            int indexOut = carInStoreList.GetSelectedRow();

            if(-1 == indexOut) {
                player.DisplayMessage("#no_car_selected");
                return true;
            }

            DZLCarStoreItem carOut = null;
            carInStoreList.GetItemData(indexOut, 0, carOut);

            if(!carOut.IsOwner(dzlPlayer.dayZPlayerId) && !dzlPlayer.HasFractionRightCanAccessFractionGarage()) return true;

            string textPrivate = "";
            carInStoreList.GetItemText(indexOut, 1, textPrivate);

            bool isPrivateParkOut = "x" == textPrivate;

            if(carOut) {
                array<Object> excludedObjects = new array<Object>;
                array<Object> nearbyObjects = new array<Object>;

                if(GetGame().IsBoxColliding(position.spawnPositionOfVehicles, position.spawnOrientationOfVehicles, "2 2 0", excludedObjects, nearbyObjects)) {
                    player.DisplayMessage("#car_spwan_place_is_blocked");
                    return true;
                }

                if(hasInsuranceWidget.IsChecked() && !dzlPlayer.HasEnoughMoneyBank(config.carConfig.carInsurancePrice)) {
                    player.DisplayMessage("#error_not_enough_money");
                }

                GetGame().RPCSingleParam(player, DZL_RPC.EVENT_GET_CAR_FROM_STORAGE, new Param3<string, bool, bool>(carOut.GetId(), hasInsuranceWidget.IsChecked(), isPrivateParkOut), true);
            }
        } else if(w == closeButton) {
            OnHide();
            return true;
        }

        return true;
    }

    override void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DZL_RPC.EVENT_GET_CAR_DATA_FROM_STORAGE_RESPONSE) {
            autoptr Param2<ref DZLCarStorage, ref DZLCarStorage> paramGetCarDataResponse;
            if(ctx.Read(paramGetCarDataResponse)) {
                DZLCarStorage carStorage = paramGetCarDataResponse.param1;
                DZLCarStorage fractionCarStorage = paramGetCarDataResponse.param2;
                array<ref DZLCarStoreItem> items = carStorage.items;

                carInStoreList.ClearItems();

                int pos;

                foreach(DZLCarStoreItem item: items) {
                    pos = carInStoreList.AddItem(GetItemDisplayName(item.type), item, 0);
                    carInStoreList.SetItem(pos, "x", item, 1);
                }

                if(fractionCarStorage) {
                    array<ref DZLCarStoreItem> fractionItems = fractionCarStorage.items;

                    foreach(DZLCarStoreItem fractionItem: fractionItems) {
                        pos = carInStoreList.AddItem(GetItemDisplayName(fractionItem.type), fractionItem, 0);
                        carInStoreList.SetItem(pos, "x", fractionItem, 2);
                    }
                }
            }
            UpdateGUI();
        }
    }

    string GetItemDisplayName(string itemClassname) {
        string cfg;
        string displayName;

        cfg = CFG_VEHICLESPATH + " " + itemClassname + " displayName";

        GetGame().ConfigGetText(cfg, displayName);


        if(displayName == "") {
            displayName = itemClassname;
        }

        return displayName;
    }

}
