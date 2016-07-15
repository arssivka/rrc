#  TCMALLOC_INCLUDE_DIRS, where to find tcmalloc.h, Set when
#                        TCMALLOC_INCLUDE_DIR is found.
#  TCMALLOC_LIBRARIES, libraries to link against to use Tcmalloc.
#  TCMALLOC_ROOT_DIR, The base directory to search for Tcmalloc.
#                    This can also be an environment variable.
#  TCMALLOC_FOUND, If false, do not try to use Tcmalloc.
#
# also defined, but not for general use are
#  TCMALLOC_LIBRARY, where to find the Tcmalloc library.

#=============================================================================
# Copyright 2011 Blender Foundation.
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================

if (USE_TCMALLOC)
    set(_tcmalloc_NAMES tcmalloc)
else ()
    set(_tcmalloc_NAMES tcmalloc_minimal tcmalloc)
endif ()

# If TCMALLOC_ROOT_DIR was defined in the environment, use it.
if(NOT TCMALLOC_ROOT_DIR AND NOT $ENV{TCMALLOC_ROOT_DIR} STREQUAL "")
    SET(TCMALLOC_ROOT_DIR $ENV{TCMALLOC_ROOT_DIR})
endif()

set(_tcmalloc_SEARCH_DIRS
        ${TCMALLOC_ROOT_DIR}
        /usr/local
        /sw # Fink
        /opt/local # DarwinPorts
        /opt/csw # Blastwave
        /usr/include/google # Debain tcmalloc minimal
        /usr/include/gperftools) # Debian gperftools

find_path(TCMALLOC_INCLUDE_DIR
        NAMES tcmalloc.h
        HINTS ${_tcmalloc_SEARCH_DIRS}
        PATH_SUFFIXES include/tcmalloc)

find_library(TCMALLOC_LIBRARY
        NAMES ${_tcmalloc_NAMES}
        HINTS ${_tcmalloc_SEARCH_DIRS}
        PATH_SUFFIXES lib64 lib)

# handle the QUIETLY and REQUIRED arguments and set TCMALLOC_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Tcmalloc DEFAULT_MSG
        TCMALLOC_LIBRARY TCMALLOC_INCLUDE_DIR)

if(TCMALLOC_FOUND)
    set(TCMALLOC_LIBRARIES ${TCMALLOC_LIBRARY})
    set(TCMALLOC_INCLUDE_DIRS ${TCMALLOC_INCLUDE_DIR})
endif(TCMALLOC_FOUND)

mark_as_advanced(
        TCMALLOC_INCLUDE_DIR
        TCMALLOC_LIBRARY
)