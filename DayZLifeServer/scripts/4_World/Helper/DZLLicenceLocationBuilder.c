class DZLLicenceLocationBuilder
 {
    protected ref array<ref DZLNPCKeepPosition> npcs;

    void DZLLicenceLocationBuilder() {
        Init();
    }

    void Init() {
        npcs = new array<ref DZLNPCKeepPosition>;
    }

    void Create() {
		array<ref DZLLicencePosition> positions = DZLConfig.Get().licenceConfig.positionOfLicencePoints;
		foreach(DZLLicencePosition position: positions) {
		    npcs.Insert(new DZLNPCKeepPosition(CreatePositions(position)));
		}
	}

	EntityAI CreatePositions(DZLLicencePosition position) {
        Object object = DZLSpawnHelper.SpawnActionPoint(position.position, position.orientation, position.survivor);

        if (!object) {
            return null;
        }
		
		EntityAI entity = EntityAI.Cast(object);
		
		if (!entity) return null;

        array<string> attachments = position.attachments;

        foreach(string attachment: attachments) {
            entity.GetInventory().CreateInInventory(attachment);
        }

        return entity;
	}

	void CheckPosition() {
        foreach(DZLNPCKeepPosition npc: npcs) {
            npc.FixPosition();
        }
	}
};
