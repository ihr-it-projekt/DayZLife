modded class DZLLicencePosition {

    void DZLLicencePosition(vector _position, vector _orientation) {
        Init(_position, _orientation);
    }

    protected void Init(vector _position, vector _orientation) {
        this.position = _position;
        this.orientation = _orientation;
    }
}
