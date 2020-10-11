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


const std::string file_originalcamsettings = "OriginalCamDefualtSettings.pfs";
const std::string file_drvmsettings = "UXDC-DRVM-CamSettings.pfs";
    

int main(int argc, char* argv[])
{

    bool ShowGrabbedImage = true;
    
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
    usedCamera.SaveCamParametersToFile(file_originalcamsettings);
    usedCamera.SetMandatoryDefaultParameters();
    usedCamera.LoadCamParametersFromFile(file_drvmsettings);
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

            int iFrameNumber = ptrMyImage->GetImageNumber();
            int iTimestamp = ptrMyImage->GetTimeStamp();
            cout << "Frame No: " << iFrameNumber << endl;
            
            // Convert Basler Image to BGR8 Standard Image and send it away
            formatConverter.Convert(pylonImage, ptrMyImage);

            int iImageWidth = pylonImage.GetWidth();
            int iImageHeight = pylonImage.GetHeight();
            int iImageSizeBytes = pylonImage.GetImageSize();


            // Convert Image to an openCV Matrix (for jpeg compression and displaying)
            Mat image_matrix = Mat(pylonImage.GetHeight(), pylonImage.GetWidth(), CV_8UC3, (uint8_t *)pylonImage.GetBuffer());

            

                
            if (ShowGrabbedImage)    
            {
                namedWindow("Digital Rear View Mirror Live View", WINDOW_AUTOSIZE);
                imshow("Digital Rear View Mirror Live View", image_matrix);
                waitKey(1);
            }
        }
    }
    



    return exitCode;
}
