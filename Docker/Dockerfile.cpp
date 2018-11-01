FROM ubuntu:18.04

ENV cvVersion="3.4.3"

RUN apt -y update \
	&& apt -y remove x264 libx264-dev \
	&& apt -y install build-essential checkinstall cmake pkg-config yasm mc \
	&& apt -y install git gfortran libjpeg8-dev libpng-dev software-properties-common \
	&& add-apt-repository "deb http://security.ubuntu.com/ubuntu xenial-security main" \
	&& apt -y update \
	&& apt -y install libjasper1 libtiff-dev \
	&& apt -y install libavcodec-dev libavformat-dev libswscale-dev libdc1394-22-dev \
	&& apt -y install libxine2-dev libv4l-dev \
	&& cd /usr/include/linux \
	&& ln -s -f ../libv4l1-videodev.h videodev.h \
	&& cd - \
	&& apt -y install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev \
	&& apt -y install libgtk2.0-dev libtbb-dev qt5-default \
	&& apt -y install libatlas-base-dev \
	&& apt -y install libfaac-dev libmp3lame-dev libtheora-dev \
	&& apt -y install libvorbis-dev libxvidcore-dev \
	&& apt -y install libopencore-amrnb-dev libopencore-amrwb-dev \
	&& apt -y install libavresample-dev \
	&& apt -y install x264 v4l-utils \
	&& apt -y install libprotobuf-dev protobuf-compiler \
	&& apt -y install libgoogle-glog-dev libgflags-dev \
	&& apt -y install libgphoto2-dev libeigen3-dev libhdf5-dev doxygen \
	&& cd /root \
	&& git clone https://github.com/opencv/opencv.git \
	&& git clone https://github.com/opencv/opencv_contrib.git \
	&& cd opencv && git checkout $cvVersion \
	&& cd ../opencv_contrib	&& git checkout $cvVersion \
	&& mkdir -p /root/opencv/build && cd ../opencv/build \
	&& cmake -D CMAKE_BUILD_TYPE=RELEASE \
	-D CMAKE_INSTALL_PREFIX=/usr/local \
	-D INSTALL_C_EXAMPLES=ON \
	-D INSTALL_PYTHON_EXAMPLES=ON \
	-D WITH_TBB=ON \
	-D WITH_V4L=ON \
	-D WITH_QT=ON \
	-D WITH_OPENGL=ON \
	-D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules \
	-D BUILD_EXAMPLES=ON .. \
	&& make -j4 \
	&& make install \
	&& sh -c 'echo "/usr/local/lib" >> /etc/ld.so.conf.d/opencv.conf' \
	&& ldconfig \
	&& rm -rf /root && rm -rf opencv*

