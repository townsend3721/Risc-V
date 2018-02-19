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
void set_bit(unsigned x,
             unsigned n,
             unsigned v) {
    int mask = ~(1 << n);
    x = x & mask;
    int vee = (v << n);
    x = x | vee;

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
    unsigned int return_val = 0;
    unsigned int list1[4] = {1,2,3,4};
    unsigned int i1;
    for (i1 = 0; i1 < 4; i1++) {
        unsigned int j = 0;
        set_bit( return_val, j, get_bit(instruction.sbtype.imm5,(unsigned) list1[i1]));
        j++;
    }
    int list2[6] = {0,1,2,3,4,5};
    int i2;
    for (i2 = 0; i2 < 6; i2++) {
        unsigned int j = 4;
        set_bit(return_val, j, get_bit(instruction.sbtype.imm7,(unsigned) list2[i2]));
        j++;
    }
    set_bit( return_val, 10, get_bit(instruction.sbtype.imm5, 0));
    set_bit( return_val, 11, get_bit(instruction.sbtype.imm7, 6));
    return sign_extend_number((return_val) * 2,13);
}
/* Returns the number of bytes (from the current PC) to the jump label using the given
 * jump instruction */
int get_jump_offset(Instruction instruction) {
    unsigned int return_val = 0;
    unsigned int list1[10] = {9,10,11,12,13,14,15,16,17,18};
    unsigned int list2 [8] = {0,1,2,3,4,5,6,7};
    int i1;
    for (i1 = 0; i1 < 10; i1++) {
        unsigned int j = 0;
        set_bit(return_val, j, get_bit(instruction.ujtype.imm, list1[i1]));
        j++;
    }
    set_bit(return_val, 10, get_bit(instruction.ujtype.imm, 8));
    int i2;
    for (i2 = 0; i2 < 8; i2++) {
        unsigned int j = 11;
        set_bit(return_val, j, get_bit(instruction.ujtype.imm,(unsigned) list2[i2]));
        j++;
    }
    set_bit(return_val, 19, get_bit(instruction.ujtype.imm, 19));
    return sign_extend_number(return_val * 2, 21);
    }

int get_store_offset(Instruction instruction) {
    unsigned int return_val = 0;
    unsigned int list1[5] = {0,1,2,3,4};
    unsigned int list2[7] = {0,1,2,3,4,5,6};
    int i1;
    for (i1 = 0; i1 < 5; i1++) {
        unsigned int j = 0;
        set_bit(return_val, j, get_bit(instruction.stype.imm5,(unsigned) list1[i1]));
        j++;
    }
    int i2;
    for (i2 = 0; i2 < 5; i2++) {
        unsigned int j = 5;
        set_bit(return_val, j, get_bit(instruction.stype.imm7,(unsigned) list2[i2]));
        j++;
    }
    return sign_extend_number(return_val, 12);
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

