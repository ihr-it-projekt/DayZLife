modded class DayZGame {
    override void OnRespawnEvent(int time)	{
        super.OnRespawnEvent(2);

        if(m_LoginTimeScreen)m_LoginTimeScreen.Hide();
    }
}