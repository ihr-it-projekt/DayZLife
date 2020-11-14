class DZLBaseMenu: UIScriptedMenu
{
    protected ref DZLUIItemCreator creator;
    protected ref DZLConfig config;
    protected string layoutPath;
    protected ButtonWidget closeButton;
    protected PlayerBase player;
    protected DZLPlayer dzlPlayer;

    protected void Construct() {
        if(GetGame().IsClient()){
            GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
        }
    }

    protected void Destruct() {
        OnHide();
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void SetPlayer(PlayerBase _player) {
        this.player = _player;
        this.dzlPlayer = _player.dzlPlayer;
    }
    void UpdatePlayer(PlayerBase player) {
        SetPlayer(player);
        UpdateGUI();
    }

    void SetConfig(ref DZLConfig config) {
        this.config = config;
    }

    void UpdateGUI(string message = "") {
       if(message) {
            player.DisplayMessage(message);
       }
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {

    }

    override Widget Init() {
        creator = new DZLUIItemCreator(layoutPath);
        closeButton = creator.GetButtonWidget("Button_Closed");
        closeButton.Show(true);
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
        GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_INVENTORY);
        GetGame().GetUIManager().ShowCursor(true);
        GetGame().GetInput().ChangeGameFocus(1);
    }

    override void OnHide() {
        super.OnHide();
        GetGame().GetUIManager().ShowCursor(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetMission().PlayerControlEnable(true);
        Close();
    }
}