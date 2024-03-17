modded class DZLJobHouseDefinitionCollection {

    void MigrateToVersion6(string job, array<ref DZLJobHouseDefinition> _houseDefinitions) {
        if(jobId != job) return;
        houseDefinitions = _houseDefinitions;
    }

}