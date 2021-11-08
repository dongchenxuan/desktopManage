#include "todo.h"

todo::todo(QWidget *parent) : QWidget(parent)
{
    init();

}

void todo::init()
{
    this->setWindowTitle("todo");
    this->setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint& ~Qt::WindowMinimizeButtonHint& ~Qt::WindowCloseButtonHint);//最大化最小化关闭失效
    this->setFixedSize(500,400);//设置窗口大小
    this->setAttribute(Qt::WA_TranslucentBackground);//背景透明
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);//在taskbar没有对应的任务图标，并且不能被关闭，如若需要做桌面悬浮工具栏，可以使用QDockWidget
    this->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);//去掉标题栏


    Addkongjian();

}

void todo::Addkongjian()
{
    QFont title ( "Microsoft YaHei",  10,   75);
    QFont font ( "Microsoft YaHei",  10,   25);

    QLabel *label = new QLabel(tr("坚持程度，决定了成功的高度！"));
    label->setFont(title);
    label->setAlignment(Qt::AlignHCenter);
    label->setGeometry(100,0,300,30);
    label->setParent(this);

    daiban = new QLineEdit("在此输入待办...");
    daiban->setFont(font);
    daiban->setGeometry(100,30,300,30);
    daiban->setParent(this);

    addbutton = new QPushButton();
    addbutton->setStyleSheet("QPushButton{"
                             "background-image: url(:/images/addTODO.png);"
                             "background-color: rgba(0, 0, 0, 0);"
                             "background-position:center;"
                             "background-repeat:no-repeat;}");
    addbutton->setToolTip("添加代办");
    addbutton->setFixedSize(50,50);
    addbutton->move(20,10);
//    //此处可以嵌入图片，目前我只用add来做,这里拜托邱宇了
    addbutton->setParent(this);
    QObject::connect(addbutton,&QPushButton::clicked,this,&todo::addbutton_clicked);

    delbutton = new QPushButton();
    delbutton->setStyleSheet("QPushButton{"
                             "background-image: url(:/images/delTODO.png);"
                             "background-color: rgba(0, 0, 0, 0);"
                             "background-position:center;"
                             "background-repeat:no-repeat;}");
    delbutton->setToolTip("代办已完成");
    delbutton->setFixedSize(50,50);
    delbutton->move(430,10);
//    //此处可以嵌入图片，目前我只用del来做
    delbutton->setParent(this);
    QObject::connect(delbutton,&QPushButton::clicked,this,&todo::delbutton_clicked);

    list = new QListWidget(this);
    list->move(20,70);
    list->setFont(font);
    list->setFixedSize(460,310);
    list->setIconSize(QSize(460,30));
    list->setMovement(QListView::Static);
    list->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
//    list->setContextMenuPolicy("contextMenuPolicy", Qt::CustomContextMenu);//添加右键管理菜单
    QObject::connect(list,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(show_menu(QPoint)));
    QObject::connect(list,SIGNAL(currentTextChanged(QString)),this,SLOT(setText(QString)));

}

void todo::addbutton_clicked()
{
    QString str = daiban->text();
    if( str=="在此输入待办..." || str.remove(QRegExp("\\s")) == "" || str=="请不要输入空格"){
        daiban->setText("请不要输入空格");
        return;
    }
    list->addItem(str);
    daiban->setText("在此输入待办...");

}

void todo::contextMenuEvent ( QContextMenuEvent * event )
{
    if(!(int(event->x()) >= 20 and int(event->x()) <= 480)){
        return;
    }
    if(!(int(event->y()) >= 70 and int(event->y()) <= 370)){
        return;
    }
    popMenu = new QMenu(this);
//    popMenu->addAction(new QAction("删除", this));

    del = new QAction("删除", this);
    popMenu->addAction(del);
    connect(this->del, SIGNAL(triggered()), this, SLOT(delbutton_clicked()));

    popMenu->exec(QCursor::pos()); // 菜单出现的位置为当前鼠标的位置
}



void todo::delbutton_clicked()
{
//    QListWidgetItem *deletedItem=this->list->takeItem(0);
//    delete deletedItem;
    /*获取当前选中的Item*/
    QList<QListWidgetItem*> items = list->selectedItems();

    if (items.count() > 0)
    {
       /*弹出询问对话框*/
      foreach(QListWidgetItem* var, items) {
         list->removeItemWidget(var);
         items.removeOne(var);
         delete var;
       }
     }
}


todo::~todo()
{

}
