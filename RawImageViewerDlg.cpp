// RawImageViewerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RawImageViewer.h"
#include "RawImageViewerDlg.h"
#include "ImageWind_Diag.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CRawImageViewerDlg dialog




CRawImageViewerDlg::CRawImageViewerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRawImageViewerDlg::IDD, pParent)
	, CStr_Path_text(_T(""))
	, ImageWidth(0)
	, ImageHeight(0)
	, statureFlag(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRawImageViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, EDIT_FILEPATH, CStr_Path_text);
	DDX_Text(pDX, EDIT_WIDTH, ImageWidth);
	DDX_Text(pDX, EDIT_HEIGHT, ImageHeight);
	DDX_Control(pDX, COMBO_FILETYPE, ComboBox_Type);
}

BEGIN_MESSAGE_MAP(CRawImageViewerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(OpenFile_BUTTON, &CRawImageViewerDlg::OnBnClickedOpenButton)
	ON_BN_CLICKED(IDOK, &CRawImageViewerDlg::OnBnClickedOk)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(COMBO_FILETYPE, &CRawImageViewerDlg::OnCbnSelchangeFiletype)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CRawImageViewerDlg message handlers

BOOL CRawImageViewerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	// TODO: Add extra initialization here
	GetDlgItem(EDIT_FILEPATH)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);


	//----- combobox ------
	pstrTypeName[0] = (LPCTSTR)_T("RGB32(bgra)");
	pstrTypeName[1] = (LPCTSTR)_T("RGB32(rgba)");
	pstrTypeName[2] = (LPCTSTR)_T("RGB24(bgr)");
	pstrTypeName[3] = (LPCTSTR)_T("RGB565");

	for (int i=0; i<YTPYNUMBER; i++)
	{
		ComboBox_Type.AddString((LPCTSTR)pstrTypeName[i]);
	}

	printf("argc: %d\n", __argc);
	// char   *svCmdLine = GetCommandLine();
	// printf("%s\n", GetCommandLine());

	


	if (__argc >= 2)
	{
		// printf("%s\n", __wargv[1]);
 		// AfxMessageBox(__wargv[0], MB_ICONQUESTION); 
 		// AfxMessageBox(__wargv[1], MB_ICONQUESTION); 

		// AfxMessageBox(__wargv[1], MB_ICONQUESTION); 

		rivFManager.FilePathName = (CString)(__wargv[1]);

		// AfxMessageBox(rivFManager.FilePathName, MB_ICONQUESTION); 

		rivFManager.RIVFM_CloseFile(); // 关闭原有文件
		if (RIV_OK != rivFManager.RIVFM_OpenFile())// 打开新文件
		{
			return FALSE;
		}

		CStr_Path_text = rivFManager.FilePathName;
		ImageWidth = 0;
		ImageHeight = 0;

		UpdateData(FALSE);//更新控件数值
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		GetDlgItem(EDIT_FILEPATH)->EnableWindow(FALSE);

		CString CstrTemp = _T("选择类型");
		GetDlgItem(TXT_USER_INFOR)->SetWindowText(CstrTemp);

	}


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRawImageViewerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRawImageViewerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRawImageViewerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CRawImageViewerDlg::OnBnClickedOpenButton()
{
	int res;
	CString CstrTemp;

	GetDlgItem(EDIT_FILEPATH)->EnableWindow(TRUE);

	res = rivFManager.RIVFM_GetFilePath(CStr_Path_text);
	if (RIV_OK == res)
	{
		rivFManager.RIVFM_CloseFile(); // 关闭原有文件
		if (RIV_OK != rivFManager.RIVFM_OpenFile())// 打开新文件
		{
			return;
		}

		UpdateData(FALSE);//更新控件数值
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		GetDlgItem(EDIT_FILEPATH)->EnableWindow(FALSE);

		CstrTemp = _T("选择类型");
		GetDlgItem(TXT_USER_INFOR)->SetWindowText(CstrTemp);

	}
	else
	{
		ImageHeight = 0;
		ImageWidth = 0;

		UpdateData(FALSE);//更新控件数值

		// GetDlgItem(IDOK)->EnableWindow(FALSE);
		GetDlgItem(EDIT_FILEPATH)->EnableWindow(FALSE);
		
		CstrTemp = _T("打开文件");
		GetDlgItem(TXT_USER_INFOR)->SetWindowText(CstrTemp);
		GetDlgItem(IDOK)->EnableWindow(FALSE);
	}

	
}


