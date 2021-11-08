#include "defaultlattice.h"

#include <QDir>
#include <QStringList>
#include <QListWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <Windows.h>
#include <QScreen>
#include <QPainter>
#include <QFrame>
#include <QPushButton>
#include <QToolButton>
#include <QLineEdit>
#include <qmenu>
#include <QCloseEvent>
#include <QIcon>
#include <QApplication>
#include <QProcess>
#include <QDesktopServices>
#include <QMessageBox>
#include <QPoint>
#include <qDebug>

//图标展示
const QSize IMAGE_SIZE(95, 95);//图标大小
const QSize ITEM_SIZE(95, 125);//整体大小
//列表展示
const QSize FILE_SIZE(32, 32);//图标大小
const QSize FITEM_SIZE(320, 32);//整体大小

DefaultLattice::DefaultLattice(QWidget *parent)
    : QWidget(parent)
{

    this->setFixedSize(350, 830);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);
    this->setAttribute(Qt::WA_TranslucentBackground);
    //this->setWindowOpacity(0.5);
    //this->setStyleSheet("background-color: rgba(255, 255, 255, 0.5);");

    this->initDefaultLattice();
    this->installEventFilter(this);
    this->initTrayIcon();

    this->initMonitLattice();
    this->initComMemorial();
    this->initFileLattice();
    //this->openFileLattice();
}

DefaultLattice::~DefaultLattice()
{

}

//拦截桌面窗口事件
void DefaultLattice::closeEvent(QCloseEvent *event)
{
    if(trayIcon->isVisible())
    {
        hide(); //隐藏窗口
        event->ignore(); //忽略事件
    }
}

/*
void DefaultLattice::openFileLattice(){
    //fileWin = new fileLattice;
    //fileWin ->show();
}
*/

