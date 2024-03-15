class DZLTicket: DZLIdModel {
    int value;
    string reason;
    ref DZLDate creationDate;

    void DZLTicket(int _value, string _reason) {
        this.value = _value;
        this.reason = _reason;
        creationDate = new DZLDate;
        SetId();
    }
};