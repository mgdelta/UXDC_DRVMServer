#include "BaslerCamera.h"

#include <fstream>

BaslerCamera::BaslerCamera()
{
    // Before using any pylon methods, the pylon runtime must be initialized. 
    Pylon::PylonInitialize();
    camera = 0;
    nodemap = 0;
}
BaslerCamera::~BaslerCamera()
{
    if (camera->IsOpen())
        camera->Close();

    delete camera;
    camera = 0;
    Pylon::PylonTerminate();
}

void BaslerCamera::OpenFirstCamera()
{
    try {
        // Create an instant camera object with the camera device found first.
        camera = new Pylon::CInstantCamera( Pylon::CTlFactory::GetInstance().CreateFirstDevice());
        camera->Open();
        nodemap = &camera->GetNodeMap();
    }
        catch (const Pylon::GenericException &e)
    {
        // Error handling.
        std::cerr << "An exception occurred." << std::endl << e.GetDescription() << std::endl;
    }
}

void BaslerCamera::SaveCamParametersToFile(std::string filename)
{
    if (nodemap != 0)
        // Save the content of the camera's node map into the file.
        Pylon::CFeaturePersistence::Save( filename.c_str(), nodemap );
}

void BaslerCamera::SetMandatoryDefaultParameters()
{
            // Set the pixel data format.
            Pylon::CEnumParameter(nodemap, "PixelFormat").SetValue("BayerRG12");
            Pylon::CFloatParameter(nodemap, "AcquisitionFrameRate").SetValue(max_framerate);
}

void BaslerCamera::LoadCamParametersFromFile(std::string filename)
{
    std::ifstream f(filename);

    if (f.good())
    {
        std::cout << "Reading UXDC file back to camera's node map..."<< std::endl;
        Pylon::CFeaturePersistence::Load( filename.c_str(), nodemap, true );
    }
    else
    {
        std::cout << "File not found, using camera parameters" << std::endl;
    }
}

void BaslerCamera::StartGrabbing()
{
   // The parameter MaxNumBuffer can be used to control the count of buffers
        // allocated for grabbing. The default value of this parameter is 10.
        camera->MaxNumBuffer = 5;

        // Start the grabbing of c_countOfImagesToGrab images.
        // The camera device is parameterized with a default configuration which
        // sets up free-running continuous acquisition.
        //camera.StartGrabbing( c_countOfImagesToGrab);
        
        try
        {
            camera->StartGrabbing();
        }
        catch(const Pylon::GenericException e)
        {
        // Error handling.
        std::cerr << "An exception occurred." << std::endl << e.GetDescription() << std::endl;
        }
}      

bool BaslerCamera::CamIsGrabbing()
{
    return camera->IsGrabbing();
}

void BaslerCamera::GetGrabbedImage(Pylon::CGrabResultPtr &ptrImagePointer)
{
    try {
        // Wait for an image and then retrieve it. A timeout of 5000 ms is used.
        camera->RetrieveResult( 5000, ptrImagePointer, Pylon::TimeoutHandling_ThrowException);
    }
          catch(const Pylon::GenericException e)
        {
        // Error handling.
        std::cerr << "An exception occurred." << std::endl << e.GetDescription() << std::endl;
        }  
}