void DefaultLattice::initDefaultLattice() {
    // 窗口基本设置
    //this->setWindowTitle("Image Preview");//窗体标题



    m_showWidget.setWindowTitle("Image Show");
    m_showWidget.setAlignment(Qt::AlignCenter);

    //顶部菜单栏
    topMenu = new QFrame(this);
    topMenu->setFrameShape(QFrame::HLine);
    topMenu->setFrameShadow(QFrame::Sunken);
    topMenu->setStyleSheet("QFrame{border:2px; "
                           "solid #014F84;"
                           "background:transparent;"
                           "border:1px solid #9900FF;}");
    topMenu->setGeometry(QRect(0,0,350,40));

    //窗体缩放
    foldButton = new QPushButton;//折叠/展开分区
    foldButton->setGeometry(QRect(5,5,30,30));
    foldButton->setParent(topMenu);
    foldButton->setStyleSheet("QPushButton{"
                              "background-image: url(:/images/foldOff.png);"
                              "background-color: rgba(0, 0, 0, 0);"
                              "background-position:center;"
                              "background-repeat:no-repeat;}");
    foldButton->setToolTip("收起分区");
    // 信号和槽的机制
    // 点击 b1 按钮， 窗口 w 关闭，涉及到两个对象之间的交互
    // 1、信号的发送者
    // 2、发送的信号         ----->  信号
    // 3、信号的接收者
    // 4、接收者要做的处理    ----->  槽
    QObject::connect(foldButton,&QPushButton::clicked, this, &DefaultLattice::foldButtonClicked);


    lockButton = new QPushButton;//格子是否锁定
    lockButton->setGeometry(QRect(35,5,30,30));
    lockButton->setParent(topMenu);
    lockButton->setStyleSheet("QPushButton{"
                              "background-image: url(:/images/unlock.png);"
                              "background-color: rgba(0, 0, 0, 0);"
                              "background-position:center;"
                              "background-repeat:no-repeat;}");
    lockButton->setToolTip("已解锁，分区可以任意拖动");
    QObject::connect(lockButton,&QPushButton::clicked, this, &DefaultLattice::lockButtonClicked);


    QLineEdit *nameLabel = new QLineEdit;//格子名称
    nameLabel->setGeometry(QRect(80,5,130,30));
    nameLabel->setText("新建格子");
    nameLabel->setStyleSheet("QLineEdit{"
                             "border-with:0;"
                             "border-style:outset;"
                             "background-color: rgba(255, 255, 255, 0.01);"
                             "qproperty-alignment:AlignHCenter;}");
    nameLabel->setParent(topMenu);

    QToolButton *addButton = new QToolButton;//添加
    addButton->setGeometry(QRect(225,5,30,30));
    addButton->setParent(topMenu);
    addButton->setStyleSheet("QToolButton{"
                             "background-image: url(:/images/new.png);"
                             "background-color: rgba(0, 0, 0, 0);"
                             "background-position:center;"
                             "background-repeat:no-repeat;}");
    addButton->setToolTip("添加");
    /*
    QMenu *menu=new QMenu();
    menu->addAction(QIcon(":/images/controls/name.png"),tr("名称"));
    menu->addAction(QIcon(":/images/controls/size.png"),tr("大小"));
    menu->addAction(QIcon(":/images/controls/file-type.png"),tr("文件类型"));
    menu->addAction(QIcon(":/images/controls/modification-date.png"),tr("修改日期"));
    menu->addSeparator();
    menu->addAction(QIcon(":/images/controls/checked.png"),tr("递增"));
    menu->addAction(QIcon(":/images/controls/uncheck.png"),tr("递减"));
    menu->addSeparator();
    menu->addAction(QIcon(":/images/controls/uncheck.png"),tr("实时排序"));
    sortButton->setMenu(menu);
    sortButton->setPopupMode(QToolButton::InstantPopup);
    */

    QPushButton *searchButton = new QPushButton;//搜索
    searchButton->setGeometry(QRect(255,5,30,30));
    searchButton->setParent(topMenu);
    searchButton->setStyleSheet("QPushButton{"
                                "background-image: url(:/images/search.png);"
                                "background-color: rgba(0, 0, 0, 0);"
                                "background-position:center;"
                                "background-repeat:no-repeat;}");
    searchButton->setToolTip("查找");

    skinButton = new QPushButton;//主题切换
    skinButton->setGeometry(QRect(285,5,30,30));
    skinButton->setParent(topMenu);
    skinButton->setStyleSheet("QPushButton{"
                              "background-image: url(:/images/skin.png);"
                              "background-color: rgba(0, 0, 0, 0);"
                              "background-position:center;"
                              "background-repeat:no-repeat;}");
    skinButton->setToolTip("更换主题");
    QObject::connect(skinButton,&QPushButton::clicked, this, &DefaultLattice::skinButtonClicked);

    QPushButton *moreButton = new QPushButton(this);//更多（设置）
    moreButton->setGeometry(QRect(315,5,30,30));
    moreButton->setParent(topMenu);
    moreButton->setStyleSheet("QPushButton{"
                              "background-image: url(:/images/more.png);"
                              "background-color: rgba(0, 0, 0, 0);"
                              "background-position:center;"
                              "background-repeat:no-repeat;}");
    moreButton->setToolTip("更多");



    //中间格子区
    lattice = new QFrame(this);
    lattice->setFrameShape(QFrame::HLine);
    lattice->setFrameShadow(QFrame::Sunken);
    lattice->setGeometry(QRect(0,40,350,320));
    lattice->setStyleSheet("QFrame{"
                           "border:2px; "
                           "solid #014F84;"
                           "background:transparent;"
                           "border:1px solid #9933FF;}");

    //底部菜单栏
    footMenu = new QFrame(this);
    footMenu->setFrameShadow(QFrame::Sunken);
    footMenu->setGeometry(QRect(0,360,350,40));
    footMenu->setStyleSheet("QFrame{border:2px; "
                            "solid #014F84;"
                            "background-color: rgba(255, 255, 255, 0.01);"
                            "border:1px solid #9966FF;}");
    QPushButton *topButton = new QPushButton;//置顶按钮
    topButton->setGeometry(QRect(5,5,30,30));
    topButton->setParent(footMenu);
    topButton->setStyleSheet("QPushButton{background-image: url(:/images/top.png);background-color: rgba(0, 0, 0, 0);background-position:center;background-repeat:no-repeat;}");
    topButton->setToolTip("文件置顶");

    QToolButton *sortButton = new QToolButton;//排序方式
    sortButton->setGeometry(QRect(285,5,30,30));
    sortButton->setParent(footMenu);
    sortButton->setStyleSheet("QToolButton{"
                              "background-image: url(:/images/sort.png);"
                              "background-color: rgba(0, 0, 0, 0);"
                              "background-position:center;"
                              "background-repeat:no-repeat;}");
    sortButton->setToolTip("排序方式");
    sortMenu = new QMenu();
    sortMenu->addAction(QIcon(":/images/controls/name.png"),tr("名称"));
    sortMenu->addAction(QIcon(":/images/controls/size.png"),tr("大小"));
    sortMenu->addAction(QIcon(":/images/controls/file-type.png"),tr("文件类型"));
    sortMenu->addAction(QIcon(":/images/controls/modification-date.png"),tr("修改日期"));
    sortMenu->addSeparator();
    sortMenu->addAction(QIcon(":/images/controls/checked.png"),tr("递增"));
    sortMenu->addAction(QIcon(":/images/controls/uncheck.png"),tr("递减"));
    sortMenu->addSeparator();
    sortMenu->addAction(QIcon(":/images/controls/uncheck.png"),tr("实时排序"));
    sortButton->setMenu(sortMenu);
    sortButton->setPopupMode(QToolButton::InstantPopup);
    connect (sortMenu,SIGNAL(triggered(QAction*)),this,SLOT(trigersortMenu(QAction*)));


    seeAppButton = new QPushButton;//展示方式
    seeAppButton->setGeometry(QRect(315,5,30,30));
    seeAppButton->setParent(footMenu);
    seeAppButton->setStyleSheet("QPushButton{"
                              "background-image: url(:/images/see.png);"
                              "background-color: rgba(0, 0, 0, 0);"
                              "background-position:center;"
                              "background-repeat:no-repeat;}");
    seeAppButton->setToolTip("添加//删除应用目录14");
    QObject::connect(seeAppButton,&QPushButton::clicked, this, [=](){seeButtonClicked(0);});



    // 判断路径是否存在
    //m_strPath = "G:\\QtCreator\\baseCaja\\desktopManage\\testImsges";
    //正确的相对目录
    m_strPath =QDir::currentPath() +  "/testImsges";
    //桌面目录
    //m_strPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    //qDebug() << m_strPath;
    QDir dir(m_strPath);
    //判断路径是否存在
    if (!dir.exists()) {
        return;
    }


    // 设置过滤器
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    QStringList filters;
    filters << "*.png" << "*.jpg";
    //filters << QString("*.lnk") << QString("*.pif");
    dir.setNameFilters(filters);
    m_imgList = dir.entryList();
    if (m_imgList.count() <= 0) {
        return;
    }

    // QListWidget基本设置
    m_listWidget = new QListWidget(this);
    m_listWidget->setIconSize(IMAGE_SIZE);
    m_listWidget->setResizeMode(QListView::Adjust);
    m_listWidget->setViewMode(QListView::IconMode);
    m_listWidget->setMovement(QListView::Static);
    m_listWidget->setSpacing(8);

    // 创建单元项
    for (int i = 0; i<m_imgList.count(); ++i) {
        QPixmap pixmap(m_strPath + "\\" + m_imgList.at(i));
        QListWidgetItem *listWidgetItem = new QListWidgetItem(QIcon(pixmap.scaled(IMAGE_SIZE)), m_imgList.at(i));
        listWidgetItem->setSizeHint(ITEM_SIZE);
        m_listWidget->insertItem(i, listWidgetItem);
    }

    // 窗口布局
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_listWidget);
    mainLayout->setMargin(0);
    this->lattice->setLayout(mainLayout);

    // 信号与槽
    connect(m_listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slot_itemClicked(QListWidgetItem*)));
    //f_listWidget

}

