class DZLBankingPosition
{
    vector position;
	vector orientation
    string survivor;
    array<string> attachments;

    void DZLBankingPosition(vector position, vector orientation, string survivor, array<string> attachments) {
        this.position = position;
        this.orientation = orientation;
        this.survivor = survivor;
        this.attachments = attachments;
    }

}