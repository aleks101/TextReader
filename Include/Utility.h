#pragma once

#include <string>
#include <iostream>

std::string get_file_content(const char* filename);

#define UTILITY_PRINT_TO_CONSOLE
#define DEBUG

#ifdef DEBUG
    #define print(msg) std::cout<<msg
    #define println(msg) std::cout<<msg<<"\n"
#endif
#ifndef DEBUG
    #define print(msg)
    #define println(msg)
#endif
#ifdef UTILITY_PRINT_TO_CONSOLE
    #define printToConsole(msg) std::cout<<msg<<std::endl;
#endif
#ifndef UTILITY_PRINT_TO_CONSOLE
    #define printToConsole(msg) 
#endif

struct Vec2{
    float x,y;
};
struct Vec3{
    float x,y,z;
};
class ColorRGB {
public:
    ColorRGB();
    ~ColorRGB();
    ColorRGB(int r, int g, int b);
    ColorRGB(const ColorRGB& obj);
    ColorRGB& operator=(const ColorRGB& obj);
public:
    float R=0,G=0,B=0;
};
struct Rect{
    int x,y,w,h;
};