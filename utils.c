#include "utils.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>

/* Sign extends the given field to a 32-bit integer where field is
 * interpreted an n-bit integer. */
unsigned get_bit(unsigned x, unsigned n) {
    // YOUR CODE HERE
    // Returning -1 is a placeholder (it makes
    // no sense, because get_bit only returns
    // 0 or 1)
    return (x>>n) & 1;
}
unsigned set_bit(unsigned x,
             unsigned n,
             unsigned v) {
    int mask = ~(1 << n);
    x = x & mask;
    int vee = (v << n);
    x = x | vee;
    return x;
}
int sign_extend_number( unsigned int field, unsigned int n) {
    if (get_bit(field, (n-1)) == 0) {
        return field;
    }
    else {
        return (~(1 << (32-n)) << n) + field;
    }
}

/* Unpacks the 32-bit machine code instruction given into the correct
 * type within the instruction struct */ 
Instruction parse_instruction(uint32_t instruction_bits) {
    Instruction instruction;
    instruction.bits = instruction_bits;
    return instruction;
}

/* Return the number of bytes (from the current PC) to the branch label using the given
 * branch instruction */
int get_branch_offset(Instruction instruction) {
    struct bit_field {
        unsigned int bits : 12;
    };
    struct bit_field *bitField0 = (struct bit_field *) malloc(sizeof(struct bit_field));
    bitField0->bits = set_bit( bitField0->bits, 0, get_bit(instruction.sbtype.imm5, 1));
    bitField0->bits = set_bit( bitField0->bits, 1, get_bit(instruction.sbtype.imm5, 2));
    bitField0->bits = set_bit( bitField0->bits, 2, get_bit(instruction.sbtype.imm5, 3));
    bitField0->bits = set_bit( bitField0->bits, 3, get_bit(instruction.sbtype.imm5, 4));
    bitField0->bits = set_bit( bitField0->bits, 4, get_bit(instruction.sbtype.imm7, 0));
    bitField0->bits = set_bit( bitField0->bits, 5, get_bit(instruction.sbtype.imm7, 1));
    bitField0->bits = set_bit( bitField0->bits, 6, get_bit(instruction.sbtype.imm7, 2));
    bitField0->bits = set_bit( bitField0->bits, 7, get_bit(instruction.sbtype.imm7, 3));
    bitField0->bits = set_bit( bitField0->bits, 8, get_bit(instruction.sbtype.imm7, 4));
    bitField0->bits = set_bit( bitField0->bits, 9, get_bit(instruction.sbtype.imm7, 5));
    bitField0->bits = set_bit( bitField0->bits, 10, get_bit(instruction.sbtype.imm5, 0));
    bitField0->bits = set_bit( bitField0->bits, 11, get_bit(instruction.sbtype.imm7, 6));
    return sign_extend_number((bitField0->bits) * 2,13);
}
/* Returns the number of bytes (from the current PC) to the jump label using the given
 * jump instruction */
int get_jump_offset(Instruction instruction) {
    struct bit_field {
        unsigned int bits : 20;
    };
    struct bit_field *bitField1 = (struct bit_field *) malloc(sizeof(struct bit_field));
    bitField1->bits = set_bit(bitField1->bits, 0, get_bit(instruction.ujtype.imm, 9));
    bitField1->bits = set_bit(bitField1->bits, 1, get_bit(instruction.ujtype.imm, 10));
    bitField1->bits = set_bit(bitField1->bits, 2, get_bit(instruction.ujtype.imm, 11));
    bitField1->bits = set_bit(bitField1->bits, 3, get_bit(instruction.ujtype.imm, 12));
    bitField1->bits = set_bit(bitField1->bits, 4, get_bit(instruction.ujtype.imm, 13));
    bitField1->bits = set_bit(bitField1->bits, 5, get_bit(instruction.ujtype.imm, 14));
    bitField1->bits = set_bit(bitField1->bits, 6, get_bit(instruction.ujtype.imm, 15));
    bitField1->bits = set_bit(bitField1->bits, 7, get_bit(instruction.ujtype.imm, 16));
    bitField1->bits = set_bit(bitField1->bits, 8, get_bit(instruction.ujtype.imm, 17));
    bitField1->bits = set_bit(bitField1->bits, 9, get_bit(instruction.ujtype.imm, 18));
    bitField1->bits = set_bit(bitField1->bits, 10, get_bit(instruction.ujtype.imm, 8));
    bitField1->bits = set_bit(bitField1->bits, 11, get_bit(instruction.ujtype.imm, 0));
    bitField1->bits = set_bit(bitField1->bits, 12, get_bit(instruction.ujtype.imm, 1));
    bitField1->bits = set_bit(bitField1->bits, 13, get_bit(instruction.ujtype.imm, 2));
    bitField1->bits = set_bit(bitField1->bits, 14, get_bit(instruction.ujtype.imm, 3));
    bitField1->bits = set_bit(bitField1->bits, 15, get_bit(instruction.ujtype.imm, 4));
    bitField1->bits = set_bit(bitField1->bits, 16, get_bit(instruction.ujtype.imm, 5));
    bitField1->bits = set_bit(bitField1->bits, 17, get_bit(instruction.ujtype.imm, 6));
    bitField1->bits = set_bit(bitField1->bits, 18, get_bit(instruction.ujtype.imm, 7));
    bitField1->bits = set_bit(bitField1->bits, 19, get_bit(instruction.ujtype.imm, 19));
    return sign_extend_number((bitField1->bits) * 2, 21);
    }

int get_store_offset(Instruction instruction) {
    struct bit_field {
        unsigned int bits : 12;
    };
    struct bit_field *bitField2 = (struct bit_field *) malloc(sizeof(struct bit_field));
    bitField2->bits = set_bit(bitField2->bits, 0, get_bit(instruction.stype.imm5, 0));
    bitField2->bits = set_bit(bitField2->bits, 1, get_bit(instruction.stype.imm5, 1));
    bitField2->bits = set_bit(bitField2->bits, 2, get_bit(instruction.stype.imm5, 2));
    bitField2->bits = set_bit(bitField2->bits, 3, get_bit(instruction.stype.imm5, 3));
    bitField2->bits = set_bit(bitField2->bits, 4, get_bit(instruction.stype.imm5, 4));
    bitField2->bits = set_bit(bitField2->bits, 5, get_bit(instruction.stype.imm7, 0));
    bitField2->bits = set_bit(bitField2->bits, 6, get_bit(instruction.stype.imm7, 1));
    bitField2->bits = set_bit(bitField2->bits, 7, get_bit(instruction.stype.imm7, 2));
    bitField2->bits = set_bit(bitField2->bits, 8, get_bit(instruction.stype.imm7, 3));
    bitField2->bits = set_bit(bitField2->bits, 9, get_bit(instruction.stype.imm7, 4));
    bitField2->bits = set_bit(bitField2->bits, 10, get_bit(instruction.stype.imm7, 5));
    bitField2->bits = set_bit(bitField2->bits, 11, get_bit(instruction.stype.imm7, 6));
    return sign_extend_number((bitField2->bits), 12);
}

void handle_invalid_instruction(Instruction instruction) {
    printf("Invalid Instruction: 0x%08x\n", instruction.bits); 
}

void handle_invalid_read(Address address) {
    printf("Bad Read. Address: 0x%08x\n", address);
    exit(-1);
}

void handle_invalid_write(Address address) {
    printf("Bad Write. Address: 0x%08x\n", address);
    exit(-1);
}

