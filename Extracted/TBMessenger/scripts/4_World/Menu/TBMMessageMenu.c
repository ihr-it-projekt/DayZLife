class TBMMessageMenu
{
	private ref TBMUIItemCreator creator;
	private MultilineTextWidget message;
	private ref Timer timer;
	private string messageText;
	private Widget layoutRoot;


    void ~TBMMessageMenu() {
        if (layoutRoot) layoutRoot.Show(false);
    }


    void Init() {
        creator = new TBMUIItemCreator("TBMessenger/layout/TBM_Message.layout");
        message = creator.GetMultilineTextWidget("Announcements");
        layoutRoot = creator.GetLayoutRoot();

        layoutRoot.Show(false);
        timer = new Timer;
    }

    void SetText(string text) {
        messageText = text;
    }

    void Show() {
        message.SetText(messageText);
        layoutRoot.Show(true);
        timer.Run(10, this, "CloseMenu");
    }

    void CloseMenu() {
        layoutRoot.Show(false);
        timer.Stop();
    }
}
