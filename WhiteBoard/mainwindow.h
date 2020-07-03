#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "tmview.h"
#include <QMainWindow>
#include <QPaintEvent>
#include <QVector>
#include <QStringListModel>
#include "components.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPoint lastPoint;
    QPoint currentPoint;
    bool requiresVector=false;
    bool selectGroup=false;
    virtual void paintEvent(QPaintEvent *event);
    void registerComponents();
    bool clicked=false;

private slots:
    void on_drawFreeHandButton_clicked();

    void on_drawLineButton_clicked();

    void on_drawRectangleButton_clicked();

    void on_drawCircleButton_clicked();
    void on_selectGroup_clicked();

protected:
    virtual void keyPressEvent(QKeyEvent *event);
private:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    Ui::MainWindow *ui;
    int state=-1;
    bool isCircle=false;
    bool scribble=false;
    bool isFreeHand=false;
    bool isLine=false;
    bool isRectangle=false;
    DrawComponent *componentBeingUsed=nullptr;
    DrawComponent *nonVecterComponentBeingUsed=nullptr;
    TMView *view =nullptr;
    QVector<QPoint>* pointsVector=nullptr;
     QStringList stringList;
    QStringListModel *modelList;

};
#endif // MAINWINDOW_H
