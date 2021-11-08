#include "defaultlattice.h"
#include "filelattice.h"
#include <QApplication>

#include <windows.h>
//#include <QDesktopWidget>
#include <QScreen>


bool enumUserWindowsCB(HWND hwnd, LPARAM lParam)
{
    long wflags = GetWindowLong(hwnd, GWL_STYLE);
    if (!(wflags & WS_VISIBLE)) {
        return TRUE;
    };

    HWND sndWnd;
    if (!(sndWnd=FindWindowEx(hwnd, NULL, L"SHELLDLL_DefView", NULL))) {
        return TRUE;
    }
    HWND targetWnd;
    if (!(targetWnd=FindWindowEx(sndWnd, NULL, L"SysListView32", L"FolderView"))) {
        return TRUE;
    }

    HWND* resultHwnd = (HWND*)lParam;
    *resultHwnd = targetWnd;
    return FALSE;
}

HWND findDesktopIconWnd()
{
    HWND resultHwnd = NULL;
    EnumWindows((WNDENUMPROC)enumUserWindowsCB, (LPARAM)&resultHwnd);
    return resultHwnd;
}


int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication a(argc, argv);
    DefaultLattice w;


    /*
    HWND desktopHwnd = findDesktopIconWnd();
    // 设置桌面为父窗口
    if (desktopHwnd) {
        SetParent((HWND)w.winId(), desktopHwnd);
    }
    */


    /*
    w.setStyleSheet("background-color: rgba(0, 0, 0, 0);");
    w.setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);
    w.setAttribute(Qt::WA_TranslucentBackground);
    */


    QList<QScreen *> list_screen =  QGuiApplication::screens();  //多显示器
    QRect rect = list_screen.at(0)->geometry();
    int desktop_width = rect.width();
    /*
    if(dWidget==NULL){
        iWidth = 0;
        //iHeight = 0;
    }
    else{
        if(dWidget->screenCount()<=1){
            iWidth = dWidget->width();
            //iHeight = dWidget->height();
        }
        else{
            iWidth = dWidget->screenGeometry(0).width();
            //iHeight = dWidget->screenGeometry(0).height();
        }
    }
    */
    w.move(desktop_width-360,10);

    w.show();


    return a.exec();

}
