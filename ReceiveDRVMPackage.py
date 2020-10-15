import ecal
import sys
#import VS_CamStream_pb2
import UXDC_DRVM_pb2
import threading
import numpy as np
import cv2


class BaslerReceiver:
    def __init__(self):
        print("Initializing UXDC Videostrem Web server...")
        print("eCAL %s (%s)\n" % (ecal.getversion(), ecal.getdate()))
        # initialize eCAL API
        ecal.initialize(sys.argv, "py_Basler_Receiver")

        # needs module helper
        #filedescriptor = helper.get_descriptor_from_type(CameraImage_pb2.CameraImage)

        # create eCAL subscriber for Basler camera message
        basler_subscriber = ecal.subscriber("DRIVER_BASLER", "proto:pb.AL.CamStream.PassengerCameraData")
        basler_subscriber.set_callback(self.callback)

        # Set some class variables for decompressing
        self.image = None
        self.image_height = None
        self.image_width = None
        self.Baslerimg_jpg = None

        # Event object for synchronization
        self.event = threading.Event()
        self.lock = threading.Lock()

    def __del__(self):
        # finalize eCAL API
        ecal.finalize()

    def callback(self, topic_name, msg, time):
        # Basler camera eCAL message object
        baslermessage = VS_CamStream_pb2.PassengerCameraData()
        # deserialize Basler eCAL message
        baslermessage.ParseFromString(msg)
        self.image = baslermessage.CameraStreamData.image_payload
        self.image_height = baslermessage.CameraStreamData.image_height
        self.image_width = baslermessage.CameraStreamData.image_width

        # convert Basler Image to JPG (streamable)
        jpgimg = self.convert_image()

        # save MFC image as jpg bytestream
        self.lock.acquire()
        self.Baslerimg_jpg = jpgimg
        self.lock.release()

        # set Event for synchronization
        self.event.set()

    def getimage(self):
        return self.Baslerimg_jpg

    def convert_image(self):
        # convert Basler image payload to numpy array
        image_nparray = np.frombuffer(self.image, dtype=np.uint8)
        # reshape array to RGB matrix
        image_nparray = np.reshape(image_nparray, (self.image_height, self.image_width, 3))
        # color conversion
        image_nparray = cv2.cvtColor(image_nparray, cv2.COLOR_RGB2BGR)
        # flip image
        image_basler_raw = cv2.flip(image_nparray, 1)
        # resize to target aspect ratio
        image_basler_resized = cv2.resize(image_basler_raw, (453, 340))
        #cv2.imshow("Basler_RAW", image_basler_raw)
        #cv2.waitKey(1)
        # encode image to jpg
        ret_value, jpeg_image = cv2.imencode('.jpg', image_basler_resized)
        return jpeg_image.tobytes()











