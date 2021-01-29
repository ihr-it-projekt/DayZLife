class DZLMedicHelpMenu : DZLBaseMenu
{
	private ButtonWidget killButton;
	private ButtonWidget healButton;
	private ButtonWidget hospitalButton;
	private bool hasRequestForMedic = false;

    void DZLMedicHelpMenu() {
        Construct();
    }
    void ~DZLMedicHelpMenu() {
        Destruct();
    }

    override Widget Init() {
        layoutPath = "DayZLife/layout/MedicHelp/MedicHelp.layout";
        super.Init();
		
        killButton = creator.GetButtonWidget("KillButton");
        healButton = creator.GetButtonWidget("HealButton");
        healButton.SetText("#call_a_medic (" + config.medicConfig.priceMedicHeal.ToString() + ")");
        hospitalButton = creator.GetButtonWidget("HospitalButton");
        hospitalButton.SetText("#go_to_hospital (" + config.medicConfig.priceHospitalHeal.ToString() + ")");

        return layoutRoot;
    }

    override bool OnClick(Widget w, int x, int y, int button) {
        if (super.OnClick(w, x, y, button)) return true;

        if (w == killButton) {
            player.willDie = true;
            OnHide();
        } else if (w == healButton) {
			GetGame().RPCSingleParam(player, DAY_Z_LIFE_MEDIC_CALL, null, true);
			healButton.Show(false);
			dzlPlayer.SetWillHealByMedic();
			OnHide();
		} else if (w == hospitalButton) {
		    dzlPlayer.SetWillHealByHospital();
		    player.willDie = true;
			GetGame().RPCSingleParam(player, DAY_Z_LIFE_EVENT_HOSPITAL_HEAL_PLAYER, null, true);
			OnHide();
		}

        return false;
    }

}
