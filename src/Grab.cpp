// Grab.cpp
/*
    Note: Before getting started, Basler recommends reading the "Programmer's Guide" topic
    in the pylon C++ API documentation delivered with pylon.
    If you are upgrading to a higher major version of pylon, Basler also
    strongly recommends reading the "Migrating from Previous Versions" topic in the pylon C++ API documentation.

    This sample illustrates how to grab and process images using the CInstantCamera class.
    The images are grabbed and processed asynchronously, i.e.,
    while the application is processing a buffer, the acquisition of the next buffer is done
    in parallel.

    The CInstantCamera class uses a pool of buffers to retrieve image data
    from the camera device. Once a buffer is filled and ready,
    the buffer can be retrieved from the camera object for processing. The buffer
    and additional image data are collected in a grab result. The grab result is
    held by a smart pointer after retrieval. The buffer is automatically reused
    when explicitly released or when the smart pointer object is destroyed.
*/

// Include files to use the pylon API.
#include <pylon/PylonIncludes.h>
#ifdef PYLON_WIN_BUILD
#    include <pylon/PylonGUI.h>
#endif

#include <opencv2/opencv.hpp>

#include "SampleImageCreator.h"
#include <fstream>

#include "BaslerCamera.h"

using namespace cv;

// Namespace for using pylon objects.
using namespace Pylon;

// Namespace for using cout.
using namespace std;

// Number of images to be grabbed.
static const uint32_t c_countOfImagesToGrab = 1000;


const char Filename[] = "CamDefaultNodeMap.pfs";
const char UXDCFilename[] = "UXDCNodeMap.pfs";

const std::string dateiname = "MeineDatei.pfs";
const std::string loaddatei = "Gibtesnicht.pfs";
    
    //Mat image;
    //Mat image = imread("star-wars-logo.jpg", 1);


