modded class MissionGameplay
{
    private bool holdRControl = false;
    private bool holdLControl = false;
	private bool holdOne = false;
	private bool holdTow = false;
	private bool holdTree = false;
	private bool holdFour = false;

	private ref DZLPlayerEventListener playerEventListener;
	private ref DZLCarEventListener carEventListener;
	private ref DZLMessageDB messageDB;

   	PlayerBase player;

	override void OnInit() {
		super.OnInit();
		playerEventListener = new DZLPlayerEventListener;
		carEventListener = new DZLCarEventListener;
		messageDB = new DZLMessageDB;
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
            case KeyCode.KC_4:
                holdFour = false;
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
				 
                if ((holdRControl && holdLControl || holdOne && holdLControl) && g_Game.GetUIManager().GetMenu() == NULL) {
                    GetGame().GetUIManager().ShowScriptedMenu(player.GetAlmanacMenu(), NULL);
                }

                break;
            case KeyCode.KC_LCONTROL:
                holdLControl = true;
                if ((holdRControl && holdLControl || holdOne && holdLControl) && g_Game.GetUIManager().GetMenu() == NULL) {
					GetGame().GetUIManager().ShowScriptedMenu(player.GetAlmanacMenu(), NULL);
                }

                if ((holdLControl && holdTow) && g_Game.GetUIManager().GetMenu() == NULL) {
                    player.ShowHealMenuFromMission();
                }

                if ((holdLControl && holdTree && player.CanReSpawn()) && !player.IsRestrained() && g_Game.GetUIManager().GetMenu() == NULL) {
                    GetGame().GetUIManager().ShowScriptedMenu(player.GetSpawnPositionMenu(), NULL);
                }

                if ((holdLControl && holdFour && !player.IsRestrained() && !player.IsUnconscious()) && g_Game.GetUIManager().GetMenu() == NULL && player.HasInInventory("PersonalRadio")) {
                    GetGame().GetUIManager().ShowScriptedMenu(player.GetSpawnPositionMenu(), NULL);
                }

                break;
			case KeyCode.KC_1:
				holdOne = true;
				if ((holdRControl && holdLControl || holdOne && holdLControl) && g_Game.GetUIManager().GetMenu() == NULL) {
					GetGame().GetUIManager().ShowScriptedMenu(player.GetAlmanacMenu(), NULL);
                }
                break;
			case KeyCode.KC_2:
				holdTow = true;
				if ((holdLControl && holdTow) && g_Game.GetUIManager().GetMenu() == NULL) {
					player.ShowHealMenuFromMission();
                }
                break;

            case KeyCode.KC_3:
				holdTree = true;
				if ((holdLControl && holdTree && player.CanReSpawn()) && g_Game.GetUIManager().GetMenu() == NULL && !player.IsRestrained()) {
					GetGame().GetUIManager().ShowScriptedMenu(player.GetSpawnPositionMenu(), NULL);
                }
                break;
            case KeyCode.KC_4:
				holdFour = true;
				if ((holdLControl && holdFour && !player.IsRestrained() && !player.IsUnconscious()) && g_Game.GetUIManager().GetMenu() == NULL && player.HasInInventory("PersonalRadio")) {
					GetGame().GetUIManager().ShowScriptedMenu(player.GetMessageSystemMenu(), NULL);
                }
                break;
            default:
                super.OnKeyPress(key);
                break;
        }
    }
 }
