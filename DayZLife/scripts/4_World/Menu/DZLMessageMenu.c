class DZLMessageMenu: UIScriptedMenu
{
	private ref DZLUIItemCreator creator;
	private MultilineTextWidget message;
	private ref Timer timer;
	private string messageText;

    override Widget Init() {
        creator = new DZLUIItemCreator("DayZLife/layout/DZL_Message.layout");
        message = creator.GetMultilineTextWidget("Announcements");
        layoutRoot = creator.GetLayoutRoot();

        layoutRoot.Show(false);
        timer = new Timer;

        return layoutRoot;
    }

    void SetText(string text) {
        messageText = text;
    }

    override void OnShow() {
        message.SetText(messageText);
        layoutRoot.Show(true);
        timer.Run(10, this, "OnHide");
    }

    override void OnHide() {
        layoutRoot.Show(false);
        timer.Stop();
        super.OnHide();
        Close();
    }
}