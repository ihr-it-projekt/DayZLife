class DZLLoadOutLocationBuilder: DZLLicenceLocationBuilder {

    override void Create() {
		Build(DZLConfig.Get().jobConfig.loadOutsCops.loadOutPosition, DAY_Z_LIFE_JOB_COP);
		Build(DZLConfig.Get().jobConfig.loadOutsMedics.loadOutPosition, DAY_Z_LIFE_JOB_MEDIC);
		Build(DZLConfig.Get().jobConfig.loadOutsArmy.loadOutPosition, DAY_Z_LIFE_JOB_ARMY);
	}
	
	private void Build(array<ref DZLLoadOutPosition> positions, string jobId) {
		foreach(DZLLoadOutPosition position: positions) {

			if (jobId == DAY_Z_LIFE_JOB_COP) {
			    CreatePositions(position, "DZLLoadoutCopActionObject");
			} else if (jobId == DAY_Z_LIFE_JOB_MEDIC) { 
			    CreatePositions(position, "DZLLoadoutMedicActionObject");
			} else {
			    CreatePositions(position, "DZLLoadoutArmyActionObject");
			}
        }
	}
};
