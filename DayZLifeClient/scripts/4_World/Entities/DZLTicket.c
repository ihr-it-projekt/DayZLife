class DZLTicket: DZLIdModel
{
	int value;
	string reason;
	ref DZLDate creationDate;

	void DZLTicket(int value, string reason) {
		this.value = value;
		this.reason = reason;
		creationDate = new DZLDate;
		SetId();
	}
}
