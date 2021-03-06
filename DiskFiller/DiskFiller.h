#pragma once

#include "resource.h"

class CDiskFillerApp : public CWinApp
{
public:
    CDiskFillerApp();
    virtual BOOL InitInstance();
    virtual void FillDisk(CString path, long long gb, long long mb, long long kb);
    virtual void Quit();
    virtual void StartFillDisk(long long gb, long long mb, long long kb);
    virtual void MessageError(UINT err);

    DECLARE_MESSAGE_MAP()
};
