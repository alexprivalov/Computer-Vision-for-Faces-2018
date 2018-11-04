#!/bin/bash

set -ex
DOCKER_IMG="alexprivalov/opencv:3.4.3"

script() {
	echo "$#"
	echo "$@"
    [ "$#" -lt 1 ] && ( usage && exit 0 ) || main "$@"
}

function usage {
    self_script_name="$(basename "$(test -L "$0" && readlink "$0" || echo "$0")")"
    echo
    echo "Usage: "
    echo "      ${self_script_name} path_to_mount_inside_docker_container"
    echo "Examples: "
    echo "      ${self_script_name} . #mount current dir"
    echo "      ${self_script_name} /home/user/dir #mount /home/user/dir into container"
    echo
}

function main()
{
	resolved_dir=$(readlink -f $1)
	
	docker pull $DOCKER_IMG || true
	xhost +local:
	docker run --device=/dev/video0:/dev/video0 \
				-v /tmp/.X11-unix:/tmp/.X11-unix \
				-e DISPLAY=$DISPLAY \
				-p 5000:5000 -p 8888:8888 -it --rm \
				-v "${resolved_dir}":"${resolved_dir}" \
				$DOCKER_IMG bash -c "cd \"${resolved_dir}\" && bash"
}

script "$@"
