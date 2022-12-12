class TBLO_CCTActionObject: CCTBase
{
    protected float m_MaximalActionDistanceSq;

	void TBLO_CCTActionObject(float maximal_target_distance = UAMaxDistances.DEFAULT) {
		m_MaximalActionDistanceSq = maximal_target_distance * maximal_target_distance;
	}

    override bool Can(PlayerBase player, ActionTarget target) {
		if(!target) return false;
        if(!target.GetObject()) return false;
        TBLOLoadoutActionObject objectTarget = TBLOLoadoutActionObject.Cast(target.GetObject());
        if (!objectTarget) return false;

		vector playerHeadPos;
		MiscGameplayFunctions.GetHeadBonePos(player, playerHeadPos);

		float distanceRoot = vector.DistanceSq(objectTarget.GetPosition(), player.GetPosition());
		float distanceHead = vector.DistanceSq(objectTarget.GetPosition(), playerHeadPos);

		return (distanceRoot <= m_MaximalActionDistanceSq || distanceHead <= m_MaximalActionDistanceSq);
	}
}