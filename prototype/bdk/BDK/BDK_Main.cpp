#if defined _M_IX86
  #pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
  #pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
  #pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
  #pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

#include <windows.h>
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")
#include <commdlg.h>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>
#include <shlobj.h>
#include "Decoder.h"
using namespace std;

#define IDM_FILE_SAVEAS 7001
#define IDM_FILE_OPEN	7003
#define IDM_APP_EXIT	7002

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;
void PopFileInitialize (HWND hwnd);
BOOL PopFileSaveDlg (HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName);
BOOL PopFileOpenDlg (HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName);
int info_out(HDC, unsigned int line_number, unsigned int line_nr_pixel);

static OPENFILENAME ofn;
PTCHAR HOMEPATH;	
static TCHAR szAppName[]	= TEXT ("HelloWin") ;
static TCHAR szFilter[]		= TEXT ("jpc Datei (*.jpc)\0*.jpc\0")  \
							  TEXT ("Alle Dateien (*.*)\0*.*\0\0") ;
TEXTMETRIC tm;
BDK::Decoder *ptr_decoder = NULL;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
     
     HWND         hwnd ;
     MSG          msg ;
	 WNDCLASS     wndclass ;
	 HMENU        hMenu;
	 HMENU        hMenuPopup;
	 stringstream s;
	
	
 InitCommonControls();
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

	HOMEPATH = new TCHAR[MAX_PATH + 1]; 
	HOMEPATH[MAX_PATH] = NULL;
	 SHGetFolderPath(NULL, CSIDL_MYPICTURES, NULL, SHGFP_TYPE_CURRENT, HOMEPATH);

	 hMenu		= CreateMenu();
	 hMenuPopup	= CreateMenu();
	 AppendMenu(hMenuPopup,MF_STRING, IDM_FILE_OPEN ,L"Öffnen");
	 AppendMenu(hMenuPopup,MF_STRING, IDM_FILE_SAVEAS,L"Speichern &unter ...");
	 AppendMenu(hMenuPopup,MF_SEPARATOR, 0, NULL);
	 AppendMenu(hMenuPopup,MF_STRING, IDM_APP_EXIT, L"&Beenden");
	 AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hMenuPopup, L"&Datei");
	

      hwnd = CreateWindow (szAppName,                 // Name der Fensterklasse
                  TEXT ("Generator"),                 // Fenstertitel
                  WS_OVERLAPPEDWINDOW,                // Fensterstil
                  CW_USEDEFAULT,                      // X-Position des Fensters
                  CW_USEDEFAULT,                      // Y-Position des Fensters
                  CW_USEDEFAULT,                      // Fensterbreite
                  CW_USEDEFAULT,                      // Fensterhöhe
                  NULL,                               // übergeordnetes Fenster
                  hMenu,                               // Menü
                  hInstance,                          // Programm-Kopiezähler (Programm-ID)
                  szCmdLine) ;                             // zusätzliche Parameter
     
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
     //RECT        rect ;
	 static TCHAR szFileName[MAX_PATH + 2], szTitleName[MAX_PATH + 2] ;
	 DWORD		 err;	
	 ifstream		*ptr_ifstream;
	 static unsigned int line_number = 0;
	 static unsigned int line_nr_pixel = 4;
	 static TCHAR temptext[20];
     //HMENU	     hMenu;
     switch (message)
     {
     case WM_CREATE:
         hdc = GetDC(hwnd);
		 GetTextMetrics(hdc, &tm);
		 line_nr_pixel = tm.tmHeight + tm.tmExternalLeading;
		 PopFileInitialize(hwnd);
			
		 ReleaseDC(hwnd, hdc);
          break;

     case WM_PAINT:
          hdc = BeginPaint (hwnd, &ps) ;
          info_out(hdc,line_number, line_nr_pixel);
          EndPaint (hwnd, &ps) ;
          break ;
          
     case WM_DESTROY:
          PostQuitMessage (0) ;
          break ;
	 case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDM_APP_EXIT:
			SendMessage(hwnd, WM_CLOSE, 0, 0);
			break;
		case IDM_FILE_SAVEAS:
           if (PopFileSaveDlg (hwnd, szFileName, szTitleName))
           {
				
			}
			else
			{
				 err = CommDlgExtendedError();

				 switch(err)
				 {
				 case CDERR_DIALOGFAILURE:
					MessageBox (NULL, TEXT ("Konnte Datei Speichern Dialog nicht öffnen -> CDERR_DIALOGFAILURE"), szAppName, MB_ICONERROR) ;
					break;
				 case CDERR_FINDRESFAILURE:
					MessageBox (NULL, TEXT ("Konnte Datei Speichern Dialog nicht öffnen -> CDERR_FINDRESFAILURE"), szAppName, MB_ICONERROR) ;
					break;
				 case CDERR_INITIALIZATION:
					MessageBox (NULL, TEXT ("Konnte Datei Speichern Dialog nicht öffnen -> CDERR_INITIALIZATION"), szAppName, MB_ICONERROR) ;
					break;
				 case CDERR_LOADRESFAILURE:
					MessageBox (NULL, TEXT ("Konnte Datei Speichern Dialog nicht öffnen -> CDERR_LOADRESFAILURE"), szAppName, MB_ICONERROR) ;
					break;
				 case CDERR_LOADSTRFAILURE:
					MessageBox (NULL, TEXT ("Konnte Datei Speichern Dialog nicht öffnen -> CDERR_LOADSTRFAILURE"), szAppName, MB_ICONERROR) ;
					break;
				 case CDERR_LOCKRESFAILURE:
					MessageBox (NULL, TEXT ("Konnte Datei Speichern Dialog nicht öffnen -> CDERR_LOCKRESFAILURE"), szAppName, MB_ICONERROR) ;
					break;
				 case CDERR_MEMALLOCFAILURE:
					MessageBox (NULL, TEXT ("Konnte Datei Speichern Dialog nicht öffnen -> CDERR_MEMALLOCFAILURE"), szAppName, MB_ICONERROR) ;
					break;
				 case CDERR_MEMLOCKFAILURE:
					MessageBox (NULL, TEXT ("Konnte Datei Speichern Dialog nicht öffnen -> CDERR_MEMLOCKFAILURE"), szAppName, MB_ICONERROR) ;
					break;
				 case CDERR_NOHINSTANCE:
					MessageBox (NULL, TEXT ("Konnte Datei Speichern Dialog nicht öffnen -> CDERR_NOHINSTANCE"), szAppName, MB_ICONERROR) ;
					break;
				 case CDERR_NOHOOK:
					MessageBox (NULL, TEXT ("Konnte Datei Speichern Dialog nicht öffnen -> CDERR_NOHOOK"), szAppName, MB_ICONERROR) ;
					break;
				 case CDERR_NOTEMPLATE:
					MessageBox (NULL, TEXT ("Konnte Datei Speichern Dialog nicht öffnen -> CDERR_NOTEMPLATE"), szAppName, MB_ICONERROR) ;
					break;
				 case CDERR_STRUCTSIZE:
					MessageBox (NULL, TEXT ("Konnte Datei Speichern Dialog nicht öffnen -> CDERR_STRUCTSIZE"), szAppName, MB_ICONERROR) ;
					break;
				 case FNERR_BUFFERTOOSMALL:
					MessageBox (NULL, TEXT ("Konnte Datei Speichern Dialog nicht öffnen -> FNERR_BUFFERTOOSMALL"), szAppName, MB_ICONERROR) ;
					break;
				 case FNERR_INVALIDFILENAME:
					MessageBox (NULL, TEXT ("Konnte Datei Speichern Dialog nicht öffnen -> FNERR_INVALIDFILENAME"), szAppName, MB_ICONERROR) ;
					break;
				 case FNERR_SUBCLASSFAILURE:
					MessageBox (NULL, TEXT ("Konnte Datei Speichern Dialog nicht öffnen -> FNERR_SUBCLASSFAILURE"), szAppName, MB_ICONERROR) ;
					break;

				 }
			}
			break;

		case IDM_FILE_OPEN:
			hdc = GetDC(hwnd);
           if (PopFileOpenDlg (hwnd, szFileName, szTitleName))
           {
				ptr_ifstream = new ifstream(szFileName,ios::binary);
				try{
					ptr_decoder = new BDK::Decoder(ptr_ifstream);
						
				}catch(BDK::Default_Exceptionhandler *e){
					MessageBox(NULL, (e->toString()).c_str() , szAppName, MB_ICONERROR) ;
				}
			}

		    ReleaseDC(hwnd, hdc);
			break;
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
     ofn.lpstrFile         = NULL ;          // Bei Öffnen bzw. Schließen gesetzt
     ofn.nMaxFile          = MAX_PATH ;
     ofn.lpstrFileTitle    = NULL ;          // Bei Öffnen bzw. Schließen gesetzt
     ofn.nMaxFileTitle     = MAX_PATH ;
     ofn.lpstrInitialDir   = NULL ;
     ofn.lpstrTitle        = NULL ;
     ofn.Flags             = 0 ;             // Bei Öffnen bzw. Schließen gesetzt
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

BOOL PopFileOpenDlg (HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName)
{
     ofn.hwndOwner         = hwnd ;
     ofn.lpstrFile         = pstrFileName ;
     ofn.lpstrFileTitle    = pstrTitleName ;
	 ofn.lpstrInitialDir   = HOMEPATH;
     ofn.Flags             = OFN_OVERWRITEPROMPT ;
     
     return GetOpenFileName (&ofn) ;
}


int info_out(HDC hdc, unsigned int line_number, unsigned int line_nr_pixel)
{
	TCHAR temptext[20];
	unsigned int iWork1 = 0;
	if(ptr_decoder != NULL){
		if(ptr_decoder->ptr_SIZ_part_one != NULL){

			lstrcpy(&temptext[0], L"SIZ");
			TextOut(hdc, 2, 2 + line_nr_pixel * line_number , &temptext[0], lstrlen(&temptext[0]));
			++line_number;
			lstrcpy(&temptext[0], L"Lsiz");
			TextOut(hdc, 2, 2 + line_nr_pixel * line_number , &temptext[0], lstrlen(&temptext[0]));
			wsprintf(&temptext[0],L"%d",ptr_decoder->ptr_SIZ_part_one->Lsiz);
			TextOut(hdc, 100, 2 + line_nr_pixel * line_number , &temptext[0], lstrlen(&temptext[0]));
			++line_number;

			lstrcpy(&temptext[0], L"Rsiz");
			TextOut(hdc, 2, 2 + line_nr_pixel * line_number , &temptext[0], lstrlen(&temptext[0]));
			wsprintf(&temptext[0],L"%d",ptr_decoder->ptr_SIZ_part_one->Rsiz);
			TextOut(hdc, 100, 2 + line_nr_pixel * line_number , &temptext[0], lstrlen(&temptext[0]));
			++line_number;

			lstrcpy(&temptext[0], L"Xsiz");
			TextOut(hdc, 2, 2 + line_nr_pixel * line_number , &temptext[0], lstrlen(&temptext[0]));
			wsprintf(&temptext[0],L"%d",ptr_decoder->ptr_SIZ_part_one->Xsiz);
			TextOut(hdc, 100, 2 + line_nr_pixel * line_number , &temptext[0], lstrlen(&temptext[0]));
			++line_number;

			lstrcpy(&temptext[0], L"Ysiz");
			TextOut(hdc, 2, 2 + line_nr_pixel * line_number , &temptext[0], lstrlen(&temptext[0]));
			wsprintf(&temptext[0],L"%d",ptr_decoder->ptr_SIZ_part_one->Ysiz);
			TextOut(hdc, 100, 2 + line_nr_pixel * line_number , &temptext[0], lstrlen(&temptext[0]));
			++line_number;

			lstrcpy(&temptext[0], L"XOsiz");
			TextOut(hdc, 2, 2 + line_nr_pixel * line_number , &temptext[0], lstrlen(&temptext[0]));
			wsprintf(&temptext[0],L"%d",ptr_decoder->ptr_SIZ_part_one->XOsiz);
			TextOut(hdc, 100, 2 + line_nr_pixel * line_number , &temptext[0], lstrlen(&temptext[0]));
			++line_number;

			lstrcpy(&temptext[0], L"YOsiz");
			TextOut(hdc, 2, 2 + line_nr_pixel * line_number , &temptext[0], lstrlen(&temptext[0]));
			wsprintf(&temptext[0],L"%d",ptr_decoder->ptr_SIZ_part_one->YOsiz);
			TextOut(hdc, 100, 2 + line_nr_pixel * line_number , &temptext[0], lstrlen(&temptext[0]));
			++line_number;

			lstrcpy(&temptext[0], L"XTOsiz");
			TextOut(hdc, 2, 2 + line_nr_pixel * line_number , &temptext[0], lstrlen(&temptext[0]));
			wsprintf(&temptext[0],L"%d",ptr_decoder->ptr_SIZ_part_one->XTOsiz);
			TextOut(hdc, 100, 2 + line_nr_pixel * line_number , &temptext[0], lstrlen(&temptext[0]));
			++line_number;

			lstrcpy(&temptext[0], L"YTOsiz");
			TextOut(hdc, 2, 2 + line_nr_pixel * line_number , &temptext[0], lstrlen(&temptext[0]));
			wsprintf(&temptext[0],L"%d",ptr_decoder->ptr_SIZ_part_one->YTOsiz);
			TextOut(hdc, 100, 2 + line_nr_pixel * line_number , &temptext[0], lstrlen(&temptext[0]));
			++line_number;

			lstrcpy(&temptext[0], L"Csiz");
			TextOut(hdc, 2, 2 + line_nr_pixel * line_number , &temptext[0], lstrlen(&temptext[0]));
			wsprintf(&temptext[0],L"%d",ptr_decoder->ptr_SIZ_part_one->Csiz);
			TextOut(hdc, 100, 2 + line_nr_pixel * line_number , &temptext[0], lstrlen(&temptext[0]));
			++line_number;
			
			for(iWork1 = 0; iWork1 < ptr_decoder->ptr_SIZ_part_one->siz_part_two.size(); iWork1++){
				lstrcpy(&temptext[0], L"Ssiz");
				TextOut(hdc, 2, 2 + line_nr_pixel * line_number , &temptext[0], lstrlen(&temptext[0]));
				wsprintf(&temptext[0],L"%d",ptr_decoder->ptr_SIZ_part_one->siz_part_two[iWork1]->Ssiz);
				TextOut(hdc, 100, 2 + line_nr_pixel * line_number , &temptext[0], lstrlen(&temptext[0]));		
				++line_number;

				lstrcpy(&temptext[0], L"YRsiz");
				TextOut(hdc, 2, 2 + line_nr_pixel * line_number , &temptext[0], lstrlen(&temptext[0]));
				wsprintf(&temptext[0],L"%d",ptr_decoder->ptr_SIZ_part_one->siz_part_two[iWork1]->YRsiz);
				TextOut(hdc, 100, 2 + line_nr_pixel * line_number , &temptext[0], lstrlen(&temptext[0]));		
				++line_number;

				lstrcpy(&temptext[0], L"XRsiz");
				TextOut(hdc, 2, 2 + line_nr_pixel * line_number , &temptext[0], lstrlen(&temptext[0]));
				wsprintf(&temptext[0],L"%d",ptr_decoder->ptr_SIZ_part_one->siz_part_two[iWork1]->XRsiz);
				TextOut(hdc, 100, 2 + line_nr_pixel * line_number , &temptext[0], lstrlen(&temptext[0]));		
				++line_number;

			}

		}
	}
	return line_number;
}


