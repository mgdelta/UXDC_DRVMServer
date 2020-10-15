import ecal.core.core as ecal_core
from ecal.core.subscriber import ProtoSubscriber
import sys
import UXDC_DRVM_pb2
import threading
import numpy as np
import cv2
from turbojpeg import TurboJPEG, TJPF_GRAY, TJSAMP_GRAY


class BaslerReceiver:
    def __init__(self):
        print("Initializing UXDC Videostrem Web server...")
        # print eCAL version and date
        print("eCAL {} ({})\n".format(ecal_core.getversion(),ecal_core.getdate()))
        # initialize eCAL API
        ecal_core.initialize(sys.argv, "UXDC_DRVM-WebServer")

        # needs module helper
        #filedescriptor = helper.get_descriptor_from_type(CameraImage_pb2.CameraImage)
        # set process state
        ecal_core.set_process_state(1, 1, "I feel good")

        # create eCAL subscriber for Basler camera message
        sub = ProtoSubscriber("DRVM_VideoStream", UXDC_DRVM_pb2.DRVM_VideoStream)
        sub.set_callback(self.callback)

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
        ecal_core.finalize()

    def callback(self, topic_name, msg, time):
        # Basler camera eCAL message object
        pb_grabbedimage = msg.mGrabbedImage
        #print("Grabbed")

        # deserialize Basler eCAL message
        self.image = pb_grabbedimage.Payload
        self.image_height = pb_grabbedimage.Size_y
        self.image_width = pb_grabbedimage.Size_x
        self.image_size_bytes = pb_grabbedimage.ImageSize
        self.image_compression = pb_grabbedimage.Compression
        
        if self.image_compression == "JPEG":
            #print("JPEG compression")
            self.lock.acquire()
            self.Baslerimg_jpg = self.image
            self.lock.release()
        elif self.image_compression == "RAW":
            print("Raw mode")

        # set Event for synchronization
        self.event.set()

    def getimage(self):
        return self.Baslerimg_jpg

    # not needed, prepare JPEG image for HMI (flip, crop, resize, color space...)
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











