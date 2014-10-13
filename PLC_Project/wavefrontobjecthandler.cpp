#include "wavefrontobjecthandler.h"

WaveFrontObjectHandler::WaveFrontObjectHandler(char* file_name)
{
    load_WaveFront(file_name);
}

WaveFrontObjectHandler::~WaveFrontObjectHandler(){}

bool WaveFrontObjectHandler::load_WaveFront(char* file_name)
{
    cout << "[INFO] loading wave front object" << endl;
    fstream file_object;
    file_object.open(file_name);

    if (file_object.is_open()){
        cout << "[INFO] wave front file successfully opened" << endl;
        char line_buffer[255];
        while(file_object.good()){           
            file_object.getline(line_buffer, 255);
            parse_line(line_buffer);
        }
        cout << "[INFO] closing the obj file" << endl;
        file_object.close();
        return true;
    }
    cout << "[ERROR] failed to open .obj file" << endl;
    file_object.close();
    return false;
}

void WaveFrontObjectHandler::parse_line(char* l)
{
    if(!strlen(l))
        return;

    char* l_type = strtok(strdup(l), " ");
    if(!strcmp(l_type, "v"))
        WaveFrontObjectHandler::parse_vertex(l);
    else if(!strcmp(l_type, "f"))
        WaveFrontObjectHandler::parse_face(l);
    else if(!strcmp(l_type, "#"))
        WaveFrontObjectHandler::parse_comments(l);
}

void WaveFrontObjectHandler::parse_vertex(char* l)
{
    vertices.push_back(Vector());
    sscanf(l, "v %f %f %f",&vertices.back().x, &vertices.back().y, &vertices.back().z);
}


void WaveFrontObjectHandler::parse_face(char* l)
{
    faces.push_back(Face());
    sscanf(l, "f %d %d %d", &faces.back().indice_1, &faces.back().indice_2, &faces.back().indice_3);
}

void WaveFrontObjectHandler::parse_comments(char* l)
{
    string comment_line = string(l);
    comments.append(comment_line + "\n");
}
