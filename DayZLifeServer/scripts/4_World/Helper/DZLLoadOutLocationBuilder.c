class DZLLoadOutLocationBuilder: DZLLicenceLocationBuilder {

    void vzDZLLoadOutLocationBuilder() {
        Init();
    }

    override void Create() {
		array<ref DZLLoadOutPosition> positions = DZLConfig.Get().jobConfig.loadOutsCops.loadOutPosition;
		
		foreach(DZLLoadOutPosition position: positions) {
           npcs.Insert(new DZLNPCKeepPosition(CreatePositions(position)));
        }
	}
};
