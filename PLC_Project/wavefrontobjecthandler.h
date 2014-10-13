#ifndef WAVEFRONTOBJECTHANDLER_H
#define WAVEFRONTOBJECTHANDLER_H

#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

struct Vector{
    float x,y,z;
};

struct Face{
    int indice_1,
        indice_2,
        indice_3;
};

class WaveFrontObjectHandler
{
    private:
        void parse_line(char* l);
        void parse_vertex(char* l);
        void parse_face(char* l);
        void parse_comments(char* l);
        bool load_WaveFront(char* file_name);


    public:
        WaveFrontObjectHandler(char* file_path);
       ~WaveFrontObjectHandler();
        vector<Vector> vertices;
        vector<Face> faces;
        string comments;


};

#endif // WAVEFRONTOBJECTHANDLER_H
