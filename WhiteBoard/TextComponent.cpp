#include "drawcomponent.h"
#include <QPainter>
#include <QColor>
#include <QTextStream>
#include <QMessageBox>
class TextComponent : public DrawComponent{
private :
    int Ax;
    int Ay;
    int Bx;
    int By;
    QFont fontFamily;
    QString colorString;
    int alingment;
    QString text;
    QVector<QPoint> *pointVector=nullptr;

public:
   TextComponent(int Ax,int Ay ,int Bx,int By,QString text,QFont fontFamily,int alingmnet ,QString color){
    this->Ax=Ax;
       this->text=text;
       this->Ay = Ay;
       this->Bx = Bx;
       this->By =By;
       this->fontFamily=fontFamily;
       this->colorString = color;
       this->alingment = alingment;
   }
   QString toString() {
       return "Text";
   }

   void drawComponent(QPainter *painter,QVector <QPoint> *pointVector){
//       this->pointsVector=pointVector;
       int size=this->pointVector->size();
QTextStream(stdout) << "Line component..."<<QString::number(size)<<endl;
int i=0;
    painter->drawLine(this->pointVector->at(0),this->pointVector->at(size-1));
   }
void drawComponent(QPainter *painter){
QTextStream(stdout) << "Text component"<<endl;

    if(Ax<0)Ax=0;
    if(Ay<0)Ay=0;
    if(Bx<0) Bx=0;
    if(By<0) By=0;


    QColor color(colorString);
    painter->setPen(QPen(color));
    painter->setFont(fontFamily);
    painter->drawText(Ax,Ay,Bx,By,Qt::AlignCenter,text);

}

bool canSelect(QPoint *currentPoint){
    int Gx=currentPoint->rx();
    int Gy = currentPoint->ry();
    int x1=this->Ax;
    int y1=this->Ay;
    int x2=this->Bx+x1;
    int y2 = this->By+y1;
QTextStream(stdout)<<QString::number(x1)<<","<<QString::number(y1)<<"::"<<QString::number(x2)<<","<<QString::number(y2)<<endl;
    if (Gx>=x1 && Gx<=x2 && Gy>=y1 && Gy<=y2)return true;
    return false;
 return false;
}

void selectComponent(QPainter *painter){
    QTextStream(stdout)<<"Text Selected";


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
