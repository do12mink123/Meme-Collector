
#include "Main.h"

#define ilstr 14

const char *smeme[ilstr] = {
	"https://jbzdy.pl/strona/",
	"https://www.chamsko.pl/page/",
	"https://demotywatory.pl/page/",
	"http://komixxy.pl/page/",
	"https://pocisk.org/page/",
	"https://mistrzowie.org/page/",
	"http://redmik.pl/",
	"http://memy.pl/?page=",
	"http://www.hopaj.pl/hopy,",
	"https://kwejk.pl/strona/",
	"http://mamtak.pl/page/",
	"http://takmam.pl/page/",
	"https://besty.pl/pages/",
	"https://fabrykamemow.pl/page/",
};

std::string smemeo[ilstr] = {
	"https://jbzdy.pl",
	"https://www.chamsko.pl",
	"https://demotywatory.pl",
	"http://komixxy.pl",
	"https://pocisk.org",
	"https://mistrzowie.org",
	"http://redmik.pl",
	"http://memy.pl",
	"http://www.hopaj.pl",
	"https://kwejk.pl",
	"http://mamtak.pl",
	"http://takmam.pl",
	"https://besty.pl",
	"https://fabrykamemow.pl",
};


int main() {
	using namespace std;

	for (int i=0; i < ilstr; i++) {
		int st = 1;
		int bl = 0;
		bool dzielaj = 1;
		string phstr;
		int brnowch = 0;
		while (dzielaj) {
			if (brnowch > 400)break;
			string aaa = smeme[i];
			aaa += to_string(st);
			int timo = 0;
		ponowww:
			HRESULT hr = URLDownloadToFile(
				NULL,
				aaa.data(),
				"temp.html",
				0,
				NULL);
			timo++;
			if ((hr < 0) && (timo < 5))goto ponowww;
			if (SUCCEEDED(hr))
			{
				string nh = gh("temp.html");
				if (nh == phstr) {
					dzielaj = 0;
					break;
				}
				phstr = nh;
				fstream ttt("temp.html", ios::in | ios::binary);
				if (ttt.good())
					while (!ttt.eof()) {
						char z = 0;
						ttt.read(&z, 1);
						if (z != '.') {
							continue;
						}
						ttt.read(&z, 1);
						bool gooo = 0;
						string konc;
						switch (z)
						{
						case('j')://jpg
						{
							ttt.read(&z, 1);
							if (z == 'p') {
								ttt.read(&z, 1);
								if (z == 'g') {
									gooo = 1;
									konc = ".jpg";
								}
							}
						}
						break;
						case('p')://png
						{
							ttt.read(&z, 1);
							if (z == 'n') {
								ttt.read(&z, 1);
								if (z == 'g') {
									gooo = 1;
									konc = ".png";
								}
							}
						}
						break;
						case('b')://bmp
						{
							ttt.read(&z, 1);
							if (z == 'm') {
								ttt.read(&z, 1);
								if (z == 'p') {
									gooo = 1;
									konc = ".bmp";
								}
							}
						}
						break;
						case('g')://gif
						{
							ttt.read(&z, 1);
							if (z == 'i') {
								ttt.read(&z, 1);
								if (z == 'f') {
									gooo = 1;
									konc = ".gif";
								}
							}
						}
						break;
						case('h')://html
						{
							ttt.read(&z, 1);
							if (z == 't') {
								ttt.read(&z, 1);
								if (z == 'm') {
									ttt.read(&z, 1);
									if (z == 'l') {
										gooo = 0;//lol
										konc = ".html";
									}
								}
							}
						}
						break;
						default:
							break;
						}

						if (gooo == 1) {
							int d = ttt.tellp();
							while (1) {
								d--;
								ttt.seekp(d);
								ttt.read(&z, 1);
								if (z == '"')break;
							}
							string a;
							while (1) {
								ttt.read(&z, 1);
								if (z == '"')break;
								a += z;
							}
							bool nowe = 0;
							if ((a.data()[0] == '/') || (a.data()[0] == '\\')) {
								pkol(smemeo[i] + a, konc,nowe);
							}
							else {
								pkol(a, konc,nowe);
							}
							if (nowe) {
								brnowch=0;
							}
							else {
								brnowch++;
							}
						}
					}
				ttt.close();
				DeleteFile("temp.html");

			}
			else {
				if (bl > 10)dzielaj = 0;
				bl++;
			}
			st++;
		}

	}
	return 0;
}




