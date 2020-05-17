////////////////////////////////////////////////////////////////
// 1999 Paul DiLascia
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// 
#ifndef FTAB_H
#define FTAB_H

// style flags

#define FTS_FULLBORDER	0x1				 // draw full border
class CFolderTab {
private:
	CString	m_sText; // tab text
	CRect		m_rect;			// bounding rect
	CRgn		m_rgn;			// polygon region to fill (trapezoid)

	
	
	BOOL		HitTest(CPoint pt)			{ return m_rgn.PtInRegion(pt); }
	
	
protected:
	virtual int		Draw(CDC& dc, CFont& font, BOOL bSelected);
	virtual void		GetTrapezoid(const CRect& rc, CPoint* pts) const;
	friend class CFolderTabCtrl;

public:
	CRect		GetRect() const				{ return m_rect; }
	int		ComputeRgn(CDC& dc, int x);
	CFolderTab(LPCTSTR lpszText) : m_sText(lpszText) { }
	LPCTSTR	GetText() const				{ return m_sText; }
	void  	SetText(LPCTSTR lpszText)	{ m_sText = lpszText; }
};

enum { FTN_TABCHANGED = 1 };				 // notification: tab changed

struct NMFOLDERTAB : public NMHDR {		 // notification struct
	int iItem;										 // item index 
	const CFolderTab* pItem;					 // ptr to data, if any
};

//////////////////
// Folder tab control, similar to tab control
//
class CFolderTabCtrl : public CWnd {
protected:
	CPtrList		m_lsTabs;					 // array of CFolderTabs
	DWORD			m_dwFtabStyle;				 // folder tab style flags
	int			m_iCurItem;					 // current selected tab
	CFont			m_fontNormal;				 // current font, normal ntab
	CFont			m_fontSelected;			 // current font, selected tab
	int			m_nDesiredWidth;			 // exact fit width

	// helpers
	void InvalidateTab(int iTab, BOOL bErase=TRUE);
	virtual void DrawTabs(CDC& dc, const CRect& rc);
	CFolderTab* GetTab(int iPos);

public:
	CFolderTabCtrl();
	virtual ~CFolderTabCtrl();

	BOOL CreateFromStatic(UINT nID, CWnd* pParent);

	virtual BOOL Create(DWORD dwWndStyle, const RECT& rc,
		CWnd* pParent, UINT nID, DWORD dwFtabStyle=0);
	virtual BOOL Load(UINT nIDRes);

	CFolderTab* GetItem(int iPos)		{ return (CFolderTab*)GetTab(iPos); }
	int	GetSelectedItem()				{ return m_iCurItem; }
	int	GetItemCount()					{ return m_lsTabs.GetCount(); }
	int	GetDesiredWidth()				{ return m_nDesiredWidth; }
	int	GetDesiredHeight()			{ return GetSystemMetrics(SM_CYHSCROLL); }
	BOOL  AddItem(LPCTSTR lpszText);
	BOOL  RemoveItem(int iPos);
	void	RecomputeLayout();
	int	HitTest(CPoint pt);
	int	SelectItem(int iTab);
	void	SetFonts(CFont& fontNormal, CFont& fontSelected);

protected:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_DYNAMIC(CFolderTabCtrl);
	DECLARE_MESSAGE_MAP()
};

#endif // FTAB_H
