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
	
o_files = " ".join("temp/"+x for x in c_files if x != "kernel")
	
for file in c_files:
     subprocess.check_output("i686-w64-mingw32-gcc -masm=intel -Wall -Wextra -ffreestanding -O0 -nostdlib -c -otemp/"+file+" src/kernel/"+file+".c", shell=True)
     print("i686-w64-mingw32-gcc -masm=intel -Wall -Wextra -ffreestanding -O0 -nostdlib -c -otemp/"+file+" src/kernel/"+file+".c")

subprocess.check_output("i686-w64-mingw32-as -c -otemp/isr_wrapper src/kernel/isr_wrapper.s", shell=True)
print("i686-w64-mingw32-as -c -otemp/isr_wrapper src/kernel/isr_wrapper.s")

subprocess.check_output("nasm -fbin -otemp/bootsector.img src/boot_loader/bootsector.asm", shell=True)
print("nasm -fbin -otemp/bootsector.img src/boot_loader/bootsector.asm")
subprocess.check_output("i686-w64-mingw32-ld --image-base=0x100000 -o temp/kernel.exe temp/kernel temp/isr_wrapper "+o_files, shell=True)
print("i686-w64-mingw32-ld -Wl --stack,0xffff --image-base=0x100000 -o temp/kernel.exe temp/kernel temp/isr_wrapper "+o_files)
subprocess.check_output("i686-w64-mingw32-strip temp/kernel.exe", shell=True)
print("i686-w64-mingw32-strip temp/kernel.exe")

bootSector = open("temp/bootsector.img","rb")
kernel = open("temp/kernel.exe","rb")

sectors = 60
bootsector_size = os.stat("temp/bootsector.img").st_size
if bootsector_size > 512:
	print("SIZE OF BOOTSECTOR IS TO BIG!!!")
	raise Exception()
kernel_size = os.stat("temp/kernel.exe").st_size
size = bootsector_size + kernel_size
if size > (sectors + 1)*512:
	print("SIZE OF KERNEL IS TO BIG!!!")
	raise Exception()
empty_bytes = bytes((sectors + 1)*512 - kernel_size)
print("\n---------------------------------")
print("You still have "+str(((sectors + 1)*512-kernel_size)/1024)+"KB free.")
print("On kernel has been used "+str(kernel_size/1024)+"KB")
buffer = []
buffer = bootSector.read() + kernel.read() + empty_bytes
image = open("image/boot.img","wb")
image.write(buffer)

bootSector.close()
kernel.close()
image.close()
