PROJECT(ImageRescaler)

FIND_PACKAGE(ITK)
IF(ITK_FOUND)
  INCLUDE(${ITK_USE_FILE})
ELSE(ITK_FOUND)
  MESSAGE(FATAL_ERROR
          "ITK not found. Please set ITK_DIR")
ENDIF(ITK_FOUND)

ADD_EXECUTABLE(irescale irescale.cpp)
TARGET_LINK_LIBRARIES(irescale ${ITK_LIBRARIES})

if (UNIX)
	INSTALL(TARGETS irescale DESTINATION /usr/local/bin)
endif (UNIX)
