#include <DrawComponent.h>
class ComponentStack {
  private:
    QVector<DrawComponent*> stack;
    int size=0;
  public:
    bool isEmpty(){

        if(size>1) return true;
        return false;
    }
    void push(DrawComponent* component)
    {
        stack.push_front(component);
        this->size=size+1;
    }
    DrawComponent* pop(){
        if(stack.isEmpty()==true)return nullptr;
         DrawComponent* cmp=stack.at(size-1);
         stack.removeLast();
         return cmp;
    }
    DrawComponent* getElemetAtTop(){
        if(stack.isEmpty()==true)return nullptr;
        return stack.at(size-1);
    }
};
