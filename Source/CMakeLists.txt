cmake_minimum_required(VERSION 2.6)

PROJECT( vpp )

SET(EXECUTABLE_OUTPUT_PATH ${vpp_SOURCE_DIR}/../bin)
SET(LIBRARY_OUTPUT_PATH ${vpp_SOURCE_DIR}/../lib)
SET(RUNTIME_OUTPUT_DIRECTORY ${vpp_SOURCE_DIR}/../bin)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${vpp_SOURCE_DIR}/../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${vpp_SOURCE_DIR}/../bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${vpp_SOURCE_DIR}/../bin)

message("vpp_CONTRIB_DIR directories:" $ENV{vpp_CONTRIB_DIR})
message("BOOST_INCLUDE_DIR:" $ENV{BOOST_INCLUDE_DIR})
message("MS SDK: " $ENV{MSSDK})
message("Adding DS baselasses ${DSHOWBASECLASSES}")

IF(WIN32)
IF(MSVC12)
set(vpp_CONTRIB_DIR_LIBS $ENV{vpp_CONTRIB_DIR}/lib/VC12)
set(MSVC_VER VC12)
ELSEIF(MSVC11)
set(vpp_CONTRIB_DIR_LIBS $ENV{vpp_CONTRIB_DIR}/lib/VC11)
set(MSVC_VER VC11)
ELSEIF(MSVC10)
set(vpp_CONTRIB_DIR_LIBS $ENV{vpp_CONTRIB_DIR}/lib/VC10)
set(MSVC_VER VC10)
ELSE(MSVC12)
set(vpp_CONTRIB_DIR_LIBS $ENV{vpp_CONTRIB_DIR}/lib)
ENDIF(MSVC12)
ENDIF(WIN32)

# hack for backwards compatibility to pre-CMake projects
add_definitions(-DVPP_CMAKE_BUILD)

# registering of DS filters
SET(REGISTER_DS_FILTERS false)

# NOTE: this has many additional dependencies such as boost, glog, LiveMediaExt, cpp-util
# RtspSinkFilter relies on LiveMediaExt
SET(BUILD_RTSP_SINK_FILTER true)

# Opus
SET(OPUS_SUPPORT true)

IF (BUILD_RTSP_SINK_FILTER)
message("LiveMediaExt: $ENV{LIVE_MEDIA_EXT_ROOT}")
# we need glog
add_library( glog UNKNOWN IMPORTED )
set_target_properties( glog PROPERTIES IMPORTED_LOCATION_DEBUG $ENV{LIVE_MEDIA_EXT_ROOT}/lib/Debug/libglog.lib )
set_target_properties( glog PROPERTIES IMPORTED_LOCATION_RELEASE $ENV{LIVE_MEDIA_EXT_ROOT}/lib/Release/libglog.lib )
add_library( LiveMediaExt UNKNOWN IMPORTED )
add_library( SimpleRateAdaptation UNKNOWN IMPORTED )
set_target_properties( LiveMediaExt PROPERTIES IMPORTED_LOCATION_DEBUG $ENV{LIVE_MEDIA_EXT_ROOT}/lib/Debug/LiveMediaExt.lib )
set_target_properties( LiveMediaExt PROPERTIES IMPORTED_LOCATION_RELEASE $ENV{LIVE_MEDIA_EXT_ROOT}/lib/Release/LiveMediaExt.lib )
set_target_properties( SimpleRateAdaptation PROPERTIES IMPORTED_LOCATION_DEBUG $ENV{LIVE_MEDIA_EXT_ROOT}/lib/Debug/SimpleRateAdaptation.lib )
set_target_properties( SimpleRateAdaptation PROPERTIES IMPORTED_LOCATION_RELEASE $ENV{LIVE_MEDIA_EXT_ROOT}/lib/Release/SimpleRateAdaptation.lib )
ENDIF(BUILD_RTSP_SINK_FILTER)

