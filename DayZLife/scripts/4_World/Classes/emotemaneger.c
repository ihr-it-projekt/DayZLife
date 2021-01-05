modded class EmoteManager
{
    override void KillPlayer(){
        if (GetGame().IsServer()) {
           m_Player.SetCanBeDestroyed(true);
        }

        super.KillPlayer();
    }
}
