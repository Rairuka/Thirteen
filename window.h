//window.h

#ifndef WINDOW_H
#define WINDOW_H

class window
{
    private:
        int menuoptionchosen;
        //***put last card played view


    public:
        window();
        //menu methods
        void start(); //start will use menuoptionchosen to call the other methods
        void play();
        void help();
        void quit();
        void clear();
        ~window();
};

#endif