//
// Created by lhk12 on 2023-03-21.
//

#ifndef OPENGLDEMO_IMAGEDATA_H
#define OPENGLDEMO_IMAGEDATA_H

#include <stdio.h>
#include <cstdlib>
#include <cstring>

class ImageData {

public:
    int width;
    int height;
    int format;
    uint8_t *data;
    uint64_t size;

    ImageData(int width,
              int height,
              int format,
              uint8_t *data,
              uint64_t size) {

        this->width = width;
        this->height = height;
        this->format = format;
        this->size = size;

        this->data = static_cast<uint8_t *>(malloc(size));
        memset(this->data, 0, size);
        memcpy(this->data, data, size);
    }

    ~ImageData() {
        if (data != NULL) {
            free(data);
        }
    }
};


#endif //OPENGLDEMO_IMAGEDATA_H
