class DZLSpawnPositionMenu : DZLBaseMenu
{
	private MapWidget spawnMap;
	private TextListboxWidget spawnPoints;
	private ButtonWidget randomSpawn;
	private ButtonWidget spawn;

    override Widget Init() {
        layoutPath = "DayZLife/layout/SpawnMenu/SpawnMenu.layout";
        showCourser = false;
        hasCloseButton = false;

        super.Init();

		spawnMap = creator.GetMapWidget("map");
		spawnPoints = creator.GetTextListboxWidget("spawnPoints");
        randomSpawn = creator.GetButtonWidget("randomButton");
        spawn = creator.GetButtonWidget("spawnButton");

		police.Show(false);
    }
	
	override void OnShow() {
	    super.OnShow();

	}

    override bool OnClick(Widget w, int x, int y, int button) {
        if (super.OnClick(w, x, y, button)) return true;

        if (w == police) {

        } else if (w == medic) {

        } else if (w == civilian) {

        }

        return false;
    }

    private bool OpenSpawnPositionMenu() {

    }
}
