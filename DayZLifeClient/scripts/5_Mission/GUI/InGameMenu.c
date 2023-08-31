modded class InGameMenu
{

	override protected void GameRespawn(bool random) {
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		player.willDie = true;
		player.medicHelpMenuWasShown = true;
		
		super.GameRespawn(random);	
	}
	
}
