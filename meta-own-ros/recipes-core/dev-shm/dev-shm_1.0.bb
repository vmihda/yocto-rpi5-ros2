SUMMARY = "Mount tmpfs on /dev/shm at boot for Fast DDS shared memory"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://dev-shm.sh"
S = "${WORKDIR}"

inherit update-rc.d

# Right after udev (S04), which creates /dev/shm as a plain directory
INITSCRIPT_NAME = "dev-shm"
INITSCRIPT_PARAMS = "start 05 S ."

do_install() {
	install -d ${D}${sysconfdir}/init.d
	install -m 0755 ${WORKDIR}/dev-shm.sh ${D}${sysconfdir}/init.d/dev-shm
}
