
class DZL_CCTCar: CCTBase
{
	protected float m_MaximalActionDistanceSq;
	private bool mustHaveAccess;

	void DZL_CCTCar(bool _mustHaveAccess = true, float maximal_target_distance = UAMaxDistances.DEFAULT) {
		m_MaximalActionDistanceSq = maximal_target_distance * maximal_target_distance;
		mustHaveAccess = _mustHaveAccess;
	}

	override bool Can(PlayerBase player, ActionTarget target) {
		Object targetParent = target.GetParent();
		if (!targetParent || !player)	return false;

		CarScript carScript = CarScript.Cast(target.GetParent());
        if (!carScript || carScript.HasPlayerAccess(player) != mustHaveAccess) return false;

		vector playerHeadPos;
		MiscGameplayFunctions.GetHeadBonePos(player, playerHeadPos);

		float distanceRoot = vector.DistanceSq(targetParent.GetPosition(), player.GetPosition());
		float distanceHead = vector.DistanceSq(targetParent.GetPosition(), playerHeadPos);

		return (distanceRoot <= m_MaximalActionDistanceSq || distanceHead <= m_MaximalActionDistanceSq);
	}
};