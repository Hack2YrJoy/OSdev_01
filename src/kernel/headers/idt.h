#pragma pack(push, 1)

void initialize_idt(void);

struct idt_structure {
	unsigned short low_base;
	unsigned short seg_selector;
	unsigned char zero_field;
	unsigned char flags;
	unsigned short high_base;
} __attribute__((packed));

struct lidt_record {
    unsigned short limit;      /* Size of IDT array - 1 */
    unsigned long base;       /* Pointer to IDT array  */
}__attribute__((packed));

void set_idt(unsigned short idx,
			  unsigned long base,
			  unsigned short seg_selector,
			  unsigned char flags);

#pragma pack(pop)
