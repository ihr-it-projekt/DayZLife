modded class MissionGameplay
{
    private bool holdLControl = false;
	private bool holdOne = false;

	private ref TBMPlayerEventListener playerEventListener;
	private ref TBMMessageDB messageDB;
   	PlayerBase tbmPlayerBase;

	override void OnInit() {
		super.OnInit();
		playerEventListener = new TBMPlayerEventListener;
		messageDB = new TBMMessageDB;
		TBMPlayerClientDB.Get();
		GetGame().RPCSingleParam(TBMPlayerBaseHelper.GetPlayer(), DAY_Z_LIFE_EVENT_GET_CONFIG, null, true);
	}

    override void OnKeyRelease(int key) {
        tbmPlayerBase = TBMPlayerBaseHelper.GetPlayer();

        if (!tbmPlayerBase) return;
        bool wasActionDone = false;
        switch (key){
            case KeyCode.KC_ESCAPE:
                wasActionDone = tbmPlayerBase.CloseMenu();
                break;
            case KeyCode.KC_LCONTROL:
                holdLControl = false;
                break;
			case KeyCode.KC_1:
                holdOne = false;
                break;
            default:
                break;
        }

        if (false == wasActionDone){
            super.OnKeyRelease(key);
        }
    }

    override void OnKeyPress(int key) {
        tbmPlayerBase = TBMPlayerBaseHelper.GetPlayer();
        if (!tbmPlayerBase) return;

        switch (key){
           case KeyCode.KC_LCONTROL:
                holdLControl = true;
				CheckOpenMenu();
                break;
			case KeyCode.KC_1:
				holdOne = true;
				CheckOpenMenu();
                break;
            default:
                super.OnKeyPress(key);
                break;
        }
    }

    private void CheckOpenMenu() {
    	if (holdLControl && g_Game.GetUIManager().GetMenu() == NULL) {
			if (holdOne && tbmPlayerBase.CanOpenMessageMenu()) {
				GetGame().GetUIManager().ShowScriptedMenu(tbmPlayerBase.GetMessageSystemMenu(), NULL);
			}
		}
    }
 }
