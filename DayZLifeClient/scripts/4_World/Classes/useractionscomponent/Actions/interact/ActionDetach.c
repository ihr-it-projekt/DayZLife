modded class ActionDetach {
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if(!super.ActionCondition(player, target, item)) return false;
        if(!target) return false;

        CarScript carScript = CarScript.Cast(target.GetParent());
        if(carScript) return carScript.HasPlayerAccess(player);

        return true;
    }
};
