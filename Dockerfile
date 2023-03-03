# Use the latest version of Ubuntu
FROM ubuntu:20.04

# Set the Timezone
ENV TZ=Europe/Paris
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# Update the package list and install the dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    python3-pip \
    cmake \
    libasio-dev \
    doxygen \
    libudev-dev \
    libgl-dev \
    libx11-xcb-dev \
    libfontenc-dev \
    libxaw7-dev \
    libxcomposite-dev \
    libxcursor-dev \
    libxdamage-dev \
    libxfixes-dev \
    libxi-dev \
    libxinerama-dev \
    libxmu-dev \
    libxmuu-dev \
    libxpm-dev \
    libxrandr-dev \
    libxres-dev \
    libxss-dev \
    libxtst-dev \
    libxv-dev \
    libxvmc-dev \
    libxxf86vm-dev \
    libxcb-render-util0-dev \
    libxcb-xkb-dev \
    libxcb-icccm4-dev \
    libxcb-image0-dev \
    libxcb-keysyms1-dev \
    libxcb-randr0-dev \
    libxcb-shape0-dev \
    libxcb-sync-dev \
    libxcb-xfixes0-dev \
    libxcb-xinerama0-dev \
    libxcb-dri3-dev \
    pkg-config \
    libxkbfile-dev \
    uuid-dev \
    libxcb-util-dev

# Install Cmake
RUN apt-get install -y software-properties-common lsb-release
RUN apt-get clean all
RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null
RUN apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 42D5A192B819C5DA
RUN apt-add-repository "deb https://apt.kitware.com/ubuntu/ $(lsb_release -cs) main"
RUN apt-get update -y
RUN apt-get install -y kitware-archive-keyring
RUN rm /etc/apt/trusted.gpg.d/kitware.gpg
RUN apt-get update -y
RUN apt-get install -y cmake

# Install Conan
RUN pip install conan
RUN pip install conan_package_tools

# Add the Conan remote repository
RUN conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan

# Copy the game source code into the container
COPY . /app

# Set the working directory to the source code
WORKDIR /app

#Avoid problems with CMake
RUN rm CMakeCache.txt

# Build the game
RUN conan install .
RUN cmake . -DCMAKE_BUILD_TYPE=Release && cmake --build . --config Release && cpack -C Release