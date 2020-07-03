#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DrawComponent.h"
#include "components.h"
#include "tmview.h"
#include <QPixmap>
#include <QPainter>
#include <QRect>
#include <QFont>
#include <QTextStream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
        this->view =new TMView() ;

this->modelList=new QStringListModel();
this->ui->componentList->setModel(this->modelList);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::registerComponents(){

    this->view =new TMView() ;

}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::RightButton){
       QPoint lastPoint2(event->pos().rx()-20,event->pos().ry()-10);
        int x=(event->pos().rx())-20;
        int y =(event->pos().ry())-10;
        if(x<0 || y <0)return;
        int w=(int)680*0.80;
        int h=(int)550*0.80;
        if(x>w || y>h) return;
        clicked=true;
        QTextStream(stdout)<<"Right Click"<<QString::number(x)<<","<<QString::number(y);
        this->lastPoint=lastPoint2;
        update();
    }
//this->ui->textarea->setPlainText("mouse pressed"+QString::number(event->pos().rx())+","+QString::number(event->pos().ry()));
    if(event->button()==Qt::LeftButton){
        if (this->view->isComponentSelected()){
            clicked=false;
            this->view->unSelectComponent();
        }
        QPoint lastPoint2(event->pos().rx()-20,event->pos().ry()-10);
        int x=(event->pos().rx())-20;
        int y =(event->pos().ry())-10;
        if(x<0 || y <0)return;
        int w=(int)680*0.80;
        int h=(int)550*0.80;
        QTextStream(stdout)<<QString::number(x)<<","<<QString::number(y);
        if(x>w || y>h) return;

 //       this->view->processClick(x,y);

        lastPoint = event->pos();
        if (this->pointsVector==nullptr){
            return;
        }
        this->pointsVector->append(lastPoint2);
        QTextStream(stdout)<<"mousePressEvent"<<QString::number(event->pos().rx())<<","<<QString::number(event->pos().ry());


        scribble=true;
    }
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if((event->MouseMove)&& scribble && clicked==false){
        QPoint currentPoint2(event->pos().rx()-20,event->pos().ry()-10);
        currentPoint=event->pos();
        this->pointsVector->append(currentPoint2);
        QTextStream(stdout)<<"mouse moved"<<endl;

        update();
        //lastPoint=currentPoint;
   }

}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){

    if((event->button()==Qt::LeftButton) && scribble && clicked==false){
        int x=(event->pos().rx())-20;
        int y =(event->pos().ry())-10;
        if(x<0 || y<0) return;
//        if(x<20 && y<10)return;
        int w=(int)680*0.80;
        int h=(int)550*0.80;
        if(x>w || y >h )return;


        this->pointsVector->append(QPoint(event->pos().rx()-20,event->pos().ry()-10));
    currentPoint=event->pos();
    QTextStream(stdout)<<"mouse relaesed"<<endl;

    if(this->requiresVector){
   this->pointsVector=new QVector<QPoint>;
    QString className = this->componentBeingUsed->toString();
    QTextStream(stdout)<<className<<"*******************************";
       DrawComponent *component=nullptr;
    if(className.compare("Free Hand")==0 && isFreeHand){
   component=new FreeHandComponent(this->pointsVector,"black");

}
    if(className.compare("Line")==0 && isLine){
    component=new LineComponent(this->pointsVector,0,"black");

    }
    if(className.compare("Rectangle")==0 && isRectangle){
        component=new RectangleComponent(this->pointsVector,0,"black");
    }
    if(className.compare("Ellipse")==0 && isCircle){
        component=new EllipseComponent(this->pointsVector,"black");
    }
    if(className.compare(("Group"))==0 && selectGroup){
        this->view->addGroup(new Group());
        this->stringList.push_front("Group");
        this->modelList->setStringList(this->stringList);

    }
   if(component!=nullptr){
    this->view->add(component);
    this->componentBeingUsed=component;
    this->stringList.push_front(component->toString());
    this->modelList->setStringList(this->stringList);
    this->ui->componentList->setModel(this->modelList);
   }

    } QTextStream(stdout)<<"size:"<<QString::number(this->pointsVector->size())<<endl;
    update();


    }
}


void MainWindow::keyPressEvent(QKeyEvent *event){
if(this->view->isComponentSelected()){
    switch (event->key()) {
    case Qt::Key_Down:
    {QTextStream(stdout)<<"down";
        this->view->moveSelectedComponentByDistance(0,10);
         update();
        break;
    }
     case Qt::Key_Up:
     {   QTextStream(stdout)<<"up";
        this->view->moveSelectedComponentByDistance(0,-10);
            update();
            break;
    }
     case Qt::Key_Left:{
        QTextStream(stdout)<<"left";
        this->view->moveSelectedComponentByDistance(-10,0);
            update();
            break;
    }
     case Qt::Key_Right:
     {   QTextStream(stdout)<<"right";
        this->view->moveSelectedComponentByDistance(10,0);
        update();
        break;
    }

     case Qt::Key_Enter:
     {   QTextStream(stdout)<<"enter";
        this->view->unSelectComponent();
        clicked=false;
        break;
        update();
    }


    }

}
}



