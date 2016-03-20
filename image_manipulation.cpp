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
#include <cmath>



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
            std::ifstream rawFile(fileName.c_str(), /*std::ios::in |*/ std::ios::binary);
            if (!rawFile){
                std::cerr << "File open failed!" << std::endl;
                return false;
            }
            for (int j=0; j<height; j++){
                rows[j] = new unsigned char [width];
                rawFile.read(reinterpret_cast<char*>(rows[j]), width);
                /*for (int k=0; k<width; k++){
                    //rawFile >> rows[j][k]; 
                }*/
            }
            slices.push_back(rows);
        }
        std::cout << "Number of images: " << numImages << std::endl;
        std::cout << "Number of bytes required: " << VolImage::volImageSize() << " bytes" << std::endl;
        
    }
    
    void VolImage::diffmap(int sliceI, int sliceJ, std::string output_prefix) {
        std::string outputHeader = output_prefix + ".data";
        std::string outputFile = output_prefix + ".raw";
        std::ofstream fileHOutput (outputHeader.c_str());
        std::ostringstream oss;
        oss << width << " " << height;
        std::string headerInfo;
        headerInfo = oss.str() + " 1";
        fileHOutput <<  headerInfo;
        std::ofstream fileOutput(outputFile.c_str(), std::ios::out | std::ios::binary);
        for (int i=0; i<height; i++){
            unsigned char * temp = new unsigned char [width];
            for (int j=0; j<width; j++){
                temp[j] = (unsigned char)(std::abs((float)slices[sliceI][i][j] - (float)slices[sliceJ][i][j])/2);
                //fileOutput << (unsigned char)(std::abs((float)slices[sliceI][i][j] - (float)slices[sliceJ][i][j])/2);
            }
            fileOutput.write(reinterpret_cast<char*>(temp), width);
            /*if (i < height-1){
                fileOutput << std::endl;
            }*/
        }
        std::cout << "diffmap of slices " << sliceI << " and " << sliceJ << " written to file " << outputFile << std::endl;
    }
    
    void VolImage::extract(int sliceId, std::string output_prefix){
        std::string outputHeader = output_prefix + ".data";
        std::string outputFile = output_prefix + ".raw";
        std::ofstream fileHOutput (outputHeader.c_str());
        std::ostringstream oss;
        oss << width << " " << height;
        std::string headerInfo;
        headerInfo = oss.str() + " 1";
        fileHOutput <<  headerInfo;
        std::ofstream fileOutput(outputFile.c_str(), /*std::ios::out |*/ std::ios::binary);
        for (int i=0; i<height; i++){
            fileOutput.write(reinterpret_cast<char*>(slices[sliceId][i]), width);
            /*for (int j=0; j<width; j++){
                fileOutput << slices[sliceId][i][j];
            }*/
            /*if (i < height-1){
                fileOutput << std::endl;
            }*/
        }
        std::cout << "slice " << sliceId << " written to file " << outputFile << std::endl;
    }
    
    int VolImage::volImageSize(){
        return (width*height*slices.size())*sizeof(char**);
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