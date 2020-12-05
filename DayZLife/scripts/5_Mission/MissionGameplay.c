modded class MissionGameplay
{
    private bool holdRControl = false;
    private bool holdLControl = false;
	private UIScriptedMenu almanac;
	private ScriptCallQueue queue = GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM);

   	PlayerBase player
	
	override void OnInit() {
		super.OnInit();
		GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
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

    void CreateSpawnMenu() {
        player = PlayerBaseHelper.GetPlayer();
        if (!player) {
            DebugMessageDZL("no player to spawn");
            return;
        }

        GetGame().GetUIManager().ShowScriptedMenu(player.GetJobSpawnMenu(), null);
        queue.Remove(CreateSpawnMenu);
    }


    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        if (rpc_type == DAY_Z_LIFE_NEW_SPAWN_CLIENT) {
            player = PlayerBaseHelper.GetPlayer();
            if (!player) {
                DebugMessageDZL("no player to spawn");
                return;
            }

            queue.CallLater(CreateSpawnMenu, 1750, true);
        }
    }

    override void OnKeyPress(int key) {
        player = PlayerBaseHelper.GetPlayer();
        if (!player) return;

        player = PlayerBaseHelper.GetPlayer();

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
