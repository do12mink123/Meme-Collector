#pragma once

#include "openssl/sha.h"
#include <openssl/ssl.h>
#include <openssl/ec.h>
#include <openssl/ripemd.h>
#include <fstream>
#include <math.h>
#include <iostream>
#include <string>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <ws2def.h>

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"libcrypto.lib")
#pragma comment(lib,"urlmon.lib")

namespace suuuuu {
	struct SocketInitializer
	{
		SocketInitializer() {
			WSAData init;
			WSAStartup(MAKEWORD(2, 2), &init);


		}
		~SocketInitializer() {
			WSACleanup();
		}
	};
	SocketInitializer glo;
};
#else

#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#endif

void base58_encode(unsigned char *data, unsigned int len, char *result) {
	const char code_string[] = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

	BIGNUM *x, *rem, *base, *tmp, *tmp2;
	x = BN_new();
	rem = BN_new();
	base = BN_new();
	tmp = BN_new();
	char * output_string = (char *)malloc(64);

	x = BN_bin2bn(data, len, x);

	BN_set_word(rem, 1);
	BN_set_word(base, 58);

	BN_CTX *bnctx;
	bnctx = BN_CTX_new();

	int i = 0;
	while (!BN_is_zero(x)) {
		BN_div(tmp, rem, x, base, bnctx);
		output_string[i++] = code_string[BN_get_word(rem)];


		tmp2 = x;
		x = tmp;
		tmp = tmp2;
	}


	int i2 = 0;
	while (data[i2] == 0) {
		output_string[i++] = code_string[0];
		i2++;
	}

	int base58len = i;
	while (i >= 0) {
		result[base58len - i] = output_string[i - 1];
		i--;
	}
	result[base58len] = 0;

	BN_free(x);
	BN_free(base);
	BN_free(rem);
	BN_free(tmp);
	BN_CTX_free(bnctx);
	free(output_string);
}

std::string gh(std::string nzw) {
	using namespace std;
	fstream plik(nzw, ios::in | ios::binary);
	int dl = 0;
	plik.seekg(0, ios::end);
	dl = plik.tellg();
	plik.seekg(0);
	if (dl > 1000000000)return "1";
	if (dl <= 0)return "0";
	char *pl = new char[dl];
	plik.read(pl, dl);
	unsigned char md[SHA256_DIGEST_LENGTH];
	unsigned char * haa = SHA256((unsigned char*)pl, dl, md);
	delete[] pl;
	char b58[64];
	base58_encode(haa, SHA256_DIGEST_LENGTH, b58);
	string w = b58;
	return w;
}

void zobr(std::string tempz, std::string konc) {
	using namespace std;
	string hash = gh(tempz);
	hash += konc;
	if (CopyFile(tempz.data(), (string("C:/DATA/") + hash).data(),1))
	{
		cout << hash << endl;
	}
	DeleteFile(tempz.data());
}

void pkol(std::string adr, std::string konc) {
	HRESULT hr = URLDownloadToFile(
		NULL,
		adr.data(),
		(std::string("temp") + konc).data(),
		0,
		NULL);
	if (SUCCEEDED(hr))
	{
		zobr(std::string("temp") + konc, konc);
	}
}
