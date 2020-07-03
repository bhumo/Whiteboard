#ifndef TMVIEW_H
#define TMVIEW_H
#include "DrawComponent.h"
#include "ComponentStack.cpp"
#include "Group.cpp"
#include <QPainter>
#include <QList>
class TMView
{
private:
    QList<DrawComponent *> components;
    ComponentStack *stack;
    Group *group=nullptr;
    DrawComponent *selectedComponent=nullptr;
public:
    TMView();
     void add(DrawComponent *component);
     void drawComponents(QPainter *painter);
     void drawComponents(QPainter *painter,DrawComponent *component);
     void clearAll();
     void undo();
     void processClick(int x,int y,QPainter *painter);
     DrawComponent* getSelectedComponent();
     void moveSelectedComponentByDistance(int distanceX,int distanceY);
     bool isComponentSelected();
     void unSelectComponent();
     void addGroup(Group*);
     void drawGroup(QPainter *painter,QPoint &lastPoint,QPoint &currentPoint);
     void processGroupSelection(QPainter *painter);
     void selectGroup(QPainter *painter);
     void moveGroup(int distanceX,int distanceY);
     void unselectGroup();

         void clear(QPainter *painter);
};

#endif // TMVIEW_H
