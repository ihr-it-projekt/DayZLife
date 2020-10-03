class DLClientConfig {
    private ref array<ref DLHouseConfig> houseConfigs;

    void DLClientConfig() {
        houseConfigs = new array<ref DLHouseConfig>;

        houseConfigs.Insert(new DLHouseConfig("1 0 0", "Land_House_1W03"));
    }


}