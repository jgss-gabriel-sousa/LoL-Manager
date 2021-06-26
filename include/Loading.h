#ifndef LOADING_H
#define LOADING_H

#include <State.h>

class Loading : public State{
public:
    Loading(){}
    virtual ~Loading(){}

    void init();
    void cleanup();

    void pause();
    void resume();

    void handleEvents();
    void update();
    void draw();

protected:

private:
};

#endif // LOADING_H
