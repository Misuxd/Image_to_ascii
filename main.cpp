#include <iostream>
#include <map>
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


int main()
{

    unsigned char *img=stbi_load("fluture.jpg",&imagine.width,&imagine.height,&imagine.channels,0);
    int p;
    if (img==nullptr)
    {
        cout << "imaginea nu s-a loadat";
        exit(1);
    }

    cout << imagine.width << " x " << imagine.height << " x " << imagine.channels << endl;

    cout << "Introdu inaltimea respectiv latimea pozei pe care vrei sa o transformi in ascii: "<< '\n';
    int newwidth, newheight;
    cin >> newheight >> newwidth;

    unsigned char *resized_img = new unsigned char[newwidth * newheight * imagine.channels];

    stbir_resize_uint8_linear(
        img,
        imagine.width,
        imagine.height,
        0,
        resized_img,
        newwidth,
        newheight,
        0,
        STBIR_RGB);
    // stbi_write_png("resized_test.png", newwidth, newheight, channels, resized_img, newwidth * channels);
    // cout << "Successfully saved resized_test.png!" << endl;

    for (int i=0;i<newheight;i++)
    {
        for (int j=0;j<newwidth;j++)
        {
            p=(j*newwidth+j)*imagine.channels;

            unsigned char r=resized_img[p+0];
            unsigned char g=resized_img[p+1];
            unsigned char b=resized_img[p+2];
            int brightness=0.299*r+0.587*g+0.114*b;

            if (brightness<25) cout<<color.simbol[25];
            else if (brightness<50) cout<<color.simbol[50];
            else if (brightness<75) cout<<color.simbol[75];
            else if (brightness<100) cout<<color.simbol[100];
            else if (brightness<125) cout<<color.simbol[125];
            else if (brightness<150) cout<<color.simbol[150];
            else if (brightness<175) cout<<color.simbol[175];
            else if (brightness<200) cout<<color.simbol[200];
            else if (brightness<225) cout<<color.simbol[225];
            else if (brightness<255) cout<<color.simbol[255];

            //cout << " " << brightness;
        }
        cout << endl;

    }



    delete[] resized_img;
    stbi_image_free(img);
    return 0;
}





/*
    int gray_channels;
    if (channels == 4) {
        gray_channels = 2;
    } else {
        gray_channels = 1;
    }
    size_t img_size = width * height * channels;
    size_t gray_size = width * height * gray_channels;
    unsigned char *grey_img = (unsigned char *)malloc(gray_size);
    if (grey_img == NULL)
    {
        cout << "imaginea gri nu s-a loadat";
        exit(1);
    }

*/
    // ----- CELE DE JOS IAU IMAGINEA DEJA LOADATA SI O CREAZA IN FISIER / COPIAZA ------
    // stbi_write_png("alex.png", width, height, channels, img, width*channels);
    // stbi_write_jpg("fluture.jpg", width, height, channels, img, 100);


//MAX BRIGHTNESS 255 255/10 = 25.5 ~ 25
//