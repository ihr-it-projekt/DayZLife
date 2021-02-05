modded class MissionGameplay
{
    private bool holdRControl = false;
    private bool holdLControl = false;
	private bool holdOne = false;
	private bool holdTow = false;
	private bool holdTree = false;


	private UIScriptedMenu almanac;
	private UIScriptedMenu spawnMenu;
	private ref DZLPlayerEventListener playerEventListener;
	private ref DZLCarEventListener carEventListener;

   	PlayerBase player;

	override void OnInit() {
		super.OnInit();
		playerEventListener = new DZLPlayerEventListener;
		carEventListener = new DZLCarEventListener;
	}

    override void OnKeyRelease(int key) {
        player = PlayerBaseHelper.GetPlayer();

        if (!player) return;

        switch (key){
            case KeyCode.KC_ESCAPE:
                player.CloseMenu();
                break;
            case KeyCode.KC_RCONTROL:
                holdRControl = false;
                break;
            case KeyCode.KC_LCONTROL:
                holdLControl = false;
                break;
			case KeyCode.KC_1:
                holdOne = false;
                break;
			case KeyCode.KC_2:
                holdTow = false;
                break;
            case KeyCode.KC_3:
                holdTree = false;
                break;
            default:
                super.OnKeyRelease(key);
                break;
        }
    }

    override void OnKeyPress(int key) {
        player = PlayerBaseHelper.GetPlayer();
        if (!player) return;

        switch (key){
            case KeyCode.KC_RCONTROL:
                holdRControl = true;
				 
                if ((holdRControl && holdLControl || holdOne && holdLControl) && !almanac && !GetGame().GetUIManager().IsCursorVisible()) {
                    almanac = GetGame().GetUIManager().ShowScriptedMenu(player.GetAlmanacMenu(), NULL);
                }

                break;
            case KeyCode.KC_LCONTROL:
                holdLControl = true;
                if ((holdRControl && holdLControl || holdOne && holdLControl) && !almanac && !GetGame().GetUIManager().IsCursorVisible()) {
					almanac = GetGame().GetUIManager().ShowScriptedMenu(player.GetAlmanacMenu(), NULL);
                }

                if ((holdLControl && holdTow) && !GetGame().GetUIManager().IsCursorVisible()) {
                    player.ShowHealMenuFromMission();
                }

                if ((holdLControl && holdTree && player.CanReSpawn()) && !GetGame().GetUIManager().IsCursorVisible() && !player.IsRestrained()) {
                    spawnMenu = GetGame().GetUIManager().ShowScriptedMenu(player.GetSpawnPositionMenu(), NULL);
                }

                break;
			case KeyCode.KC_1:
				holdOne = true;
				if ((holdRControl && holdLControl || holdOne && holdLControl) && !almanac && !GetGame().GetUIManager().IsCursorVisible()) {
					almanac = GetGame().GetUIManager().ShowScriptedMenu(player.GetAlmanacMenu(), NULL);
                }
                break;
			case KeyCode.KC_2:
				holdTow = true;
				if ((holdLControl && holdTow) && !GetGame().GetUIManager().IsCursorVisible()) {
					player.ShowHealMenuFromMission();
                }
                break;

            case KeyCode.KC_3:
				holdTree = true;
				if ((holdLControl && holdTree && player.CanReSpawn()) && !GetGame().GetUIManager().IsCursorVisible() && !player.IsRestrained()) {
					spawnMenu = GetGame().GetUIManager().ShowScriptedMenu(player.GetSpawnPositionMenu(), NULL);
                }
                break;
            default:
                super.OnKeyPress(key);
                break;
        }
    }
 }
