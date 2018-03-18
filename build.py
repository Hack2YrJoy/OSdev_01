import os
import glob
import subprocess
import sys

if not os.path.exists("temp"):
    os.makedirs("temp")
if not os.path.exists("image"):
    os.makedirs("image")
	
c_files = []
for root, dirs, files in os.walk("src/kernel"):
    for file in files:
        if file.endswith('.c'):
            c_files.append(file.split(".")[0])
	
o_files = " ".join("temp/"+x for x in c_files)
	
for file in c_files:
	subprocess.check_output("gcc -ffreestanding -O0 -nostdlib -c -otemp/"+file+" src/kernel/"+file+".c", shell=True)

subprocess.check_output("nasm -fbin -otemp/bootsector.img src/boot_loader/bootsector.asm", shell=True)
subprocess.check_output("ld --image-base=0x100000 -o temp/kernel.exe "+o_files, shell=True)
subprocess.check_output("strip temp/kernel.exe", shell=True)

bootSector = open("temp/bootsector.img","rb")
kernel = open("temp/kernel.exe","rb")

sectors = 30
bootsector_size = os.stat("temp/bootsector.img").st_size
if bootsector_size > 512:
	print("SIZE OF BOOTSECTOR IS TO BIG!!!")
	raise Exception()
kernel_size = os.stat("temp/kernel.exe").st_size
size = bootsector_size + ((sectors*512) - kernel_size)
if size < 0:
	print("SIZE OF KERNEL IS TO BIG!!!")
	raise Exception()
empty_bytes = bytes(sectors*512 - kernel_size)
buffer = []
buffer = bootSector.read() + kernel.read() + empty_bytes
image = open("image/boot.img","wb")
image.write(buffer)

bootSector.close()
kernel.close()
image.close()
