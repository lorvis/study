#include <windows.h>
#include <CommCtrl.h>
#include <time.h>
#include <stdio.h>


const char g_szClassName[] = "myWindowClass";

enum {
    STATIC_ID1 = 1,
    STATIC_ID2,
    STATIC_ID3,
    STATIC_ID4,
    ID_TIMER,
};

typedef struct {
char * name;
double weight;
double height;
} fighter_s;

HINSTANCE hInst;
WNDPROC OldButtonProc;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ButtonProc (HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

int WINAPI WinMain(
                   HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow
                  )
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    hInst = hInstance;

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "The title of my window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 250,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
//        pos = (((int)clock())/CLOCKS_PER_SEC)%4;

        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
//    static HWND hButton;
    static HWND hStatic1;
    static HWND hStatic2;
    static HWND hStatic3;
    static HWND hStatic4;

    char staticText[50];

    fighter_s fightTeam[] = {
    {
       .name = "Boris",
       .weight = 76.3,
       .height = 183.5,
    },
    {
        .name = "John",
        .weight = 65.3,
        .height = 178,

    },
    {
        .name = "Cena",
        .weight = 133,
        .height = 195.21,

    },
    {
        .name =  "Nicolas",
        .weight = 66,
        .height = 166.666,
    },
    };

    int pos = 0;

    switch(msg)
    {
        case WM_CREATE:
//            hButton = CreateWindowEx(0,
//                              WC_BUTTON,
//                              "My Button",
//                              WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON,
//                              50, 50, 130, 23,
//                              hwnd,
//                              (HMENU)BUTTON_ID,
//                              hInst,
//                              NULL);
//            OldButtonProc = (WNDPROC) SetWindowLong (hButton, GWL_WNDPROC, (LONG) ButtonProc);
            hStatic1 = CreateWindowEx(0,
                              WC_STATIC,
                              "Label",
                              WS_CHILD | WS_VISIBLE,
                              50, 60, 180, 50,
                              hwnd,
                              (HMENU)STATIC_ID1,
                              hInst,
                              NULL);
            SetWindowText(hStatic1, TEXT("Static"));


             hStatic2 = CreateWindowEx(0,
                              WC_STATIC,
                              "Label",
                              WS_CHILD | WS_VISIBLE,
                              50, 80, 180, 20,
                              hwnd,
                              (HMENU)STATIC_ID1,
                              hInst,
                              NULL);
            SetWindowText(hStatic2, TEXT("Static"));

            hStatic3 = CreateWindowEx(0,
                              WC_STATIC,
                              "Label",
                              WS_CHILD | WS_VISIBLE,
                              50, 100, 180, 20,
                              hwnd,
                              (HMENU)STATIC_ID1,
                              hInst,
                              NULL);
            SetWindowText(hStatic3, TEXT("Static"));

            hStatic4 = CreateWindowEx(0,
                              WC_STATIC,
                              "Label",
                              WS_CHILD | WS_VISIBLE,
                              50, 120, 180, 20,
                              hwnd,
                              (HMENU)STATIC_ID1,
                              hInst,
                              NULL);
            SetWindowText(hStatic4, TEXT("Static"));

            const int TIMER_TICK = 1000;
            			int ret = SetTimer(hwnd, ID_TIMER, TIMER_TICK, NULL);
			if(ret == 0)
				MessageBox(hwnd, "Could not SetTimer()!", "Error", MB_OK | MB_ICONEXCLAMATION);

            break;

        case WM_TIMER:
        pos = (int)(((int)clock())/CLOCKS_PER_SEC)%4;

        sprintf(staticText,"Name : %s",fightTeam[pos].name);
        SetWindowText(hStatic1,TEXT(staticText));
        sprintf(staticText,"Weight : %.3f",fightTeam[pos].weight);
        SetWindowText(hStatic2,TEXT(staticText));
        sprintf(staticText,"Height is %.3f",fightTeam[pos].height);
        SetWindowText(hStatic3,TEXT(staticText));
        sprintf(staticText,"pos is %i",pos);
        SetWindowText(hStatic4,TEXT(staticText));

            break;

        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;

        default:

            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}


//LRESULT CALLBACK ButtonProc (HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
//    HWND parent = GetParent(hwnd);
//    HWND hStatic = GetDlgItem(parent, STATIC_ID);
//    switch (msg) {
//        case WM_LBUTTONDOWN:
//            SetWindowText(hStatic, TEXT("DOWN"));
//            break;
//        case WM_LBUTTONUP:
//            SetWindowText(hStatic, TEXT("UP"));
//            break;
//    }
//    return CallWindowProc(OldButtonProc, hwnd, msg, wp, lp);
//}
