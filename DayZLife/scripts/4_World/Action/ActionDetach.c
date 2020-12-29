modded class ActionDetach
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
		if (target) {
            CarScript carScript = CarScript.Cast(target.GetParent());
			if (carScript && carScript.HasPlayerAccess(player.GetIdentity().GetId())) {
                return super.ActionCondition(player, target, item);
			}
		}

        return super.ActionCondition(player, target, item);
    }
};
