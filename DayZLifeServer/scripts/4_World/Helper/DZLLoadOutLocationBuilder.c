class DZLLoadOutLocationBuilder: DZLLicenceLocationBuilder {

    override void Create() {
		Build(DZLConfig.Get().jobConfig.loadOutsCops.loadOutPosition, DAY_Z_LIFE_JOB_COP);
		Build(DZLConfig.Get().jobConfig.loadOutsMedics.loadOutPosition, DAY_Z_LIFE_JOB_MEDIC);
	}
	
	private void Build(array<ref DZLLoadOutPosition> positions, string jobId) {
		foreach(DZLLoadOutPosition position: positions) {

			if (jobId == DAY_Z_LIFE_JOB_COP) {
			    CreatePositions(position, "DZLLoadoutCopActionObject");
			} else {
			    CreatePositions(position, "DZLLoadoutMedicActionObject");
			}
        }
	}
};
