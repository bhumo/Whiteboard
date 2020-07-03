#include <DrawComponent.h>
#include <QList>
#include <QTextStream>
class Group{
    QList<DrawComponent*> groupList;
    int x1=0;
    int y1=0;
    int x2=0;
    int y2=0;


    public:
    QString toString(){
        return "Group";
    }

    void  addToList(DrawComponent *component){
    this->groupList.append(component);
}
    QList<DrawComponent*> getGroupList(){
    return this->groupList;
}
     QPoint* getLastPoint(){
        return new QPoint(this->x1,this->y1);
    }
     QPoint* getCurrentPoint(){
         return new QPoint(this->x2,this->y2);
     }

    void drawComponent(QPainter *painter,QPoint &lastPoint,QPoint &currentPoint){
        if (this->x1==0 || this->y1==0){
            this->x1=lastPoint.rx();
            this->y1=lastPoint.ry();
        }
        QTextStream(stdout)<<"draw group";
        this->x2=currentPoint.rx();
        this->y2=currentPoint.ry();
        int newW=this->x1-this->x2;
        int newH=this->y1-this->y2;
        if(newW<0)newW=newW*(-1);
        if (newH<0)newH=newH*(-1);
        painter->fillRect(QRect(this->x1,this->y1,newW,newH),QBrush(QColor(153,204,255,128),Qt::Dense1Pattern));
    }

};
