#ifndef DEFAULTLATTICE_H
#define DEFAULTLATTICE_H


#include <QtWidgets/QWidget>
#include <QLabel>
#include <QCloseEvent>//重新定义关闭事件
#include <QFrame>
#include <QPushButton>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QVBoxLayout>
#include <QSystemTrayIcon>

#include <filewindow.h>
#include <monit.h>
#include <commemorial.h>

class QStringList;
class QListWidget;
class QListWidgetItem;

class DefaultLattice : public QWidget
{
    Q_OBJECT
public:
    filewindow* fileWin;
    Monit* mointWin;
    comMemorial* memWin;
public:
    DefaultLattice(QWidget *parent = 0);
    ~DefaultLattice();
    QFrame* topMenu;
    QFrame* lattice;
    QFrame* footMenu;
    QFrame* fileTopMemu;
    QFrame* fileLattice;
    QFrame* fileFootMenu;
    QMenu* sortMenu;
private:
    QPushButton *foldButton;//折叠/展开分区
    QPushButton *lockButton;//锁定/解锁分区
    QPushButton *skinButton;//切换主题
    QPushButton *seeAppButton;
    QPushButton *WordButton;
    QPushButton *PPTButton;
    QPushButton *ExcelButton;
    QPushButton *seeFileButton;

private:
    //托盘菜单相关
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QAction *quitAction;

private:
    void initDefaultLattice();    // 初始化默认格子
    void initFileLattice();       // 初始化文档格子
    void initTrayIcon();          // 初始化托盘菜单
    void initMonitLattice();      // 初始化实时性能监控器
    void initComMemorial();       // 初始化综合备忘录
    //void openFileLattice();       // 打开文档格子
    QPoint getQScreenSize();      // 获得窗体大小的方法
    void getFileData(QString path);           // 读取文件数据
    void setFileData(QString path);           // 写入文件数据
    QString defaultFilepath = "/bin/file.dat"; //默认保存文档目录的文件
    QString defaultApppath = "/bin/app.dat";   //默认保存应用目录的文件
    void closeEvent(QCloseEvent *event);
protected:
    bool eventFilter(QObject *watched, QEvent *evt);
private slots:
    void slot_itemClicked(QListWidgetItem*);
    void slot_itemFileClicked(QListWidgetItem*);
    void foldButtonClicked();
    void lockButtonClicked();
    void skinButtonClicked();
    void seeButtonClicked(int sel);
    void fileSelectButtonCilcked(int select);

    void trigersortMenu(QAction *act);
public:
    //添加鼠标事件
    bool moveWindows = true;
private:
    bool locked = false;
    bool unlock = true;
    //按钮的默认图片显示
    bool listView = false;
    bool lock = unlock;
    bool foldshow = true;
    //默认的文件选择状态
    bool docx = false;
    bool pptx = false;
    bool xlsx = false;
private:
    QStringList m_imgList;      // 文件目录下所有的图像文件名
    QListWidget *m_listWidget;  // 桌面预览窗口
    QListWidget *f_listWidget;  // 文件预览窗口
    QStringList f_fileList;
    QStringList w_fileList;      // 文件目录下所有的word文件名
    QStringList p_fileList;      // 文件目录下所有的ppt文件名
    QStringList e_fileList;      // 文件目录下所有的excel文件名
    QString m_strPath;          // 文件夹路径
    QString f_strPath;          // 文件夹路径
    QLabel m_showWidget;        // 图像显示窗口
    QVBoxLayout *mainLayout;
    QVBoxLayout *fileLayout;
signals:
    //void sendFilepath(QString); //用来传递数据的信号
};

#endif // DEFAULTLATTICE_H