//文件分类格子初始化
void DefaultLattice::initFileLattice(){
    fileTopMemu = new QFrame(this);
    fileTopMemu->setFrameShape(QFrame::HLine);
    fileTopMemu->setFrameShadow(QFrame::Sunken);
    fileTopMemu->setStyleSheet("QFrame{border:2px; "
                               "solid #014F84;"
                               "background:transparent;"
                               "border:1px solid #9999FF;}");
    //QRect(x,y,w,h)
    fileTopMemu->setGeometry(QRect(0,400,350,40));


    WordButton = new QPushButton;
    WordButton->setGeometry(QRect(0,0,350/3,40));
    WordButton->setParent(fileTopMemu);
    WordButton->setStyleSheet("QPushButton{"
                              "background-color: rgba(0, 0, 0, 0);"
                              "background-image: url(:/images/word.png);"
                              "background-position:left ;"
                              "background-origin:content;"
                              "padding-left:25px;"
                              "border:0.5px solid #9999FF;"
                              "color:Blue;"
                              "background-repeat:no-repeat;}");
    WordButton->setText("   Word");
    WordButton->setToolTip("查看我的文档");
    //QObject::connect(WordButton,&QPushButton::clicked, this, &DefaultLattice::fileSelectButtonCilcked);
    connect(WordButton, &QPushButton::clicked, this, [=](){fileSelectButtonCilcked(0);});



    PPTButton = new QPushButton;
    PPTButton->setGeometry(QRect(350/3,0,350/3,40));
    PPTButton->setParent(fileTopMemu);
    PPTButton->setStyleSheet("QPushButton{"
                             "background-color: rgba(0, 0, 0, 0);"
                             "background-image: url(:/images/ppt.png);"
                             "background-position:left ;"
                             "background-origin:content;"
                             "padding-left:25px;"
                             "border:0.5px solid #9999FF;"
                             "color:Chocolate;"
                             "background-repeat:no-repeat;}");
    PPTButton->setText("   PPT  ");
    PPTButton->setToolTip("查看我的幻灯片");
    connect(PPTButton, &QPushButton::clicked, this, [=](){fileSelectButtonCilcked(1);});



    ExcelButton = new QPushButton;
    ExcelButton->setGeometry(QRect(350/3*2,0,350/3+1,40));
    ExcelButton->setParent(fileTopMemu);
    ExcelButton->setStyleSheet("QPushButton{"
                               "background-color: rgba(0, 0, 0, 0);"
                               "background-image: url(:/images/excel.png);"
                               "background-position:left ;"
                               "background-origin:content;"
                               "padding-left:25px;"
                               "border:0.5px solid #9999FF;"
                               "color:Green;"
                               "background-repeat:no-repeat;}");
    ExcelButton->setText("   Excel");
    ExcelButton->setToolTip("查看我的表格");
    connect(ExcelButton, &QPushButton::clicked, this, [=](){fileSelectButtonCilcked(2);});

    fileLattice = new QFrame(this);
    fileLattice->setFrameShape(QFrame::HLine);
    fileLattice->setFrameShadow(QFrame::Sunken);
    fileLattice->setStyleSheet("QFrame{"
                               "border:2px; "
                               "solid #014F84;"
                               "background:transparent;"
                               "border:1px solid #99CCFF;}");
    //QRect(x,y,w,h)
    fileLattice->setGeometry(QRect(0,440,350,350));


    fileFootMenu = new QFrame(this);
    fileFootMenu->setFrameShape(QFrame::HLine);
    fileFootMenu->setFrameShadow(QFrame::Sunken);
    fileFootMenu->setStyleSheet("QFrame{"
                                "border:2px; "
                                "solid #014F84;"
                                "background-color: rgba(255, 255, 255, 0.01);"
                                "border:1px solid #99FFFF;}");
    //QRect(x,y,w,h)
    fileFootMenu->setGeometry(QRect(0,790,350,40));

    seeFileButton = new QPushButton;//展示方式
    seeFileButton->setGeometry(QRect(315,5,30,30));
    seeFileButton->setParent(fileFootMenu);
    seeFileButton->setStyleSheet("QPushButton{"
                              "background-image: url(:/images/see.png);"
                              "background-color: rgba(0, 0, 0, 0);"
                              "background-position:center;"
                              "background-repeat:no-repeat;}");
    seeFileButton->setToolTip("添加//删除文件目录");

    QObject::connect(seeFileButton,&QPushButton::clicked, this, [=](){seeButtonClicked(1);});


    // 判断路径是否存在
    //f_strPath = "G:\\QtCreator\\baseCaja\\desktopManage\\testFile";
    //正确的相对目录
    f_strPath =QDir::currentPath() +  "/testFile";
    //qDebug()<<f_strPath;//测试目录需要引用头文件qDebug
    QDir dirfiles(f_strPath);
    if (!dirfiles.exists()) {
        return;
    }
    // 设置过滤器
    dirfiles.setFilter(QDir::Files | QDir::NoSymLinks);
    QStringList files;
    //files << "*.png" << "*.jpg" ;
    files << "*.docx" << "*.doc" << "*.pptx" << "*.ppt" << "*.xlsx" << "*.xls";
    dirfiles.setNameFilters(files);
    f_fileList = dirfiles.entryList();
    if (f_fileList.count() <= 0) {
        return;
    }

    // QListWidget基本设置
    f_listWidget = new QListWidget(this);
    f_listWidget->setIconSize(FILE_SIZE);
    f_listWidget->setResizeMode(QListView::Adjust);
    f_listWidget->setViewMode(QListView::ListMode);
    f_listWidget->setMovement(QListView::Static);
    f_listWidget->setSpacing(2);

    // 创建单元项
    for (int i = 0; i<f_fileList.count(); ++i) {

        QString filename = f_fileList.at(i);
        QStringList tempList = filename.split(".");
        if(tempList.at(tempList.count()-1)==QString::fromLocal8Bit("docx")||
                tempList.at(tempList.count()-1)==QString::fromLocal8Bit("doc")){
            QPixmap pixmap(":/images/word.png");
            QListWidgetItem *listWidgetItem = new QListWidgetItem(QIcon(pixmap.scaled(FILE_SIZE)), f_fileList.at(i));
            listWidgetItem->setSizeHint(FITEM_SIZE);
            f_listWidget->insertItem(i, listWidgetItem);
            w_fileList << f_fileList.at(i);
        }
        else if(tempList.at(tempList.count()-1)==QString::fromLocal8Bit("pptx")||
                tempList.at(tempList.count()-1)==QString::fromLocal8Bit("ppt")){
            QPixmap pixmap(":/images/ppt.png");
            QListWidgetItem *listWidgetItem = new QListWidgetItem(QIcon(pixmap.scaled(FILE_SIZE)), f_fileList.at(i));
            listWidgetItem->setSizeHint(FITEM_SIZE);
            f_listWidget->insertItem(i, listWidgetItem);
            p_fileList << f_fileList.at(i);
        }
        else {
            QPixmap pixmap(":/images/excel.png");
            QListWidgetItem *listWidgetItem = new QListWidgetItem(QIcon(pixmap.scaled(FILE_SIZE)), f_fileList.at(i));
            listWidgetItem->setSizeHint(FITEM_SIZE);
            f_listWidget->insertItem(i, listWidgetItem);
            e_fileList << f_fileList.at(i);
        }
    }

    fileLayout = new QVBoxLayout;
    fileLayout->addWidget(f_listWidget);
    fileLayout->setMargin(0);
    this->fileLattice->setLayout(fileLayout);


}

