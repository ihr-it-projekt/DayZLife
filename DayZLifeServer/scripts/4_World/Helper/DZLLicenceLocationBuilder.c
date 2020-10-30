class DZLLicenceLocationBuilder {

    static void Create() {
        DZLLicenceConfig config = new DZLLicenceConfig;
		array<ref DZLLicencePosition> positions = config.positionOfLicencePoints;
		foreach(DZLLicencePosition position: positions) {
		    DZLLicenceLocationBuilder.CreatePositions(position, false, true);
		}
	}

	static void CreatePositions(DZLLicencePosition position, bool isBanking, bool isLicence) {
        PlayerBase player = DZLSpawnHelper.SpawnActionPoint(position.position, position.orientation, position.survivor, isBanking, isLicence);

        if (!player) {
            return;
        }

        array<string> attachments = position.attachments;

        foreach(string attachment: attachments) {
            player.GetInventory().CreateInInventory(attachment);
        }
	}
};