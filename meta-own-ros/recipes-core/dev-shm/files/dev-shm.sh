#!/bin/sh
### BEGIN INIT INFO
# Provides:          dev-shm
# Required-Start:    udev
# Required-Stop:
# Default-Start:     S
# Default-Stop:
# Short-Description: Mount tmpfs on /dev/shm
### END INIT INFO

# Fast DDS (ROS 2) passes data between local processes through /dev/shm.
# sysvinit in poky does not mount it: mountall.sh (S03) runs before udev (S04)
# creates the directory, so an fstab entry would fail silently.

case "$1" in
start)
	[ -d /dev/shm ] || mkdir -m 1777 /dev/shm
	mountpoint -q /dev/shm || mount -t tmpfs -o mode=1777,nosuid,nodev tmpfs /dev/shm
	;;
esac

exit 0