void MainWindow::paintEvent(QPaintEvent *event){
    QRect geometryOfWindow = this->geometry();
//   int x = geometryOfWindow.x();
//   int y = geometryOfWindow.y();
    int w = geometryOfWindow.width();
    int h = geometryOfWindow.height();

    w=(int)680*0.80;
    h=(int)550*0.80;
    QTextStream(stdout)<<"weidth:"<<w<<" height:"<<h<<endl;
    QPixmap pixMap(w,h);
    QPainter paintPixMap(&pixMap);
//    paintPixMap.drawLine(10,10,20,10);
    QPainter painter(this);
    pixMap.fill(Qt::white);
    if(state==-1){

           painter.drawPixmap(20,10,pixMap);
    }



    if(scribble  && event->MouseMove && clicked==false){
        //pixPainter.drawLine(lastPoint,currentPoint);
       // lastPoint=currentPoint;
       // drawPointsFromVector(&paintPixMap);
        if(this->selectGroup==true){
            QTextStream(stdout)<<"group";
            QPoint l(lastPoint.rx(),lastPoint.ry());
            QPoint c(currentPoint.rx(),currentPoint.ry());
            this->view->drawGroup(&paintPixMap,l,c);
        }

    if(requiresVector==true && pointsVector!=nullptr){
componentBeingUsed->drawComponent(&paintPixMap,pointsVector);

  }
   else{
if(nonVecterComponentBeingUsed!=nullptr){
    QTextStream(stdout)<<nonVecterComponentBeingUsed;
        nonVecterComponentBeingUsed->drawComponent(&paintPixMap);

  }

    }

    QTextStream(stdout)<<"mouse moved";
       //painter.drawPixmap(20,10,pixMap);
    }
    if(scribble && event->MouseButtonRelease && clicked==false){
QTextStream(stdout) <<lastPoint.rx()<<":"<<lastPoint.ry()<<","<<currentPoint.rx()<<","<<currentPoint.ry()<<"mouse released";
//this->view->drawComponents(&paintPixMap);
 //    painter.drawPixmap(20,10,pixMap);

    }

QTextStream(stdout) << "inside to print" << endl;
// pixMap.fill(Qt::white);
      this->view->drawComponents(&paintPixMap);

if(event->MouseButtonPress && clicked){

    //clicked=false;
    if(this->view->isComponentSelected()){
       DrawComponent* cmp=this->view->getSelectedComponent();
       cmp->selectComponent(&paintPixMap);

    }
    else{
    QTextStream(stdout)<<QString::number(lastPoint.rx())<<" y "<<QString::number(lastPoint.ry())<<endl;
    this->view->processClick(lastPoint.rx(),lastPoint.ry(),&paintPixMap);
    }
}
if(event->MouseButtonRelease && clicked==false){
    if(this->selectGroup==true){

        QPoint l(lastPoint.rx(),lastPoint.ry());
        QPoint c(currentPoint.rx(),currentPoint.ry());
        this->view->drawGroup(&paintPixMap,l,c);
        this->view->processGroupSelection(&paintPixMap);
    }
}



    painter.drawPixmap(20,10,pixMap);
}


void MainWindow::on_drawFreeHandButton_clicked()
{
    this->pointsVector=new QVector<QPoint>;
    DrawComponent *component = new FreeHandComponent(this->pointsVector,"black");
    this->componentBeingUsed=new FreeHandComponent(this->pointsVector,"black");
    this->view->add(component);
    this->requiresVector=true;
    scribble=true;
    isFreeHand=true;
    isLine=false;
    isRectangle=false;
    isCircle=false;
    QTextStream(stdout)<<"free************"<<this->componentBeingUsed->toString();
    update();

}

void MainWindow::on_drawLineButton_clicked()
{
    this->pointsVector=new QVector<QPoint>;
    DrawComponent *component = new LineComponent(this->pointsVector,0,"black");
    this->componentBeingUsed=component;
    this->view->add(component);
    this->requiresVector=true;
    scribble=true;
    isLine=true;
    isFreeHand=false;
    isRectangle=false;
    isCircle=false;
    this->selectGroup=false;
    update();

}

void MainWindow::on_drawRectangleButton_clicked(){
    this->pointsVector=new QVector<QPoint>;
    DrawComponent *componet=new RectangleComponent(this->pointsVector,0,"black");
    this->componentBeingUsed=componet;
    this->view->add(componet);
    this->requiresVector=true;
    scribble=true;
    isRectangle=true;
    isLine=false;
    isCircle=false;
    isFreeHand=false;
    this->selectGroup=false;
    update();
}

void MainWindow::on_drawCircleButton_clicked()
{
    this->pointsVector=new QVector<QPoint>;
    DrawComponent *component = new EllipseComponent(this->pointsVector,"black");
    this->componentBeingUsed=component;
    this->view->add(component);
    this->requiresVector=true;
    isCircle=true;
    scribble=true;
    isRectangle=false;
    isLine=false;
    isFreeHand=false;
    this->selectGroup=false;
    update();
}

void MainWindow::on_selectGroup_clicked()
{
    this->selectGroup=true;
    Group *g=new Group();
    this->view->addGroup(g);
    QTextStream(stdout)<<"group added"<<endl;
    isCircle=true;
    scribble=true;
    isRectangle=false;
    isLine=false;
    isFreeHand=false;
    update();

}
