// Include files to use the pylon API.
#include <pylon/PylonIncludes.h>


#include <opencv2/opencv.hpp>

//#include "SampleImageCreator.h"
#include <fstream>

#include "BaslerCamera.h"

using namespace cv;

// Namespace for using pylon objects.
using namespace Pylon;

// Namespace for using cout.
using namespace std;


const std::string dateiname = "MeineDatei.pfs";
const std::string loaddatei = "Gibtesnicht.pfs";
    

int main(int argc, char* argv[])
{

    bool ShowGrabbedImage = false;
    
    // The exit code of the sample application.
    int exitCode = 0;

    if (argc > 1)
    {
        if (std::string(argv[1]) == "-show")
        {
            std::cout << "Argument -show gefunden" << std::endl;
            ShowGrabbedImage = true;
        }
    }

    // Prepare everything for camera usage
    BaslerCamera usedCamera;
    usedCamera.OpenFirstCamera();
    usedCamera.SaveCamParametersToFile(dateiname);
    usedCamera.SetMandatoryDefaultParameters();
    usedCamera.LoadCamParametersFromFile(loaddatei);
    usedCamera.UpdateDeviceParameters(true);
    usedCamera.StartGrabbing();


    //while( cin.get() != '\n');
    CGrabResultPtr ptrMyImage;
    CImageFormatConverter formatConverter;
	formatConverter.OutputPixelFormat = PixelType_BGR8packed;
    CPylonImage pylonImage;

    // endless loop for grabbing images
    while (usedCamera.CamIsGrabbing())
    {
        // get Grabbed Image as smart pointer object
        usedCamera.GetGrabbedImage(ptrMyImage);

        // do image related things when grab was successful
        if (ptrMyImage->GrabSucceeded())
        {
            // Update actual camera parameters to data class
            usedCamera.UpdateDeviceParameters(true);
            
            // Access the image data.
            const uint8_t *pImageBuffer = (uint8_t *) ptrMyImage->GetBuffer();
            
                
            //cout << "SizeX: " << ptrGrabResult->GetWidth() << endl;
            //cout << "SizeY: " << ptrGrabResult->GetHeight() << endl;
            //cout << "Timestamp: " << ptrGrabResult->GetTimeStamp() << endl;
            //cout << "Size Bytes: " << ptrGrabResult->GetImageSize() << endl;
            //cout << "Frame No: " << ptrMyImage->GetImageNumber() << endl;

            

                
            if (ShowGrabbedImage)    
            {
                formatConverter.Convert(pylonImage, ptrMyImage);

                Mat camimage = Mat(1200,1600,CV_8UC3, (uint8_t *) pylonImage.GetBuffer());
                namedWindow("Digital Rear View Mirror Live View", WINDOW_AUTOSIZE);
                imshow("Digital Rear View Mirror Live View", camimage);
                waitKey(1);
            }
        }
    }
    



    return exitCode;
}
