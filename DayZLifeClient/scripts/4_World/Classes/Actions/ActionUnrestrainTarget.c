modded class ActionUnrestrainTarget: ActionContinuousBase
{
	override void OnFinishProgressServer( ActionData action_data )
	{
		PlayerBase player_target = PlayerBase.Cast(action_data.m_Target.GetObject());
		PlayerBase player_source = PlayerBase.Cast(action_data.m_Player);
		
		if (CanReceiveAction(action_data.m_Target) && player_target.IsRestrained())
		{
			EntityAI unrestraining_tool = action_data.m_MainItem;
			EntityAI restraining_item = player_target.GetItemInHands();
	
			player_target.SetRestrained(false);
			
			
			//Damage applied to tool
			CachedObjectsArrays.ARRAY_STRING.Clear();
			
			restraining_item.ConfigGetTextArray( "CanBeUnrestrainedBy", CachedObjectsArrays.ARRAY_STRING );
			restraining_item.ConfigGetFloatArray( "CanBeUnrestrainedByDMG", CachedObjectsArrays.ARRAY_FLOAT );
			
			string item_in_hands_name = unrestraining_tool.GetType();
			float damageToTool = 0;
			
			for(int i = 0; i < CachedObjectsArrays.ARRAY_STRING.Count(); i++)
			{
				string class_name = CachedObjectsArrays.ARRAY_STRING.Get(i);
				if(	GetGame().IsKindOf(item_in_hands_name, class_name) )
				{
					damageToTool = CachedObjectsArrays.ARRAY_FLOAT.Get(i/2);
					break;
				}
			}
			
			MiscGameplayFunctions.DealAbsoluteDmg(action_data.m_MainItem, damageToTool);
			//---------------------------
			
			MiscGameplayFunctions.TransformRestrainItem(restraining_item, unrestraining_tool, player_source, player_source);
			
			action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
		}
	}
}