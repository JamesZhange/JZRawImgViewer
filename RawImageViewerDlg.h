// RawImageViewerDlg.h : header file
//

#pragma once

#include "FileManage.h"
#include "afxwin.h"

#include "ImageWind_Diag.h"

#define YTPYNUMBER 4


// CRawImageViewerDlg dialog
class CRawImageViewerDlg : public CDialog
{
// Construction
public:
	CRawImageViewerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_RAWIMAGEVIEWER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	CString				CStr_Path_text;
	int					ImageWidth;
	int					ImageHeight;
	RIV_FileManage		rivFManager;
	// RIV_RawDateManage	rivDManager;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
public:
	afx_msg void OnBnClickedOpenButton();
	afx_msg void OnBnClickedOk();
	afx_msg void reShowImageDate(LPBYTE data, int imgWidth, int imgHeight);

private:
	int				BufferLen;
	unsigned char	*ImgBuffer;
public:
	LPCTSTR		pstrTypeName[YTPYNUMBER];
	CComboBox	ComboBox_Type;

	ImageWind_Diag	imgShowWind;

private:
	int statureFlag;
	
public:
	afx_msg void OnCbnSelchangeFiletype();
	afx_msg void OnDropFiles(HDROP hDropInfo);
};