IF (OPUS_SUPPORT)
message("Opus: $ENV{OPUS_ROOT}")
add_library( opus UNKNOWN IMPORTED )
add_library( celt UNKNOWN IMPORTED )
add_library( silk_common UNKNOWN IMPORTED )
add_library( silk_fixed UNKNOWN IMPORTED )
add_library( silk_float UNKNOWN IMPORTED )
set_target_properties( opus PROPERTIES IMPORTED_LOCATION_DEBUG $ENV{OPUS_ROOT}/lib/Debug/opus.lib )
set_target_properties( opus PROPERTIES IMPORTED_LOCATION_RELEASE $ENV{OPUS_ROOT}/lib/Release/opus.lib )
set_target_properties( celt PROPERTIES IMPORTED_LOCATION_DEBUG $ENV{OPUS_ROOT}/lib/Debug/celt.lib )
set_target_properties( celt PROPERTIES IMPORTED_LOCATION_RELEASE $ENV{OPUS_ROOT}/lib/Release/celt.lib )
set_target_properties( silk_common PROPERTIES IMPORTED_LOCATION_DEBUG $ENV{OPUS_ROOT}/lib/Debug/silk_common.lib )
set_target_properties( silk_common PROPERTIES IMPORTED_LOCATION_RELEASE $ENV{OPUS_ROOT}/lib/Release/silk_common.lib )
set_target_properties( silk_fixed PROPERTIES IMPORTED_LOCATION_DEBUG $ENV{OPUS_ROOT}/lib/Debug/silk_fixed.lib )
set_target_properties( silk_fixed PROPERTIES IMPORTED_LOCATION_RELEASE $ENV{OPUS_ROOT}/lib/Release/silk_fixed.lib )
set_target_properties( silk_float PROPERTIES IMPORTED_LOCATION_DEBUG $ENV{OPUS_ROOT}/lib/Debug/silk_float.lib )
set_target_properties( silk_float PROPERTIES IMPORTED_LOCATION_RELEASE $ENV{OPUS_ROOT}/lib/Release/silk_float.lib )
ENDIF(OPUS_SUPPORT)

#define 3rd party libs under windows
# on linux these will have been installed
IF(WIN32)
# Assuming the Foo-root dir is defined in FOO_DIR
add_library( amr UNKNOWN IMPORTED )
#add_library( baseclasses UNKNOWN IMPORTED )
add_library( faac UNKNOWN IMPORTED )
add_library( faad UNKNOWN IMPORTED )
#add_library( liveMedia UNKNOWN IMPORTED )
#add_library( BasicUsageEnvironment UNKNOWN IMPORTED )
#add_library( groupsock UNKNOWN IMPORTED )
#add_library( UsageEnvironment UNKNOWN IMPORTED )

# You can define two import-locations: one for debug and one for release.

set_target_properties( amr PROPERTIES IMPORTED_LOCATION_DEBUG ${vpp_CONTRIB_DIR_LIBS}/libamr_nb_d.lib )
set_target_properties( amr PROPERTIES IMPORTED_LOCATION_RELEASE ${vpp_CONTRIB_DIR_LIBS}/libamr_nb.lib )

#set_target_properties( baseclasses PROPERTIES IMPORTED_LOCATION_DEBUG ${vpp_CONTRIB_DIR_LIBS}/strmbasd.lib )
#set_target_properties( baseclasses PROPERTIES IMPORTED_LOCATION_RELEASE ${vpp_CONTRIB_DIR_LIBS}/strmbase.lib )

set_target_properties( faac PROPERTIES IMPORTED_LOCATION_DEBUG ${vpp_CONTRIB_DIR_LIBS}/libfaacD.lib )
set_target_properties( faac PROPERTIES IMPORTED_LOCATION_RELEASE ${vpp_CONTRIB_DIR_LIBS}/libfaac.lib )

set_target_properties( faad PROPERTIES IMPORTED_LOCATION_DEBUG ${vpp_CONTRIB_DIR_LIBS}/libfaadD.lib )
set_target_properties( faad PROPERTIES IMPORTED_LOCATION_RELEASE ${vpp_CONTRIB_DIR_LIBS}/libfaad.lib )

