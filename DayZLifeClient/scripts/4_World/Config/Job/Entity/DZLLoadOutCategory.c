class DZLLoadOutCategory
{
    string name;
    ref array<ref DZLLoadOutType> items;

     void DZLLoadOutCategory(string name, array<ref DZLLoadOutType> items) {
        this.name = name;
        this.items = items;
     }

}
