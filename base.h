//base.h

#ifndef BASE_H
#define BASE_H

#include <iostream>

//abstract class that will have common commands across all classes
class parent
{
public:
    virtual void view()=0; //classes will all use views, polymorphism 
    void set(); //to set attributes in derived classes
};

#endif