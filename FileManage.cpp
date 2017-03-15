
#include "stdafx.h"
#include "RawImageViewer.h"
#include "RawImageViewerDlg.h"
#include "resource.h"
#include "FileManage.h"


//----------------------------------------------------
// RIV_FileManage::RIV_FileManage()
// {
// 
// }

int RIV_FileManage::RIVFM_GetFilePath(CString &CStr_Path)
{
	CString CstrTemp;
	CString CStrNULL("");

	GetModuleFileName(NULL,ProgramPath.GetBufferSetLength (MAX_PATH+1),MAX_PATH);
	ProgramPath.ReleaseBuffer ();
	int nPos;
	nPos=ProgramPath.ReverseFind ('\\');
	ProgramPath=ProgramPath.Left (nPos);

	CString lpszFilter = _T("RGB File (*.rgb)|*.rgb|;YUV File (*.yuv)|*.yuv|;All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE,NULL,NULL,NULL,lpszFilter,NULL/*this*/);///TRUE为OPEN对话框，FALSE为SAVE AS对话框
	dlg.m_pOFN->lpstrInitialDir = ProgramPath;

	if(dlg.DoModal() == IDOK)
	{
		FilePathName = dlg.GetPathName();
		FileName = dlg.GetFileTitle();
		FileFullName = dlg.GetFileName();

		CStr_Path = FilePathName;

		// RIVFM_CloseFile(); // debug
		
		return RIV_OK;
	}
	else
	{
		CStr_Path = CStrNULL;
		
		FilePathName = CStrNULL;
		FileName = CStrNULL;
		FileFullName = CStrNULL;

		return RIV_FAIL;
	}
}

int RIV_FileManage::RIVFM_OpenFile()
{
	if (NULL == (inFile = _tfopen(FilePathName, _T("rb")))) // unicode 工程中用_tfopen 打开 CString 路径
	{
		AfxMessageBox(_T("错误：打开文件失败!"), MB_ICONQUESTION);
		// AfxMessageBox(FilePathName);
		return RIV_ERR;
	}

	fseek(inFile, 0, SEEK_SET);
	fseek(inFile, 0, SEEK_END);
	fsize = ftell(inFile);
	fseek(inFile, 0, SEEK_SET);

	return RIV_OK;
}

int RIV_FileManage::RIVFM_CloseFile()
{
	if (inFile)
	{
		fclose(inFile);
		inFile = NULL;
		fsize = 0;
	}
	return RIV_OK;
}

int RIV_FileManage::RIVFM_FillBuffer(unsigned char *tDstBuf, 
									 int tDstBufLen, 
									 int imgWidth, 
									 int imgHeight, 
									 CString imgType,
									 int frameNum)
{
	if (NULL == inFile)
	{
		//未打开文件
		AfxMessageBox(_T("错误：文件尚未正确打开！"), MB_ICONQUESTION);
		return RIV_ERR;
	}
	//--
	int dstDateLen = imgWidth * imgHeight * RGB32Len;
	if (dstDateLen > tDstBufLen)
	{
		return RIV_NOTENOUGHBUFF;
	}
	unsigned char *pu8dst = tDstBuf;

	//--
	int srcDateLen;
	unsigned char *pu8src = NULL;
	

	if (0 == imgType.CompareNoCase(_T("RGB24(bgr)")))
	{
		srcDateLen = imgWidth * imgHeight * RGB24Len;

		if (srcDateLen*(frameNum+1) > fsize)
		{
			// not enough data.
			AfxMessageBox(_T("错误：文件长度与图像尺寸及类型不符"), MB_ICONQUESTION);
			return RIV_NOTENOUGHDATE;
		}
		pu8src = new unsigned char[srcDateLen];
		fseek(inFile, srcDateLen*frameNum, SEEK_SET);
		fread(pu8src, 1, srcDateLen, inFile);


		unsigned char * pu8srct = pu8src;
		for(int i=0; i<imgHeight; i++)
		{
			for(int j=0; j<imgWidth; j++)
			{
				pu8dst[0] = pu8srct[0];
				pu8dst[1] = pu8srct[1];
				pu8dst[2] = pu8srct[2];
				pu8dst[3] = 0;

				pu8dst += RGB32Len;
				pu8srct += RGB24Len;
			}
		}

		delete []pu8src;
	}
	else if (0 == imgType.CompareNoCase(_T("RGB32(bgra)")))
	{
		// int rlen = fread(tDstBuf, 1, dstDateLen, inFile);
		srcDateLen = imgWidth * imgHeight * RGB32Len;

		if (srcDateLen*(frameNum+1) > fsize)
		{
			AfxMessageBox(_T("错误：文件长度与图像尺寸及类型不符"), MB_ICONQUESTION);
			return RIV_NOTENOUGHDATE;
		}
		pu8src = new unsigned char[srcDateLen];
		fseek(inFile, srcDateLen*frameNum, SEEK_SET);
		fread(pu8src, 1, srcDateLen, inFile);


		unsigned char * pu8srct = pu8src;
		for(int i=0; i<imgHeight; i++)
		{
			for(int j=0; j<imgWidth; j++)
			{
// 				pu8dst[0] = pu8srct[0];
// 				pu8dst[1] = pu8srct[1];
// 				pu8dst[2] = pu8srct[2];
// 				pu8dst[3] = 0;

				pu8dst[0] = pu8srct[2];
				pu8dst[1] = pu8srct[1];
				pu8dst[2] = pu8srct[0];
				pu8dst[3] = pu8srct[3];

				pu8dst += RGB32Len;
				pu8srct += RGB32Len;
			}
		}

		delete []pu8src;
	}
	else if (0 == imgType.CompareNoCase(_T("RGB32(rgba)")))
	{
		// int rlen = fread(tDstBuf, 1, dstDateLen, inFile);
		srcDateLen = imgWidth * imgHeight * RGB32Len;

		if (srcDateLen*(frameNum+1) > fsize)
		{
			AfxMessageBox(_T("错误：文件长度与图像尺寸及类型不符"), MB_ICONQUESTION);
			return RIV_NOTENOUGHDATE;
		}
		pu8src = new unsigned char[srcDateLen];
		fseek(inFile, srcDateLen*frameNum, SEEK_SET);
		fread(pu8src, 1, srcDateLen, inFile);


		unsigned char * pu8srct = pu8src;
		for(int i=0; i<imgHeight; i++)
		{
			for(int j=0; j<imgWidth; j++)
			{
				pu8dst[0] = pu8srct[0];
				pu8dst[1] = pu8srct[1];
				pu8dst[2] = pu8srct[2];
				pu8dst[3] = pu8srct[3];

				pu8dst += RGB32Len;
				pu8srct += RGB32Len;
			}
		}

		delete []pu8src;
	}
	else if (0 == imgType.CompareNoCase(_T("RGB565")))
	{
		// int rlen = fread(tDstBuf, 1, dstDateLen, inFile);
		srcDateLen = imgWidth * imgHeight * RGB565Len;

		if (srcDateLen*(frameNum+1) > fsize)
		{
			AfxMessageBox(_T("错误：文件长度与图像尺寸及类型不符"), MB_ICONQUESTION);
			return RIV_NOTENOUGHDATE;
		}
		pu8src = new unsigned char[srcDateLen];
		fseek(inFile, srcDateLen*frameNum, SEEK_SET);
		fread(pu8src, 1, srcDateLen, inFile);

		unsigned short *pu16src = (unsigned short *)pu8src;
		for(int i=0; i<imgHeight; i++)
		{
			for(int j=0; j<imgWidth; j++)
			{

				pu8dst[2] = ((pu16src[0]&0xF800)>>11)<<3;
				pu8dst[1] = ((pu16src[0]&0x07E0)>>5)<<2; 
				pu8dst[0] = ((pu16src[0]&0x001F))<<3; 

				pu8dst[3] = 0;

				pu8dst += RGB32Len;
				pu16src++;
			}
		}

		delete []pu8src;
	}
	else
	{
		AfxMessageBox(_T("错误：未知图像格式！"), MB_ICONQUESTION);
	}




}

//----------------------------------------------------











