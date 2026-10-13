SUMMARY = "Counter publisher and subscriber with a start/stop service"
DESCRIPTION = "ROS 2 package counter_demo from ros2_ws/src in this repository"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Apache-2.0;md5=89aea4e17d99a7cacdbeed46a0096b10"

inherit ros_distro_jazzy
inherit ros_component

# The sources live in ros2_ws/src at the repository root, the same tree
# that colcon builds on the host, so the board and the host run the same code
FILESEXTRAPATHS:prepend := "${THISDIR}/../../../ros2_ws/src:"
SRC_URI = "file://counter_demo"
S = "${WORKDIR}/counter_demo"

# Same dependencies as in package.xml, with BitBake names (- instead of _)
ROS_BUILD_DEPENDS = " \
    rclcpp \
    std-msgs \
    std-srvs \
"
ROS_BUILDTOOL_DEPENDS = " \
    ament-cmake-native \
"
ROS_EXEC_DEPENDS = " \
    rclcpp \
    std-msgs \
    std-srvs \
"

DEPENDS = "${ROS_BUILD_DEPENDS} ${ROS_BUILDTOOL_DEPENDS}"
RDEPENDS:${PN} += "${ROS_EXEC_DEPENDS}"

ROS_BUILD_TYPE = "ament_cmake"
inherit ros_${ROS_BUILD_TYPE}
