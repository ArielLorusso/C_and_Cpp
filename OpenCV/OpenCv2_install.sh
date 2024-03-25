# https://docs.opencv.org/4.x/d7/d9f/tutorial_linux_install.html

        # Quick start

# Install minimal prerequisites (Ubuntu 18.04 as reference)
sudo apt update && sudo apt install -y cmake g++ wget unzip
 
# Download and unpack sources
wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip
unzip opencv.zip
 
# Create build directory
mkdir -p build && cd build
 
# Configure
cmake ../opencv-4.x
 
# Build
cmake --build .

        # Detailed process
        # Install compiler and build tools

# To compile OpenCV you will need a C++ compiler. Usually it is G++/GCC or Clang/LLVM:
    # Install GCC...
    sudo apt install -y g++
    # or Clang:
    sudo apt install -y clang

# OpenCV uses CMake build configuration tool:
    sudo apt install -y cmake
# CMake can generate scripts for different build systems, e.g. make, ninja: 
    #Install Make...
    sudo apt install -y make
    #... or Ninja:
    sudo apt install -y ninja-build
#Install tool for getting and unpacking sources:
    #  wget and unzip...
    sudo apt install -y wget unzip
    #... or git:
    sudo apt install -y git


    # Configure and build
# Create build directory:
    mkdir -p build && cd build
# Configure - generate build scripts for the preferred build system:
    #For make...
    cmake ../opencv
    #... or for ninja:
    #cmake -GNinja ../opencv
# Build - run actual compilation process: 
    #Using make...
    make -j4
    #... or ninja:
    # ninja

    #Install
#Warning
#The installation process only copies files to predefined locations and does minor patching. Installing using this method does not integrate opencv into the system package registry and thus, for example, opencv can not be uninstalled automatically. We do not recommend system-wide installation to regular users due to possible conflicts with system packages.
#  By default OpenCV will be installed to the /usr/local directory, all files will be copied to following locations:
# /usr/local/bin - executable files
# /usr/local/lib - libraries (.so)
# /usr/local/cmake/opencv4 - cmake package
# /usr/local/include/opencv4 - headers

sudo make install
# or
# sudo ninja install
