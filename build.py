import os
import subprocess
import sys

subprocess.check_output("nasm -fbin -otemp\\bootsector.img src\\boot_loader\\bootsector.asm", shell=True)
subprocess.check_output("gcc -nostdlib -otemp\\kernel.exe src\\kernel\\kernel.c", shell=True)
subprocess.check_output("strip temp\\kernel.exe", shell=True)

bootSector = open("temp\\bootsector.img","rb")
kernel = open("temp\kernel.exe","rb")

sectors = 10
bootsector_size = os.stat("temp\\bootsector.img").st_size
if bootsector_size > 512:
	print("SIZE OF BOOTSECTOR IS TO BIG!!!")
	raise Exception()
kernel_size = os.stat("temp\\kernel.exe").st_size
size = bootsector_size + ((sectors*512) - kernel_size)
if size < 0:
	print("SIZE OF KERNEL IS TO BIG!!!")
	raise Exception()
empty_bytes = bytes(sectors*512 - kernel_size)
buffer = []
buffer = bootSector.read() + kernel.read() + empty_bytes
image = open("image\\boot.img","wb")
image.write(buffer)

bootSector.close()
kernel.close()
image.close()
