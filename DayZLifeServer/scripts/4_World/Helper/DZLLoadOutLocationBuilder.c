class DZLLoadOutLocationBuilder: DZLLicenceLocationBuilder {

    void vzDZLLoadOutLocationBuilder() {
        Init();
    }

    override void Create() {
		Build(DZLConfig.Get().jobConfig.loadOutsCops.loadOutPosition);
		Build(DZLConfig.Get().jobConfig.loadOutsMedics.loadOutPosition);
	}
	
	private void Build(array<ref DZLLoadOutPosition> positions) {
		foreach(DZLLoadOutPosition position: positions) {
			EntityAI npc = CreatePositions(position);
			if (npc) {
				npcs.Insert(new DZLNPCKeepPosition(npc));
			}
           
        }
	}
};
