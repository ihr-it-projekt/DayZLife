class DZLFileSerializer {

    string fileName;
    protected string path;

    void Init(string _path, string _fileName) {
        this.fileName = _fileName + ".bin";
        path = _path;
    }

    void Save() {
        Delete();

        FileSerializer serial = new FileSerializer();
        serial.Open(path + fileName, FileMode.WRITE);
        if(!serial.CanWrite()) return;

        Write(serial);

        serial.Close();
    }

    protected bool Load() {
        if(!FileExist(path + fileName)) return false;

        FileSerializer serial = new FileSerializer();
        serial.Open(path + fileName, FileMode.READ);
        if(!serial.CanRead()) return false;

        bool isOkay = Read(serial);

        serial.Close();

        return isOkay;
    }

    void Delete() {
        if(FileExist(path + fileName)) DeleteFile(path + fileName);
    }

    protected bool Read(FileSerializer ctx) {}
    protected void Write(FileSerializer ctx) {}

}