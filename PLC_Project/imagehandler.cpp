#include "imagehandler.h"


ImageHandler::ImageHandler(){}

ImageHandler::~ImageHandler(){}


void ImageHandler::create_image(WaveFrontObjectHandler *obj, QString save_location){
    //create the raw_image
    cout<<"creating raw image"<<endl;
    raw_image_data_creator(obj);
    //retrieve size of image
    uint row_size = raw_image.size();
    uint col_size = 0;
    for(vector<Color> v : raw_image){
        if(col_size < v.size())
            col_size = v.size();
    }
    cout<<"[info] readying the image"<<endl;
    cout<<"[info] image size : "<<row_size<<" x "<<col_size<<endl;
    byte data[row_size * col_size];
    for(uint i = 0; i < row_size; ++i){
        for(uint j = 0; j < col_size; ++j){
            data[i*col_size + j] = raw_image[i][j].r;
        }
    }
    QVector<QRgb> grey_scale;
    for(uint i = 0; i < row_size*col_size; ++i){
        grey_scale.append(qRgb(i, i, i));
    }
    QImage image = QImage(data, col_size, row_size, QImage::Format_Indexed8);
    image.setColorTable(grey_scale);
    cout<<"[info] saving the image"<<endl;
    image.save(save_location, "bmp", 100);
}
/*
void ImageHandler::raw_image_data_creator(WaveFrontObjectHandler* obj){
    cout<<"[info] creating the raw image"<<endl;
    //test if obj is null or empty
    if(!obj || obj->vertices.empty())
        return;

    // step 1: find z-axis min and max of the verticies
    float min_v = obj->vertices[0].z;
    float max_v = min_v;
    cout<<"[info] retrieving min max values of z axis"<<endl;
    for(uint i = 0; i < obj->vertices.size(); ++i){
        if(min_v > obj->vertices[i].z)
            min_v = obj->vertices[i].z;
        if(max_v < obj->vertices[i].z)
            max_v = obj->vertices[i].z;
    }
    // step 2: change the range from [min, max] to [0, 1]
    cout<<"[info] changing values for color" <<endl;
    for(uint i = 0; i < obj->vertices.size(); ++i){
       obj->vertices[i].z -= min_v;
       obj->vertices[i].z /= abs(max_v)+abs(min_v);
          // cout<<"[debug] z axis of vertice " << i << " = " << obj->vertices[i].z << endl;
    }
    // step 3: transform into a matrix of color
    cout<<"[info] creating the color matrix"<<endl;
    for(uint i = 0; i < obj->vertices.size(); ++i){
       // create color
       Color c;
       c.r = c.g = c.b = obj->vertices[i].z * 255;
       c.a = 255;
       // check if new row

       //cout<<"[debug] color of pixel "<<i<<" is rgba("<<(int)c.r<<", "<<(int)c.g<<", "<<(int)c.b<<", "<<(int)c.a<<")"<<endl;
       if(i != 0 && obj->vertices[i-1].x != obj->vertices[i].x){
           //add padding until row is multiple of 4
           raw_image.push_back(vector<Color>());
       }
       // add color to new cell
       raw_image.back().push_back(c);
    }
}*/

void ImageHandler::raw_image_data_creator(WaveFrontObjectHandler* obj){
    //compute size of image, rows must be multiple of 4
    uint height = 0;
    uint width = 0;
    cout<<"[info] computing correct dimensions for image"<<endl;
    cout<<obj->vertices.size()<<endl;
    for(int i = 0; height == 0; ++i) {
       if(obj->vertices[i].x != obj->vertices[i+1].x) {
           height = i+1;
       }
        ++width;
    }
    uint act_height = height;
    uint act_width = width;
    while(height%4 != 0){
        ++height;}
//    while(width%4 != 0){
//        ++width;}

    cout<<"[info] image dimensions: "<<width<<"x"<<height<<endl;
    //get min max of z-axis
    float min_v = obj->vertices[0].z;
    float max_v = min_v;
    cout<<"[info] retrieving min max values of z axis"<<endl;
    for(uint i = 0; i < obj->vertices.size(); ++i){
        if(min_v > obj->vertices[i].z)
            min_v = obj->vertices[i].z;
        if(max_v < obj->vertices[i].z)
            max_v = obj->vertices[i].z;
    }
    //changing the range from [min, max] to [0,1]
    vector<float> z_array;
    for(Vector v : obj->vertices){
        float temp = v.z;
        temp -= min_v;
        temp /= abs(max_v) + abs(min_v);
        z_array.push_back(temp);
    }

    //creating the raw image
    raw_image = vector< vector<Color> >(width, vector<Color>(height));
    for(uint i = 0; i < width; ++i){
        for(uint j = 0; j < height; ++j){
            Color c;
            if(j > act_height || i > act_width){
                //add padding
                c.r = c.g = c.b = c.a = ~0;
            }else{
                c.r = c.g = c.b = z_array[i*width + j] * 255;
                c.a = ~0;
            }
            raw_image[i][j] = c;
        }
    }
}
