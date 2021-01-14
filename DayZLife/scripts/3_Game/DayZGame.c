modded class DayZGame
{

    override void EnterLoginTime(UIMenuPanel parent) {}
	
	
	override void OnRespawnEvent(int time)	{	
		if (GetPlayer()) GetPlayer().StopDeathDarkeningEffect();
		
		PPEffects.SetDeathDarkening(1);
	}
}
