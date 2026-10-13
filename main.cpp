#include <iostream>
#include <map>
#include <fstream>
#include <stdlib.h>
#include <vector>
using namespace std;
#define STB_IMAGE_IMPLEMENTATION
#include "stbimage/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stbimage/stb_image_write.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stbimage/stb_image_resize2.h"

struct img_related{
    int width, height, channels;
}imagine;

struct ascii {
    map<int, char> simbol = {
        {25, '@'}, {50, '%'}, {75, '#'}, {100, '*'}, {125, '+'}, {150, '='}, {175, '-'}, {200, ':'}, {225, '.'},
        {255, ' '}
    };
    // 10 caractere in total || max brightness = 255

}color;

// !!! DE FACUT CA UIT -- MUTAT IMAGINI IN FOLDERUL DE IMAGINI -- FOLOSIT ARGV PT FILENAME , WIDTH , HEIGHT
// ALSO DE GASIT O METODA SA IL FAC SA ARATE MAI FRUMOS

int main(int argc , char *argv[])
{

    if (argc<2) {
        cout << "Usage: " << argv[0] << " <path_to_image>" << endl;
        cout<<"Introdu o imagine valida\n";
        return 0;
    }

    int widthdorit;
    int heightdorit;

    const char *filepath = argv[1];
    if (argv[2]!=NULL&&argv[3]!=NULL) {
         widthdorit = stoi(argv[2]);
         heightdorit = stoi(argv[3]);
    }

    unsigned char *img=stbi_load(filepath,&imagine.width,&imagine.height,&imagine.channels,0);
    int p;
    if (img==nullptr)
    {
        cout << "imaginea nu s-a loadat || "<<stbi_failure_reason()<<endl;
        exit(1);
    }

    cout << "Dimensiuni initiale: " << imagine.width << " x " << imagine.height << " x " << imagine.channels << endl;

    //cout << "Introdu inaltimea respectiv latimea pozei pe care vrei sa o transformi in ascii: "<< '\n';
    //int newwidth , newheight;
    //cin >> newwidth >> newheight;
    ofstream Afis("Rezultat.txt"); // textfile read only cu rezultatul
    bool ok=false;
    if (argv[2]!=NULL&&argv[3]!=NULL) {
        cout << "Doresti sa dai resize la imagine?\n (1 - DA , 0 - NU)";
        cin >> ok;
    }
    if (ok==true) {
        unsigned char *resized_img = new unsigned char[widthdorit * heightdorit * imagine.channels];

        stbir_resize_uint8_linear(
            img,
            imagine.width,
            imagine.height,
            0,
            resized_img,
            widthdorit,
            heightdorit,
            0,
            STBIR_RGB);


        for (int i=0;i<heightdorit;i++)
        {
            for (int j=0;j<widthdorit;j++)
            {
                p=(i*widthdorit+j)*imagine.channels;

                unsigned char r=resized_img[p+0];
                unsigned char g=resized_img[p+1];
                unsigned char b=resized_img[p+2];
                int brightness=0.299*r+0.587*g+0.114*b;

                if (brightness<25) Afis<<color.simbol[25]<<" ";
                else if (brightness<50) Afis<<color.simbol[50]<<" ";
                else if (brightness<75) Afis<<color.simbol[75]<<" ";
                else if (brightness<100) Afis<<color.simbol[100]<<" ";
                else if (brightness<125) Afis<<color.simbol[125]<<" ";
                else if (brightness<150) Afis<<color.simbol[150]<<" ";
                else if (brightness<175) Afis<<color.simbol[175]<<" ";
                else if (brightness<200) Afis<<color.simbol[200]<<" ";
                else if (brightness<225) Afis<<color.simbol[225]<<" ";
                else if (brightness<255) Afis<<color.simbol[255]<<" ";

                // cout << " " << brightness;
            }
            Afis << endl;

        }
    delete[] resized_img;
    }
    else {
        for (int i=0;i<imagine.height;i++)
        {
            for (int j=0;j<imagine.width;j++)
            {
                p=(i*imagine.width+j)*imagine.channels;

                unsigned char r=img[p+0];
                unsigned char g=img[p+1];
                unsigned char b=img[p+2];
                int brightness=0.299*r+0.587*g+0.114*b;

                if (brightness<25) Afis<<color.simbol[25]<<" ";
                else if (brightness<50) Afis<<color.simbol[50]<<" ";
                else if (brightness<75) Afis<<color.simbol[75]<<" ";
                else if (brightness<100) Afis<<color.simbol[100]<<" ";
                else if (brightness<125) Afis<<color.simbol[125]<<" ";
                else if (brightness<150) Afis<<color.simbol[150]<<" ";
                else if (brightness<175) Afis<<color.simbol[175]<<" ";
                else if (brightness<200) Afis<<color.simbol[200]<<" ";
                else if (brightness<225) Afis<<color.simbol[225]<<" ";
                else if (brightness<255) Afis<<color.simbol[255]<<" ";

                // cout << " " << brightness;
            }
            Afis << endl;

        }
    }

    Afis.close();
    stbi_image_free(img);
    return 0;
}

    // ----- CELE DE JOS IAU IMAGINEA DEJA LOADATA SI O CREAZA IN FISIER / COPIAZA ------
    // stbi_write_png("fluture.png", width, height, channels, img, width*channels);
    // stbi_write_jpg("fluture.jpg", width, height, channels, img, 100);

//MAX BRIGHTNESS 255 255/10 = 25.5 ~ 25
//
    // stbi_write_png("*.png", newwidth, newheight, channels, resized_img, newwidth * channels);
    // cout << "Successfully save!" << endl;