//实时性能监控器初始化
void DefaultLattice::initMonitLattice(){
    mointWin = new Monit;
    mointWin->show();
}

//代办初始化
void DefaultLattice::initComMemorial(){
    memWin = new comMemorial;

    QPoint point=getQScreenSize();
    memWin->move(point.x()-870,10);
    memWin->show();

}

//托盘初始化
void DefaultLattice::initTrayIcon(){

    QIcon ico = QIcon(":ico.ico");
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(ico);
    trayIcon->setToolTip("爱上桌面");
    trayIcon->show(); //必须调用，否则托盘图标不显示

    //创建菜单项动作(以下动作只对windows有效)
    /*
    minimizeAction = new QAction("个人中心", this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide())); //绑定信号槽

    maximizeAction = new QAction("检查更新", this);
    connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

    restoreAction = new QAction("设置", this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showSetFocus()));
    */

    quitAction = new QAction("退出~", this);
    QObject::connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit())); //关闭应用，qApp对应的是程序全局唯一指针

    //创建托盘菜单(必须先创建动作，后添加菜单项，还可以加入菜单项图标美化)
    trayIconMenu = new QMenu(this);
    trayIconMenu->setStyleSheet("background-color: rgb(248, 248, 255);");
    /*
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    */
    trayIconMenu->addSeparator();
    //addAction(QIcon(":/images/controls/uncheck.png"),tr("实时排序"));
    trayIconMenu->addAction(quitAction);
    trayIcon->setContextMenu(trayIconMenu);
    connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
        this,SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));


}

