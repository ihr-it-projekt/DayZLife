modded class ActionLockedDoors {

    override string GetText()
	{
		return "#unlock";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return false;
	}

	override void OnExecuteClient( ActionData action_data )
    {
    }

    override void OnExecuteServer( ActionData action_data )
    {
    }
}