#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <math.h>
using namespace std;

struct timetype {
    int hours;
    int minutes;
};

struct datetype {
    int day;
    int month;
    int year;
};


struct match {
    string result;
    datetype date;
    int scoreMatch;
    timetype time;
};


struct player {
    string alias = " ";
    string name;
    string surname;
    datetype birthday;
    match history[20];
    int matchesPlayed = 0;
};