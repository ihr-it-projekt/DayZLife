class DZLTuningMenu: DZLBaseMenu {
    private TextListboxWidget carFoundList;
    private TextListboxWidget carTuningOptionList;
    private ButtonWidget tuneButton;

    override Widget Init() {
        layoutPath = "DayZLifeClient/layout/Tuning/Tuning.layout";
        super.Init();

        carFoundList = creator.GetTextListboxWidget("carFoundList");
        carTuningOptionList = creator.GetTextListboxWidget("carTuningOptionList");
        tuneButton = creator.GetButtonWidget("tuneButton");

        return layoutRoot;
    }

    override void UpdateGUI(string message = "") {
        super.UpdateGUI(message);
        carFoundList.ClearItems();
        ref array<ref DZLTuneOption> carTypes = DZLConfig.Get().tuningConfig.options;
        foreach(DZLTuneOption carType: carTypes) {
            CarScript playerCar = DZLObjectFinder.GetCarForTuning(player.GetPosition(), carType.car);
            if(playerCar && !playerCar.isSold) {
                string name = "";
                g_Game.ObjectGetDisplayName(playerCar, name);
                name += " (" + playerCar.GetType() + ",";
                name += " " + playerCar.ownerName + ")";
                carFoundList.AddItem(name, playerCar, 0);
            }
        }
    }

    override void OnShow() {
        super.OnShow();

        UpdateGUI();
    }

    override bool OnClick(Widget w, int x, int y, int button) {
        if(w == tuneButton) {
            int index = carFoundList.GetSelectedRow();
            int indexTarget = carTuningOptionList.GetSelectedRow();

            if(-1 == index) {
                player.DisplayMessage("#no_car_selected");
                return true;
            }

            if(-1 == indexTarget) {
                player.DisplayMessage("#no_target_type_selected");
                return true;
            }

            CarScript car = null;
            carFoundList.GetItemData(index, 0, car);

            DZLCarTuneConfig targetTuneConfig = null;
            carTuningOptionList.GetItemData(indexTarget, 0, targetTuneConfig);

            if(car && targetTuneConfig) {
                bool carIsEmpty = true;
                for(int seat = 0; seat < car.CrewSize(); seat++) {
                    if(car.CrewMember(seat)) {
                        player.DisplayMessage("#car_is_not_empty");
                        return true;
                    }
                }

                g_Game.RPCSingleParam(car, DZL_RPC.EVENT_TUNE_CAR, new Param1<string>(targetTuneConfig.type), true);
                OnHide();
            }
        } else if(w == carFoundList) {
            int indexFoundList = carFoundList.GetSelectedRow();

            if(-1 == indexFoundList) {
                return true;
            }

            carTuningOptionList.ClearItems();
            CarScript _car = null;
            carFoundList.GetItemData(index, 0, _car);

            if(_car) {
                array<ref DZLCarTuneConfig>options = config.tuningConfig.GetTargetCarsForCar(_car.GetType());
                if(options) {
                    foreach(DZLCarTuneConfig option: options) {
                        string name = GetItemDisplayName(option.type);
                        carTuningOptionList.AddItem(name + "(" + option.type + ")", option, 0);
                    }
                }
            }

            return true;
        } else if(w == closeButton) {
            OnHide();
            return true;
        }

        return true;
    }


    string GetItemDisplayName(string itemClassname) {
        string cfg;
        string displayName;

        cfg = CFG_VEHICLESPATH + " " + itemClassname + " displayName";

        g_Game.ConfigGetText(cfg, displayName);


        if(displayName == "") {
            displayName = itemClassname;
        }

        return displayName;
    }

}
