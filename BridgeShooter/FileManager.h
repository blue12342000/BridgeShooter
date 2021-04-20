//#pragma once
//#include "Singleton.h"
//#include <fstream>
//#include <string>
//#include <sstream>
//#include <map>
//
//using namespace std;
//
//class FileManager : public Singleton<FileManager>
//{
//private:
//	map<string, float> mDataSet;
//
//public:
//	bool ReadFile(string path);
//	
//	template<typename T>
//	T GetData(string key);
//
//	//HANDLE hFile;
//	//INT	nRead = 1234;
//	//DWORD dwTemp;
//	//hFile = (HANDLE)CreateFile("test.ini", GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//	//WriteFile(hFile, &nRead, sizeof(INT), &dwTemp, NULL);
//	//CloseHandle(hFile);
//
//};
//
//template<typename T>
//inline T FileManager::GetData(string key)
//{
//	if (mDataSet.find(key) != NULL)
//	{
//		return T();
//	}
//	
//}
