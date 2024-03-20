modded class MissionGameplay {
    private bool holdRControl = false;
    private bool holdLControl = false;
    private bool holdOne = false;
    private bool holdTow = false;
    private bool holdTree = false;
    private bool holdFour = false;
    private bool holdFive = false;
    private bool holdSix = false;

    private ref DZLPlayerEventListener playerEventListener;
    private ref DZLMessageDB messageDB;

    PlayerBase dzlPlayerBase;

    override void OnInit() {
        super.OnInit();
        playerEventListener = new DZLPlayerEventListener;
        messageDB = new DZLMessageDB;
        DZLPlayerClientDB.Get();
    }

    override void OnKeyRelease(int key) {
        dzlPlayerBase = DZLPlayerBaseHelper.GetPlayer();

        if(!dzlPlayerBase) return;
        bool wasActionDone = false;
        switch(key) {
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
            case KeyCode.KC_6:
                holdSix = false;
                break;
            default:
                break;
        }

        if(false == wasActionDone) {
            super.OnKeyRelease(key);
        }
    }

    override void OnKeyPress(int key) {
        dzlPlayerBase = DZLPlayerBaseHelper.GetPlayer();
        if(!dzlPlayerBase) return;

        switch(key) {
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
            case KeyCode.KC_6:
                holdSix = true;
                CheckOpenMenu();
                break;
            default:
                super.OnKeyPress(key);
                break;
        }
    }

    private void CheckOpenMenu() {
        if(holdLControl && g_Game.GetUIManager().GetMenu() == NULL) {
            if(holdRControl || holdOne) {
                GetGame().GetUIManager().ShowScriptedMenu(dzlPlayerBase.GetAlmanacMenu(), NULL);
            } else if(holdTree && dzlPlayerBase.CanReSpawn() && !dzlPlayerBase.IsRestrained()) {
                GetGame().GetUIManager().ShowScriptedMenu(dzlPlayerBase.GetSpawnPositionMenu(), NULL);
            } else if(holdFour && dzlPlayerBase.CanOpenMessageMenu()) {
                GetGame().GetUIManager().ShowScriptedMenu(dzlPlayerBase.GetMessageSystemMenu(), NULL);
            } else if(holdFive && !dzlPlayerBase.IsUnconscious()) {
                GetGame().GetUIManager().ShowScriptedMenu(dzlPlayerBase.GetPayTicketMenu(), NULL);
            } else if(holdSix) {
                dzlPlayerBase.RequestUpdateDZLPlayer();
                GetGame().GetUIManager().ShowScriptedMenu(dzlPlayerBase.GetFractionMenu(), NULL);
            }
        }
    }
}
