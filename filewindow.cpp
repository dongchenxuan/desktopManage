#include "filewindow.h"

#include <QCloseEvent>
#include <QApplication>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QDesktopServices>

#include <QDebug>


filewindow::filewindow(QWidget *parent) : QWidget(parent)
{
    initSkinwindow();
    //readFile();
}

QString filewindow::getfilepath(){
    return this->path;
}

//接受父窗体传递的目录
void filewindow::receiveFilepath(QString str){
    //判断需要添加的是应用还是目录
    int select;
    QStringList temp = str.split("/");
    if(temp.at(temp.size()-1)==QString::fromLocal8Bit("app.dat"))
        select=0;
    else
        select=1;
    this->path = str;
    QFile file(str);
    //如果文件存在
    if(file.exists()){

    }
    else{
        QString filepath = QDir::currentPath() + "/bin";
        //qDebug() << filepath;
        QDir dir(filepath);
        //如果文件夹存在，直接创建文件
        if(dir.exists()){
            file.open( QIODevice::ReadWrite | QIODevice::Text );
            file.close();
        }
        else{
            dir.mkdir(filepath);
            file.open( QIODevice::ReadWrite | QIODevice::Text );
            file.close();
        }

    }

    //开始初始化控件
    mainframe = new QFrame(this);
    mainframe->setFrameShape(QFrame::HLine);
    mainframe->setFrameShadow(QFrame::Sunken);
    mainframe->setGeometry(QRect(0,0,800,450));

    addButton = new QPushButton;
    addButton->setGeometry(QRect(0,450,100,50));
    addButton->setParent(this);
    addButton->setStyleSheet("QPushButton{"
                              "background-color: rgba(0, 0, 0, 0);"
                              "background-image: url(:/images/filewin/add.png);"
                              "background-position:left;"
                              "background-origin:content;"
                              "padding-left:25px;"
                              "border:0.5px solid #9999FF;"
                              "color:black;"
                              "background-repeat:no-repeat;}");
    addButton->setText("添加");
    addButton->setToolTip("添加目录");
    connect(addButton, &QPushButton::clicked, this, [=](){addButtonClicked(select);});


    delButton = new QPushButton;
    delButton->setGeometry(QRect(700,450,100,50));
    delButton->setParent(this);
    delButton->setStyleSheet("QPushButton{"
                              "background-color: rgba(0, 0, 0, 0);"
                              "background-image: url(:/images/filewin/del.png);"
                              "background-position:left;"
                              "background-origin:content;"
                              "padding-left:25px;"
                              "border:0.5px solid #9999FF;"
                              "color:black;"
                              "background-repeat:no-repeat;}");
    delButton->setText("移除");
    delButton->setToolTip("移除目录");
    QObject::connect(delButton,&QPushButton::clicked, this, &filewindow::delButtonClicked);



    listview = new QListWidget(this);
    //listview->setIconSize(QSize(32,32));
    //listview->setSizeHint(QSize(32,32));
    listview->setResizeMode(QListView::Adjust);
    listview->setViewMode(QListView::ListMode);
    listview->setMovement(QListView::Static);
    listview->setSpacing(2);

    ItemModel = new QStandardItemModel(this);
    strList = new QStringList;

    //开始遍历文件存有的目录
    QFile rfile(str);
    if(rfile.open(QIODevice::ReadOnly|QIODevice::Text)){
        while(!rfile.atEnd()){
            QByteArray line = rfile.readLine();
            strList->append(line);
        }
        rfile.close();
    }

    for(int i=0;i<strList->size();i++){
        QListWidgetItem *listWidgetItem = new QListWidgetItem(strList->at(i));
        listWidgetItem->setSizeHint(QSize(32,32));
        listview->insertItem(i,listWidgetItem);
    }
    connect(listview, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(selectClicked(QListWidgetItem*)));


    // 窗口布局
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(listview);
    mainLayout->setMargin(0);
    this->mainframe->setLayout(mainLayout);
}

void filewindow::initSkinwindow(){
    this->setFixedSize(800, 500);
    /*
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    */
    this->setWindowTitle("更新目录");//窗体标题
    this->setStyleSheet("background: rgba(255, 255, 240 );");
    this->setWindowOpacity(1);
}

void filewindow::closeEvent(QCloseEvent *event){

    this->hide();
    event->ignore();
}

void filewindow::addButtonClicked(int sel){
    QString file;
    QString desktop = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    if(sel==0){
        file = QFileDialog::getOpenFileName(this, tr("选择应用"), desktop, tr("exe(*.exe);lnk(*.lnk);"));
        QString filepath = QDir::currentPath() + "/bin/app.dat";
        if(!file.isNull()){
            QFile *wfile = new QFile(filepath);
            //如果文件没有被占用
            if(wfile->open(QIODevice::ReadWrite | QIODevice::Append)==true){
                // 创建stream
                QTextStream txtOutput(wfile);
                txtOutput.setCodec("UTF-8");
                // 在stream追加数据，并换行
                txtOutput << file << endl;
                txtOutput.flush();

            }
            wfile->close();

        }
    }
    else{
        file = QFileDialog::getExistingDirectory(this, tr("选择目录"), desktop, QFileDialog::ShowDirsOnly);
        QString filepath = QDir::currentPath() + "/bin/file.dat";
        if(!file.isNull()){
            QFile *wfile = new QFile(filepath);
            //如果文件没有被占用
            if(wfile->open(QIODevice::ReadWrite | QIODevice::Append)==true){
                // 创建stream
                QTextStream txtOutput(wfile);
                txtOutput.setCodec("UTF-8");
                // 在stream追加数据，并换行
                txtOutput << file << endl;
                txtOutput.flush();

            }
            wfile->close();

        }
    }
}

void filewindow::delButtonClicked(){

}

void filewindow::selectClicked(QListWidgetItem * item){
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if("delButton" == btn->objectName()){
        //重置数据
        int n = listview->count();
        for(int i=0;i<n;i++){
            QListWidgetItem *item = listview->takeItem(0);
            delete item;
        }
    }


    /*
    strList->move(item,item);
    for(int i=0;i<strList->size();i++){
        QListWidgetItem *listWidgetItem = new QListWidgetItem(strList->at(i));
        listWidgetItem->setSizeHint(QSize(32,32));
        listview->insertItem(i,listWidgetItem);
    }
    */
}

void filewindow::readFile(QString path){


}

void filewindow::writeFile(QString path){


}
