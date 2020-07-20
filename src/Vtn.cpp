#include <Vtn.hpp>
#include <iostream>

const wchar_t *className = L"uwu";

Ventana::~Ventana()
{
	DestroyWindow(m_handle);
	DestroyCursor(m_cursor);
}

Ventana::Ventana(Vec2<int> size, const wchar_t *title)
: m_handle(NULL)
, m_cursor(LoadCursor(NULL, IDC_ARROW))
, m_windowOpen(true)
{
	WNDCLASSW wc;
	wc.cbClsExtra 	 = 0;
	wc.cbWndExtra 	 = 0;
	wc.hbrBackground = NULL;
	wc.hCursor 		 = m_cursor;
	wc.hIcon 		 = NULL;
	wc.hInstance 	 = GetModuleHandleW(0);
	wc.lpfnWndProc 	 = OnEvent;
	wc.lpszClassName = className;
	wc.lpszMenuName  = NULL;
	wc.style 		 = 0;
	RegisterClassW(&wc);

	m_handle = CreateWindowW(className, title,
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT, CW_USEDEFAULT,
							size.x, size.y,
							NULL, NULL, GetModuleHandleW(0), this);

	if (m_handle == NULL) {
		MessageBoxW(NULL, L"CreateWindow() failed:  Cannot create a window.",
			L"Error", MB_OK);
		exit(1);
    }

	ShowWindow(m_handle, SW_SHOW);
}

bool Ventana::operator >>(std::deque<std::string> &events)
{
	checkEvents();
	events = m_events;
	m_events = {};
	return m_windowOpen;
}

void Ventana::close()
{
	PostQuitMessage(0);
	this->~Ventana();
	m_windowOpen = false;
}

void Ventana::checkEvents()
{
	MSG msg;
	while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void Ventana::checkEvents(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		m_events.push_back("closed");
	case WM_MOUSEMOVE:
		m_events.push_back("mouse moved");
	}
}

LRESULT CALLBACK Ventana::OnEvent(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_CREATE)
	{
		LONG_PTR window = (LONG_PTR)reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams;
		SetWindowLongPtrW(handle, GWLP_USERDATA, window);
	}

	Ventana *ventana = handle? reinterpret_cast<Ventana*>(GetWindowLongPtr(handle, GWLP_USERDATA)) : NULL;

	if (ventana) ventana->checkEvents(msg, wParam, lParam);

	if (msg == WM_CLOSE)
		return 0;

	return DefWindowProcW(handle, msg, wParam, lParam);
}
