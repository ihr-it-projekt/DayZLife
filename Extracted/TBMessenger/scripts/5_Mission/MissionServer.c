modded class MissionServer {

    private ref TBMMessageListener messageListener;
    private ref TBMConfigListener configListener;

	override void OnInit() {
	    super.OnInit();
	    TBMConfig.Get();
        messageListener = new TBMMessageListener;
        configListener = new TBMConfigListener;
    }
}
