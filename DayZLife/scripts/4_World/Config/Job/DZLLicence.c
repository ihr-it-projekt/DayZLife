class DZLLicence
{
	int price;
	string name;
	vector position;
	int range;
	string dependencyLicence;
	string id;


	void DZLLicence(int price, string name, vector position, int range, string dependencyLicence) {
		this.price = price;
		this.name = name;
		this.position = position;
		this.range = range;
		this.dependencyLicence = dependencyLicence;

		SetId();
	}

	bool HasCorrectId() {
	    return id == name + dependencyLicence + price.ToString() + position.ToString(false) + range.ToString();
	}

	void SetId() {
	    id = name + dependencyLicence + price.ToString() + position.ToString(false) + range.ToString();
	}
}