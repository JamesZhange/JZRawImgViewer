#pragma once


// ImageWind_Diag dialog

class ImageWind_Diag : public CDialog
{
	DECLARE_DYNAMIC(ImageWind_Diag)

public:
	ImageWind_Diag(CWnd* pParent = NULL);   // standard constructor
	virtual ~ImageWind_Diag();

// Dialog Data
	enum { IDD = IDD_IMAGEWIND_DIAG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

public:
	LPBYTE imgData;
	int imgWidth;
	int imgHeight;
	void PaintImgOnDiag(/*LPBYTE data, int WIDTH,int HEIGHT*/);

	int CreatFlag;

	DECLARE_MESSAGE_MAP()
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnPaint();
};
