########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(minizip_FIND_QUIETLY)
    set(minizip_MESSAGE_MODE VERBOSE)
else()
    set(minizip_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/minizipTargets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${minizip_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(minizip_VERSION_STRING "1.2.13")
set(minizip_INCLUDE_DIRS ${minizip_INCLUDE_DIRS_DEBUG} )
set(minizip_INCLUDE_DIR ${minizip_INCLUDE_DIRS_DEBUG} )
set(minizip_LIBRARIES ${minizip_LIBRARIES_DEBUG} )
set(minizip_DEFINITIONS ${minizip_DEFINITIONS_DEBUG} )


# Only the last installed configuration BUILD_MODULES are included to avoid the collision
foreach(_BUILD_MODULE ${minizip_BUILD_MODULES_PATHS_DEBUG} )
    message(${minizip_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


