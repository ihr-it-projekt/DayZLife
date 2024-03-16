class DZLJobHouseDefinitionCollection {
    string jobId;
    ref array<ref DZLJobHouseDefinition> houseDefinitions = new array<ref DZLJobHouseDefinition>();

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

    void MigrateToVersion6(string job, array<ref DZLJobHouseDefinition> _houseDefinitions) {
        if(jobId != job) return;
        houseDefinitions = _houseDefinitions;
    }

}