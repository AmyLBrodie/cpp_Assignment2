
/* 
 * Author: Amy Brodie (BRDAMY004)
 * CSC3002H Tutorial 2
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
        // checks if argument is imageBase
        if (i == 1){
            namePrefix = temp;
            // check if specified file was found
            if (volImage.readImages(namePrefix) == false){
                return 0;
            }
        }
        // checks if argument is extract switch
        else if (temp == "-x"){
            temp = string(argv[i+1]) + " " + string(argv[i+2]);
            istringstream iss(temp);
            iss >> sliceI >> outputFile;
            volImage.extract(sliceI, outputFile);
            break;
        }
        // checks if argument is diffmap switch
        else if (temp == "-d"){
            temp = string(argv[i+1]) + " " + string(argv[i+2]) + " " + string(argv[i+3]);
            istringstream iss(temp);
            iss >> sliceI >> sliceJ >> outputFile;
            volImage.diffmap(sliceI, sliceJ, outputFile);
            break;
        }
        // checks if argument is row extract switch
        else if (temp == "-g"){
            temp = string(argv[i+1]) + " " + string(argv[i+2]);
            istringstream iss(temp);
            iss >> sliceI >> outputFile;
            volImage.rowExtract(sliceI, outputFile);
            break;
        }
    }
    return 0;
}

