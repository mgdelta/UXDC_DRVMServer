cmake_minimum_required (VERSION 3.5)

project(UXDC-DRVMServer)



#set(BOOST_LIBRARYDIR /usr/lib/arm-linux-gnueabihf)
find_package(eCAL REQUIRED)
find_package(Protobuf REQUIRED)
#find_package(Boost REQUIRED system)
#find_library(HALLO rt)
#message(STATUS "HALLO: ${HALLO}")

#create_targets_protobuf()

find_package( OpenCV REQUIRED )


set(SRC_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Grab.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/BaslerCamera.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/CamParameters.cpp
)



include_directories( 
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  /opt/pylon/include )


#get_filename_component(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR} ABSOLUTE)
#message(STATUS "Variable SRC_PATH: ${SRC_DIR}")
#set(PROTO_IDL_DIR ${SRC_DIR}/protobuf)
#set(PROTO_IDL_FILES
#	${PROTO_IDL_DIR}/IAA_HaloSteeringWheel.proto
#	${PROTO_IDL_DIR}/UXDC_Halo.proto
#)




#message(STATUS "Protoc Inputs")
#message(STATUS "Proto IDL dir: ${PROTO_IDL_DIR}")
#message(STATUS "Proto IDL files: ${PROTO_IDL_FILES}")

#PROTOBUF_GENERATE_CPP_EXT(PROTO_SRC_FILES PROTO_HDR_FILES PROTO_INCLUDE_DIRS ${PROTO_IDL_DIR} ${PROTO_IDL_FILES})
#message(STATUS "Generated Protos")
#message(STATUS "PROTO_SRC_FILES are: ${PROTO_SRC_FILES}")
#message(STATUS "PROTO_HDR_FILES are: ${PROTO_HDR_FILES}")
#message(STATUS "PROTO_INCL_DIR: ${PROTO_INCLUDE_DIRS}")

#message(STATUS "Boost Libraries: ${Boost_LIBRARIES}")
#message(STATUS "Boost Includedir: ${Boost_INCLUDE_DIRS}")

link_directories(/opt/pylon/lib)


add_executable(${PROJECT_NAME}
	${SRC_FILES}
#	${PROTO_SRC_FILES}
#	${PROTO_HDR_FILES}
#${CMAKE_CURRENT_SOURCE_DIR}/src/Adafruit_DotStar.cpp
#${CMAKE_CURRENT_SOURCE_DIR}/src/ecalcomm.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE 
#	${PROTO_INCLUDE_DIRS}/
	${CMAKE_CURRENT_SOURCE_DIR}/include/
#	${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/stb
#${Boost_INCLUDE_DIRS}
	/opt/pylon/include
	${OpenCV_INCLUDE_DIRS}
)

#message(STATUS "libapa: ${CMAKE_SOURCE_DIR}")

target_link_libraries(${PROJECT_NAME}
  eCAL::core
  protobuf::libprotobuf
  
#  atomic
#  wiringPi
  #${Boost_LIBRARIES}
#	rt
#Boost::system
pylonbase
pylonutility
GenApi_gcc_v3_1_Basler_pylon
GCBase_gcc_v3_1_Basler_pylon
${OpenCV_LIBS}
)

#file(GLOB ANIMATION_FILES ${CMAKE_CURRENT_SOURCE_DIR}/assets/*.bmp)
#message(STATUS "Animation Files are: ${ANIMATION_FILES}")

#install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
#install(FILES ${ANIMATION_FILES} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)

