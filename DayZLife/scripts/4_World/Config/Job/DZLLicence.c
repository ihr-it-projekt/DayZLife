class DZLLicence
{
	int price;
	string name;
	vector position;
	int range;
	string dependencyLicence;
	
	void DZLLicence(int price, string name, vector position, int range, string dependencyLicence = "") {
		this.price = price;
		this.name = name;
		this.position = position;
		this.range = range;
		this.dependencyLicence = dependencyLicence;
	}
}