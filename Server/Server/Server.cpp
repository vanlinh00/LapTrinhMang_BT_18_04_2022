//  bài này là tạo server  bạn cũng có thể tạo server bằng netcat : nc64.exe 192.168.0.103 8000
// VD3.cpp : Tao server nhan cau chao tu client, sau do doc du lieu tu ban phim roi gui sang client.

#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32")

int main()
{
	// Khoi tao thu vien
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// Tao socket
	SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// Khai bao dia chi server
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(8000);

	// Gan cau truc dia chi voi socket
	bind(listener, (SOCKADDR*)&addr, sizeof(addr));

	// Chuyen sang trang thai cho ket noi
	listen(listener, 5);

	// Cho ket noi moi
	SOCKET client = accept(listener, NULL, NULL);
	// Lien tuc doc du lieu tu ban phim va gui sang client
		// Nhan du lieu tu client
	char buf[256];
	while (1)
	{
		int ret = recv(client, buf, sizeof(buf), 0);
		// Them ky tu ket thuc xau va in ra man hinh
		buf[ret] = 0;
		printf("Du lieu tu client: %s\n", buf);
	}
	// Dong ket noi va giai phong thu vien
	closesocket(client);
	closesocket(listener);
	WSACleanup();
}
