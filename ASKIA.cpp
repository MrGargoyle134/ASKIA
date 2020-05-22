#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <string>
#include <locale>
#include <codecvt>
using namespace std;
#include <stdio.h>
#include <Windows.h>

void Color(int col)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, col);
}

bool bMap = true;
bool bPositionAndFPS = true;

int nScreenWidth = 120;
int nScreenHeight = 40;

float fPlayerX = 8.0f;
float fPlayerY = 8.0f;
float fPlayerA = 0.0f;

int nMapHeight = 16;
int nMapWidth = 16;

float fFOV = 3.14159 / 4.0;

float fDepth = 16.0f;

int main()
{
	Color(7);
	cout << endl << endl;
	cout << "                AAA                  SSSSSSSSSSSSSSS KKKKKKKKK    KKKKKKKIIIIIIIIII               AAA               \n";
	cout << "               A:::A               SS:::::::::::::::SK:::::::K    K:::::KI::::::::I              A:::A              \n";
	cout << "              A:::::A             S:::::SSSSSS::::::SK:::::::K    K:::::KI::::::::I             A:::::A             \n";
	cout << "             A:::::::A            S:::::S     SSSSSSSK:::::::K   K::::::KII::::::II            A:::::::A            \n";
	cout << "            A:::::::::A           S:::::S            KK::::::K  K:::::KKK  I::::I             A:::::::::A           \n";
	cout << "           A:::::A:::::A          S:::::S              K:::::K K:::::K     I::::I            A:::::A:::::A          \n";
	cout << "          A:::::A A:::::A          S::::SSSS           K::::::K:::::K      I::::I           A:::::A A:::::A         \n";
	cout << "         A:::::A   A:::::A          SS::::::SSSSS      K:::::::::::K       I::::I          A:::::A   A:::::A        \n";
	cout << "        A:::::A     A:::::A           SSS::::::::SS    K:::::::::::K       I::::I         A:::::A     A:::::A       \n";
	cout << "       A:::::AAAAAAAAA:::::A             SSSSSS::::S   K::::::K:::::K      I::::I        A:::::AAAAAAAAA:::::A      \n";
	cout << "      A:::::::::::::::::::::A                 S:::::S  K:::::K K:::::K     I::::I       A:::::::::::::::::::::A     \n";
	cout << "     A:::::AAAAAAAAAAAAA:::::A                S:::::SKK::::::K  K:::::KKK  I::::I      A:::::AAAAAAAAAAAAA:::::A    \n";
	cout << "    A:::::A             A:::::A   SSSSSSS     S:::::SK:::::::K   K::::::KII::::::II   A:::::A             A:::::A   \n";
	cout << "   A:::::A               A:::::A  S::::::SSSSSS:::::SK:::::::K    K:::::KI::::::::I  A:::::A               A:::::A  \n";
	cout << "  A:::::A                 A:::::A S:::::::::::::::SS K:::::::K    K:::::KI::::::::I A:::::A                 A:::::A \n";
	cout << " AAAAAAA                   AAAAAAA SSSSSSSSSSSSSSS   KKKKKKKKK    KKKKKKKIIIIIIIIIIAAAAAAA                   AAAAAAA\n";
	cout << endl;

	int iChoice = 0;

	
	    cout << "1-Start\n";
		cout << "2-Load a map\n";
		cout << "3-Options\n";
		cout << "4-Exit\n";
	
	cout << "> "; Color(15); cin >> iChoice;
	Color(7);

	string filename;

	if (iChoice == 2)
	{
		system("cls");
		Color(15);
		cout << "--LOAD A MAP--\n";
		Color(7);
		cout << "Enter the file's name > "; Color(15); cin >> filename; Color(7);
		cout << "Enter the width of the map > "; Color(15); cin >> nMapWidth; Color(7);
		cout << "Enter the height of the map > "; Color(15); cin >> nMapHeight; Color(7);
		cout << "Player's spawn position X > "; Color(15); cin >> fPlayerX; Color(7);
		cout << "Player's spawn position Y > "; Color(15); cin >> fPlayerY; Color(7);
		cout << "Map width: " << nMapWidth << ". Map height: " << nMapHeight << ". Map name: " << filename << ". X: " << fPlayerX << ". Y: " << fPlayerY << endl;
		Sleep(3000);
	}
	if (iChoice == 3)
	{
		system("cls");
		Color(15);
		cout << "--OPTIONS--\n";
		Color(7);
		cout << "Map (1/0): "; Color(15); cin >> bMap; 
		Color(7);
		cout << "Position (1/0): "; Color(15); cin >> bPositionAndFPS;
		Color(7);
		system("cls");
		main();
	}

	ifstream mapfile(filename);

	if (iChoice == 4)
	{
		return 0;
	}

	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	wstring map;
	if (iChoice == 1)
	{
		map += L"################";
		map += L"#..............#";
		map += L"#..............#";
		map += L"###..#..#..#####";
		map += L"#..............#";
		map += L"####...........#";
		map += L"#......#.......#";
		map += L"#......###.....#";
		map += L"#..............#";
		map += L"#..##........###";
		map += L"#..............#";
		map += L"#..............#";
		map += L"#.....##########";
		map += L"#..............#";
		map += L"#..............#";
		map += L"################";
	}
	else if (iChoice == 2)
	{

		if (mapfile)
		{
			string line; 
			while(getline(mapfile, line)) 
			{
				wstring wLine(line.begin(), line.end());
				map += wLine;
			}
		}
		else{return -1;}
	}
	auto tp1 = chrono::system_clock::now();
	auto tp2 = chrono::system_clock::now();

	for (;;) //Game loop
	{
		tp2 = chrono::system_clock::now();
		chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		float fElapsedTime = elapsedTime.count();

		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
			fPlayerA -= (0.8f) * fElapsedTime;

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
			fPlayerA += (0.8f) * fElapsedTime;

		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			fPlayerX += sinf(fPlayerA) * 5.0f * fElapsedTime;
			fPlayerY += cosf(fPlayerA) * 5.0f * fElapsedTime;

			//Collision

			if (map[(int)fPlayerY * nMapWidth + (int)fPlayerX] == '#')
			{
				fPlayerX -= sinf(fPlayerA) * 5.0f * fElapsedTime;
				fPlayerY -= cosf(fPlayerA) * 5.0f * fElapsedTime;
			}
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			fPlayerX -= sinf(fPlayerA) * 5.0f * fElapsedTime;
			fPlayerY -= cosf(fPlayerA) * 5.0f * fElapsedTime;

			//Collision

			if (map[(int)fPlayerY * nMapWidth + (int)fPlayerX] == '#')
			{
				fPlayerX += sinf(fPlayerA) * 5.0f * fElapsedTime;
				fPlayerY += cosf(fPlayerA) * 5.0f * fElapsedTime;
			}
		}

		for (int x = 0; x < nScreenWidth; x++)
		{
			float fRayAngle = (fPlayerA - fFOV / 2.0f) + ((float)x / (float)nScreenWidth) * fFOV;

			float fDistanceToWall = 0;
			bool bHitWall = false;
			bool bBoundary = false;

			float fEyeX = sinf(fRayAngle);
			float fEyeY = cosf(fRayAngle);
			while (!bHitWall && fDistanceToWall < fDepth)
			{
				fDistanceToWall += 0.1f;
				int nTestX = (int)(fPlayerX + fEyeX * fDistanceToWall);
				int nTestY = (int)(fPlayerY + fEyeY * fDistanceToWall);

				if (nTestX < 0 || nTestX >= nMapWidth || nTestY < 0 || nTestY >= nMapHeight)
				{
					bHitWall = true;
					fDistanceToWall = fDepth;
				}
				else
				{
					if (map[nTestY * nMapWidth + nTestX] == '#')
					{
						bHitWall = true;
						vector<pair<float, float>> p;
						for (int tx = 0; tx < 2; tx++)

							for (int ty = 0; ty < 2; ty++)
							{
								float vy = (float)nTestY + ty - fPlayerY;
								float vx = (float)nTestX + tx - fPlayerX;
								float d = sqrt(vx * vx + vy * vy);
								float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
								p.push_back(make_pair(d, dot));
							}
						sort(p.begin(), p.end(), [](const pair<float, float>& left, const pair<float, float>& right) {return left.first < right.first; });

						float fBound = 0.01;

						if (acos(p.at(0).second) < fBound) bBoundary = true;
						if (acos(p.at(1).second) < fBound) bBoundary = true;
						if (acos(p.at(2).second) < fBound) bBoundary = true;
					}
				}
			}
			int nCelling = (float)(nScreenHeight / 2.0) - nScreenHeight / ((float)fDistanceToWall);
			int nFloor = nScreenHeight - nCelling;

			short nShade = ' ';
			short nShade2;
			if (fDistanceToWall <= fDepth / 4.0f)     nShade = 0x2588; //Near
			else if (fDistanceToWall < fDepth / 3.0f) nShade = 0x2593;
			else if (fDistanceToWall < fDepth / 2.0f) nShade = 0x2592;
			else if (fDistanceToWall < fDepth)        nShade = 0x2591;
			else                                      nShade = ' ';    //Far
			if (bBoundary)                            nShade = ' ';

			for (int y = 0; y < nScreenHeight; y++)
			{
				if (y < nCelling)
					screen[y * nScreenWidth + x] = ' ';
				else if (y > nCelling&& y <= nFloor)
					screen[y * nScreenWidth + x] = nShade;
				else
				{
					float b = 1.0f - (((float)y - nScreenHeight / 2.0f) / ((float)nScreenHeight / 2.0f));
					if (b < 0.25)      nShade2 = '#';
					else if (b < 0.5)  nShade2 = 'x';
					else if (b < 0.75) nShade2 = '.';
					else if (b < 0.9)  nShade2 = '-';
					else               nShade2 = ' ';
					screen[y * nScreenWidth + x] = nShade2;
				}
			}

		}
		if (bPositionAndFPS)
		{
			swprintf_s(screen, 40, L"X=%3.2f, Y=%3.2f, A=%3.2f FPS:%3.2f ", fPlayerX, fPlayerY, fPlayerA, 1.0f / fElapsedTime);
		}
		if (bMap)
		{
			for (int nx = 0; nx < nMapWidth; nx++)
			{
				for (int ny = 0; ny < nMapWidth; ny++)
				{
					screen[(ny + 1) * nScreenWidth + nx] = map[ny * nMapWidth + nx];
				}
			}
		}
		screen[((int)fPlayerY + 1) * nScreenWidth + (int)fPlayerX] = '@';
		screen[nScreenWidth * nScreenHeight - 1] = '\0';
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
	}

	return 0;
}
