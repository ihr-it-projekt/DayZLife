class DZLBankingLocationBuilder {

    static void Create() {
        DZLBankingConfig bankingConfig = new DZLBankingConfig;
		array<ref DZLBankingPosition> positions = bankingConfig.positionOfBankingPoints;
		
		foreach(DZLBankingPosition position: positions) {
			PlayerBase player = DZLSpawnHelper.SpawnBankingPoint(position.position, position.orientation, position.survivor);
			
			if (!player) {
				continue;
			} 
			
			array<string> attachments = position.attachments;

            foreach(string attachment: attachments) {
                player.GetInventory().CreateInInventory(attachment);
            }
		}
	}
};