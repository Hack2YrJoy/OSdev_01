#include "headers\portIO.h"

__asm__(".global _outw \n\
		_outw: \n\
		push ebp \n\
		mov ebp, esp \n\
		mov edx, [ebp + 8] \n\
		mov eax, [ebp + 12] \n\
		out dx, ax \n\
		mov esp, ebp \n\
		pop ebp \n\
		ret \n");
		
__asm__(".global _inw \n\
		_inw: \n\
		push ebp \n\
		mov ebp, esp \n\
		mov dx, [ebp + 8] \n\
		in ax, dx \n\
		mov esp, ebp \n\
		pop ebp \n\
		ret \n");
		