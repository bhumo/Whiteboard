#include "drawcomponent.h"
#include <QPainter>
#include <QColor>
#include <QTextStream>
#include <QMessageBox>
#include <QPainterPath>

class PathComponent : public DrawComponent{
private :
    int x;
    int y;
    QString fillGradient;
    QVector<QPoint> *pointVector=nullptr;
    //int fillRule;
    QString colorString;

public:
   PathComponent(int x,int y ,QString color,QString fillGradient){
    this->x=x;
    this->y = y;
    this->fillGradient=fillGradient;
    //this->fillRule =fillRule;
    this->colorString = color;
   }
   QString toString() {
       return "Path";
   }


   void drawComponent(QPainter *painter,QVector <QPoint> *pointVector){
//       this->pointsVector=pointVector;
       int size=this->pointVector->size();
QTextStream(stdout) << "Line component..."<<QString::number(size)<<endl;
int i=0;
    QPainterPath path;

    painter->drawLine(this->pointVector->at(0),this->pointVector->at(size-1));
   }

void drawComponent(QPainter *painter){
QTextStream(stdout) << "Arc component"<<endl;

    if(x<0)x=0;
    if(y<0)y=0;

    QColor color(colorString);

    QPainterPath path;

    path.moveTo(20, 30);
    path.cubicTo(80, 0, 50, 50, 80, 80);


     painter->setPen(color);
    painter->drawPath(path);




}


bool canSelect(QPoint *currentPoint){
 return false;
}

void selectComponent(QPainter *painter){
return;
}

void moveComponentByDistance(int dx, int dy) {
if(this->pointVector==nullptr)return;
   for(int i=0;i<this->pointVector->size();i++){
       QPoint A = this->pointVector->at(i);
       QPoint B (A.rx()-dx,A.ry()-dy);
       this->pointVector->insert(i,B);
   }
QTextStream(stdout)<<"Updated";
}
QPoint * getXRange() override;
QPoint * getYRange() override;


};
