SUMMARY = "Load the ROS 2 environment in login shells"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://ros2.sh"
S = "${WORKDIR}"

# setup.sh is installed by ros-workspace
RDEPENDS:${PN} = "ros-workspace"

do_install() {
	install -d ${D}${sysconfdir}/profile.d
	sed -e 's,@ROS_PREFIX@,/opt/ros/${ROS_DISTRO},g' ${WORKDIR}/ros2.sh \
		> ${D}${sysconfdir}/profile.d/ros2.sh
	chmod 0644 ${D}${sysconfdir}/profile.d/ros2.sh
}

FILES:${PN} = "${sysconfdir}/profile.d/ros2.sh"
