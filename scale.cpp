// Author: Zuhayer Tashin
// Course: CSCI-135
// Instructor: Tong Yi
// Assignment: Lab 8E
// Program scale.cpp. Scale the original picture to 200% of its size. 
// It can be done by increasing the size of the picture by the factor of 2, 
// and copying each pixel of the input as a small 2x2 square in the output. 
// (We don’t do any interpolation of colors as more advanced scaling procedures would do.)

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <math.h>
using namespace std;

const int MAX_H = 512;
const int MAX_W = 512;

// Function to read the input image from a file
void readImage(int image[MAX_H][MAX_W], int &height, int &width) {
    char c;
    int x;
    ifstream instr;
    instr.open("inImage.pgm");

    // Read and validate the PGM file header
    instr >> c;
    assert(c == 'P');
    instr >> c;
    assert(c == '2');

    // Skip any comments in the file
    while ((instr >> ws).peek() == '#') {
        instr.ignore(4096, '\n');
    }

    // Read image width, height, and maximum pixel value
    instr >> width;
    instr >> height;
    assert(width <= MAX_W);
    assert(height <= MAX_H);
    int max;
    instr >> max;
    assert(max == 255);

    // Read pixel values into the image array
    for (int row = 0; row < height; row++)
        for (int col = 0; col < width; col++)
            instr >> image[row][col];
    instr.close();
    return;
}

// Function to write the output image to a file
void writeImage(int image[MAX_H][MAX_W], int height, int width) {
    ofstream ostr;
    ostr.open("outImage.pgm");
    if (ostr.fail()) {
        cout << "Unable to write file\n";
        exit(1);
    };

    // Write the PGM file header
    ostr << "P2" << endl;
    ostr << width * 2 << ' ';
    ostr << height * 2 << endl;
    ostr << 255 << endl;

    // Write pixel values to the output file
    for (int row = 0; row < height; row++) {
        for (int i = 0; i < 2; i++) {
             for (int col = 0; col < width; col++) {
                for (int j = 0; j < 2; j++) {  // Scale width by 2
                    assert(image[row][col] < 256);
                    assert(image[row][col] >= 0);
                    ostr << image[row][col] << ' ';
                }
                ostr << endl;

            }}}
    ostr.close();
    return;
}

int main() {
    int img[MAX_H][MAX_W];
    int h, w;

    // Read the input image from the file
    readImage(img, h, w);

    int out[MAX_H][MAX_W];

    // Copy the input image to the output image
    for(int row = 0; row < h; row++) {
        for(int col = 0; col < w; col++) {
            out[row][col] = img[row][col];
        }}

    // Calculate dimensions and position of the 50/50 dimensional box
    // int boxWidth = w / 2;
    // int boxHeight = h / 2;
    // int boxStartX = (w - boxWidth) / 2;
    // int boxStartY = (h - boxHeight) / 2;

    // // Perform the image processing (creating the outer frame)
    // for(int row = boxStartY; row < boxHeight + boxStartY; row++) {
    //     for(int col = boxStartX; col < boxWidth + boxStartX; col++) {
    //         if (row == boxStartY || row == boxHeight + boxStartY - 1 || col == boxStartX || col == boxWidth + boxStartX - 1) {
    //             // Set pixel value to 255 (white) for the outer frame
    //             out[row][col] = 255;
    //         }
    //     }
    // }

    // Calculate dimensions and position of the inner box
    // int innerBoxWidth = boxWidth - 2;
    // int innerBoxHeight = boxHeight - 2;
    // int innerBoxStartX = boxStartX + 1;
    // int innerBoxStartY = boxStartY + 1;

    // // Perform the image processing (creating the inner box)
    // for(int row = innerBoxStartY; row < innerBoxHeight + innerBoxStartY; row++) {
    //     for(int col = innerBoxStartX; col < innerBoxWidth + innerBoxStartX; col++) {
    //         // Copying pixel values from the input image to the inner box area
    //         out[row][col] = img[row][col];
    //     }
    // }
       
    // Write the processed image to the output file
    writeImage(out, h, w);
    return 0;
}
