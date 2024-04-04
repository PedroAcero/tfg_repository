#!/bin/sh
set -e

. "/opt/ros/$ROS_DISTRO/setup.sh"

exec "$@"
