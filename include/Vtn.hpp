#pragma once
#include <Windows.h>
#include <string>
#include <deque>

template <typename T>
struct Vec2
{
	Vec2(): x(0), y(0) {}
	Vec2(T X, T Y): x(X), y(Y) {}
	T x;
	T y;
};

struct Vtn
{
	~Vtn();
	Vtn(Vec2<int> size, const wchar_t *title);
	bool operator >>(std::deque<std::string> &events);
	void close();
private:
	void checkEvents();
	void checkEvents(UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK OnEvent(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam);
	HWND m_handle;
	HCURSOR m_cursor;
	bool m_windowOpen;
	std::deque<std::string> m_events;
};
