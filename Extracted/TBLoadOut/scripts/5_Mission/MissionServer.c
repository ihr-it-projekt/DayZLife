modded class MissionServer {

    private ref TBLOLoadOutLocationBuilder builder;
    private ref TBLOConfigListener configListener;
    private ref TBLOLoadOutListener listener;

	override void OnInit() {
	    super.OnInit();
        builder = new TBLOLoadOutLocationBuilder;
        configListener = new TBLOConfigListener;
        listener = new TBLOLoadOutListener;

        builder.Create();
    }
}
