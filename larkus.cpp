#include <Windows.h>
#include <iostream>
#include <math.h>
#include <cmath>
#include <ctime>
#include <thread>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "ntdll.lib")
typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE r;
		BYTE g;
		BYTE b;
		BYTE Reserved;
	};
}_RGBQUAD, * PRGBQUAD;
int red, green, blue;
bool ifcolorblue = false, ifblue = false;
COLORREF Hue(int length) {
	if (red != length) {
		red < length; red++;
		if (ifblue == true) {
			return RGB(red, 0, length);
		}
		else {
			return RGB(red, 0, 0);
		}
	}
	else {
		if (green != length) {
			green < length; green++;
			return RGB(length, green, 0);
		}
		else {
			if (blue != length) {
				blue < length; blue++;
				return RGB(0, length, blue);
			}
			else {
				red = 0; green = 0; blue = 0;
				ifblue = true;
			}
		}
	}
}
DWORD WINAPI TextOut(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	int sx = GetSystemMetrics(0);
	int sy = GetSystemMetrics(1);
	LPCWSTR lpText = L"Hello!";
	while (true)
	{
		hdc = GetDC(0);
		SetBkColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		TextOutW(hdc, rand() % sx, rand() % sy, lpText, wcslen(lpText));
		ReleaseDC(GetDesktopWindow(), hdc);
		DeleteDC(hdc);
		Sleep(1);
	}
}
DWORD WINAPI CursorText(LPVOID lpvd) {
	HDC hdc = GetDC(0);
	POINT cursorPt;
	int sx = GetCursorPos(&cursorPt);
	int sy = GetCursorPos(&cursorPt);
	LPCWSTR lpText = L"Hello!";
	while (true)
	{
		hdc = GetDC(0);
		GetCursorPos(&cursorPt);
		SetBkColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		TextOutW(hdc, cursorPt.x, cursorPt.y, lpText, wcslen(lpText));
		ReleaseDC(GetDesktopWindow(), hdc);
		DeleteDC(hdc);
		Sleep(10);
	}
}

DWORD WINAPI shader1(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			//INT x = i % w, y = i / w;
			rgbScreen[i].rgb -= 666;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		Sleep(100);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
DWORD WINAPI MoveScreenInvert(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	while (true)
	{
		hdc = GetDC(0);
		BitBlt(hdc, 0, -30, w, h, hdc, 0, 0, SRCCOPY);
		BitBlt(hdc, 0, h - 30, w, h, hdc, 0, 0, NOTSRCCOPY);
		BitBlt(hdc, -30, 0, w, h, hdc, 0, 0, SRCCOPY);
		BitBlt(hdc, w - 30, 0, w, h, hdc, 0, 0, NOTSRCCOPY);
		ReleaseDC(GetDesktopWindow(), hdc);
		DeleteDC(hdc);
	}
}
DWORD WINAPI profect(LPVOID lpParam) {
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	while (1) {
		HDC hdc = GetDC(0);
		BitBlt(hdc, 0, 0, w, h, hdc, -30, 0, SRCCOPY);
		BitBlt(hdc, 0, 0, w, h, hdc, w - 30, 0, SRCCOPY);
		BitBlt(hdc, 0, 0, w, h, hdc, 0, -30, SRCCOPY);
		BitBlt(hdc, 0, 0, w, h, hdc, 0, h - 30, SRCCOPY);
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(hdc, brush);
		BitBlt(hdc, 0, 0, w, h, hdc, 0, 0, PATINVERT);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
		Sleep(10);
	}
}
DWORD WINAPI vertwide(LPVOID lpParam) {
	HDC desk;
	int sw, sh;

	while (1) {
		desk = GetDC(0);
		sw = GetSystemMetrics(0);
		sh = GetSystemMetrics(1);
		StretchBlt(desk, 0, -20, sw, sh + 40, desk, 0, 0, sw, sh, SRCCOPY);
		ReleaseDC(0, desk);
		Sleep(4);
	}
}
VOID WINAPI sound1() {
	HWAVEOUT hwo = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11400, 11400, 1, 8, 0, };
	waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[11400 * 30];
	for (DWORD t = 0; t < sizeof(buffer); t++)
		buffer[t] = static_cast<char>((t * (1 + (5 & t >> 10)) * (3 + (t >> 17 & 1 ? (2 ^ 2 & t >> 14) / 3 : 3 & (t >> 13) + 1)) >> (3 & t >> 9)) & (t & 4096 ? (t * (t ^ t % 9) | t >> 3) >> 1 : 255));

	WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
	waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
	waveOutClose(hwo);
}
VOID WINAPI sound2() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 12000, 12000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[12000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (t ^ t + (t >> 8 | 1) / (t - 12800 ^ t) >> 10));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound3() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * ((t & 4096 ? t % 65536 < 59392 ? 7 : t & 7 : 16) ^ (1 & t >> 14)) >> (3 & -t >> (t & 2048 ? 2 : 10)));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound4() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 9000, 9000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[9000 * 40] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((9 * t & t >> 4 | 5 * t & t >> 7 | 3 * t & t >> 10) - 0);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound5() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t*((t/2>>10|t%16*t>>8)&8*t>>12&18)|-(t/16)+64);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

	if (MessageBoxW(NULL, L"This is a GDI", L"larkus.exe", MB_YESNO | MB_ICONEXCLAMATION | MB_SYSTEMMODAL) == IDNO)
	{
		ExitProcess(0);
	}
	else
	{
		if (MessageBoxW(NULL, L"It contains loud sound and cool GDI effects.", L"larkus.exe", MB_YESNO | MB_ICONEXCLAMATION | MB_SYSTEMMODAL) == IDNO)
		{
			ExitProcess(0);
		}
		else
		{

	Sleep(500);
	HANDLE Z1 = CreateThread(0, 0, TextOut, 0, 0, 0);
	HANDLE Z1R1 = CreateThread(0, 0, CursorText, 0, 0, 0);
	sound1();
	Sleep(30000);
	TerminateThread(Z1, 0);
	CloseHandle(Z1);
	TerminateThread(Z1R1, 0);
	CloseHandle(Z1R1);
	Sleep(100);
	HANDLE Z2 = CreateThread(0, 0, shader1, 0, 0, 0);
	sound2();
	Sleep(30000);
	TerminateThread(Z2, 0);
	CloseHandle(Z2);
	Sleep(100);
	HANDLE Z3 = CreateThread(0, 0, MoveScreenInvert, 0, 0, 0);
	sound3();
	Sleep(30000);
	TerminateThread(Z3, 0);
	CloseHandle(Z3);
	Sleep(100);
	HANDLE Z4 = CreateThread(0, 0, profect, 0, 0, 0);
	sound4();
	Sleep(40000);
	TerminateThread(Z4, 0);
	CloseHandle(Z4);
	Sleep(100);
	HANDLE Z5 = CreateThread(0, 0, vertwide, 0, 0, 0);
	sound5();
	Sleep(30000);
	TerminateThread(Z5, 0);
	CloseHandle(Z5);
	Sleep(100);


		}
	}
}