#!/bin/sh

do_start () {
	# If setting for device is needed, do here
}

## for setting default brightness
set_display () {
	BL_BRT=
	for file in /sys/class/backlight/*; do
	#	echo $file
		if [ -e $file ]; then
			BL_BRT=$file/brightness
			break
		fi
	done
	/bin/echo `/usr/bin/vconftool get db/setting/Brightness | /usr/bin/awk '{print $4}'` > $BL_BRT
	/bin/echo 0 > /sys/class/leds/leds-torch/brightness
}

case "$1" in
	start)
		do_start
		;;
	display)
		set_display
		;;
	*)
		echo "Usage: $0 start | display"
		exit 1

esac

exit 0

