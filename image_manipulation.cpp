/* 
 * Author: Amy Brodie (BRDAMY004)
 * CSC3002H Tutorial 2
 * Created on 18 March 2016, 2:15 PM
 */

#include "image_manipulation.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>



namespace BRDAMY004{
    VolImage::VolImage() : width(0), height(0) {
        
    }
    
    bool VolImage::readImages(std::string baseName){
        std::string fileDirec = "raws/" + baseName + ".data";
        std::ifstream headerFile(fileDirec.c_str());
        if (!headerFile){
            std::cerr << "File open failed!" << std::endl;
            return false;
        }
        int numImages;
        headerFile >> width >> std::ws >> height >> std::ws >> numImages;
        for (int i=0; i<numImages; i++){
            unsigned char ** rows = new unsigned char * [height];
            std::ostringstream oss;
            oss << i;
            std::string num;
            num = oss.str();
            std::string fileName = "raws/" + baseName + num + ".raw";
            //std::cout << fileName << std::endl;
            std::ifstream rawFile(fileName.c_str(), std::ios::in | std::ios::binary);
            if (!rawFile){
                std::cerr << "File open failed!" << std::endl;
                return false;
            }
            for (int j=0; j<height; j++){
                rows[j] = new unsigned char [width];
                for (int k=0; k<width; k++){
                    rawFile >> rows[j][k]; 
                }
            }
            slices.push_back(rows);
        }
    }
    
    void VolImage::diffmap(int sliceI, int sliceJ, std::string output_prefix) {
        
    }
    
    void VolImage::extract(int sliceId, std::string output_prefix){
        
    }
    
    int VolImage::volImageSize(){
        
    }
    
    VolImage::~VolImage(){
        for (int i=0; i<slices.size(); i++){
            for (int j=0; j<height; j++){    
                delete [] slices[i][j];
            }
            delete [] slices[i];
        }
        slices.empty();
    }
    
}