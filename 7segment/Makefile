obj-m += 7segment.o

all: run dt

run:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

dt: overlay.dts
	dtc -@ -I dts -O dtb -o overlay.dtbo overlay.dts
	sudo dtoverlay overlay.dtbo
