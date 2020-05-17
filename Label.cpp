// Label.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "Label.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLabel

CLabel::CLabel()
{
//	m_font.CreatePointFont (160,"Arial Black");
	m_brBackGrndBrush.CreateSysColorBrush (COLOR_WINDOW);
	m_clrRed=RGB(255,0,0);
	m_clrBlue=RGB(0,0,255);
	m_clrGreen=RGB(0,150,0);
	m_clrBlack=RGB(0,0,0);
	m_clrText=m_clrBlack;;
}

CLabel::~CLabel()
{
m_brBackGrndBrush.DeleteObject ();
}


BEGIN_MESSAGE_MAP(CLabel, CStatic)
	//{{AFX_MSG_MAP(CLabel)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLabel message handlers
















 void CLabel::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect rc(0,0,0,0);
	CFont* oldFont=dc.SelectObject (GetFont());
	dc.SetBkMode (TRANSPARENT);
/*	COLORREF clrLabel=::GetSysColor(COLOR_BTNFACE);
	dc.SetTextColor( clrLabel );
*/
	CString oldText;
	GetWindowText(oldText);
	dc.SetTextColor( m_clrText );
	dc.DrawText (oldText,&rc,DT_CALCRECT);
	
	dc.DrawText (oldText,rc,DT_LEFT|DT_END_ELLIPSIS);
	
	
	//dc.DrawText (m_szText,rc,DT_CALCRECT);
	
	//dc.DrawText (m_szText,rc,DT_LEFT|DT_END_ELLIPSIS);
	
  	dc.SelectObject(oldFont);
 } 

void CLabel::SetLabelFont(CFont* pNewFont)
{
	
	SetFont(pNewFont);
	UpdateControl();
	//m_font.Attach (newFont.Detach ());
}
void CLabel::SetLabelFont(LPCTSTR szFontName,int nSize)
{
	CFont font;
	font.CreatePointFont (nSize*10,szFontName,NULL);
	SetFont(&font);
	UpdateControl();
}
void CLabel::SetColor(COLORREF newColor)
{
m_clrText=newColor;
UpdateControl();
}


void CLabel::SetText(const CString& Text)
{
	if(::IsWindow(m_hWnd))
	{
	SetWindowText(Text);
	UpdateControl();
	}
	
}




void CLabel::UpdateControl()
{
 CRect rect;
 GetWindowRect(&rect);
 	
 RedrawWindow();
 GetParent()->ScreenToClient (&rect);
 GetParent()->InvalidateRect (&rect);
 GetParent()->UpdateWindow ();

}



int CLabel::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	ModifyStyleEx(0, WS_EX_TRANSPARENT);   

	return 0;
}

HBRUSH CLabel::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	if (nCtlColor == CTLCOLOR_STATIC )
	{
		// установить отмену отрисовки фона перед изменениями
	//	pDC->SetBkMode(TRANSPARENT);
		// вернуть пустую кисть для любого закрашивания
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	
	// TODO: Return a non-NULL brush if the parent's handler should not be called
	return NULL;

}




