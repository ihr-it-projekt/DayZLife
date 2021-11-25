modded class DayZGame
{

    override void EnterLoginTime(UIMenuPanel parent) {}
	
	
	override void OnRespawnEvent(int time)	{	
		if (GetPlayer())
			GetPlayer().StopDeathDarkeningEffect();
		PPERequesterBank.GetRequester(PPERequester_DeathDarkening).Start(new Param1<float>(1.0));
	}
}
