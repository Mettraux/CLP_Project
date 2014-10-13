#include <QCoreApplication>
#include <string>
#include "wavefrontobjecthandler.h"
#include "imagehandler.h"
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cout << argc << endl;
    for(int i = 0; i < argc; ++i){
        cout << argv[i] << endl;
    }
    if(argc > 1){
        cout << "[info] creating wave front object" << endl;
        WaveFrontObjectHandler testobj = WaveFrontObjectHandler(argv[1]);
        string comments = testobj.comments;
        cout << comments << endl;
        ImageHandler image_handler = ImageHandler();

        QString save_location = QString("debug/test.bmp");
        cout<<"[info] starting to create image"<<endl;
        image_handler.create_image(&testobj, save_location);
    }
    return a.exec();
}
