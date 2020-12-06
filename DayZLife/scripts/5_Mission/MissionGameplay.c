modded class MissionGameplay
{
    private bool holdRControl = false;
    private bool holdLControl = false;
	private UIScriptedMenu almanac;
	private ref DZLPlayerEventListener playerEventListener;

   	PlayerBase player
	
	override void OnInit() {
		super.OnInit();
		playerEventListener = new DZLPlayerEventListener;
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
				 
                if (holdRControl && holdLControl && !almanac && !GetGame().GetUIManager().IsCursorVisible()) {
                    almanac = GetGame().GetUIManager().ShowScriptedMenu(player.GetAlmanacMenu(), NULL);
                }

                break;
            case KeyCode.KC_LCONTROL:
                holdLControl = true;
                if (holdRControl && holdLControl && !almanac && !GetGame().GetUIManager().IsCursorVisible()) {
					almanac = GetGame().GetUIManager().ShowScriptedMenu(player.GetAlmanacMenu(), NULL);
                }

                break;
            default:
                super.OnKeyPress(key);
                break;
        }
    }
 }
