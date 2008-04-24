
/*-----------------------------------------------------------------------
   HELLOWIN.C – Zeigt "Hello, Windows 98!" in seinem Anwendungsbereich an
                 (c) Charles Petzold, 1998
  -----------------------------------------------------------------------*/

#include <windows.h>

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
     static TCHAR szAppName[] = TEXT ("HelloWin") ;
     HWND         hwnd ;
     MSG          msg ;
     WNDCLASS     wndclass ;

     wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
     wndclass.lpfnWndProc   = WndProc ;
     wndclass.cbClsExtra    = 0 ;
     wndclass.cbWndExtra    = 0 ;
     wndclass.hInstance     = hInstance ;
     wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
     wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
     wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
     wndclass.lpszMenuName  = NULL ;
     wndclass.lpszClassName = szAppName ;

     if (!RegisterClass (&wndclass))
     {    // UNICODE-Compilierung ist die einzige realistische Fehlermöglichkeit 
          MessageBox (NULL, TEXT ("Programm arbeitet mit Unicode und setzt Windows NT voraus!"), 
                      szAppName, MB_ICONERROR) ;
          return 0 ;
     }

      hwnd = CreateWindow (szAppName,                 // Name der Fensterklasse
                  TEXT ("Das erste echte Programm"),  // Fenstertitel
                  WS_OVERLAPPEDWINDOW,                // Fensterstil
                  CW_USEDEFAULT,                      // X-Position des Fensters
                  CW_USEDEFAULT,                      // Y-Position des Fensters
                  CW_USEDEFAULT,                      // Fensterbreite
                  CW_USEDEFAULT,                      // Fensterhöhe
                  NULL,                               // übergeordnetes Fenster
                  NULL,                               // Menü
                  hInstance,                          // Programm-Kopiezähler (Programm-ID)
                  NULL) ;                             // zusätzliche Parameter
     
     ShowWindow (hwnd, iCmdShow) ;
     UpdateWindow (hwnd) ;
     
     while (GetMessage (&msg, NULL, 0, 0))
     {
          TranslateMessage (&msg) ;
          DispatchMessage (&msg) ;
     }
     return msg.wParam ;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     HDC         hdc ;
     PAINTSTRUCT ps ;
     RECT        rect ;
     
     switch (message)
     {
     case WM_CREATE:
          //PlaySound (TEXT ("hellowin.wav"), NULL, SND_FILENAME | SND_ASYNC) ;
          return 0 ;

     case WM_PAINT:
          hdc = BeginPaint (hwnd, &ps) ;
          
          GetClientRect (hwnd, &rect) ;
          
          DrawText (hdc, TEXT ("Hello, Windows 98!"), -1, &rect,
                    DT_SINGLELINE | DT_CENTER | DT_VCENTER) ;

          EndPaint (hwnd, &ps) ;
          return 0 ;
          
     case WM_DESTROY:
          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}
