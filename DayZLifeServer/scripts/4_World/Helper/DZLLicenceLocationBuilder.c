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
		    npcs.Insert(new DZLNPCKeepPosition(CreatePositions(position, false, true, false, false, false)));
		}
	}

	PlayerBase CreatePositions(DZLLicencePosition position, bool isBanking, bool isLicence, bool isTrader, bool isLoadOut, bool isGarage) {
        PlayerBase player = DZLSpawnHelper.SpawnActionPoint(position.position, position.orientation, position.survivor, isBanking, isLicence, isTrader, isLoadOut, isGarage);

        if (!player) {
            return null;
        }

        array<string> attachments = position.attachments;

        foreach(string attachment: attachments) {
            player.GetInventory().CreateInInventory(attachment);
        }

        return player;
	}

	void CheckPosition() {
        foreach(DZLNPCKeepPosition npc: npcs) {
            npc.FixPosition();
        }
	}
};
