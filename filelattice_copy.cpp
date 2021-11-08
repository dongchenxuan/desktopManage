#include "filelattice.h"


void fileLattice::initfileLattice(){
    this->setMinimumSize(200, 200);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);
    //this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setStyleSheet("background: rgba(255, 255, 240 );");
    this->setWindowOpacity(1);
}
