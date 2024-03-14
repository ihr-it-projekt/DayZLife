class DZLMedicHelpMenu : DZLBaseMenu {
    private ButtonWidget killButton;
    private ButtonWidget healButton;
    private ButtonWidget hospitalButton;
    private TextWidget healTextWidget;
    private TextWidget killTextWidget;
    private TextWidget medicCountWidget;
    private bool hasRequestForMedic = false;
    private ref Timer checkButtonTimer;

    void DZLMedicHelpMenu() {
        Construct();

    }
    void ~DZLMedicHelpMenu() {
        Destruct();
    }

    override void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if(rpc_type == DZL_RPC.GET_MEDIC_COUNT_RESPONSE) {
            autoptr Param1<int> paramMedicCount;
            if(ctx.Read(paramMedicCount)) {
                medicCountWidget.SetText(paramMedicCount.param1.ToString());
                player.medicCount = paramMedicCount.param1;
            }
        }
    }

    override Widget Init() {
        layoutPath = "DayZLifeClient/layout/MedicHelp/MedicHelp.layout";
        super.Init();

        killButton = creator.GetButtonWidget("KillButton");
        healButton = creator.GetButtonWidget("HealButton");
        healButton.SetText("#call_a_medic (" + config.medicConfig.priceMedicHeal.ToString() + " $)");
        hospitalButton = creator.GetButtonWidget("HospitalButton");
        hospitalButton.SetText("#go_to_hospital (" + config.medicConfig.priceHospitalHeal.ToString() + " $)");
        healTextWidget = creator.GetTextWidget("HealTextWidget");
        killTextWidget = creator.GetTextWidget("KillTextWidget");
        medicCountWidget = creator.GetTextWidget("countMedic");

        if(!player.canHealInHospital || !player.canSeeKillButton) {
            checkButtonTimer = new Timer;
            checkButtonTimer.Run(1, this, "CheckButtons", null, true);
            hospitalButton.Show(false);
            killButton.Show(false);
            healTextWidget.Show(true);
            killTextWidget.Show(true);
        } else {
            healTextWidget.Show(false);
            killTextWidget.Show(false);
            killButton.Show(true);
            hospitalButton.Show(true);
        }

        GetGame().RPCSingleParam(player, DZL_RPC.GET_MEDIC_COUNT, null, true);

        return layoutRoot;
    }

    void CheckButtons() {
        if(player.canHealInHospital) {
            hospitalButton.Show(true);
            healTextWidget.Show(false);
        } else {
            healTextWidget.SetText("#hospital_heal_will_enabled " + player.GetWaitTimeForHospital().ToString());
        }

        if(player.canSeeKillButton) {
            killButton.Show(true);
            killTextWidget.Show(false);
        } else {
            killTextWidget.SetText("#kill_will_enabled " + player.GetWaitTimeForKill().ToString());
        }

        if(player.canSeeKillButton && player.canHealInHospital) {
            checkButtonTimer.Stop();
        }
    }

    override bool OnClick(Widget w, int x, int y, int button) {
        if(super.OnClick(w, x, y, button)) return true;

        if(w == killButton) {
            player.willDie = true;
            OnHide();
        } else if(w == healButton) {
            GetGame().RPCSingleParam(player, DZL_RPC.MEDIC_CALL, null, true);
            healButton.Show(false);
            dzlPlayer.SetWillHealByMedic();
            OnHide();
        } else if(w == hospitalButton) {
            dzlPlayer.SetWillHealByHospital();
            player.willDie = true;
            GetGame().RPCSingleParam(player, DZL_RPC.EVENT_HOSPITAL_HEAL_PLAYER, null, true);
            OnHide();
        }

        return false;
    }

}
