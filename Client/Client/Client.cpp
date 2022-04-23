
#include <stdio.h>
#include <WinSock2.h>
#include <wchar.h>
#include <comdef.h>

#pragma comment(lib, "ws2_32")
#pragma warning(disable:4996)

int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("192.168.0.103");
    addr.sin_port = htons(8000);

    system("pause");

    int ret = connect(server, (SOCKADDR*)&addr, sizeof(addr));
    if (ret == SOCKET_ERROR)
    {
        ret = WSAGetLastError();
        printf("Ket noi khong thanh cong - %d\n", ret);
        return 1;
    }
    
    // tên máy tính
    wchar_t computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computerName) / sizeof(computerName[0]);

    int r = GetComputerNameW(computerName, &size);

    if (r == 0) {
        wprintf(L"Failed to get computer name %ld", GetLastError());
        return 1;
    }

  wprintf(L"Computer name: %ls\n", computerName);

    _bstr_t b(computerName);
    const char* msg = b;

    send(server, msg, strlen(msg), 0);


  
  //  GetLogicalDriveStringsA() - Trả về danh sách ký tự ổ đĩa của máy tính
   
    wchar_t LogicalDrives[MAX_PATH] = { 0 };
    DWORD Lgd = GetLogicalDriveStringsW(MAX_PATH, LogicalDrives);

    if (Lgd == 0) {
        wprintf(L"Failed to get drive names %ld", GetLastError());
        return 1;
    }

    if (Lgd > 0 && Lgd <= MAX_PATH) {

        wchar_t* SingleDrive = LogicalDrives;

        while (*SingleDrive) {

            wprintf(L"%ls\n", SingleDrive);

            _bstr_t b(SingleDrive);
            const char* msg = b;
            send(server, msg, strlen(msg), 0);


            SingleDrive += wcslen(SingleDrive) + 1;

     
        }
    }
    
    


 
// GetDiskFreeSpaceA() - Trả về kích thước của ổ đĩa

    unsigned __int64 freeCall,
        total,
        free;

    int DF = GetDiskFreeSpaceExW(L"C:\\", (PULARGE_INTEGER)&freeCall,
        (PULARGE_INTEGER)&total, (PULARGE_INTEGER)&free);

    if (DF == 0) {

        wprintf(L"Failed to get free disk space %ld", GetLastError());
        return 1;
    }

 wprintf(L"Available space to caller: %I64u MB\n", freeCall / (1024 * 1024));

    _bstr_t b0(freeCall);
    const char* msg0 = b0;
    send(server, msg0, strlen(msg0), 0);

 wprintf(L"Total space: %I64u MB\n", total / (1024 * 1024));


    _bstr_t b1(total);
    const char* msg1 = b1;
    send(server, msg1, strlen(msg1), 0);

  wprintf(L"Free space on drive: %I64u MB\n", free / (1024 * 1024));

    _bstr_t b2(free);
    const char* msg2 = b2;
    send(server, msg2, strlen(msg2), 0);


     // Nhan du lieu tu server va in ra man hinh
    char buf[256];
    while (1)
    {
        ret = recv(server, buf, sizeof(buf), 0);
        if (ret <= 0)
            break;

        // Them ky tu ket thuc xau va in ra man hinh
        buf[ret] = 0;
        printf("Du lieu tu server: %s\n", buf);
    }

    closesocket(server);
    WSACleanup();
}
