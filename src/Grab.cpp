// Include files to use the pylon API.
#include <pylon/PylonIncludes.h>
#include <opencv2/opencv.hpp>

#include "BaslerCamera.h"
#include "GeneralParameters.h"

#include <ecal/ecal.h>
#include <ecal/msg/protobuf/publisher.h>

#include "UXDC_DRVM.pb.h"    

#include <map>

const std::string file_originalcamsettings = "OriginalCamDefaultSettings.pfs";
const std::string file_drvmsettings = "UXDC-DRVM-CamSettings.pfs";


int main(int argc, char* argv[])
{
	eCAL::Initialize(0, 0, "UXDC_DRVMServer");
	eCAL::Process::SetState(proc_sev_healthy, proc_sev_level1, "I feel good !");
    eCAL::protobuf::CPublisher<UXDC::DRVM::DRVM_Status> pub_status("DRVM_Status");
    eCAL::protobuf::CPublisher<UXDC::DRVM::DRVM_VideoStream> pub_videostream("DRVM_VideoStream");

    UXDC::DRVM::DRVM_Status msg_status;
    UXDC::DRVM::CameraDeviceInfo msg_deviceinfo;
    UXDC::DRVM::SensorSettings msg_sensorsettings;
    UXDC::DRVM::ImageSettings msg_imagesettings;
    UXDC::DRVM::GrabbedImage msg_grabbedimage;
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

    CamGeneralParameters *ptrGeneralParameters = usedCamera.GetGeneralParametersPtr();
    
    
    msg_sensorsettings.set_sensor_width(ptrGeneralParameters->GetSensorWidth());
    msg_sensorsettings.set_sensor_height(ptrGeneralParameters->GetSensorHeight());
    msg_sensorsettings.set_sensor_roi_widthmax(ptrGeneralParameters->GetSensorROIWidthMax());
    msg_sensorsettings.set_sensor_roi_heightmax(ptrGeneralParameters->GetSensorROIHeightMax());
    msg_sensorsettings.set_roi_height(ptrGeneralParameters->GetROIHeight());
    msg_sensorsettings.set_roi_width(ptrGeneralParameters->GetROIWidth());
    msg_sensorsettings.set_roi_offsetx(ptrGeneralParameters->GetROIOffsetX());
    msg_sensorsettings.set_roi_offsety(ptrGeneralParameters->GetROIOffsetY());
    msg_sensorsettings.set_usbspeed(ptrGeneralParameters->GetUSBSpeedMode());
    msg_sensorsettings.set_linkspeed_bps(ptrGeneralParameters->GetLinkspeed());
    msg_sensorsettings.set_speedlimit_bps(ptrGeneralParameters->GetSpeedlimit());
    msg_sensorsettings.set_fps_limit(ptrGeneralParameters->GetFPSLimit());

    msg_imagesettings.set_gain_db(ptrGeneralParameters->GetGain());
    msg_imagesettings.set_gain_lowerlimit(ptrGeneralParameters->GetGainLowerLimit());
    msg_imagesettings.set_gain_upperlimit(ptrGeneralParameters->GetGainUpperLimit());
    msg_imagesettings.set_gainauto(ptrGeneralParameters->GetGainAutoMode());
    msg_imagesettings.set_gamma(ptrGeneralParameters->GetGamma());
    msg_imagesettings.set_brightness(ptrGeneralParameters->GetBrightness());
    msg_imagesettings.set_contrast(ptrGeneralParameters->GetContrast());
    msg_imagesettings.set_balanceratio(ptrGeneralParameters->GetBalanceRatio());
    msg_imagesettings.set_lightpreset(ptrGeneralParameters->GetLightPreset());
    msg_imagesettings.set_pixelformat(ptrGeneralParameters->GetPixelFormat());
    msg_imagesettings.set_exposure_us(ptrGeneralParameters->GetExposureTime());
    msg_imagesettings.set_exposure_lowerlimit(ptrGeneralParameters->GetExposureLowerLimit());
    msg_imagesettings.set_exposure_upperlimit(ptrGeneralParameters->GetExposureUpperLimit());
    msg_imagesettings.set_exposuremode(ptrGeneralParameters->GetExposureMode());
    msg_imagesettings.set_exposureauto(ptrGeneralParameters->GetExposureAuto());

    msg_videostream.set_allocated_mdeviceinfo(&msg_deviceinfo);
    msg_videostream.set_allocated_mimagesettings(&msg_imagesettings);
    msg_videostream.set_allocated_msensorsettings(&msg_sensorsettings);
    msg_videostream.set_allocated_mgrabbedimage(&msg_grabbedimage);

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

            
            // Convert Basler Image to BGR8 Standard Image and send it away
            formatConverter.Convert(pylonImage, ptrMyImage);

            // Convert Image to an openCV Matrix (for jpeg compression and displaying)
            cv::Mat image_matrix = cv::Mat(pylonImage.GetHeight(), pylonImage.GetWidth(), CV_8UC3, (uint8_t *)pylonImage.GetBuffer());

            std::vector<uchar> jpeg_image;
            bool erfolgreich = cv::imencode(".jpg", image_matrix, jpeg_image);

            // Mat dst=imdecode(jpeg_image,1);
            // namedWindow("Test", WINDOW_AUTOSIZE);
            // imshow("Test",dst);
            // waitKey(1);
            msg_grabbedimage.set_compression("JPEG");
            msg_grabbedimage.set_fps_actual(ptrGeneralParameters->GetFPSActual());
            msg_grabbedimage.set_size_x(pylonImage.GetWidth());
            msg_grabbedimage.set_size_y(pylonImage.GetHeight());
            msg_grabbedimage.set_reverse_x(ptrGeneralParameters->GetReverseX());
            msg_grabbedimage.set_reverse_y(ptrGeneralParameters->GetReverseY());
            msg_grabbedimage.set_timestamp(ptrMyImage->GetTimeStamp());
            msg_grabbedimage.set_framenumber(ptrMyImage->GetImageNumber());
            msg_grabbedimage.set_imagesize(jpeg_image.size());
            msg_grabbedimage.set_payload(jpeg_image.data(), jpeg_image.size());

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