bool DefaultLattice::eventFilter(QObject *watched, QEvent *evt)
{
    static QPoint mousePoint;
    static bool mousePressed = false;

    QMouseEvent *event = static_cast<QMouseEvent *>(evt);
    if (event->type() == QEvent::MouseButtonPress) {
        if (event->button() == Qt::LeftButton) {
            mousePressed = true;
            mousePoint = event->globalPos() - this->pos();

            return true;
        } else {
            exit(0);
        }
    } else if (event->type() == QEvent::MouseButtonRelease) {
        mousePressed = false;
        return true;
    } else if (event->type() == QEvent::MouseMove) {
        if (mousePressed && (event->buttons() && Qt::LeftButton)) {
            if(moveWindows == true){
                this->move(event->globalPos() - mousePoint);
                return true;
            }
        }
    }

    return QWidget::eventFilter(watched, event);
}

// 最大化窗口显示图像
void DefaultLattice::slot_itemClicked(QListWidgetItem * item) {
    m_showWidget.setPixmap(QPixmap(m_strPath + "\\" + m_imgList.at(m_listWidget->row(item))));
    m_showWidget.showMaximized();
}


//
void DefaultLattice::seeButtonClicked(int sel){
    QString path = QDir::currentPath() + defaultApppath;
    fileWin = new filewindow;

    if(sel==0)
        path = QDir::currentPath() + defaultApppath;
    if(sel==1)
        path = QDir::currentPath() + defaultFilepath;
    //qDebug() << path;
    //connect(this,SIGNAL(sendFilepath(QString)),fileWin,SIGNAL(receiveFilepath(QString)));
    fileWin->receiveFilepath(path);
    //emit sendFilepath(path);
    fileWin->show();
    /*

    */
    /*
    if(listView==false){
        viewButton->setToolTip("切换至图标模式");
        viewButton->setStyleSheet("QPushButton{"
                                  "background-image: url(:/images/tileView.png);"
                                  "background-color: rgba(0, 0, 0, 0);"
                                  "background-position:center;"
                                  "background-repeat:no-repeat;}");
        listView==true;
    }
    else{
        viewButton->setToolTip("切换至列表模式");
        viewButton->setStyleSheet("QPushButton{"
                                  "background-image: url(:/images/listView.png);"
                                  "background-color: rgba(0, 0, 0, 0);"
                                  "background-position:center;"
                                  "background-repeat:no-repeat;}");
        listView==true;
    }
    */
}

