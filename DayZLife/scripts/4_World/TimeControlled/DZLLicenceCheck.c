class DZLLicenceCheck: RestCallback
{
    private static ref DZLLicenceCheck check;

    private DZLServerLicence licence;
    private ref JsonSerializer json = new JsonSerializer;
	private ref Timer checkTimer;
	private bool activeLicence = true;
	private static string serverUrl = "https://tools.dayz-life.net/";
	private ref RestApi restApi;
	private ref RestContext ctx;
	private int maxPlayers;

    static DZLLicenceCheck Get() {
        if (!check) {
            check = new DZLLicenceCheck;
        }

        return check;
    }

    void DZLLicenceCheck() {
        licence = DZLServerLicence.Get();
		checkTimer = new Timer();
		checkTimer.Run(6000, this, "Check", null, true);
		restApi = CreateRestApi();
		restApi.EnableDebug(DAY_Z_LIFE_DEBUG);

		string server = serverUrl;
//        if (DAY_Z_LIFE_DEBUG) {
//            server = "http:/127.0.0.1:8000/";
//        }

        ctx = restApi.GetRestContext(server);

		Check();
	}
	
	bool HasActiveLicence(PlayerIdentity player) {
		if (!activeLicence && player) {
			DZLSendMessage(player, "#server_admin_must_upgrade_licences_dayZ_life_mod_deactivate");
		}
		return activeLicence;
	}

	void Check() {
		int registeredPlayerCount = DZLDatabaseLayer.Get().GetPlayerIds().playerIdentities.Count();

		string key = licence.GetLicenceKey();
		if (licence.GetLicenceKey() == "") {
		    key = "free";
		}

        string url = "api/subscription/" + key + "/" + registeredPlayerCount;
        ctx.GET(this, url);
	}

	override void OnError(int errorCode){
		activeLicence = false;
		LogMessageDZL("DayZLife is disabled. Please be sure that you can reach: " + serverUrl + " from your server");
	};

	override void OnTimeout(){
	    activeLicence = false;
		LogMessageDZL("DayZLife is disabled. Please be sure that you can reach: " + serverUrl + " from your server");
	};

	override void OnSuccess(string data, int dataSize){
		if(dataSize > 0) {
		    string error;
		    DZLLicenceResponse response = new DZLLicenceResponse;
		    json.ReadFromString(response, data, error);
            activeLicence = 200 == response.status;
            maxPlayers = response.maxPlayer;
            if (!activeLicence) {
                LogMessageDZL(response.message);
            } else {
				if (response.message) {
					LogMessageDZL(response.message);
				}
                LogMessageDZL("Licence is valid");
            }
		}
	};
}

