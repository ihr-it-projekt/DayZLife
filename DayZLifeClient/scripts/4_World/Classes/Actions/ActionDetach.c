modded class ActionDetach {
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if (target) {
            CarScript carScript = CarScript.Cast(target.GetParent());
            if (carScript && carScript.HasPlayerAccess(player)) {
                return super.ActionCondition(player, target, item);
            } else if (carScript) {
                return false;
            }
        }

        return super.ActionCondition(player, target, item);
    }
};