//打开文档Word、PPT、Excel
void DefaultLattice::slot_itemFileClicked(QListWidgetItem * item) {
    QString  path = f_strPath;
    if(docx == true){
        path += "/" + w_fileList.at(f_listWidget->row(item));
        QFile file(path);
        if(file.exists()){
            QDesktopServices::openUrl(QUrl::fromLocalFile(path));
            return;
        }else{
            QMessageBox mesg;
            mesg.warning(this,"警告","文件不存在，无法读取");
            return;
        }
        //qDebug()<< w_fileList.at(f_listWidget->row(item));
    }
    else if(pptx == true){
        path += "/" + p_fileList.at(f_listWidget->row(item));
        QFile file(path);
        if(file.exists()){
            QDesktopServices::openUrl(QUrl::fromLocalFile(path));
            return;
        }else{
            QMessageBox mesg;
            mesg.warning(this,"警告","文件不存在，无法读取");
            return;
        }
        //qDebug()<< p_fileList.at(f_listWidget->row(item));
    }
    else{
        path += "/" + e_fileList.at(f_listWidget->row(item));
        QFile file(path);
        if(file.exists()){
            QDesktopServices::openUrl(QUrl::fromLocalFile(path));
            return;
        }else{
            QMessageBox mesg;
            mesg.warning(this,"警告","文件不存在，无法读取");
            return;
        }
        //qDebug()<< e_fileList.at(f_listWidget->row(item));
    }
}

