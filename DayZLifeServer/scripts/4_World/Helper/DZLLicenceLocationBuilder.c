class DZLLicenceLocationBuilder {

    static void Create() {
        DZLLicenceConfig config = DZLConfig.Get().licenceConfig;
		array<ref DZLLicencePosition> positions = config.positionOfLicencePoints;
		foreach(DZLLicencePosition position: positions) {
		    DZLLicenceLocationBuilder.CreatePositions(position, false, true, false);
		}
	}

	static PlayerBase CreatePositions(DZLLicencePosition position, bool isBanking, bool isLicence, bool isTrader) {
        PlayerBase player = DZLSpawnHelper.SpawnActionPoint(position.position, position.orientation, position.survivor, isBanking, isLicence, isTrader);

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
