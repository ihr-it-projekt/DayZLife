class DZLBankingLocationBuilder {

    void Create(DZLBankingConfig bankingConfig) {
		array<ref DZLBankingPosition> positions = bankingConfig.positionOfBankingPoints;
		
		foreach(DZLBankingPosition position: positions) {
			DZLSpawnHelper.SpawnBankingPoint(position.position, position.orientation, position.survivor);
			
			array<string> attachments = position.attachments;
			
			foreach(string attachment: attachments) {
				EntityAI itemClothing = player.FindAttachmentBySlotName("Body");
				if (itemClothing){
					itemClothing.GetInventory().CreateInInventory(attachment);
				}
			}
		}
	}
};