#set_target_properties( liveMedia PROPERTIES IMPORTED_LOCATION_DEBUG ${vpp_CONTRIB_DIR_LIBS}/libliveMediaD.lib )
#set_target_properties( BasicUsageEnvironment PROPERTIES IMPORTED_LOCATION_DEBUG ${vpp_CONTRIB_DIR_LIBS}/libBasicUsageEnvironmentD.lib )
#set_target_properties( groupsock PROPERTIES IMPORTED_LOCATION_DEBUG ${vpp_CONTRIB_DIR_LIBS}/libgroupsockD.lib )
#set_target_properties( UsageEnvironment PROPERTIES IMPORTED_LOCATION_DEBUG ${vpp_CONTRIB_DIR_LIBS}/libUsageEnvironmentD.lib )
#set_target_properties( liveMedia PROPERTIES IMPORTED_LOCATION_RELEASE ${vpp_CONTRIB_DIR_LIBS}/libliveMedia.lib )
#set_target_properties( BasicUsageEnvironment PROPERTIES IMPORTED_LOCATION_RELEASE ${vpp_CONTRIB_DIR_LIBS}/libBasicUsageEnvironment.lib )
#set_target_properties( groupsock PROPERTIES IMPORTED_LOCATION_RELEASE ${vpp_CONTRIB_DIR_LIBS}/libgroupsock.lib )
#set_target_properties( UsageEnvironment PROPERTIES IMPORTED_LOCATION_RELEASE ${vpp_CONTRIB_DIR_LIBS}/libUsageEnvironment.lib )

ENDIF(WIN32)

SET(live555Includes
${vpp_SOURCE_DIR}/3rdParty/LiveMedia/live/BasicUsageEnvironment/include
${vpp_SOURCE_DIR}/3rdParty/LiveMedia/live/groupsock/include
${vpp_SOURCE_DIR}/3rdParty/LiveMedia/live/liveMedia/include
${vpp_SOURCE_DIR}/3rdParty/LiveMedia/live/UsageEnvironment/include
)

IF(WIN32)
SET(vppIncludes
${vpp_SOURCE_DIR}
${vpp_SOURCE_DIR}/RtvcLib
$ENV{BOOST_INCLUDE_DIR}
$ENV{vpp_CONTRIB_DIR}
${live555Includes}
$ENV{DSHOWBASECLASSES}
$ENV{MSSDK}/Include
$ENV{MSSDK}/Include/um
$ENV{MSSDK}/Include/shared
)
ENDIF(WIN32)

SET(vppCodecIncludes
${vpp_SOURCE_DIR}/Codecs/CodecUtils
${vpp_SOURCE_DIR}/Codecs/H264v2
${vpp_SOURCE_DIR}/Codecs/H264v2Codec
)

SET(vppUtilIncludes
${vpp_SOURCE_DIR}/RtvcLib/DirectShow
${vpp_SOURCE_DIR}/RtvcLib/GeneralUtils
${vpp_SOURCE_DIR}/RtvcLib/Image
${vpp_SOURCE_DIR}/RtvcLib/Shared
)

# we need ${CMAKE_LIBRARY_ARCHITECTURE} on 64-bit linux systems to locate xerces

# lib directories
IF(WIN32)
SET(vppLink
${vpp_SOURCE_DIR}/../lib
$ENV{BOOST_LIB_DIR}
${vpp_CONTRIB_DIR_LIBS}
$ENV{MSSDK}/Lib
)
ENDIF(WIN32)

IF(WIN32)
SET(vppLibs
ws2_32
baseclasses
comctl32
winmm
strmiids
)
ENDIF(WIN32)

SET(LiveMediaLibs
liveMedia
groupsock
UsageEnvironment
BasicUsageEnvironment
)

IF(WIN32)
SET(vppLibsDsApp
vpp
baseclasses
${vppLibs}
winmm
)
ENDIF(WIN32)

ADD_SUBDIRECTORY( 3rdParty ) 
#ADD_SUBDIRECTORY( Apps ) 
ADD_SUBDIRECTORY( Codecs ) 
ADD_SUBDIRECTORY( Filters ) 
ADD_SUBDIRECTORY( RtvcLib ) 
