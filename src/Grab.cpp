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

#include "UXDC_DRVM.pb.h"    

#include <map>
#include "GeneralParameters.h"

int main(int argc, char* argv[])
{
	eCAL::Initialize(0, 0, "UXDC_DRVMServer");
	eCAL::Process::SetState(proc_sev_healthy, proc_sev_level1, "I feel good !");
    eCAL::protobuf::CPublisher<UXDC::DRVM::DRVM_Status> pub_status("DRVM_Status");
    eCAL::protobuf::CPublisher<UXDC::DRVM::DRVM_VideoStream> pub_videostream("DRVM_VideoStream");

    UXDC::DRVM::DRVM_Status msg_status;
    UXDC::DRVM::CameraDeviceInfo msg_deviceinfo;
    UXDC::DRVM::DRVM_VideoStream msg_videostream;

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


    std::map<std::string, std::string> mapDeviceInfo = usedCamera.GetDeviceInfoMap();

    // prepare ecal message for static device info (will not change during operation)
    msg_deviceinfo.set_deviceguid(mapDeviceInfo.find("DeviceGUID")->second);
    msg_deviceinfo.set_devicefactory(mapDeviceInfo.find("DeviceFactory")->second);
    msg_deviceinfo.set_friendlyname(mapDeviceInfo.find("FriendlyName")->second);
    msg_deviceinfo.set_fullname(mapDeviceInfo.find("FullName")->second);
    msg_deviceinfo.set_modelname(mapDeviceInfo.find("ModelName")->second);
    msg_deviceinfo.set_serialnumber(mapDeviceInfo.find("SerialNumber")->second);
    msg_deviceinfo.set_vendorname(mapDeviceInfo.find("VendorName")->second);

    const CamGeneralParameters* ptrGeneralParameters = usedCamera.GetGeneralParametersPtr();
    


    msg_videostream.set_allocated_mdeviceinfo(&msg_deviceinfo);

    int counter = 0;
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
            msg_status.set_alive_counter(counter);
            counter++;
            pub_status.Send(msg_status);
            pub_videostream.Send(msg_videostream);
            
            
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
