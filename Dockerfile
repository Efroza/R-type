# Use the latest version of Ubuntu
FROM ubuntu:20.04

# Update the package list and install the dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
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

# Install Conan
RUN pip install conan

# Add the Conan remote repository
RUN conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan

# Install the dependencies using Conan
RUN conan install . -if build --build missing

# Copy the game source code into the container
COPY . /app

# Set the working directory to the source code
WORKDIR /app

# Build the game using CMake
RUN cmake . -DCMAKE_BUILD_TYPE=Release && cmake --build . --config Release