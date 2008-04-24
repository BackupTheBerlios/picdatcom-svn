

#include <windows.h>
#include <commdlg.h>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>
#include "Generator.h"
using namespace std;

#define IDM_FILE_SAVEAS 7001
#define IDM_APP_EXIT	7002

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;
void PopFileInitialize (HWND hwnd);
BOOL PopFileSaveDlg (HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName);

static OPENFILENAME ofn ;
string HOMEPATH;	
static TCHAR szAppName[]	= TEXT ("HelloWin") ;
static TCHAR szFilter[]		= TEXT ("h Datei (*.h)\0*.h\0")  \
							  TEXT ("Alle Dateien (*.*)\0*.*\0\0") ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
     
     HWND         hwnd ;
     MSG          msg ;
	 WNDCLASS     wndclass ;
	 HMENU        hMenu;
	 HMENU        hMenuPopup;
	 stringstream s;

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
     {    // UNICODE-Compilierung ist die einzige realistische Fehlermˆglichkeit 
          MessageBox (NULL, TEXT ("Programm arbeitet mit Unicode und setzt Windows NT voraus!"), 
                      szAppName, MB_ICONERROR) ;
          return 0 ;
     }
	
	 HOMEPATH += getenv("HOMEDRIVE");
	 HOMEPATH += getenv("HOMEPATH");
	 HOMEPATH += "  -  ";
	 s << MAX_PATH;
	 HOMEPATH += s.str();

	 hMenu		= CreateMenu();
	 hMenuPopup	= CreateMenu();
	 AppendMenu(hMenuPopup,MF_STRING, IDM_FILE_SAVEAS,"Speichern &unter ...");
	 AppendMenu(hMenuPopup,MF_SEPARATOR, 0, NULL);
	 AppendMenu(hMenuPopup,MF_STRING, IDM_APP_EXIT, "&Beenden");
	 AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hMenuPopup, "&Datei");
	

      hwnd = CreateWindow (szAppName,                 // Name der Fensterklasse
                  TEXT ("Generator"),  // Fenstertitel
                  WS_OVERLAPPEDWINDOW,                // Fensterstil
                  CW_USEDEFAULT,                      // X-Position des Fensters
                  CW_USEDEFAULT,                      // Y-Position des Fensters
                  CW_USEDEFAULT,                      // Fensterbreite
                  CW_USEDEFAULT,                      // Fensterhˆhe
                  NULL,                               // ¸bergeordnetes Fenster
                  hMenu,                               // Men¸
                  hInstance,                          // Programm-Kopiez‰hler (Programm-ID)
                  szCmdLine) ;                             // zus‰tzliche Parameter
     
     ShowWindow (hwnd, iCmdShow) ;
     UpdateWindow (hwnd) ;
     
     while (GetMessage (&msg, NULL, 0, 0))
     {
          TranslateMessage (&msg) ;
          DispatchMessage (&msg) ;
     }
     return (int)msg.wParam ;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     HDC         hdc ;
     PAINTSTRUCT ps ;
     RECT        rect ;
	 static TCHAR szFileName[MAX_PATH + 2], szTitleName[MAX_PATH + 2] ;
	 DWORD		 err;
	
	 static Generator *ptr_generator;
	 ofstream  *ptr_ofstream;
	

     //HMENU	     hMenu;
     switch (message)
     {
     case WM_CREATE:
          //PlaySound (TEXT ("hellowin.wav"), NULL, SND_FILENAME | SND_ASYNC) ;
		 PopFileInitialize(hwnd);
		 ptr_generator = new Generator();
          return 0 ;

     case WM_PAINT:
          hdc = BeginPaint (hwnd, &ps) ;
          
          GetClientRect (hwnd, &rect) ;
		  DrawText (hdc, HOMEPATH.c_str() , -1, &rect,
                    DT_SINGLELINE | DT_CENTER | DT_VCENTER);

          EndPaint (hwnd, &ps) ;
          return 0 ;
          
     case WM_DESTROY:
          PostQuitMessage (0) ;
          return 0 ;
	 case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDM_APP_EXIT:
			SendMessage(hwnd, WM_CLOSE, 0, 0);
			return 0;
		case IDM_FILE_SAVEAS:
           if (PopFileSaveDlg (hwnd, szFileName, szTitleName))
           {
					//MessageBox (NULL, szFileName, szAppName, MB_OK | MB_ICONEXCLAMATION) ;
					ptr_ofstream = new ofstream(szFileName);
					ptr_generator->write(ptr_ofstream);
					ptr_ofstream->close();
					ptr_ofstream->~ofstream();
			}
			else
			{
				 err = CommDlgExtendedError();

				 switch(err)
				 {
				 case CDERR_DIALOGFAILURE:
					MessageBox (NULL, TEXT ("Konnte Datei Speichern Dialog nicht ˆffnen -> CDERR_DIALOGFAILURE"), szAppName, MB_ICONERROR) ;
					break;
				 case CDERR_FINDRESFAILURE:
					MessageBox (NULL, TEXT ("Konnte Datei Speichern Dialog nicht ˆffnen -> CDERR_FINDRESFAILURE"), szAppName, MB_ICONERROR) ;
					break;
				 case CDERR_INITIALIZATION:
					MessageBox (NULL, TEXT ("Konnte Datei Speichern Dialog nicht ˆffnen -> CDERR_INITIALIZATION"), szAppName, MB_ICONERROR) ;
					break;
				 case CDERR_LOADRESFAILURE:
					MessageBox (NULL, TEXT ("Konnte Datei Speichern Dialog nicht ˆffnen -> CDERR_LOADRESFAILURE"), szAppName, MB_ICONERROR) ;
					break;
				 case CDERR_LOADSTRFAILURE:
					MessageBox (NULL, TEXT ("Konnte Datei Speichern Dialog nicht ˆffnen -> CDERR_LOADSTRFAILURE"), szAppName, MB_ICONERROR) ;
					break;
				 case CDERR_LOCKRESFAILURE:
					MessageBox (NULL, TEXT ("Konnte Datei Speichern Dialog nicht ˆffnen -> CDERR_LOCKRESFAILURE"), szAppName, MB_ICONERROR) ;
					break;
				 case CDERR_MEMALLOCFAILURE:
					MessageBox (NULL, TEXT ("Konnte Datei Speichern Dialog nicht ˆffnen -> CDERR_MEMALLOCFAILURE"), szAppName, MB_ICONERROR) ;
					break;
				 case CDERR_MEMLOCKFAILURE:
					MessageBox (NULL, TEXT ("Konnte Datei Speichern Dialog nicht ˆffnen -> CDERR_MEMLOCKFAILURE"), szAppName, MB_ICONERROR) ;
					break;
				 case CDERR_NOHINSTANCE:
					MessageBox (NULL, TEXT ("Konnte Datei Speichern Dialog nicht ˆffnen -> CDERR_NOHINSTANCE"), szAppName, MB_ICONERROR) ;
					break;
				 case CDERR_NOHOOK:
					MessageBox (NULL, TEXT ("Konnte Datei Speichern Dialog nicht ˆffnen -> CDERR_NOHOOK"), szAppName, MB_ICONERROR) ;
					break;
				 case CDERR_NOTEMPLATE:
					MessageBox (NULL, TEXT ("Konnte Datei Speichern Dialog nicht ˆffnen -> CDERR_NOTEMPLATE"), szAppName, MB_ICONERROR) ;
					break;
				 case CDERR_STRUCTSIZE:
					MessageBox (NULL, TEXT ("Konnte Datei Speichern Dialog nicht ˆffnen -> CDERR_STRUCTSIZE"), szAppName, MB_ICONERROR) ;
					break;
				 case FNERR_BUFFERTOOSMALL:
					MessageBox (NULL, TEXT ("Konnte Datei Speichern Dialog nicht ˆffnen -> FNERR_BUFFERTOOSMALL"), szAppName, MB_ICONERROR) ;
					break;
				 case FNERR_INVALIDFILENAME:
					MessageBox (NULL, TEXT ("Konnte Datei Speichern Dialog nicht ˆffnen -> FNERR_INVALIDFILENAME"), szAppName, MB_ICONERROR) ;
					break;
				 case FNERR_SUBCLASSFAILURE:
					MessageBox (NULL, TEXT ("Konnte Datei Speichern Dialog nicht ˆffnen -> FNERR_SUBCLASSFAILURE"), szAppName, MB_ICONERROR) ;
					break;

				 }
			}
			return 0;
		}
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}




