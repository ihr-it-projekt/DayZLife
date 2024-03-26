modded class DZLActionLicenceCrafting: ActionInteractBase {

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if(!super.ActionCondition(player, target, item)) return false;

        DZLCraftLicence licence = player.GetLicenceByPosition();

        string message = player.CanUseLicence(licence);
        if(!message) return true;

        DZLSendMessage(player.GetIdentity(), message);
        return false;
    }
};
