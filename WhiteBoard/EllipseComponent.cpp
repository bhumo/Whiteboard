#include "DrawComponent.h"
#include <QPainter>
#include <QColor>
#include <QTextStream>
#include <QMessageBox>
class EllipseComponent : public DrawComponent{
private :
    int x;
    int y;
    int width;
    int height;
    int startAngle;
    int spanAngle;
    int minX=0;
    int minY=0;
    int maxX=0;
    int maxY=0;
    QVector<QPoint> *pointVector=nullptr;

    QString colorString;

public:
    EllipseComponent(QVector<QPoint> *pointsVector,QString color){
        this->width = 0;
        this->height =0;
        this->colorString = color;
        this->x=0;
        this->y=0;
        this->pointVector=pointsVector;
    }
   EllipseComponent(int x,int y ,int width,int height,QString color){
    this->x=x;
       this->y = y;
       this->width = width;
       this->height =height;
       this->colorString = color;
       this->pointVector=nullptr;
   }
   QString toString() {
       return "Ellipse";
   }

   void drawComponent(QPainter *painter,QVector <QPoint> *pointVector){
//       this->pointsVector=pointVector;
       int size=this->pointVector->size();
QTextStream(stdout) << "Ellipse component..."<<QString::number(size)<<endl;

if(size<=0)return;
QPoint A = this->pointVector->at(0);
QPoint B =this->pointVector->at(size-1);
int w = B.rx()-A.rx();
int h = B.ry()-A.ry();
if(w<0) w *=(-1);
if(h<0) h*=(-1);

    painter->drawEllipse(this->pointVector->at(0),w,h);
   }


void drawComponent(QPainter *painter){
QTextStream(stdout) << "component"<<colorString<<endl;

    if(x<0)x=0;
    if(y<0)y=0;
    if(width<0) width=0;
    if(height<0) height=0;
    QColor color(colorString);
    painter->setPen(color);
    if(this->pointVector!=nullptr){
        int size = this->pointVector->size();
        if(size<=0)return;
        QPoint A(this->pointVector->at(0));
        QPoint B (this->pointVector->at(size-1));
        int w = A.rx()-B.rx();
        int h = A.ry()-B.ry();
        if(w<0) w =w*(-1);
        if(h<0) h=h*(-1);
        this->x=A.rx();
        this->y=A.ry();
        this->width=w;
        this->height=w;
        this->minX=A.rx();
        this->maxX=A.rx();
        this->maxY=A.ry();
        this->minY=A.ry();
        if(A.rx()<B.rx())maxX=B.rx();
        else minX=B.rx();

        if(A.ry()<B.ry())maxY=B.ry();
        else minY=B.ry();
        QTextStream(stdout)<<" height:" <<QString::number(this->width);
        QTextStream(stdout)<<"width: "<<QString::number(this->height);
        painter->drawEllipse(this->pointVector->at(0),w,h);

        return;
    }


//    painter->drawArc(x,y,width,height,startAngle,spanAngle);
    painter->drawEllipse(x,y,width,height);


}

bool canSelect(QPoint *currentPoint){
            QTextStream(stdout)<<"width: "<<QString::number(this->width);
                    QTextStream(stdout)<<" h: "<<QString::number(this->height);
    if(this->width == this->height){
        //then it's a cricle
        int radius = this->width;
        int x1=currentPoint->rx() - this->x;
        int y1 =currentPoint->ry()- this->y;
        if (x1<0) x1=x1*(-1);
        if(y1<0)y1=y1*(-1);
        int lhs= (x1*x1)+(y1*y1);
        int rhs =radius*radius;
        QTextStream(stdout)<<"width: "<<QString::number(this->width);
        QTextStream(stdout)<<"x :"<<QString::number(this->x)<<" y:"<<QString::number(this->y);
        QTextStream(stdout)<<" x1:"<<QString::number(x1)<<"y1:"<<QString::number(y1);
        QTextStream(stdout)<<" lhs "<<QString::number(lhs)<<" rhs:"<<QString::number(rhs)<<endl;
        if (lhs==rhs) return  true;
        if (lhs<=rhs+4) return true;



    }
 return false;
}

void selectComponent(QPainter *painter){

    QTextStream(stdout)<<"Select component";
    //if width == height then it's a circle
    if(this->width==this->height){
        int x1=this->x;
        int y1=this->y;
        int radius=this->width;
        painter->setBrush(Qt::darkBlue);
        painter->setPen(Qt::blue);
        painter->drawEllipse(x1+radius+1,y1,5,5);
        painter->drawEllipse(x1,y1-radius,5,5);
        painter->drawEllipse(x1,y1+radius,5,5);
        painter->drawEllipse(x1-radius,y1,5,5);
        painter->setBrush(Qt::white);
        painter->setPen(Qt::black);
    }
    return;
}


void moveComponentByDistance(int dx, int dy) {
if(this->pointVector==nullptr)return;
int i=this->pointVector->size();
if(i==0)return;
QPoint A = this->pointVector->at(0);
//QTextStream(stdout)<<A.rx()<<","<<A.ry()<<"move "<<dx<<","<<dy<<endl;
//QTextStream(stdout)<<this->x<<","<<this->y<<","<<this->width<<","<<this->height<<endl;
this->x=A.rx()+dx;
this->y=A.ry()+dy;
QPoint B (A.rx()+dx,A.ry()+dy);
this->pointVector->insert(0,B);
this->pointVector->removeLast();
int newW=this->width+this->x;
int newH=this->height+this->y;
this->pointVector->append(QPoint(newW,newH));



QTextStream(stdout)<<"Updated";
}

QPoint * getXRange() {
    return new QPoint(this->minX,this->maxX);
}
QPoint * getYRange() {
    return new QPoint(this->minY,this->maxY);
}



};