void PopFileInitialize (HWND hwnd)
{

     
     ofn.lStructSize       = sizeof (OPENFILENAME) ;
     ofn.hwndOwner         = hwnd ;
     ofn.hInstance         = NULL ;
     ofn.lpstrFilter       = szFilter ;
     ofn.lpstrCustomFilter = NULL ;
     ofn.nMaxCustFilter    = 0 ;
     ofn.nFilterIndex      = 0 ;
     ofn.lpstrFile         = NULL ;          // Bei ÷ffnen bzw. Schlieﬂen gesetzt
     ofn.nMaxFile          = MAX_PATH ;
     ofn.lpstrFileTitle    = NULL ;          // Bei ÷ffnen bzw. Schlieﬂen gesetzt
     ofn.nMaxFileTitle     = MAX_PATH ;
     ofn.lpstrInitialDir   = NULL ;
     ofn.lpstrTitle        = NULL ;
     ofn.Flags             = 0 ;             // Bei ÷ffnen bzw. Schlieﬂen gesetzt
     ofn.nFileOffset       = 0 ;
     ofn.nFileExtension    = 0 ;
     ofn.lpstrDefExt       = TEXT ("txt") ;
     ofn.lCustData         = 0L ;
     ofn.lpfnHook          = NULL ;
     ofn.lpTemplateName    = NULL ;
}

BOOL PopFileSaveDlg (HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName)
{
     ofn.hwndOwner         = hwnd ;
     ofn.lpstrFile         = pstrFileName ;
     ofn.lpstrFileTitle    = pstrTitleName ;
	 //ofn.lpstrInitialDir = HOMEPATH.c_str();
     ofn.Flags             = OFN_OVERWRITEPROMPT ;
     
     return GetSaveFileName (&ofn) ;
}
