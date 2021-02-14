class DZLLoadOutLocationBuilder: DZLLicenceLocationBuilder {

    override void Create() {
		Build(DZLConfig.Get().jobConfig.loadOutsCops.loadOutPosition, DAY_Z_LIFE_JOB_COP);
		Build(DZLConfig.Get().jobConfig.loadOutsMedics.loadOutPosition, DAY_Z_LIFE_JOB_MEDIC);
	}
	
	private void Build(array<ref DZLLoadOutPosition> positions, string jobId) {
		foreach(DZLLoadOutPosition position: positions) {
			DZLBaseActionObject object = CreatePositions(position);

			if (jobId == DAY_Z_LIFE_JOB_COP) {
                object.EnableCopLoadOut();
			} else {
                object.EnableMedicLoadOut();
			}
        }
	}
};
