modded class LoadingScreen
{
	void LoadingScreen(DayZGame game)
	{		
		m_ImageLogoMid.LoadImageFile(0, "DayZLifeClient/layout/MainMenu/DayZLifeLogo.edds");
		m_ImageLogoMid.SetImage(0);
		m_ImageLogoMid.SetFlags(WidgetFlags.SOURCEALPHA | WidgetFlags.BLEND | WidgetFlags.STRETCH);
		
		m_ImageLogoCorner.LoadImageFile(0, "DayZLifeClient/layout/MainMenu/DayZLifeLogo.edds");
		m_ImageLogoCorner.SetImage(0);
		m_ImageLogoCorner.SetFlags(WidgetFlags.SOURCEALPHA | WidgetFlags.BLEND | WidgetFlags.STRETCH);
		
		m_ModdedWarning.Show(false);
	}
};