int main(int argc, char* argv[])
{
    //namedWindow("Display Image", WINDOW_AUTOSIZE );
    //imshow("Display Image", image);
    //waitKey(0);	

    
    {
	    BaslerCamera usedCamera;
        usedCamera.OpenFirstCamera();
        usedCamera.SaveCamParametersToFile(dateiname);
        usedCamera.SetMandatoryDefaultParameters();
        usedCamera.LoadCamParametersFromFile(loaddatei);
        usedCamera.SaveDeviceParameters();
        usedCamera.StartGrabbing();
        while( cin.get() != '\n');
        CGrabResultPtr ptrMyImage;
        while (usedCamera.CamIsGrabbing())
        {
            usedCamera.GetGrabbedImage(ptrMyImage);
            		CImageFormatConverter formatConverter;
		            formatConverter.OutputPixelFormat = PixelType_BGR8packed;
		            CPylonImage pylonImage;
            if (ptrMyImage->GrabSucceeded())
            {
                std::cout << "Grabbed ";
                                // Access the image data.
                //cout << "SizeX: " << ptrGrabResult->GetWidth() << endl;
                //cout << "SizeY: " << ptrGrabResult->GetHeight() << endl;
                const uint8_t *pImageBuffer = (uint8_t *) ptrMyImage->GetBuffer();
                //cout << "Gray value of first pixel: " << (uint32_t) pImageBuffer[0] << endl << endl;
                
                //cout << "FPS: " << frames.GetValue() << endl;
                //cout << "Timestamp: " << ptrGrabResult->GetTimeStamp() << endl;
                cout << "Frame No: " << ptrMyImage->GetImageNumber() << endl;
                //cout << "Size Bytes: " << ptrGrabResult->GetImageSize() << endl;

                
                
                // formatConverter.Convert(pylonImage, ptrMyImage);
                // Mat camimage = Mat(1200,1600,CV_8UC3, (uint8_t *) pylonImage.GetBuffer());
                // namedWindow("Ausgabe", WINDOW_NORMAL);
                // imshow("Ausgabe", camimage);
                // waitKey(1);
                // ptrMyImage.Release();
            }
        }
    }

	//usedCamera.OpenFirstCamera();
    // The exit code of the sample application.
    int exitCode = 0;

    // Before using any pylon methods, the pylon runtime must be initialized. 
     PylonInitialize();


    try
    {
		CImageFormatConverter formatConverter;
		formatConverter.OutputPixelFormat = PixelType_BGR8packed;
		CPylonImage pylonImage;
		
        // Create an instant camera object with the camera device found first.
        CInstantCamera camera( CTlFactory::GetInstance().CreateFirstDevice());

	camera.Open();





GenApi::INodeMap& nodemap = camera.GetNodeMap();
CIntegerParameter width(nodemap, "Width");
cout << "Kamera Breite: " << width.GetValue() << endl;

CFloatParameter frames(nodemap, "ResultingFrameRate");

            // Set the pixel data format.
            CEnumParameter(nodemap, "PixelFormat").SetValue("BayerRG12");

		cout << "Saving camera's node map to file..."<< endl;
        // Save the content of the camera's node map into the file.
        CFeaturePersistence::Save( Filename, &camera.GetNodeMap() );

        ifstream f(UXDCFilename);
        bool gibtesdiedatei = f.good();

        if (gibtesdiedatei)
        {
            cout << "Reading UXDC file back to camera's node map..."<< endl;
            // Just for demonstration, read the content of the file back to the camera's node map with enabled validation.
            CFeaturePersistence::Load( UXDCFilename, &camera.GetNodeMap(), true );
        }
cout << "GetModelName: " << camera.GetDeviceInfo().GetModelName() << endl;
cout << "GetSerialNumber: " << camera.GetDeviceInfo().GetSerialNumber() << endl;
cout << "GetDeviceVersion: " << camera.GetDeviceInfo().GetDeviceVersion() << endl;
cout << "GetDeviceFactory: " << camera.GetDeviceInfo().GetDeviceFactory() << endl;
cout << "GetInterfaceID: " << camera.GetDeviceInfo().GetInterfaceID() << endl;
cout << "GetTransferMode: " << camera.GetDeviceInfo().GetTransferMode() << endl;
cout << "GetFriendlyName: " << camera.GetDeviceInfo().GetFriendlyName() << endl;
cout << "GetFullName: " << camera.GetDeviceInfo().GetFullName() << endl;
cout << "GetVendorName: " << camera.GetDeviceInfo().GetVendorName() << endl;
cout << "GetInitialBaudRate: " << camera.GetDeviceInfo().GetInitialBaudRate() << endl;
cout << "GetInternalName: " << camera.GetDeviceInfo().GetInternalName() << endl;
cout << "GetUsbDriverType: " << camera.GetDeviceInfo().GetUsbDriverType() << endl;
cout << "GetDeviceGUID: " << camera.GetDeviceInfo().GetDeviceGUID() << endl;
cout << "GetInternalName: " << camera.GetDeviceInfo().GetInternalName() << endl;
cout << "GetInternalName: " << camera.GetDeviceInfo().GetInternalName() << endl;
cout << "GetInternalName: " << camera.GetDeviceInfo().GetInternalName() << endl;









            // Create a sample image.
            CPylonImage imageRGB8packed = SampleImageCreator::CreateMandelbrotFractal( PixelType_RGB8packed, 1600, 1200);
            //ShowImage( imageRGB8packed, "Source image.");
            // Create a target image
            CPylonImage targetImage;
            // Convert the image. Note that there are more overloaded Convert methods available, e.g.
            // for converting the image from or to a user buffer.
            formatConverter.Convert( targetImage, imageRGB8packed);
            //ShowImage( targetImage, "Converted image.");
            Mat testimage = Mat(1200,1600,CV_8UC3,  (uint8_t*)imageRGB8packed.GetBuffer());
			
			namedWindow("Ausgabe", WINDOW_NORMAL);
            imshow("Ausgabe", testimage);
            waitKey(0);



        // The parameter MaxNumBuffer can be used to control the count of buffers
        // allocated for grabbing. The default value of this parameter is 10.
        camera.MaxNumBuffer = 5;

        // Start the grabbing of c_countOfImagesToGrab images.
        // The camera device is parameterized with a default configuration which
        // sets up free-running continuous acquisition.
        //camera.StartGrabbing( c_countOfImagesToGrab);
        
        camera.StartGrabbing();

        // This smart pointer will receive the grab result data.
        CGrabResultPtr ptrGrabResult;

        // Camera.StopGrabbing() is called automatically by the RetrieveResult() method
        // when c_countOfImagesToGrab images have been retrieved.
        while ( camera.IsGrabbing())
        {
            // Wait for an image and then retrieve it. A timeout of 5000 ms is used.
            camera.RetrieveResult( 5000, ptrGrabResult, TimeoutHandling_ThrowException);

            // Image grabbed successfully?
            if (ptrGrabResult->GrabSucceeded())
            {
                // Access the image data.
                cout << "SizeX: " << ptrGrabResult->GetWidth() << endl;
                cout << "SizeY: " << ptrGrabResult->GetHeight() << endl;
                const uint8_t *pImageBuffer = (uint8_t *) ptrGrabResult->GetBuffer();
                cout << "Gray value of first pixel: " << (uint32_t) pImageBuffer[0] << endl << endl;
                
                cout << "FPS: " << frames.GetValue() << endl;
                cout << "Timestamp: " << ptrGrabResult->GetTimeStamp() << endl;
                cout << "Frame No: " << ptrGrabResult->GetImageNumber() << endl;
                cout << "Size Bytes: " << ptrGrabResult->GetImageSize() << endl;

                
                
                formatConverter.Convert(pylonImage, ptrGrabResult);
                Mat camimage = Mat(1200,1600,CV_8UC3, (uint8_t *) pylonImage.GetBuffer());
                namedWindow("Ausgabe", WINDOW_NORMAL);
                imshow("Ausgabe", camimage);
                waitKey(1);
                

#ifdef PYLON_WIN_BUILD
                // Display the grabbed image.
                Pylon::DisplayImage(1, ptrGrabResult);
#endif
            }
            else
            {
                cout << "Error: " << ptrGrabResult->GetErrorCode() << " " << ptrGrabResult->GetErrorDescription() << endl;
            }
        }
    }
    catch (const GenericException &e)
    {
        // Error handling.
        cerr << "An exception occurred." << endl
        << e.GetDescription() << endl;
        exitCode = 1;
    }

    // Comment the following two lines to disable waiting on exit.
    cerr << endl << "Press enter to exit." << endl;
    while( cin.get() != '\n');

    // Releases all pylon resources. 
    PylonTerminate();  

    return exitCode;
}
