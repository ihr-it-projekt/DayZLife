class DZLJobHouseDefinitionCollection {
    string jobId;
    private ref array<ref DZLJobHouseDefinition> houseDefinitions = new array<ref DZLJobHouseDefinition>()

    void DZLJobHouseDefinitionCollection(string _jobId) {
        jobId = _jobId;
    }

    DZLJobHouseDefinition GetDefinitionByType(string type) {
        foreach(DZLJobHouseDefinition definition: houseDefinitions) {
            if(definition.houseType != type) continue;
            definition.jobId = jobId;
            return definition;
        }

        return null;
    }

    void MigrateToVersion6(sting job, array<ref DZLJobHouseDefinition> _houseDefinitions) {
        if (jobId != job) return;
        houseDefinitions = _houseDefinitions;
    }

}