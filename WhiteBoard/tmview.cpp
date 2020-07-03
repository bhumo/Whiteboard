#include "tmview.h"
#include "DrawComponent.h"
#include <QList>
#include <QPainter>
#include <QMessageBox>
#include "components.h"
#include <QTextStream>
TMView::TMView(){
this->stack=new ComponentStack();
}

void TMView::add(DrawComponent *component){
    this->components.append(component);
    this->stack->push(component);

}

void TMView::clear(QPainter* painter){
painter->restore();
}


void TMView::undo(){
    if(!(components.isEmpty())){
    free( components.takeLast());
   }

}
void TMView::clearAll(){
    DrawComponent *comp;
for(int i=0;i<this->components.length();i++){
    comp=this->components.takeAt(i);
   free(comp);
}
}
void TMView::drawComponents(QPainter *painter,DrawComponent *component){
    component->drawComponent(painter);
}
void TMView::drawComponents(QPainter *painter){
//    TMView::clear(painter);
QString length = QString::number(this->components.length());
    DrawComponent *component;
QTextStream(stdout) << length << endl;


foreach(component,components){
    component->drawComponent(painter);

}

QTextStream(stdout) << "tm view end" << endl;

return;
}

void TMView::processClick(int x,int y,QPainter *painter){
    QPoint A(x,y);
    if(this->components.length()<=0)return;
    QString length = QString::number(this->components.length());
        DrawComponent *component=nullptr;
    QTextStream(stdout) << length << endl;
   int len=this->components.length();
   bool isSelected=false;
   int i=0;
   for(i=0;i<len;i++){
       component=components.at(i);
       QTextStream(stdout)<<component->toString()<<endl;
       isSelected=component->canSelect(&A);
       if(isSelected==true)break;

   }
if(isSelected==false){
    QTextStream(stdout)<<"not seldected"<<" i " <<QString::number(i)<<endl;
    this->selectedComponent=nullptr;
}
else{
    component->selectComponent(painter);
    this->selectedComponent=component;
    QTextStream(stdout)<<"selected"<<endl;
}
}

bool TMView::isComponentSelected(){
    if (this->selectedComponent==nullptr) return false;
    return true;
}

void TMView::unSelectComponent(){
    this->selectedComponent=nullptr;
}
DrawComponent* TMView::getSelectedComponent(){
    return  this->selectedComponent;
}
void TMView::moveSelectedComponentByDistance(int distanceX, int distanceY){

    this->selectedComponent->moveComponentByDistance(distanceX,distanceY);


}

void TMView::addGroup(Group *group){
    this->group=group;
}

void TMView::processGroupSelection(QPainter *painter){
    QPoint *lastPoint=this->group->getLastPoint();
    QPoint *currentPoint=this->group->getCurrentPoint();
    int minX=lastPoint->rx();
    int maxX=lastPoint->rx();
    int minY=lastPoint->ry();
    int maxY=lastPoint->ry();
    if(minX<currentPoint->rx())maxX=currentPoint->rx();
    else minX=currentPoint->rx();
    if(minY<currentPoint->ry())maxY=currentPoint->ry();
    else minY=currentPoint->ry();
    int i=0;
    int added=0;
    DrawComponent *component=nullptr;
    for( i=0; i<this->components.size();i++){
        QPoint *XRange=component->getXRange();
        QPoint *YRange=component->getYRange();
        if(XRange->rx()>=minX && XRange->ry()<=maxX && YRange->rx()>=minY && YRange->ry()<=maxY){
            this->group->addToList(component);
            this->components.removeAt(i);
            component->drawComponent(painter);
            component->selectComponent(painter);

            added++;
        }
    }


}
void TMView::selectGroup(QPainter *painter){
    QList<DrawComponent*> list=this->group->getGroupList();
    for(DrawComponent *component:list){
        component->selectComponent(painter);
    }
}
void TMView::drawGroup(QPainter *painter,QPoint &lastPoint,QPoint &currentPoint ){
    this->group->drawComponent(painter,lastPoint,currentPoint);
}

void TMView::unselectGroup(){
    if(this->group==nullptr)return;
    QList<DrawComponent*> list=this->group->getGroupList();
    if(list.size()<=0) return;
    for(DrawComponent *component:list){
        this->components.append(component);
    }
    this->group=nullptr;
}

