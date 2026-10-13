# Load the ROS 2 environment in login shells (SSH, serial console)
if [ -f @ROS_PREFIX@/setup.sh ]; then
    . @ROS_PREFIX@/setup.sh
fi