void BaslerCamera::SaveDeviceParameters()
{
    // one time parameters of device, never changed during operation
    cCamParams.SetModelName(static_cast<std::string>(camera->GetDeviceInfo().GetModelName()));
    cCamParams.SetSerialNumber(static_cast<std::string>(camera->GetDeviceInfo().GetSerialNumber()));
    cCamParams.SetDeviceFactory(static_cast<std::string>(camera->GetDeviceInfo().GetDeviceFactory()));
    cCamParams.SetFriendlyName(static_cast<std::string>(camera->GetDeviceInfo().GetFriendlyName()));
    cCamParams.SetFullName(static_cast<std::string>(camera->GetDeviceInfo().GetFullName()));
    cCamParams.SetVendorName(static_cast<std::string>(camera->GetDeviceInfo().GetVendorName()));
    cCamParams.SetDeviceGUID(static_cast<std::string>(camera->GetDeviceInfo().GetDeviceGUID()));

    // save start & live parameters at startup
    cCamGenParams.SetGainAutoMode(static_cast<std::string>(Pylon::CEnumParameter(nodemap, "GainAuto").ToString()));
    cCamGenParams.SetPixelFormat(static_cast<std::string>(Pylon::CEnumParameter(nodemap, "PixelFormat").ToString()));
    cCamGenParams.SetExposureAuto(static_cast<std::string>(Pylon::CEnumParameter(nodemap, "ExposureAuto").ToString()));
    cCamGenParams.SetExposureMode(static_cast<std::string>(Pylon::CEnumParameter(nodemap, "ExposureMode").ToString()));
    cCamGenParams.SetLightPreset(static_cast<std::string>(Pylon::CEnumParameter(nodemap, "LightSourcePreset").ToString()));
    cCamGenParams.SetUSBSpeedMode(static_cast<std::string>(Pylon::CEnumParameter(nodemap, "BslUSBSpeedMode").ToString()));


    double gain_db = Pylon::CFloatParameter(nodemap, "Gain").GetValue();//update
    double gain_lowerlimit = Pylon::CFloatParameter(nodemap, "AutoGainLowerLimit").GetValue();//update
    double gain_upperlimit = Pylon::CFloatParameter(nodemap, "AutoGainUpperLimit").GetValue();//update
    double gamma = Pylon::CFloatParameter(nodemap, "Gamma").GetValue();

    int sensor_width = Pylon::CIntegerParameter(nodemap, "SensorWidth").GetValue();
    int sensor_height = Pylon::CIntegerParameter(nodemap, "SensorHeight").GetValue();
    int sensor_ROI_widthmax = Pylon::CIntegerParameter(nodemap, "WidthMax").GetValue();
    int sensor_ROI_heightmax = Pylon::CIntegerParameter(nodemap, "HeightMax").GetValue();

    int ROI_width = Pylon::CIntegerParameter(nodemap, "Width").GetValue();
    int ROI_height = Pylon::CIntegerParameter(nodemap, "Height").GetValue();
    int ROI_offsetx = Pylon::CIntegerParameter(nodemap, "OffsetX").GetValue();
    int ROI_offsety = Pylon::CIntegerParameter(nodemap, "OffsetY").GetValue();
    bool reverse_x = Pylon::CBooleanParameter(nodemap, "ReverseX").GetValue();
    bool reverse_y = Pylon::CBooleanParameter(nodemap, "ReverseY").GetValue();

    double exposure_us = Pylon::CFloatParameter(nodemap, "ExposureTime").GetValue();//update
    double exposure_lowerlimit = Pylon::CFloatParameter(nodemap, "AutoExposureTimeLowerLimit").GetValue();
    double exposure_upperlimit = Pylon::CFloatParameter(nodemap, "AutoExposureTimeUpperLimit").GetValue();
    double fps_limit = Pylon::CFloatParameter(nodemap, "AcquisitionFrameRate").GetValue();
    double fps_actual = Pylon::CFloatParameter(nodemap, "ResultingFrameRate").GetValue();//update

    double brightness = Pylon::CFloatParameter(nodemap, "BslBrightness").GetValue();
    double contrast = Pylon::CFloatParameter(nodemap, "BslContrast").GetValue();
    double balanceratio = Pylon::CFloatParameter(nodemap, "BalanceRatio").GetValue();//update

    int linkspeed_bps = Pylon::CIntegerParameter(nodemap, "DeviceLinkSpeed").GetValue();
    int speedlimit_Bps = Pylon::CIntegerParameter(nodemap, "DeviceLinkThroughputLimit").GetValue();

    // std::string gainauto = static_cast<std::string>(Pylon::CEnumParameter(nodemap, "GainAuto").ToString());
    // std::string pixelformat = static_cast<std::string>(Pylon::CEnumParameter(nodemap, "PixelFormat").ToString());
    // std::string exposureauto = static_cast<std::string>(Pylon::CEnumParameter(nodemap, "ExposureAuto").ToString());
    // std::string exposuremode = static_cast<std::string>(Pylon::CEnumParameter(nodemap, "ExposureMode").ToString());
    // std::string lightpreset = static_cast<std::string>(Pylon::CEnumParameter(nodemap, "LightSourcePreset").ToString());

    // std::string usbspeed = static_cast<std::string>(Pylon::CEnumParameter(nodemap, "BslUSBSpeedMode").ToString());

    std::cout << "Hallo";

}