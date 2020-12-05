class DZLSpawnJobMenu : DZLBaseMenu
{
	private ButtonWidget police;
	private ButtonWidget civilian;
	private ButtonWidget medic;
	
    override Widget Init() {
        layoutPath = "DayZLife/layout/SpawnMenu/CivCopMedicSideSpawn.layout";
		hasCloseButton = false;
		hideCourser = false;
        super.Init();

        police = creator.GetButtonWidget("cop_button");
        civilian = creator.GetButtonWidget("civ_button");
        medic = creator.GetButtonWidget("medic_button");

		return layoutRoot;
    }
	
	override void OnShow() {
	    super.OnShow();

        police.Show(player.isPolice);
	}

    override bool OnClick(Widget w, int x, int y, int button) {
        if (super.OnClick(w, x, y, button)) return true;

        if (w == police) {
           return OpenSpawnPositionMenu(DAY_Z_LIFE_JOB_COP);
        } else if (w == medic) {
            return OpenSpawnPositionMenu(DAY_Z_LIFE_JOB_MEDIC);
        } else if (w == civilian) {
            return OpenSpawnPositionMenu(DAY_Z_LIFE_JOB_CIVIL);
        }

        return false;
    }

    bool OpenSpawnPositionMenu(string jobId) {
        GetGame().GetUIManager().ShowScriptedMenu(player.GetSpawnPositionMenu(jobId), null);
		OnHide();
		return true;
    }
}
