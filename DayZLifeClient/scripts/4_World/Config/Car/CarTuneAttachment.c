class CarTuneAttachment {
    string positionName;
    string type;

    void CarTuneAttachment(string _positionName, string _type) {
        this.positionName = _positionName;
        this.type = _type;
    }

    bool IsForSamePosition(CarTuneAttachment attachment) {
        return attachment.positionName == positionName;
    }

}