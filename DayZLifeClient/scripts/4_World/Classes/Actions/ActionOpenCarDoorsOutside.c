modded class ActionOpenCarDoorsOutside {
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item ) {
        CarScript carScript = CarScript.Cast(target.GetParent());
        if ((carScript && carScript.HasPlayerAccess(player)) || (player && player.IsInVehicle())) {
            return super.ActionCondition(player, target, item);
        }

        return false;
    }
};
