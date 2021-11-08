#ifndef FILELATTICE_H
#define FILELATTICE_H

#include <QWidget>

class fileLattice : public QWidget
{
    Q_OBJECT
public:
    explicit fileLattice(QWidget *parent = nullptr);

signals:

private:
    void initfileLattice(); //初始化

public slots:
};

#endif // FILELATTICE_H
