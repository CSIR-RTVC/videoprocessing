# CMakeLists.txt

message("Adding DS baselasses $ENV{DSHOWBASECLASSES}")

INCLUDE_DIRECTORIES(
$ENV{DSHOWBASECLASSES}
)

SET(DS_SRCS 
$ENV{DSHOWBASECLASSES}/amextra.cpp
$ENV{DSHOWBASECLASSES}/amfilter.cpp
$ENV{DSHOWBASECLASSES}/amvideo.cpp
$ENV{DSHOWBASECLASSES}/arithutil.cpp
$ENV{DSHOWBASECLASSES}/combase.cpp
$ENV{DSHOWBASECLASSES}/cprop.cpp
$ENV{DSHOWBASECLASSES}/ctlutil.cpp
$ENV{DSHOWBASECLASSES}/ddmm.cpp
$ENV{DSHOWBASECLASSES}/dllentry.cpp
$ENV{DSHOWBASECLASSES}/dllsetup.cpp
$ENV{DSHOWBASECLASSES}/mtype.cpp
$ENV{DSHOWBASECLASSES}/outputq.cpp
$ENV{DSHOWBASECLASSES}/perflog.cpp
$ENV{DSHOWBASECLASSES}/pstream.cpp
$ENV{DSHOWBASECLASSES}/pullpin.cpp
$ENV{DSHOWBASECLASSES}/refclock.cpp
$ENV{DSHOWBASECLASSES}/renbase.cpp
$ENV{DSHOWBASECLASSES}/schedule.cpp
$ENV{DSHOWBASECLASSES}/seekpt.cpp
$ENV{DSHOWBASECLASSES}/source.cpp
$ENV{DSHOWBASECLASSES}/strmctl.cpp
$ENV{DSHOWBASECLASSES}/sysclock.cpp
$ENV{DSHOWBASECLASSES}/transfrm.cpp
$ENV{DSHOWBASECLASSES}/transip.cpp
$ENV{DSHOWBASECLASSES}/videoctl.cpp
$ENV{DSHOWBASECLASSES}/vtrans.cpp
$ENV{DSHOWBASECLASSES}/winctrl.cpp
$ENV{DSHOWBASECLASSES}/winutil.cpp
$ENV{DSHOWBASECLASSES}/wxdebug.cpp
$ENV{DSHOWBASECLASSES}/wxlist.cpp
$ENV{DSHOWBASECLASSES}/wxutil.cpp
)
SET(DS_HEADERS
$ENV{DSHOWBASECLASSES}/amextra.h
$ENV{DSHOWBASECLASSES}/amfilter.h
$ENV{DSHOWBASECLASSES}/cache.h
$ENV{DSHOWBASECLASSES}/checkbmi.h
$ENV{DSHOWBASECLASSES}/combase.h
$ENV{DSHOWBASECLASSES}/cprop.h
$ENV{DSHOWBASECLASSES}/ctlutil.h
$ENV{DSHOWBASECLASSES}/ddmm.h
$ENV{DSHOWBASECLASSES}/dllsetup.h
$ENV{DSHOWBASECLASSES}/dxmperf.h
$ENV{DSHOWBASECLASSES}/fourcc.h
$ENV{DSHOWBASECLASSES}/measure.h
$ENV{DSHOWBASECLASSES}/msgthrd.h
$ENV{DSHOWBASECLASSES}/mtype.h
$ENV{DSHOWBASECLASSES}/outputq.h
$ENV{DSHOWBASECLASSES}/perflog.h
$ENV{DSHOWBASECLASSES}/perfstruct.h
$ENV{DSHOWBASECLASSES}/pstream.h
$ENV{DSHOWBASECLASSES}/pullpin.h
$ENV{DSHOWBASECLASSES}/refclock.h
$ENV{DSHOWBASECLASSES}/reftime.h
$ENV{DSHOWBASECLASSES}/renbase.h
$ENV{DSHOWBASECLASSES}/schedule.h
$ENV{DSHOWBASECLASSES}/seekpt.h
$ENV{DSHOWBASECLASSES}/source.h
$ENV{DSHOWBASECLASSES}/streams.h
$ENV{DSHOWBASECLASSES}/strmctl.h
$ENV{DSHOWBASECLASSES}/sysclock.h
$ENV{DSHOWBASECLASSES}/transfrm.h
$ENV{DSHOWBASECLASSES}/transip.h
$ENV{DSHOWBASECLASSES}/videoctl.h
$ENV{DSHOWBASECLASSES}/vtrans.h
$ENV{DSHOWBASECLASSES}/winctrl.h
$ENV{DSHOWBASECLASSES}/winutil.h
$ENV{DSHOWBASECLASSES}/wxdebug.h
$ENV{DSHOWBASECLASSES}/wxlist.h
$ENV{DSHOWBASECLASSES}/wxutil.h
)

ADD_LIBRARY( baseclasses STATIC ${DS_SRCS} ${DS_HEADERS})

