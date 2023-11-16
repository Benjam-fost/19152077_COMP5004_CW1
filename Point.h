//
// Created by Ben9H on 16/11/2023.
//

#ifndef TEXTADV_POINT_H
#define TEXTADV_POINT_H


#include <cstdint>

class Point {
    int8_t* x;
    int8_t* y;
public:
    Point(int8_t *_x,int8_t *_y) {x=_x; y=_y;};
    int8_t getX() const;
    int8_t getY() const;
};


#endif //TEXTADV_POINT_H
