modded class ActionDefibrilateTarget
{

	override void OnFinishProgressServer(ActionData action_data){
		super.OnFinishProgressServer(action_data);
		
		DZLEmergencies emergencies = DZLDatabaseLayer.Get().GetEmergencies();

		PlayerBase target = PlayerBase.Cast(action_data.m_Target.GetObject());

		if(target && emergencies.HasEmergency(target.GetIdentity().GetId())) {
		    string targetId = target.GetIdentity().GetId();
		    emergencies.Remove(targetId);
		    DZLDatabaseLayer.Get().GetPlayer(targetId).AddMoneyToPlayerBank(DZLConfig.Get().medicConfig.priceMedicHeal * -1);
		    DZLDatabaseLayer.Get().GetPlayer(action_data.m_Player.GetIdentity().GetId()).AddMoneyToPlayerBank(DZLConfig.Get().medicConfig.priceMedicHeal);
		}
	}
}
