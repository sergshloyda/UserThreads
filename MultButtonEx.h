#pragma once

// MultButtonEx command target

class MultButtonEx : public CMFCToolBarMenuButton
{
	DECLARE_SERIAL(MultButtonEx)
	
public:
	//MultButtonEx();
	MultButtonEx(UINT nID=NULL,LPCTSTR lpszText=NULL,HMENU hMenu=NULL);
	//virtual ~MultButtonEx();
	
	virtual void OnDraw(CDC* pDC, const CRect& rect, CMFCToolBarImages* pImages, BOOL bHorz = TRUE, BOOL bCustomizeMode = FALSE, BOOL bHighlight = FALSE, BOOL bDrawBorder = TRUE, BOOL bGrayDisabledButtons = TRUE);


	virtual void OnGlobalFontsChanged();
	void SetText(LPCTSTR lpszNewText)
	{
		m_strText=lpszNewText;
		//InvalidateRect(this->GetHwnd(),GetInvalidateRect(),TRUE);
	}
};


