#include <stdio.h>
#include <string.h>

#include "disassembler.h"

int main() {
	unsigned char bytes[] = { 0x55, 0x31, 0xD2, 0x89, 0xE5, 0x8B, 0x45, 0x08, 0x56, 0x8B, 0x75, 0x0C, 0x53, 0x8D, 0x58, 0xFF, 0x0F, 0xB6, 0x0C, 0x16, 0x88, 0x4C, 0x13, 0x01, 0x83, 0xC2, 0x01, 0x84, 0xC9, 0x75, 0xF1, 0x5B, 0x5E, 0x5D, 0xC3 };

	char disassembled[0xFF];
	char instruction[0xFF];

	for (int i = 0, count = 0; i < sizeof(bytes); i += count) {
		count = disassemble(bytes + i, sizeof(bytes) - i, i, disassembled);

		printf("%08x: ", i);

		instruction[0] = 0;
		for (int e = 0; e < count; e++) {
			sprintf(instruction + strlen(instruction), "%02x ", bytes[i + e]);
		}

		printf("%-20s %s\n", instruction, disassembled);
	}
	
	/*
	
	Output:
	
	00000000: 55                   push ebp
	00000001: 31 d2                xor edx,edx
	00000003: 89 e5                mov ebp,esp
	00000005: 8b 45 08             mov eax,DWORD PTR [ebp+0x8]
	00000008: 56                   push esi
	00000009: 8b 75 0c             mov esi,DWORD PTR [ebp+0xc]
	0000000c: 53                   push ebx
	0000000d: 8d 58 ff             lea ebx,[eax-0x1]
	00000010: 0f b6 0c 16          movzx cl,BYTE PTR [esi+edx*1]
	00000014: 88 4c 13 01          mov BYTE PTR [ebx+edx*1+0x1],cl
	00000018: 83 c2 01             adc edx,0x1
	0000001b: 84 c9                test cl,cl
	0000001d: 75 f1                jne 0x10
	0000001f: 5b                   pop ebx
	00000020: 5e                   pop esi
	00000021: 5d                   pop ebp
	00000022: c3                   ret
	
	*/

	return 0;
}