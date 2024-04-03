modded class DZLActionRaidDoors {

    override void OnEndServer(ActionData action_data) {
        BuildingBase building = BuildingBase.Cast(action_data.m_Target.GetObject());

        int doorIndex = building.GetDoorIndex(action_data.m_Target.GetComponentIndex());

        DZLRaidListener.StartRaidDoor(action_data.m_Player, building, doorIndex);
    }

};
