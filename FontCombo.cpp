// FontCombo.cpp : implementation file
//

#include "stdafx.h"
#include "userthreads.h"
#include "FontCombo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
class CFontCombo;
/////////////////////////////////////////////////////////////////////////////
// CFontCombo
static int CALLBACK EnumFontsProc(
  CONST LOGFONT *lplf,     // logical-font data
  CONST TEXTMETRIC *lptm,  // physical-font data
  DWORD dwType,            // font type
  LPARAM lpData            // application-defined data
)
{
//CStringList* lst=reinterpret_cast<CStringList*>(lpData);
	
	CFontCombo* pThis=(CFontCombo*)lpData;
//pThis->m_lstFontNames.AddTail(lplf->lfFaceName);
	pThis->AddString (lplf->lfFaceName);
	return TRUE;
}
CFontCombo::CFontCombo()
{
//m_font.CreatePointFont (100,"Microsoft Sans Serif");
	
}

CFontCombo::~CFontCombo()
{
	//::DeleteObject((HFONT)m_font);
}


BEGIN_MESSAGE_MAP(CFontCombo, CComboBox)
	//{{AFX_MSG_MAP(CFontCombo)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, OnSelchange)
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFontCombo message handlers







void CFontCombo::PopulateFont()
{
	CClientDC dc(this);
	::EnumFontFamilies(dc.GetSafeHdc(),NULL,(FONTENUMPROC)EnumFontsProc,
		(LPARAM)this);
	/*POSITION pos = m_lstFontNames.GetHeadPosition();
	while( pos != NULL )
	{
		CString szCmp = static_cast<CString>(m_lstFontNames.GetNext( pos ));
		
		AddString (szCmp);
	}*/
	SetCurSel(0);
	
//	SetFont(&m_font);
}

void CFontCombo::PopulFontSize()
{
//	SetFont(&m_font);
	for(int i=4;i<39;i++)
	{
		TCHAR buff[256];
		_ltot(i*2,buff,10);
		AddString (buff);
	}
}

void CFontCombo::MeasureItem(LPMEASUREITEMSTRUCT lpMIS) 
{
	// TODO: Add your code to determine the size of specified item
	lpMIS->itemHeight =16;
	lpMIS->itemWidth =250;
}



void CFontCombo::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	ASSERT(lpDrawItemStruct->CtlType == ODT_COMBOBOX);
//	LPCTSTR lpszText;
	CString lpszText;
	GetLBText(lpDrawItemStruct->itemID,lpszText);//(LPCTSTR) lpDrawItemStruct->itemData;
	if(lpDrawItemStruct->itemID !=-1)
	{
		ASSERT(lpszText != "");
		CDC dc;
		
		dc.Attach(lpDrawItemStruct->hDC);
		
		// Save these value to restore them when done drawing.
		COLORREF crOldTextColor = dc.GetTextColor();
		COLORREF crOldBkColor = dc.GetBkColor();
		
		// If this item is selected, set the background color 
		// and the text color to appropriate values. Erase
		// the rect by filling it with the background color.
		if ((lpDrawItemStruct->itemAction | ODA_SELECT) &&
			(lpDrawItemStruct->itemState  & ODS_SELECTED))
		{
			dc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
			dc.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
			dc.FillSolidRect(&lpDrawItemStruct->rcItem, ::GetSysColor(COLOR_HIGHLIGHT));
		}
		else
			dc.FillSolidRect(&lpDrawItemStruct->rcItem, crOldBkColor);
		
		// Draw the text.
		CFont font;
		font.CreatePointFont (100,lpszText);
		CFont* oldFont=dc.SelectObject(&font);
		dc.DrawText(
			lpszText,
			_tcslen(lpszText),
			&lpDrawItemStruct->rcItem,
			DT_LEFT|DT_SINGLELINE|DT_VCENTER);
		
		// Reset the background color and the text color back to their
		// original values.
		dc.SetTextColor(crOldTextColor);
		dc.SetBkColor(crOldBkColor);
		dc.SelectObject(oldFont);
		dc.Detach();
	}
	
	
}



BOOL CFontCombo::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style |=CBS_OWNERDRAWFIXED;
	return CComboBox::PreCreateWindow(cs);
}

void CFontCombo::OnSelchange() 
{
	// TODO: Add your control notification handler code here
	CWnd* pWnd=AfxGetMainWnd();
	pWnd->SendMessage (WM_FONT_CHANGED);
	
}

BOOL CFontCombo::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	
	return TRUE;//CComboBox::OnMouseWheel(nFlags, zDelta, pt);
}
