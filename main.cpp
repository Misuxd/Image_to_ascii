#include <iostream>
#include <stdlib.h>
using namespace std;
#define STB_IMAGE_IMPLEMENTATION
#include "stbimage/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stbimage/stb_image_write.h"
#include "stbimage/stb_image_resize2.h"

int main()
{
    int width, height, channels;
    unsigned char *img=stbi_load("fluture.jpg",&width,&height,&channels,0);
    if (img==NULL)
    {
        cout << "imaginea nu s-a loadat";
        exit(1);
    }
    cout << width << " x " << height << " x " << channels << endl;

    stbi_write_png("alex.png", width, height, channels, img, width*channels);
    stbi_write_jpg("alex.jpg", width, height, channels, img, 100);

    stbi_image_free(img);
    return 0;
}