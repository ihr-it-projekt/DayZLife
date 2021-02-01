class DZLNPCKeepPosition
{
    EntityAI npc;
    vector position;
    vector orientation;

    void DZLNPCKeepPosition(EntityAI npc) {
        if (!npc) return;
        this.npc = npc;
        position = npc.GetPosition();
        orientation = npc.GetOrientation();
    }

    void FixPosition() {
        if (!npc) return;
        npc.SetPosition(position);
        npc.SetOrientation(orientation);
        npc.SetOrientation(npc.GetOrientation()); //Collision fix
        npc.Update();
    }

}
