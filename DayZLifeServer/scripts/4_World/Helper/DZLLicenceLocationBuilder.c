class DZLLicenceLocationBuilder {

    static void Create() {
		array<ref DZLLicencePosition> positions = DZLConfig.Get().licenceConfig.positionOfLicencePoints;
		foreach(DZLLicencePosition position: positions) {
		    DZLLicenceLocationBuilder.CreatePositions(position, false, true, false, false, false);
		}
	}

	static PlayerBase CreatePositions(DZLLicencePosition position, bool isBanking, bool isLicence, bool isTrader, bool isLoadOut, bool isGarage) {
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
};
