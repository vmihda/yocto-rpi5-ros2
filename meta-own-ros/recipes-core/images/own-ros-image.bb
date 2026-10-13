# The image from meta-own (Dropbear, Wi-Fi, secrets) plus ROS 2 Jazzy
require recipes-core/images/own-image.bb

SUMMARY = "Raspberry Pi 5 image with SSH over Wi-Fi and ROS 2 Jazzy"

IMAGE_INSTALL += " \
    ros-core \
    demo-nodes-cpp \
    counter-demo \
    ros-env \
    dev-shm \
"
