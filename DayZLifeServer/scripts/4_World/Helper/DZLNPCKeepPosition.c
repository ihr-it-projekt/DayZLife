class DZLNPCKeepPosition
{
    EntityAI npc;
    vector position;
    vector orientation;

    void DZLNPCKeepPosition(EntityAI npc) {
        this.npc = npc;
        position = npc.GetPosition();
        orientation = npc.GetOrientation();
    }

    void FixPosition() {
        npc.SetPosition(position);
        npc.SetOrientation(orientation);
        npc.SetOrientation(npc.GetOrientation()); //Collision fix
        npc.Update();
    }

}
