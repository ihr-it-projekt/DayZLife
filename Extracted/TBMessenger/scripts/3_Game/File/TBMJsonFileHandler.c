class TBMJsonFileHandler<Class T>
{
	protected static ref JsonSerializer m_Serializer = new JsonSerializer;

	static void JsonSaveFile(string filename, T data)
	{
		string file_content;
		if(!m_Serializer) m_Serializer = new JsonSerializer;
		
		m_Serializer.WriteToString(data, false, file_content);
		
		FileHandle handle = OpenFile(filename, FileMode.WRITE);
		if (handle == 0)return;
		
		FPrint(handle, file_content);
		
		CloseFile(handle);
	}

}
