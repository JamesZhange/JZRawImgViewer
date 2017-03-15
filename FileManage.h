#ifndef _RIV_FILEMANAGE_H_
#define _RIV_FILEMANAGE_H_

#include <stdlib.h>
#include <stdio.h>

class RIV_FileManage
{
public:
	LPBYTE pdata;

	RIV_FileManage()
	{
		inFile = NULL;
		pdata = NULL;
	}
	int RIVFM_GetFilePath(CString &CStr_Path);
	int RIVFM_OpenFile();
	int RIVFM_CloseFile();
	int RIVFM_FillBuffer(unsigned char *tDstBuf, int tDstBufLen, int imgWidth, int imgHeight, CString imgType, int frameNum);
private:
	FILE		*inFile;
	int			fsize;
	CString		ProgramPath; //本exe路径，作为起始路径
public:
	CString		FilePathName;
	CString		FileName;
	CString		FileFullName;
	
};

// class RIV_RawDateManage
// {
// public:
// 	int		ImageWidth;
// 	int		ImageHeight;
// 
// private:
// 	
// 	int		BufferLen;
// 	unsigned char *ImgBuffer;
// };


#endif // _RIV_FILEMANAGE_H_
