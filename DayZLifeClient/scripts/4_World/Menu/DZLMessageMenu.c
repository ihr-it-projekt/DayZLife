class DZLMessageMenu {
    private ref DZLUIItemCreator creator;
    private MultilineTextWidget message;
    private ref Timer timer;
    private string messageText;
    private Widget layoutRoot;


    void ~DZLMessageMenu() {
        if(layoutRoot) layoutRoot.Show(false);
    }

    void Init() {
        creator = new DZLUIItemCreator("DayZLifeClient/layout/DZL_Message.layout");
        message = creator.GetMultilineTextWidget("Announcements");
        layoutRoot = creator.GetLayoutRoot();

        layoutRoot.Show(false);
        timer = new Timer;
    }

    void SetText(string text) {
        messageText = Widget.TranslateString(text);
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
