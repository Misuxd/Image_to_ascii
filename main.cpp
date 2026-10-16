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

// average brightness cu sugestii
// Dimensiuni recomandate solve shit, fa cumva sa dea select la dimensiuni recomandate si sa le dea highlight si sa apas enter ca sa selectez


void Afisare_Char(int width, int height, unsigned char *imageval, int brightness_index)
{
    ofstream Afis("Rezultat.txt"); // textfile read only cu rezultatul
    for (int i=0;i<height;i++)
    {
        for (int j=0;j<width;j++)
        {
            int p=(i*width+j)*imagine.channels;

            unsigned char r=imageval[p+0];
            unsigned char g=imageval[p+1];
            unsigned char b=imageval[p+2];
            int brightness=0.299*r+0.587*g+0.114*b;

            if (brightness<0.5*brightness_index) Afis<<color.simbol[25]<<" ";
            else if (brightness<1*brightness_index) Afis<<color.simbol[50]<<" ";
            else if (brightness<1.5*brightness_index) Afis<<color.simbol[75]<<" ";
            else if (brightness<2*brightness_index) Afis<<color.simbol[100]<<" ";
            else if (brightness<2.5*brightness_index) Afis<<color.simbol[125]<<" ";
            else if (brightness<3*brightness_index) Afis<<color.simbol[150]<<" ";
            else if (brightness<3.5*brightness_index) Afis<<color.simbol[175]<<" ";
            else if (brightness<4*brightness_index) Afis<<color.simbol[200]<<" ";
            else if (brightness<4.5*brightness_index) Afis<<color.simbol[225]<<" ";
            else if (brightness<5*brightness_index) Afis<<color.simbol[255]<<" ";

             //cout << " " << brightness;
        }
        //cout << endl;
         Afis << endl;
    }
}


int main(int argc , char *argv[])
{
    int brightindx=50;
    if (argc<2) {
        cout << "Usage: " << argv[0] << " <path_to_image>" << endl;
        cout<<"Introdu o imagine valida\n";
    }
    int widthdorit;
    int heightdorit;
    char *filepath = argv[1];
    // de rezolvat introducerea asta

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

    cout<<"\n****************************************\n";
    cout << "Dimensiuni initiale: " << imagine.width << " x " << imagine.height << " x " << imagine.channels << endl
    << "Dimensiuni recomandate:\n" << "-> " << imagine.width/2 << " x " << imagine.height/2 << endl <<  "-> " << imagine.width/4 << " x " << imagine.height/4 << endl;
    cout<<"\n****************************************\n";

    ofstream Afis("Rezultat.txt"); // textfile read only cu rezultatul
    bool ok=false;
        cout<<"****************************************\n";
        cout << "Doresti sa dai resize la imagine?   (1 - DA , 0 - NU) \n";
        cin >> ok;
        cout << "introdu brightness (min - 1, max - 125, Default - 50)\n";
        cin >> brightindx;
        cout<<"****************************************\n";

        if (brightindx<1) brightindx=1;
        else if (brightindx>255) brightindx=125;


    if (ok==true) {
        unsigned char *resized_img = new unsigned char[widthdorit * heightdorit * imagine.channels];

        stbir_resize_uint8_linear(img, imagine.width, imagine.height, 0, resized_img,
            widthdorit,heightdorit,0,STBIR_RGB);

        Afisare_Char(widthdorit,heightdorit,resized_img,brightindx);

    delete[] resized_img;
    }
    else {
        Afisare_Char(imagine.width,imagine.width,img,brightindx);
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

