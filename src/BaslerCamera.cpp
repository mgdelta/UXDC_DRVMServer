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