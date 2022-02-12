modded class MissionGameplay
{
    private bool holdRControl = false;
    private bool holdLControl = false;
	private bool holdOne = false;
	private bool holdTow = false;
	private bool holdTree = false;
	private bool holdFour = false;
	private bool holdFive = false;

	private ref DZLPlayerEventListener playerEventListener;
	private ref DZLCarEventListener carEventListener;
	private ref DZLMessageDB messageDB;

   	PlayerBase player;

	override void OnInit() {
		super.OnInit();
		playerEventListener = new DZLPlayerEventListener;
		carEventListener = new DZLCarEventListener;
		messageDB = new DZLMessageDB;
		DZLPlayerClientDB.Get();
	}

    override void OnKeyRelease(int key) {
        player = PlayerBaseHelper.GetPlayer();

        if (!player) return;
        bool wasActionDone = false;
        switch (key){
            case KeyCode.KC_ESCAPE:
                wasActionDone = player.CloseMenu();
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
            case KeyCode.KC_4:
                holdFour = false;
                break;
            case KeyCode.KC_5:
                holdFive = false;
                break;
            default:
                break;
        }

        if (false == wasActionDone){
            super.OnKeyRelease(key);
        }
    }

    override void OnKeyPress(int key) {
        player = PlayerBaseHelper.GetPlayer();
        if (!player) return;

        switch (key){
            case KeyCode.KC_RCONTROL:
                holdRControl = true;
				CheckOpenMenu();
                break;
            case KeyCode.KC_LCONTROL:
                holdLControl = true;
				CheckOpenMenu();
                break;
			case KeyCode.KC_1:
				holdOne = true;
				CheckOpenMenu();
                break;
			case KeyCode.KC_2:
				holdTow = true;
				CheckOpenMenu();
                break;
            case KeyCode.KC_3:
				holdTree = true;
				CheckOpenMenu();
                break;
            case KeyCode.KC_4:
				holdFour = true;
				CheckOpenMenu();
                break;
            case KeyCode.KC_5:
				holdFive = true;
				CheckOpenMenu();
                break;
            default:
                super.OnKeyPress(key);
                break;
        }
    }

    private void CheckOpenMenu() {
    	if (holdLControl && g_Game.GetUIManager().GetMenu() == NULL) {
			if (holdRControl || holdOne) {
				GetGame().GetUIManager().ShowScriptedMenu(player.GetAlmanacMenu(), NULL);
			} else if (holdTow) {
				player.ShowHealMenuFromMission();
			} else if (holdTree && player.CanReSpawn() && !player.IsRestrained()) {
				GetGame().GetUIManager().ShowScriptedMenu(player.GetSpawnPositionMenu(), NULL);
			} else if (holdFour && !player.IsRestrained() && !player.IsUnconscious() && player.HasInInventory("PersonalRadio")) {
				GetGame().GetUIManager().ShowScriptedMenu(player.GetMessageSystemMenu(), NULL);
			} else if (holdFive && !player.IsUnconscious()) {
				GetGame().GetUIManager().ShowScriptedMenu(player.GetPayTicketMenu(), NULL);
			}
		}
    }
 }
