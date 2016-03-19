
/* 
 * File:   driver.cpp
 * Author: amy
 *
 * Created on 17 March 2016, 5:03 PM
 */

#include <cstdlib>
#include <iostream>

#include "image_manipulation.h"
#include <sstream>
#include <string>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    string namePrefix;
    string outputFile;
    int sliceI, sliceJ;
    BRDAMY004::VolImage volImage;
    for (int i=0; i<argc; i++){
        string temp = string(argv[i]);
        if (i == 1){
            namePrefix = temp;
            
            volImage.readImages(namePrefix);
        }
        else if (temp == "-x"){
            temp = string(argv[i+1]) + " " + string(argv[i+2]);
            istringstream iss(temp);
            iss >> sliceI >> outputFile;
            break;
        }
        else if (temp == "-d"){
            temp = string(argv[i+1]) + " " + string(argv[i+2]) + " " + string(argv[i+3]);
            istringstream iss(temp);
            iss >> sliceI >> sliceJ >> outputFile;
            break;
        }
    }
    
    //volImage.~VolImage();
    return 0;
}

