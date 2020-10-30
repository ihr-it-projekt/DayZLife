class DZLBankingPosition: DZLLicencePosition
{
	bool raidIsEnabled = true;

    void DZLBankingPosition(vector position, vector orientation, string survivor, array<string> attachments) {
        Init(position, orientation, survivor, attachments);
    }

}