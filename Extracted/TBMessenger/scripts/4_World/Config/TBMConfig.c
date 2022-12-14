class TBMConfig
{
    private static ref TBMConfig config;

    static TBMConfig Get() {
        if (!config) {
            config = new TBMConfig;
        }

        return config;
    }

	ref TBMMessageConfig messageConfig;
	
	bool CanSendToAll(string playerId) {
		if (!messageConfig) return false;
		
		
		foreach(string id: messageConfig.canSendToAll) {
			if (playerId == id) {
				return true;
			}
		}
		
		return false;
	}

    void TBMConfig() {
        if (GetGame().IsServer()) {
			messageConfig = new TBMMessageConfig;
        }
    }
}
