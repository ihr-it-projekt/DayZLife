class TBLOLoadOutLocationBuilder {

    void Create() {
		Build(TBLOConfig.Get().loadOuts.loadOutPosition);
	}

	TBLOLoadoutActionObject CreatePositions(TBLOLoadOutPosition position, string type) {
        Object object = TBLOSpawnHelper.SpawnActionPoint(position.position, position.orientation, type);
        return TBLOLoadoutActionObject.Cast(object);
	}
	
	private void Build(array<ref TBLOLoadOutPosition> positions) {
		foreach(TBLOLoadOutPosition position: positions) {
			CreatePositions(position, "TBLOLoadoutActionObject");
		}
	}
};
