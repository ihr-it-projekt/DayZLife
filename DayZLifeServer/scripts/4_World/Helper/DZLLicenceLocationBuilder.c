class DZLLicenceLocationBuilder {

    static void Create() {
		array<ref DZLLicencePosition> positions = DZLConfig.Get().licenceConfig.positionOfLicencePoints;
		foreach(DZLLicencePosition position: positions) {
		    DZLLicenceLocationBuilder.CreatePositions(position, false, true, false, false);
		}
	}

	static PlayerBase CreatePositions(DZLLicencePosition position, bool isBanking, bool isLicence, bool isTrader, bool IsLoadOut) {
        PlayerBase player = DZLSpawnHelper.SpawnActionPoint(position.position, position.orientation, position.survivor, isBanking, isLicence, isTrader, IsLoadOut);

        if (!player) {
            return null;
        }

        array<string> attachments = position.attachments;

        foreach(string attachment: attachments) {
            player.GetInventory().CreateInInventory(attachment);
        }

        return player;
	}
};