void DefaultLattice::foldButtonClicked()
{

    if(foldshow==true){
        foldButton->setToolTip("展开分区");
        foldButton->setStyleSheet("QPushButton{"
                                  "background-image: url(:/images/foldOn.png);"
                                  "background-color: rgba(0, 0, 0, 0);"
                                  "background-position:center;"
                                  "background-repeat:no-repeat;}");
        lattice->setVisible(false);
        footMenu->setVisible(false);
        fileTopMemu->setVisible(false);
        fileLattice->setVisible(false);
        fileFootMenu->setVisible(false);
        foldshow = false;
    }
    else{
        foldButton->setToolTip("收起分区");
        foldButton->setStyleSheet("QPushButton{"
                                  "background-image: url(:/images/foldOff.png);"
                                  "background-color: rgba(0, 0, 0, 0);"
                                  "background-position:center;"
                                  "background-repeat:no-repeat;}");
        lattice->setVisible(true);
        footMenu->setVisible(true);
        fileTopMemu->setVisible(true);
        fileLattice->setVisible(true);
        fileFootMenu->setVisible(true);
        foldshow = true;
    }

}

void DefaultLattice::lockButtonClicked()
{
    if(lock==unlock){
        lockButton->setToolTip("已锁定，分区无法移动");
        lockButton->setStyleSheet("QPushButton{"
                                  "background-image: url(:/images/locked.png);"
                                  "background-color: rgba(0, 0, 0, 0);"
                                  "background-position:center;"
                                  "background-repeat:no-repeat;}");
        lock = locked;
        moveWindows = locked;
    }
    else{
        lockButton->setToolTip("已解锁，分区可以任意拖动");
        lockButton->setStyleSheet("QPushButton{"
                                  "background-image: url(:/images/unlock.png);"
                                  "background-color: rgba(0, 0, 0, 0);"
                                  "background-position:center;"
                                  "background-repeat:no-repeat;}");
        lock = unlock;
        moveWindows = unlock;
    }
}

void DefaultLattice::trigersortMenu(QAction *act){

}

void DefaultLattice::skinButtonClicked(){

}

