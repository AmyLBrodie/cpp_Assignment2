
/* 
 * Author: Amy Brodie (BRDAMY004)
 * CSC3002H Tutorial 2
 * Created on 18 March 2016, 2:15 PM
 */


#ifndef IMAGE_MANIPULATION_H
#define IMAGE_MANIPULATION_H

#include <vector>
#include <string>

namespace BRDAMY004{
    class VolImage {
    
    private:
       int width, height;
       std::vector<unsigned char**> slices;
       
    public:
        VolImage();
        
        ~VolImage();

        bool readImages(std::string baseName);

        void diffmap(int sliceI, int sliceJ, std::string output_prefix);

        void extract(int sliceId, std::string output_prefix);

        int volImageSize(void);
    };
}


#endif /* IMAGE_MANIPULATION_H */

