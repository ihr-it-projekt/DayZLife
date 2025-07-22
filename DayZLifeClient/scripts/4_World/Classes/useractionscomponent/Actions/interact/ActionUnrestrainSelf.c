modded class ActionUnrestrainSelf {
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        bool canUse = super.ActionCondition(player, target, item);
        if(!canUse) return false;
        if(DZLConfig.Get().crimeConfig.canUnrestrainSelf) return true;
        return false;
    }
}