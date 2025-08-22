cmake_minimum_required(VERSION 3.16)

# Define the project name first
project(SmtpMime VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define a variable for the library target name for clarity and consistency
set(LIBRARY_TARGET_NAME SmtpMime)

# Find the required Qt modules: Core and Network
# Widgets is not needed for this library based on the source files
find_package(Qt6 COMPONENTS Core Network REQUIRED)

# These are important for automatic processing of Qt files
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_compile_options(-DSMTP_MIME_LIBRARY)

# Use qt_add_library to create the library target
# Note: All source files, including headers, are listed here.
# The "SmtpMime" entry without a file extension is removed.
qt_add_library(${LIBRARY_TARGET_NAME}
    emailaddress.cpp
    mimeattachment.cpp
    mimebytearrayattachment.cpp
    mimefile.cpp
    mimehtml.cpp
    mimeinlinefile.cpp
    mimemessage.cpp
    mimepart.cpp
    mimetext.cpp
    smtpclient.cpp
    quotedprintable.cpp
    mimemultipart.cpp
    mimecontentencoder.cpp
    mimebase64encoder.cpp
    mimeqpencoder.cpp
    mimeqpformatter.cpp
    mimebase64formatter.cpp
    mimecontentformatter.cpp
    emailaddress.h
    mimeattachment.h
    mimebytearrayattachment.h
    mimefile.h
    mimehtml.h
    mimeinlinefile.h
    mimemessage.h
    mimepart.h
    mimetext.h
    smtpclient.h
    quotedprintable.h
    mimemultipart.h
    smtpmime_global.h
    mimecontentencoder.h
    mimebase64encoder.h
    mimeqpencoder.h
    mimeqpformatter.h
    mimebase64formatter.h
    mimecontentformatter.h
)

# Link the required Qt modules to your library
# The correct syntax is "Qt::Core" and "Qt::Network"
# Using a variable like "Qt${QT_VERSION_MAJOR}::Core" is also a good practice
# and requires the `find_package` to define the `QT_VERSION_MAJOR` variable.
target_link_libraries(${LIBRARY_TARGET_NAME} PRIVATE
    Qt6::Core
    Qt6::Network)

# Set include directories
target_include_directories(${LIBRARY_TARGET_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/smtpmime>
)

# The PUBLIC_HEADER property must be a list of files, not a single string.
# A more robust way is to use a list and set it as the property.
# The duplicate "SmtpMime" entries without extensions are removed.
set(public_headers
    emailaddress.h
    mimeattachment.h
    mimefile.h
    mimehtml.h
    mimeinlinefile.h
    mimemessage.h
    mimepart.h
    mimetext.h
    smtpclient.h
    quotedprintable.h
    mimemultipart.h
    smtpmime_global.h
    mimecontentencoder.h
    mimebase64encoder.h
    mimeqpencoder.h
    mimeqpformatter.h
    mimebase64formatter.h
    mimecontentformatter.h
    mimebytearrayattachment.h
)

set_target_properties(${LIBRARY_TARGET_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER "${public_headers}"
)

include(GNUInstallDirs)
install(TARGETS ${LIBRARY_TARGET_NAME}
    EXPORT SmtpMimeTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/smtpmime
)

install(EXPORT SmtpMimeTargets
    NAMESPACE SmtpMime::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SmtpMime
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "SmtpMimeConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/SmtpMimeConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/SmtpMimeConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SmtpMime
)