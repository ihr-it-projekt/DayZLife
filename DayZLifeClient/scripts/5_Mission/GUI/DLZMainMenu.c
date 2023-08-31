modded class MainMenu extends UIScriptedMenu
{
	override Widget Init()
	{		
		layoutRoot = super.Init();
		
		WrapSpacerWidget top = WrapSpacerWidget.Cast(layoutRoot.FindAnyWidget("top"));
		
		ImageWidget dayz_logo = ImageWidget.Cast(layoutRoot.FindAnyWidget("dayz_logo"));
		dayz_logo.LoadImageFile(0, "DayZLifeClient/layout/MainMenu/DayZLifeLogo.edds");
		dayz_logo.SetImage(0);
		dayz_logo.SetFlags(dayz_logo.GetFlags() | WidgetFlags.SOURCEALPHA | WidgetFlags.BLEND | WidgetFlags.STRETCH);
		
		m_ModdedWarning.Show(false);
		
		return layoutRoot;
	}
	
	override void LoadMods()
	{
		m_ModdedWarning.Show(false);
	}
}
