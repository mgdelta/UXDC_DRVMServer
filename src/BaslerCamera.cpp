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

void BaslerCamera::UpdateDeviceParameters(bool bUpdateAll)
{
    if (bUpdateAll)
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

        cCamGenParams.SetReverseX(Pylon::CBooleanParameter(nodemap, "ReverseX").GetValue());
        cCamGenParams.SetReverseY(Pylon::CBooleanParameter(nodemap, "ReverseY").GetValue());

        cCamGenParams.SetGamma(Pylon::CFloatParameter(nodemap, "Gamma").GetValue());
        cCamGenParams.SetFPSLimit(Pylon::CFloatParameter(nodemap, "AcquisitionFrameRate").GetValue());
        cCamGenParams.SetBrightness(Pylon::CFloatParameter(nodemap, "BslBrightness").GetValue());
        cCamGenParams.SetContrast(Pylon::CFloatParameter(nodemap, "BslContrast").GetValue());
        cCamGenParams.SetExposureLowerLimit(Pylon::CFloatParameter(nodemap, "AutoExposureTimeLowerLimit").GetValue());
        cCamGenParams.SetExposureUpperLimit(Pylon::CFloatParameter(nodemap, "AutoExposureTimeUpperLimit").GetValue());

        cCamGenParams.SetSensorWidth(Pylon::CIntegerParameter(nodemap, "SensorWidth").GetValue());
        cCamGenParams.SetSensorHeight(Pylon::CIntegerParameter(nodemap, "SensorHeight").GetValue());
        cCamGenParams.SetSensorROIWidthMax(Pylon::CIntegerParameter(nodemap, "WidthMax").GetValue());
        cCamGenParams.SetSensorROIHeightMax(Pylon::CIntegerParameter(nodemap, "HeightMax").GetValue());
        cCamGenParams.SetROIWidth(Pylon::CIntegerParameter(nodemap, "Width").GetValue());
        cCamGenParams.SetROIHeight(Pylon::CIntegerParameter(nodemap, "Height").GetValue());
        cCamGenParams.SetROIOffsetX(Pylon::CIntegerParameter(nodemap, "OffsetX").GetValue());
        cCamGenParams.SetROIOffsetY(Pylon::CIntegerParameter(nodemap, "OffsetY").GetValue());
        cCamGenParams.SetLinkspeed(Pylon::CIntegerParameter(nodemap, "DeviceLinkSpeed").GetValue());
        cCamGenParams.SetSpeedlimit(Pylon::CIntegerParameter(nodemap, "DeviceLinkThroughputLimit").GetValue());
    }

    // Update these values every time
    cCamGenParams.SetGain(Pylon::CFloatParameter(nodemap, "Gain").GetValue());
    cCamGenParams.SetGainLowerLimit(Pylon::CFloatParameter(nodemap, "AutoGainLowerLimit").GetValue());
    cCamGenParams.SetGainUpperLimit(Pylon::CFloatParameter(nodemap, "AutoGainUpperLimit").GetValue());
    cCamGenParams.SetExposureTime(Pylon::CFloatParameter(nodemap, "ExposureTime").GetValue());
    cCamGenParams.SetFPSActual(Pylon::CFloatParameter(nodemap, "ResultingFrameRate").GetValue());
    cCamGenParams.SetBalanceRatio(Pylon::CFloatParameter(nodemap, "BalanceRatio").GetValue());

}

std::map<std::string, std::string> BaslerCamera::GetDeviceInfoMap()
{
    std::map<std::string, std::string> mapDeviceInfo;
    mapDeviceInfo.insert(std::make_pair("ModelName", cCamParams.GetModelName()));
    mapDeviceInfo.insert(std::make_pair("SerialNumber", cCamParams.GetSerialNumber()));
    mapDeviceInfo.insert(std::make_pair("DeviceFactory", cCamParams.GetDeviceFactory()));
    mapDeviceInfo.insert(std::make_pair("FriendlyName", cCamParams.GetFriendlyName()));
    mapDeviceInfo.insert(std::make_pair("FullName", cCamParams.GetFullName()));
    mapDeviceInfo.insert(std::make_pair("VendorName", cCamParams.GetVendorName()));
    mapDeviceInfo.insert(std::make_pair("DeviceGUID", cCamParams.GetDeviceGUID()));

    return mapDeviceInfo;
}
CamGeneralParameters* BaslerCamera::GetGeneralParametersPtr()
{
    return &cCamGenParams;
}