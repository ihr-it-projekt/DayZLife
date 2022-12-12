class TBLOConfig
{
    private static ref TBLOConfig config;

    ref TBLOLoadOuts loadOuts;

    static TBLOConfig Get() {
        if (!config) {
            config = new TBLOConfig;
        }

        return config;
    }

    void TBLOConfig() {
        if (GetGame().IsServer()) {
            loadOuts = new TBLOLoadOuts;
        }
    }
}
