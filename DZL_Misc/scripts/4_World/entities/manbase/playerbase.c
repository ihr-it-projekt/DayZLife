modded class PlayerBase extends ManBase
{
    override void Init()
    {
        if ( !GetGame().IsServer() || !GetGame().IsMultiplayer() ) 
		{
            DayzPlayerItemBehaviorCfg     toolsOneHanded = new DayzPlayerItemBehaviorCfg;
            toolsOneHanded.SetToolsOneHanded();

            DayzPlayerItemBehaviorCfg     twoHanded = new DayzPlayerItemBehaviorCfg;
            twoHanded.SetTwoHanded();

            DayzPlayerItemBehaviorCfg     fireArmsItemBehaviour = new DayzPlayerItemBehaviorCfg;
            fireArmsItemBehaviour.SetFirearms();

            DayzPlayerItemBehaviorCfg     heavyItemBehaviour = new DayzPlayerItemBehaviorCfg;
            heavyItemBehaviour.SetHeavyItems();

            DayzPlayerItemBehaviorCfg   pistolItemBehaviour = new DayzPlayerItemBehaviorCfg;
            pistolItemBehaviour.SetPistols();
			
			GetDayZPlayerType().AddItemInHandsProfileIK("DZL_Cement", "dz/anims/workspaces/player/player_main/weapons/player_main_2h_extinguisher.asi", twoHanded, "dz/anims/anm/player/ik/two_handed/mountain_g.anm");
		}
        super.Init();
    }
}
