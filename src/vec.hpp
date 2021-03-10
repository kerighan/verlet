#ifndef __VECH__
#define __VECH__
#include "math.h"

struct vec2 {
    vec2(){}
    vec2(float x, float y) : x(x), y(y){}

    vec2 unit(){
        if (this->x == 0 && this->y == 0)
            return vec2(0, 0);
        
        float x = this->x;
        float y = this->y;
        float norm = (float)sqrt(x*x + y*y);
        return vec2(x/norm, y/norm);
    }

    float norm(){
        return sqrt(this->x*this->x + this->y*this->y);
    }

    vec2 operator-(const vec2& vec){
        return vec2(this->x - vec.x, this->y - vec.y);
    }

    vec2 operator+(const vec2& vec){
        return vec2(this->x + vec.x, this->y + vec.y);
    }

    void operator+=(const vec2& vec){
        this->x += vec.x;
        this->y += vec.y;
    }

    float x;
    float y;
};


inline vec2 operator*(const vec2& vec, const float& alpha){
    return vec2(alpha * vec.x, alpha * vec.y);
}

inline vec2 operator*(const float& alpha, const vec2& vec){
    return vec2(alpha * vec.x, alpha * vec.y);
}

#endif