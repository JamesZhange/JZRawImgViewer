// ImageWind_Diag.cpp : implementation file
//

#include "stdafx.h"
#include "RawImageViewer.h"
#include "ImageWind_Diag.h"


// ImageWind_Diag dialog

IMPLEMENT_DYNAMIC(ImageWind_Diag, CDialog)

ImageWind_Diag::ImageWind_Diag(CWnd* pParent /*=NULL*/)
	: CDialog(ImageWind_Diag::IDD, pParent)
	, CreatFlag(0)
{

}

ImageWind_Diag::~ImageWind_Diag()
{
}

void ImageWind_Diag::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ImageWind_Diag, CDialog)
	ON_WM_GETMINMAXINFO()
	ON_WM_PAINT()
END_MESSAGE_MAP()


void ImageWind_Diag::PaintImgOnDiag(/*LPBYTE lpbits, int WIDTH,int HEIGHT*/)
{
	int i,j;

	CDC *pDC = this->GetDC();

	CDC *pMemDC = NULL;
	pMemDC = new CDC;
	pMemDC->CreateCompatibleDC(pDC);

	CBitmap *pBmp;
	pBmp = new CBitmap;
	pBmp->CreateCompatibleBitmap(pDC, imgWidth, imgHeight);
	pMemDC->SelectObject(pBmp);


	//	pMemDC->BitBlt(0, 0, WIDTH,HEIGHT,pDC, 0, 0, SRCCOPY);
	//	pBmp->GetBitmapBits(WIDTH*HEIGHT*4, lpbits);

	pBmp->SetBitmapBits(imgWidth*imgHeight*RGB32Len, imgData);

	pDC->BitBlt(0, 0, imgWidth, imgHeight, pMemDC,0, 0 , SRCCOPY );

	pBmp->DeleteObject();
	delete pBmp;
	delete pMemDC;

	ReleaseDC(pDC); 
}

/*
BOOL ImageWind_Diag::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style &= ~WS_MAXIMIZEBOX; 

	return CDialog::PreCreateWindow(cs);
}
*/

// ImageWind_Diag message handlers

void ImageWind_Diag::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: Add your message handler code here and/or call default

#define MINX 100
#define MINY 100
#define MAXX imgWidth
#define MAXY imgHeight

	if (CreatFlag)
	{
		// TODO: Add your message handler code here and/or call default
		CRect   rectWindow; 
		GetWindowRect(&rectWindow); 
		CRect   rectClient; 
		GetClientRect(&rectClient); 
		// get offset of toolbars, scrollbars, etc. 
		int   nWidthOffset   =   rectWindow.Width()   -   rectClient.Width(); 
		int   nHeightOffset   =   rectWindow.Height()   -   rectClient.Height(); 
		lpMMI-> ptMinTrackSize.x   =   MINX   +   nWidthOffset; 
		lpMMI-> ptMinTrackSize.y   =   MINY   +   nHeightOffset; 
		lpMMI-> ptMaxTrackSize.x   =   MAXX   +   nWidthOffset; 
		lpMMI-> ptMaxTrackSize.y   =   MAXY   +   nHeightOffset; 
	}

	CDialog::OnGetMinMaxInfo(lpMMI);
}

void ImageWind_Diag::OnPaint()
{
	// CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages

	CDialog::OnPaint();

	PaintImgOnDiag();
}
