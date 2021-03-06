#include "stdafx.h"
#include "DiskFiller.h"
#include "DiskFillerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);

    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

CDiskFillerDlg::CDiskFillerDlg(CWnd* pParent) : CDialog(IDD_DISKFILLER_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDiskFillerDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDiskFillerDlg, CDialog)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

BOOL CDiskFillerDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
    InitSystemMenu();
    SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);
    return TRUE;
}

void CDiskFillerDlg::InitSystemMenu(
) {
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);
    CMenu* menu = GetSystemMenu(FALSE);
    if (!menu)
        return;
    CString strAboutMenu;
    ASSERT(strAboutMenu.LoadString(IDS_ABOUTBOX));
    if (strAboutMenu.IsEmpty())
        return;
    menu->AppendMenu(MF_SEPARATOR);
    menu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
}

void CDiskFillerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else {
        CDialog::OnSysCommand(nID, lParam);
    }
}

void CDiskFillerDlg::OnPaint()
{
    if (IsIconic()) {
        OnPaintIconic();
    }
    else {
        CDialog::OnPaint();
    }
}

void CDiskFillerDlg::OnPaintIconic(
) {
    CPaintDC dc(this);
    SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
    int cxIcon = GetSystemMetrics(SM_CXICON);
    int cyIcon = GetSystemMetrics(SM_CYICON);
    CRect rect;
    GetClientRect(&rect);
    int x = (rect.Width() - cxIcon + 1) / 2;
    int y = (rect.Height() - cyIcon + 1) / 2;
    dc.DrawIcon(x, y, m_hIcon);
}

HCURSOR CDiskFillerDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CDiskFillerDlg::OnOK(
) {
    ((CDiskFillerApp*)AfxGetApp())->StartFillDisk(GetGb(), GetMb(), GetKb());
}

void CDiskFillerDlg::OnCancel(
) {
    ((CDiskFillerApp*)AfxGetApp())->Quit();
}

int CDiskFillerDlg::GetGb(
) {
    CString str;
    GetDlgItem(IDC_EDIT1)->GetWindowText(str);
    return _wtoi(str);
}

int CDiskFillerDlg::GetMb(
) {
    CString str;
    GetDlgItem(IDC_EDIT2)->GetWindowText(str);
    return _wtoi(str);
}

int CDiskFillerDlg::GetKb(
) {
    CString str;
    GetDlgItem(IDC_EDIT3)->GetWindowText(str);
    return _wtoi(str);
}

void CDiskFillerDlg::OnShowWindow(
    BOOL shown,
    UINT status
) {
    if (shown)
        GetDlgItem(IDC_EDIT1)->SetFocus();
}
