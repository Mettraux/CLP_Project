#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include <string>
#include <cstring>
#include <vector>
#include <cmath>
#include <wavefrontobjecthandler.h>
#include <QImage>
#include <QDataStream>
#include <QFile>
#include <QVector>
#include <QRgb>

typedef unsigned char byte;

struct Color {
    byte r;
    byte g;
    byte b;
    byte a;
};

class ImageHandler
{
public:
    ImageHandler();
    ~ImageHandler();
    void create_image(WaveFrontObjectHandler* obj, QString save_location);

private:
    vector< vector<Color> > raw_image;
    void raw_image_data_creator(WaveFrontObjectHandler* obj);
};

#endif // IMAGEHANDLER_H
