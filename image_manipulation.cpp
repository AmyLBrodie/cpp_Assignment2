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
    
    // Constructor for VolImage class
    VolImage::VolImage() : width(0), height(0) {
    }
    
    // Takes the supplied baseName parameter and creates the input file names for reading in the raw files
    // Opens the input files in binary mode and stores each image as a slice in the slices vector
    // Each slice is made up of a 2d array of unsigned char pointers which stores image pixel information
    // Once all images are stored it outputs the number of images stored and the bytes required to store them
    bool VolImage::readImages(std::string baseName){
        std::string fileDirec = "Raw_Files/" + baseName + ".data";
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
            std::string fileName = "Raw_Files/" + baseName + num + ".raw";
            std::ifstream rawFile(fileName.c_str(), std::ios::binary);
            if (!rawFile){
                std::cerr << "File open failed!" << std::endl;
                return false;
            }
            for (int j=0; j<height; j++){
                rows[j] = new unsigned char [width];
                rawFile.read(reinterpret_cast<char*>(rows[j]), width);
            }
            slices.push_back(rows);
            rawFile.close();
        }
        std::cout << "Number of images: " << numImages << std::endl;
        std::cout << "Number of bytes required: " << VolImage::volImageSize() << " bytes" << std::endl;
        return true;
    }
    
    // Takes in two slice numbers and calculates the diffmap between the two images
    // The diffmap is then written to the specified output raw file
    // Also creates a header file for the raw file
    void VolImage::diffmap(int sliceI, int sliceJ, std::string output_prefix) {
        std::string outputHeader = "Output_Files/" + output_prefix + ".data";
        std::string outputFile = "Output_Files/" + output_prefix + ".raw";
        std::ofstream fileHOutput (outputHeader.c_str());
        std::ostringstream oss;
        oss << width << " " << height;
        std::string headerInfo;
        headerInfo = oss.str() + " 1";
        fileHOutput <<  headerInfo;
        std::ofstream fileOutput(outputFile.c_str(), std::ios::binary);
        for (int i=0; i<height; i++){
            unsigned char * temp = new unsigned char [width];
            for (int j=0; j<width; j++){
                temp[j] = (unsigned char)(std::abs((float)slices[sliceI][i][j] - (float)slices[sliceJ][i][j])/2);
            }
            fileOutput.write(reinterpret_cast<char*>(temp), width);
            delete [] temp;
        }
        fileOutput.close();
        fileHOutput.close();
        std::cout << "diffmap of slices " << sliceI << " and " << sliceJ << " written to file " << outputFile << std::endl;
    }
    
    // Takes in a slice number and then writes the corresponding slice into the specified
    // output raw file, also creates a header file for the raw file
    void VolImage::extract(int sliceId, std::string output_prefix){
        std::string outputHeader = "Output_Files/" + output_prefix + ".data";
        std::string outputFile = "Output_Files/" + output_prefix + ".raw";
        std::ofstream fileHOutput (outputHeader.c_str());
        std::ostringstream oss;
        oss << width << " " << height;
        std::string headerInfo;
        headerInfo = oss.str() + " 1";
        fileHOutput <<  headerInfo;
        std::ofstream fileOutput(outputFile.c_str(), std::ios::binary);
        for (int i=0; i<height; i++){
            fileOutput.write(reinterpret_cast<char*>(slices[sliceId][i]), width);
        }
        fileOutput.close();
        fileHOutput.close();
        std::cout << "slice " << sliceId << " written to file " << outputFile << std::endl;
    }
    
    // Calculates the number of bytes required to store the image (including pointers)
    int VolImage::volImageSize(){
        return (width*height*slices.size())*sizeof(char*);
    }
    
    // Takes in a specific row number and then takes that row from each slice and writes
    // it to the specified output raw file, also creates a header file for the raw file
    void VolImage::rowExtract(int rowId, std::string output_prefix){
        std::string outputHeader = "Output_Files/" + output_prefix + ".data";
        std::string outputFile = "Output_Files/" + output_prefix + ".raw";
        std::ofstream fileHOutput (outputHeader.c_str());
        std::ostringstream oss;
        oss << width << " " << slices.size();
        std::string headerInfo;
        headerInfo = oss.str() + " 1";
        fileHOutput <<  headerInfo;
        std::ofstream fileOutput(outputFile.c_str(), std::ios::binary);
        for (int i=0; i<slices.size(); i++){
            fileOutput.write(reinterpret_cast<char*>(slices[i][rowId]), width);
        }
        fileOutput.close();
        fileHOutput.close();
        std::cout << "row " << rowId << " of each slice written to file " << outputFile << std::endl;
    }
    
    // Destructor for VolImage class
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