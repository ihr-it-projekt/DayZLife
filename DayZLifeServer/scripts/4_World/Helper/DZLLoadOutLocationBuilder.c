class DZLLoadOutLocationBuilder: DZLLicenceLocationBuilder {

    override void Create() {
        DZLJobConfig config = DZLConfig.Get().jobConfig;

        foreach(string job: config.paycheck.jobNames) {
            Build(config.GetLoadOuts(job).loadOutPosition, job);
        }
    }

    private void Build(array<ref DZLLoadOutPosition> positions, string jobId) {
        foreach(DZLLoadOutPosition position: positions) {

            DZLBaseActionObject object = CreatePositions(position, "DZLLoadoutActionObject");

            DZLLoadoutActionObject loadoutActionObject = DZLLoadoutActionObject.Cast(object);
            if(!loadoutActionObject) return;
            loadoutActionObject.jobName = jobId;
        }
    }
};
