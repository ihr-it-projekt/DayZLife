class DZLHouseConfig {
    string version = "7";
    int minCountOfCopsForRaid = 3;

    // deprecated remove 08.03.25
    private ref array<ref DZLJobHouseDefinition> copHouseConfigs = new array<ref DZLJobHouseDefinition>();
    private ref array<ref DZLJobHouseDefinition> medicHouseConfigs = new array<ref DZLJobHouseDefinition>();
    private ref array<ref DZLJobHouseDefinition> armyHouseConfigs = new array<ref DZLJobHouseDefinition>();
    // deprecated end

    private ref array<ref DZLJobHouseDefinitionCollection> jobHouseDefinitions = new array<ref DZLJobHouseDefinitionCollection>();

    DZLJobHouseDefinition GetJobHouseDefinition(notnull Building building) {
        array<ref DZLJobHouseDefinition> houseJobConfig = new array<ref DZLJobHouseDefinition>();

        foreach(DZLJobHouseDefinitionCollection collection: jobHouseDefinitions) {
            DZLJobHouseDefinition definition = collection.GetDefinitionByType(building.GetType());

            if(definition) return definition;
        }
        return null;
    }


}
