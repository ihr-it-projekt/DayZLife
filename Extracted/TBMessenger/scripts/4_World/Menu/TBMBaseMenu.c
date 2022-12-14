class TBMBaseMenu: UIScriptedMenu
{
    protected ref TBMUIItemCreator creator;
    protected ref TBMConfig config;
    protected string layoutPath;
    protected ButtonWidget closeButton;
    protected PlayerBase player;
    protected bool hasCloseButton = true;
    protected bool hideCourser = true;
    protected bool showCourser = true;


    protected void Construct() {
        if(GetGame().IsClient()){
            GetDayZGame().Event_OnRPC.Insert(HandleEventsTBM);
        }
    }

    protected void Destruct() {
        OnHide();
        GetDayZGame().Event_OnRPC.Remove(HandleEventsTBM);
    }

    void SetPlayer(PlayerBase _player) {
        this.player = _player;
    }

    void UpdatePlayer(PlayerBase player) {
        SetPlayer(player);
    }

    void SetConfig(ref TBMConfig config) {
        this.config = config;
    }

    void HandleEventsTBM(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {

    }

    override Widget Init() {
        creator = new TBMUIItemCreator(layoutPath);

        if (hasCloseButton) {
            closeButton = creator.GetButtonWidget("Button_Closed");
            closeButton.Show(true);
        }

        layoutRoot = creator.GetLayoutRoot();

        layoutRoot.Show(false);

        return layoutRoot;
    }

    override bool OnClick(Widget w, int x, int y, int button) {
        if (super.OnClick(w, x, y, button)) return true;

        switch(w){
            case closeButton:
                OnHide();
                return true;
            default:
                break;
        }
        return false;
    }

    override void OnShow() {
        super.OnShow();

        GetGame().GetUIManager().ShowCursor(true);
		
        GetGame().GetInput().ChangeGameFocus(1);
        GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_INVENTORY);
    }

    override void OnHide() {
        super.OnHide();

        GetGame().GetUIManager().ShowCursor(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetMission().PlayerControlEnable(true);
        Close();
    }
}
