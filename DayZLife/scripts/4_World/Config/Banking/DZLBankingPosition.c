class DZLBankingPosition: DZLLicencePosition
{
	bool raidIsEnabled = true;

    void DZLBankingPosition(vector position, vector orientation, string type) {
        Init(position, orientation, type);
    }

}