void DefaultLattice::fileSelectButtonCilcked(int select){
    /*
    fileLayout = new QVBoxLayout;
    fileLayout->addWidget(f_listWidget);
    fileLayout->setMargin(0);
    this->fileLattice->setLayout(fileLayout);
    */
    int n = f_listWidget->count();
    if(n>0){
        for(int i=0;i<n;i++){
            /*
            使用takeItem(row)函数将QListWidget中的第row个item移除，
            移除需要使用delete手动释放其在堆上占用的空间
            */
            //这里是0，不是i，因为每移除一个item都会导致每个item的row发生变化
            QListWidgetItem *item = f_listWidget->takeItem(0);
            delete item;
        }
        //fileLayout->addWidget(f_listWidget);
    }


    if(select == 0){
        docx = true ;
        pptx = false;
        xlsx = false;
        WordButton->setStyleSheet("QPushButton{"
                                   "background-color: rgba(2, 73, 206, 0.3);"
                                   "background-image: url(:/images/word.png);"
                                   "background-position:left ;"
                                   "background-origin:content;"
                                   "padding-left:25px;"
                                   "border:0.5px solid #9999FF;"
                                   "color:Blue;"
                                   "background-repeat:no-repeat;}");
        PPTButton->setStyleSheet("QPushButton{"
                                   "background-color: rgba(0, 0, 0, 0);"
                                   "background-image: url(:/images/ppt.png);"
                                   "background-position:left ;"
                                   "background-origin:content;"
                                   "padding-left:25px;"
                                   "border:0.5px solid #9999FF;"
                                   "color:Chocolate;"
                                   "background-repeat:no-repeat;}");
        ExcelButton->setStyleSheet("QPushButton{"
                                   "background-color: rgba(0, 0, 0, 0);"
                                   "background-image: url(:/images/excel.png);"
                                   "background-position:left ;"
                                   "background-origin:content;"
                                   "padding-left:25px;"
                                   "border:0.5px solid #9999FF;"
                                   "color:Green;"
                                   "background-repeat:no-repeat;}");

        // 创建单元项
        for (int i = 0; i<w_fileList.count(); ++i) {
            QPixmap pixmap(":/images/word.png");
            QListWidgetItem *listWidgetItem = new QListWidgetItem(QIcon(pixmap.scaled(FILE_SIZE)), w_fileList.at(i));
            listWidgetItem->setSizeHint(FITEM_SIZE);
            f_listWidget->insertItem(i, listWidgetItem);
        }
        connect(f_listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slot_itemFileClicked(QListWidgetItem*)));

    }

    else if(select == 1){
        docx = false ;
        pptx = true;
        xlsx = false;
        WordButton->setStyleSheet("QPushButton{"
                                   "background-color: rgba(0, 0, 0, 0);"
                                   "background-image: url(:/images/word.png);"
                                   "background-position:left ;"
                                   "background-origin:content;"
                                   "padding-left:25px;"
                                   "border:0.5px solid #9999FF;"
                                   "color:Blue;"
                                   "background-repeat:no-repeat;}");
        PPTButton->setStyleSheet("QPushButton{"
                                   "background-color: rgba(242, 105, 30, 0.3);"
                                   "background-image: url(:/images/ppt.png);"
                                   "background-position:left ;"
                                   "background-origin:content;"
                                   "padding-left:25px;"
                                   "border:0.5px solid #9999FF;"
                                   "color:Chocolate;"
                                   "background-repeat:no-repeat;}");
        ExcelButton->setStyleSheet("QPushButton{"
                                   "background-color: rgba(0, 0, 0, 0);"
                                   "background-image: url(:/images/excel.png);"
                                   "background-position:left ;"
                                   "background-origin:content;"
                                   "padding-left:25px;"
                                   "border:0.5px solid #9999FF;"
                                   "color:Green;"
                                   "background-repeat:no-repeat;}");
        for (int i = 0; i<p_fileList.count(); ++i) {
            QPixmap pixmap(":/images/ppt.png");
            QListWidgetItem *listWidgetItem = new QListWidgetItem(QIcon(pixmap.scaled(FILE_SIZE)), p_fileList.at(i));
            listWidgetItem->setSizeHint(FITEM_SIZE);
            f_listWidget->insertItem(i, listWidgetItem);
        }
        connect(f_listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slot_itemFileClicked(QListWidgetItem*)));

    }

    else{
        docx = false ;
        pptx = false;
        xlsx = true;
        WordButton->setStyleSheet("QPushButton{"
                                   "background-color: rgba(0, 0, 0, 0);"
                                   "background-image: url(:/images/word.png);"
                                   "background-position:left ;"
                                   "background-origin:content;"
                                   "padding-left:25px;"
                                   "border:0.5px solid #9999FF;"
                                   "color:Blue;"
                                   "background-repeat:no-repeat;}");
        PPTButton->setStyleSheet("QPushButton{"
                                   "background-color: rgba(0, 0, 0, 0);"
                                   "background-image: url(:/images/ppt.png);"
                                   "background-position:left ;"
                                   "background-origin:content;"
                                   "padding-left:25px;"
                                   "border:0.5px solid #9999FF;"
                                   "color:Chocolate;"
                                   "background-repeat:no-repeat;}");
        ExcelButton->setStyleSheet("QPushButton{"
                                   "background-color: rgba(2, 201, 30, 0.3);"
                                   "background-image: url(:/images/excel.png);"
                                   "background-position:left ;"
                                   "background-origin:content;"
                                   "padding-left:25px;"
                                   "border:0.5px solid #9999FF;"
                                   "color:Green;"
                                   "background-repeat:no-repeat;}");
        for (int i = 0; i<e_fileList.count(); ++i) {
            QPixmap pixmap(":/images/excel.png");
            QListWidgetItem *listWidgetItem = new QListWidgetItem(QIcon(pixmap.scaled(FILE_SIZE)), e_fileList.at(i));
            listWidgetItem->setSizeHint(FITEM_SIZE);
            f_listWidget->insertItem(i, listWidgetItem);
        }
        connect(f_listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slot_itemFileClicked(QListWidgetItem*)));


    }
}

QPoint DefaultLattice::getQScreenSize(){
    QList<QScreen *> list_screen =  QGuiApplication::screens();  //多显示器
    QRect rect = list_screen.at(0)->geometry();
    int desktop_width = rect.width();
    int desktop_height = rect.height();

    return QPoint(desktop_width,desktop_height);
}

void DefaultLattice::getFileData(QString path){

}

void DefaultLattice::setFileData(QString path){

}