void CRawImageViewerDlg::OnBnClickedOk()
{
	//--- 获取信息 ----
	CString strCobType;
	ComboBox_Type.GetWindowText(strCobType);

	UpdateData(TRUE); // 获取宽高
	
	// -- 容错判断 ---
	if ((0 == ImageWidth) || (0 == ImageHeight))
	{
		AfxMessageBox(_T("图像宽高设置有误！"), MB_ICONQUESTION);
		return;
	}
	// type判断？
	if ((0 != strCobType.CompareNoCase(_T("RGB24(bgr)")))
	 && (0 != strCobType.CompareNoCase(_T("RGB32(bgra)")))
	 && (0 != strCobType.CompareNoCase(_T("RGB32(rgba)")))
	 && (0 != strCobType.CompareNoCase(_T("RGB565"))))
	{
		AfxMessageBox(_T("未选择图像格式！"), MB_ICONQUESTION);
		return;
	}

	int bitmapSize = ImageWidth*ImageHeight*RGB32Len;

	// LPBYTE data;
	if (rivFManager.pdata)
	{
		delete []rivFManager.pdata;
		rivFManager.pdata = NULL;
	}
	rivFManager.pdata = new BYTE[bitmapSize];

	// 读取数据
	rivFManager.RIVFM_FillBuffer(rivFManager.pdata, bitmapSize, ImageWidth, ImageHeight, strCobType, 0);


	// 创建窗口
	if(imgShowWind.m_hWnd)
		imgShowWind.DestroyWindow();//销毁先前的窗口

	imgShowWind.Create(IDD_IMAGEWIND_DIAG, GetDesktopWindow());//重新创建

	CRect   rectWindow; 
	imgShowWind.GetWindowRect(&rectWindow); 
	CRect   rectClient; 
	imgShowWind.GetClientRect(&rectClient); 
	// get offset of toolbars, scrollbars, etc. 
	int nWidthOffset = rectWindow.Width() - rectClient.Width(); 
	int nHeightOffset = rectWindow.Height() - rectClient.Height(); 

	// imgWnd.SetWindowPos(&wndTopMost, 100, 20, INFILEWIDTH, INFILEHEIGHT, NULL);
	imgShowWind.SetWindowPos(NULL, 100, 20, ImageWidth+nWidthOffset, ImageHeight+nHeightOffset, SWP_NOOWNERZORDER);
	// imgWnd.SetWindowPos(&wndTopMost, 100, 20, 100, 100, NULL);

	imgShowWind.SetWindowText((LPCTSTR)rivFManager.FilePathName);

	imgShowWind.ShowWindow(SW_SHOW);

	imgShowWind.CreatFlag = 1;


	// 
	//---
	imgShowWind.imgData = rivFManager.pdata;
	imgShowWind.imgWidth = ImageWidth;
	imgShowWind.imgHeight = ImageHeight;
	imgShowWind.PaintImgOnDiag();

}

void CRawImageViewerDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	if (rivFManager.pdata)
	{
		delete []rivFManager.pdata;
		rivFManager.pdata = NULL;
	}
}

void CRawImageViewerDlg::OnCbnSelchangeFiletype()
{
	CString CStrNULL("");

	// TODO: Add your control notification handler code here
	if (rivFManager.FileName != CStrNULL)
	{
		CString CstrTemp = _T("设置宽高");
		GetDlgItem(TXT_USER_INFOR)->SetWindowText(CstrTemp);
		GetDlgItem(IDOK)->EnableWindow(TRUE);
	}
}

void CRawImageViewerDlg::OnDropFiles(HDROP hDropInfo)
{

	if(imgShowWind.m_hWnd)
		imgShowWind.DestroyWindow();//销毁先前的窗口

	// TODO: Add your message handler code here and/or call default
	TCHAR  *lpszFileName = new TCHAR[512];

	UINT nChars = DragQueryFile(hDropInfo,0,(LPWSTR)(&lpszFileName[0]),512);

	rivFManager.FilePathName = lpszFileName;

	rivFManager.RIVFM_CloseFile(); // 关闭原有文件
	if (RIV_OK != rivFManager.RIVFM_OpenFile())// 打开新文件
	{
		return;
	}

	CStr_Path_text = rivFManager.FilePathName;
	ImageWidth = 0;
	ImageHeight = 0;

	UpdateData(FALSE);//更新控件数值
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(EDIT_FILEPATH)->EnableWindow(FALSE);

	CString CstrTemp = _T("选择类型");
	GetDlgItem(TXT_USER_INFOR)->SetWindowText(CstrTemp);

	delete   []lpszFileName;

	::DragFinish (hDropInfo);       //释放内存



	// CDialog::OnDropFiles(hDropInfo);
}
