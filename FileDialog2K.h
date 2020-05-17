#if !defined(AFX_FILEDIALOG2K_H__0DE5CA7A_1DE4_4014_8B88_F761B7CFBFC4__INCLUDED_)
#define AFX_FILEDIALOG2K_H__0DE5CA7A_1DE4_4014_8B88_F761B7CFBFC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileDialog2K.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileDialog2K dialog
struct OPENFILENAME_2K
{
        OPENFILENAME        ofn;

        void                *pvReserved;
        DWORD                dwReserved;
        DWORD                FlagsEx;
};

class CFileDialog2K : public CFileDialog
{
        DECLARE_DYNAMIC(CFileDialog2K)

public:
        
        CFileDialog2K(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
                LPCTSTR lpszDefExt = NULL,
                LPCTSTR lpszFileName = NULL,
                DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
                LPCTSTR lpszFilter = NULL,
                CWnd* pParentWnd = NULL);

public:

        //{{AFX_VIRTUAL(CFileDialog2K)
        public:
        virtual int DoModal();
        protected:
        virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
        //}}AFX_VIRTUAL

protected:

        OPENFILENAME_2K *m_pofn2K;

        //{{AFX_MSG(CFileDialog2K)
        //}}AFX_MSG

        DECLARE_MESSAGE_MAP()
};


#endif // !defined(AFX_FILEDIALOG2K_H__0DE5CA7A_1DE4_4014_8B88_F761B7CFBFC4__INCLUDED_)
