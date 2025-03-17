#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <TObject.h>

class event : public TObject {

  public:

    int trajectory[50];
    int number_of_interaction_points;
    int number_of_non_interaction_points;
    event() : number_of_non_interaction_points(50), number_of_interaction_points(0) {}
    virtual ~event() {}

    ClassDef(event, 1);
};

#endif 
