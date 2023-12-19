class CarTuneAttachment {
    string positionName;
    string type;

    void CarTuneAttachment(string positionName, string type) {
        this.positionName = positionName;
        this.type = type;
    }

    bool IsForSamePosition(CarTuneAttachment attachment) {
        return attachment.positionName == positionName;
    }

}