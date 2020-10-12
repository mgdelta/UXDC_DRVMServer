cmake_minimum_required (VERSION 3.5)

project(UXDC-DRVMServer)


find_package(eCAL REQUIRED)
find_package(Protobuf REQUIRED)
find_package( OpenCV REQUIRED )

set(SRC_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Grab.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/BaslerCamera.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/DeviceParameters.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/GeneralParameters.cpp
)

include_directories( 
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  /opt/pylon/include )


get_filename_component(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR} ABSOLUTE)
#message(STATUS "Variable SRC_PATH: ${SRC_DIR}")
set(PROTO_IDL_DIR ${SRC_DIR}/protobuf)
set(PROTO_IDL_FILES
	${PROTO_IDL_DIR}/UXDC_DRVM.proto
)

#message(STATUS "Protoc Inputs")
#message(STATUS "Proto IDL dir: ${PROTO_IDL_DIR}")
#message(STATUS "Proto IDL files: ${PROTO_IDL_FILES}")

PROTOBUF_GENERATE_CPP_EXT(PROTO_SRC_FILES PROTO_HDR_FILES PROTO_INCLUDE_DIRS ${PROTO_IDL_DIR} ${PROTO_IDL_FILES})
PROTOBUF_GENERATE_PYTHON(PROTO_PYS ${PROTO_IDL_FILES})
#message(STATUS "Generated Protos")
#message(STATUS "PROTO_SRC_FILES are: ${PROTO_SRC_FILES}")
#message(STATUS "PROTO_HDR_FILES are: ${PROTO_HDR_FILES}")
#message(STATUS "PROTO_INCL_DIR: ${PROTO_INCLUDE_DIRS}")
message(STATUS "PROTO_PYS:  ${PROTO_PYS}")


link_directories(/opt/pylon/lib)


add_executable(${PROJECT_NAME}
	${SRC_FILES}
	${PROTO_SRC_FILES}
	${PROTO_HDR_FILES}
)

target_include_directories(${PROJECT_NAME} PRIVATE 
	${PROTO_INCLUDE_DIRS}/
	${CMAKE_CURRENT_SOURCE_DIR}/include/
	/opt/pylon/include
	${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
  eCAL::core
  protobuf::libprotobuf
  pylonbase
  pylonutility
  GenApi_gcc_v3_1_Basler_pylon
  GCBase_gcc_v3_1_Basler_pylon
  ${OpenCV_LIBS}
)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
add_custom_target(proto_python ALL DEPENDS ${PROTO_PYS})