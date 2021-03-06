#include "stdafx.h"
#include "DiskFiller.h"
#include "DiskFillerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace {
    struct CFinal {
        CFinal(std::function<void(void)> fn) : m_fn(fn) {}
        ~CFinal() { m_fn(); }
        std::function<void(void)> m_fn;
    };
}

BEGIN_MESSAGE_MAP(CDiskFillerApp, CWinApp)
    ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

CDiskFillerApp::CDiskFillerApp()
{
}

CDiskFillerApp theApp;

BOOL CDiskFillerApp::InitInstance()
{
    CWinApp::InitInstance();
    SetRegistryKey(_T("DiskFiller"));
    auto* dlg = new CDiskFillerDlg();
    m_pMainWnd = dlg;
    dlg->Create(IDD_DISKFILLER_DIALOG);
    dlg->ShowWindow(SW_SHOW);
    MSG msg;
    BOOL ret;
    while ((ret = GetMessage(&msg, nullptr, 0, 0)) != 0) {
        if (ret == -1)
            continue;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (BOOL)msg.wParam;
}

void CDiskFillerApp::StartFillDisk(
    long long gb,
    long long mb,
    long long kb
) {
    CFileDialog fd(FALSE, CString(L".dat"), L"DiskFiller.dat");
    if (fd.DoModal() == IDOK) {
        CString path = fd.GetPathName();
        FillDisk(path, gb, mb, kb);
    }
}

void CDiskFillerApp::Quit(
) {
    PostQuitMessage(0);
}

void CDiskFillerApp::FillDisk(
    CString path,
    long long gb,
    long long mb,
    long long kb
) {
    if (path.IsEmpty())
        return;
    if (gb < 0 || mb < 0 || kb < 0) {
        AfxMessageBox(L"Negative number was found.");
        return;
    }
    LARGE_INTEGER sz;
    sz.QuadPart = gb * 1024 * 1024 * 1024
        + mb * 1024 * 1024
        + kb * 1024;
    HANDLE h = CreateFile(path, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (h == INVALID_HANDLE_VALUE) {
        MessageError(GetLastError());
        return;
    }
    CFinal fin([h]() { CloseHandle(h); });
    DWORD ret = SetFilePointer(h, sz.LowPart, &sz.HighPart, FILE_END);
    if (ret == INVALID_SET_FILE_POINTER) {
        MessageError(GetLastError());
        return;
    }
    if (!SetEndOfFile(h)) {
        MessageError(GetLastError());
        return;
    }
}

void CDiskFillerApp::MessageError(
    UINT err
) {
    CString msg;
    msg.Format(L"CraeteFile failed: %d", err);
    AfxMessageBox(msg);
}
