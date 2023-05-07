#include <iostream>
#include <windows.h>

constexpr auto TasktrayIconID = 1000;

//タスクトレイアイコン 追加
void AddTrayIcon(HWND hWnd)
{
    NOTIFYICONDATA nid{ 0 };
    nid.cbSize = sizeof(nid);
    nid.uID = TasktrayIconID;
    nid.hWnd = hWnd;
    nid.uFlags = NIF_ICON | NIF_TIP;
    nid.hIcon = LoadIcon(NULL, IDI_INFORMATION);
    lstrcpyW(nid.szTip, L"NotifyMessage");
    Shell_NotifyIconW(NIM_ADD, &nid);
}

//通知メッセージ 表示
void Notice(HWND hwnd)
{
    if (hwnd == nullptr)
        return;

    NOTIFYICONDATA nid{ 0 };
    nid.cbSize = sizeof(nid);
    nid.hWnd = hwnd;
    nid.uID = TasktrayIconID;
    nid.uFlags = NIF_INFO;
    nid.dwInfoFlags = NIIF_INFO;

    lstrcpyW(nid.szInfoTitle, L"通知タイトル");
    lstrcpyW(nid.szInfo, L"ここにいろいろなメッセージを表示します\r\n改行もできます");

    Shell_NotifyIconW(NIM_MODIFY, &nid);
}

//タスクトレイアイコン 削除
void DeleteTrayIcon(HWND hwnd)
{
    NOTIFYICONDATA nid{ };
    nid.cbSize = sizeof(nid);
    nid.hWnd = hwnd;
    nid.uID = TasktrayIconID;
    Shell_NotifyIconW(NIM_DELETE, &nid);
}

int main()
{
    auto hwnd = ::GetConsoleWindow();

    std::wcout << L"Press any key to send toast using notify icon." << std::endl;
    std::ignore = getchar();

    //トレイアイコンを登録
    AddTrayIcon(hwnd);

    //通知メッセージを表示
    Notice(hwnd);

    //std::wcout << L"Press any key to delete notify icon." << std::endl;
    //std::ignore = getchar();

    //トレイアイコンを削除
    DeleteTrayIcon(hwnd);

    std::wcout << L"Press any key to finish." << std::endl;
    std::ignore = getchar();
}
