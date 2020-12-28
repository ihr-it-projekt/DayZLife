
modded class CarScript
{
    string lastDriverId = "";
    bool isSold = false;
   
    override void OnEngineStart() {
        super.OnEngineStart();
        Human player = CrewMember(DayZPlayerConstants.VEHICLESEAT_DRIVER);
        if (player) {
            lastDriverId = player.GetIdentity().GetId();
        }
	}
}
