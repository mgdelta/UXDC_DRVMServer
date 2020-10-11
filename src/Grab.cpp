// Include files to use the pylon API.
#include <pylon/PylonIncludes.h>


#include <opencv2/opencv.hpp>

//#include "SampleImageCreator.h"
//#include <fstream>

#include "BaslerCamera.h"

//using namespace cv;

// Namespace for using pylon objects.
//using namespace Pylon;

// Namespace for using cout.
//using namespace std;

#include <ecal/ecal.h>
#include <ecal/msg/protobuf/publisher.h>

const std::string file_originalcamsettings = "OriginalCamDefaultSettings.pfs";
const std::string file_drvmsettings = "UXDC-DRVM-CamSettings.pfs";
    

int main(int argc, char* argv[])
{
	eCAL::Initialize(0, 0, "UXDC_DRVMServer");
	eCAL::Process::SetState(proc_sev_healthy, proc_sev_level1, "I feel good !");
    // eCAL::protobuf::CPublisher<> pub_img;



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
    usedCamera.SaveCamParametersToFile(file_originalcamsettings);
    usedCamera.SetMandatoryDefaultParameters();
    usedCamera.LoadCamParametersFromFile(file_drvmsettings);
    usedCamera.UpdateDeviceParameters(true);
    usedCamera.StartGrabbing();


    //while( cin.get() != '\n');
    Pylon::CGrabResultPtr ptrMyImage;
    Pylon::CImageFormatConverter formatConverter;
	formatConverter.OutputPixelFormat = Pylon::PixelType_BGR8packed;
    Pylon::CPylonImage pylonImage;

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
            std::cout << "Frame No: " << iFrameNumber << std::endl;
            
            // Convert Basler Image to BGR8 Standard Image and send it away
            formatConverter.Convert(pylonImage, ptrMyImage);

            int iImageWidth = pylonImage.GetWidth();
            int iImageHeight = pylonImage.GetHeight();
            int iImageSizeBytes = pylonImage.GetImageSize();
            std::cout << "Imagesize " << iImageSizeBytes << std::endl;

            // Convert Image to an openCV Matrix (for jpeg compression and displaying)
            cv::Mat image_matrix = cv::Mat(pylonImage.GetHeight(), pylonImage.GetWidth(), CV_8UC3, (uint8_t *)pylonImage.GetBuffer());


            std::vector<uchar> jpeg_image;
            bool erfolgreich = cv::imencode(".jpg", image_matrix, jpeg_image);
            // cout << "JPEG SIZE " << jpeg_image.size() << endl;

            // Mat dst=imdecode(jpeg_image,1);
            // namedWindow("Test", WINDOW_AUTOSIZE);
            // imshow("Test",dst);
            // waitKey(1);
            
            
            
            if (ShowGrabbedImage)    
            {
                cv::namedWindow("Digital Rear View Mirror Live View", cv::WINDOW_AUTOSIZE);
                cv::imshow("Digital Rear View Mirror Live View", image_matrix);
                cv::waitKey(1);
            }
        }
    }
    



    return exitCode;
}
