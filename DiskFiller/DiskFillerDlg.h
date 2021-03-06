#pragma once

class CDiskFillerDlg : public CDialog
{
public:
	CDiskFillerDlg(CWnd* pParent = NULL);

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DISKFILLER_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX) override;
    virtual BOOL OnInitDialog() override;
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnShowWindow(BOOL shown, UINT status);
    virtual void OnPaintIconic();
    virtual void InitSystemMenu();
    virtual void OnOK() override;
    virtual void OnCancel() override;
    virtual int GetGb();
    virtual int GetMb();
    virtual int GetKb();

protected:
    HICON m_hIcon;

    DECLARE_MESSAGE_MAP()
};
