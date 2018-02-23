#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "utils.h"
#include "types.h"
#include "part2.c"

void test_sign_extend_number();
void test_parse_instruction_rtype();
void test_parse_instruction_itype();
void test_parse_instruction_stype();
void test_parse_instruction_sbtype();
void test_parse_instruction_ujtype();
void test_parse_instruction_utype();
void test_load();
void test_store();

int main(int arc, char **argv) {
    CU_pSuite pSuite1 = NULL;

    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    } 

    pSuite1 = CU_add_suite("Testing sign_extend_number", NULL, NULL);
    if (!pSuite1) {
        goto exit;
    }
    if(!CU_add_test(pSuite1, "test_load", test_load)) {
        goto exit;
    }

    if(!CU_add_test(pSuite1, "test_store", test_store)) {
        goto exit;
    }
    if (!CU_add_test(pSuite1, "test_sign_extend_number", test_sign_extend_number)) {
        goto exit;
    }

    if (!CU_add_test(pSuite1, "test_parse_instruction_rtype", test_parse_instruction_rtype)) {
        goto exit;
    }

    if (!CU_add_test(pSuite1, "test_parse_instruction_itype", test_parse_instruction_itype)) {
        goto exit;
    }

    if (!CU_add_test(pSuite1, "test_parse_instruction_stype", test_parse_instruction_stype)) {
        goto exit;
    }

    if (!CU_add_test(pSuite1, "test_parse_instruction_sbtype", test_parse_instruction_sbtype)) {
        goto exit;
    }

    if (!CU_add_test(pSuite1, "test_parse_instruction_ujtype", test_parse_instruction_ujtype)) {
        goto exit;
    }

    if (!CU_add_test(pSuite1, "test_parse_instruction_utype", test_parse_instruction_utype)) {
        goto exit;
    }



    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    exit:
    CU_cleanup_registry();
    return CU_get_error();
}

void test_sign_extend_number() {
    CU_ASSERT_EQUAL(sign_extend_number(0xFF, 8), 0xFFFFFFFF);
    CU_ASSERT_EQUAL(sign_extend_number(0xFF, 9), 0xFF);
    CU_ASSERT_EQUAL(sign_extend_number(0x1234, 16), 0x1234);
    CU_ASSERT_EQUAL(sign_extend_number(0x1234, 13), 0xFFFFF234);
    CU_ASSERT_EQUAL(sign_extend_number(0x0,  1), 0);
    CU_ASSERT_EQUAL(sign_extend_number(0x1, 1), 0xFFFFFFFF);
}

void test_parse_instruction_rtype() {
    Instruction inst;
    inst = parse_instruction(0x009402b3);
    CU_ASSERT_EQUAL(inst.rtype.opcode, 0x33);
    CU_ASSERT_EQUAL(inst.rtype.funct3, 0x0);
    CU_ASSERT_EQUAL(inst.rtype.rd, 0x5);
    CU_ASSERT_EQUAL(inst.rtype.rs1, 0x8);
    CU_ASSERT_EQUAL(inst.rtype.rs2, 0x9);
    CU_ASSERT_EQUAL(inst.rtype.funct7, 0x0);
}

void test_parse_instruction_itype() {
    Instruction inst;
    inst = parse_instruction(0x00a50313);
    CU_ASSERT_EQUAL(inst.itype.opcode, 0x13);
    CU_ASSERT_EQUAL(inst.itype.funct3, 0x0);
    CU_ASSERT_EQUAL(inst.itype.rd, 0x6);
    CU_ASSERT_EQUAL(inst.itype.rs1, 10);
    CU_ASSERT_EQUAL(inst.itype.imm, 10);
}

void test_parse_instruction_stype() {
    Instruction inst;
    inst = parse_instruction(0x014aa023);
    CU_ASSERT_EQUAL(inst.stype.opcode, 0x23);
    CU_ASSERT_EQUAL(inst.stype.funct3, 0x2);
    CU_ASSERT_EQUAL(inst.stype.rs1, 21);
    CU_ASSERT_EQUAL(inst.stype.rs2, 20);
    CU_ASSERT_EQUAL(inst.stype.imm7, 0);
    CU_ASSERT_EQUAL(inst.stype.imm5, 0);
}

void test_parse_instruction_sbtype() {
    Instruction inst;
    inst = parse_instruction(0x00058063);
    CU_ASSERT_EQUAL(inst.sbtype.opcode, 0x63);
    CU_ASSERT_EQUAL(inst.sbtype.funct3, 0x0);
    CU_ASSERT_EQUAL(inst.sbtype.rs1, 11);
    CU_ASSERT_EQUAL(inst.sbtype.rs2, 0);
    CU_ASSERT_EQUAL(inst.sbtype.imm7, 0);
    CU_ASSERT_EQUAL(inst.sbtype.imm5, 0);
}

void test_parse_instruction_utype() {
    Instruction inst;
    inst = parse_instruction(0xFFFFF437);
    CU_ASSERT_EQUAL(inst.utype.opcode, 0x37);
    CU_ASSERT_EQUAL(inst.utype.rd, 8);
    CU_ASSERT_EQUAL(inst.utype.imm, 0xFFFFF);
}

void test_parse_instruction_ujtype() {
    Instruction inst;
    inst = parse_instruction(0x000000EF);
    CU_ASSERT_EQUAL(inst.ujtype.opcode, 0x6F);
    CU_ASSERT_EQUAL(inst.ujtype.rd, 1);
    CU_ASSERT_EQUAL(inst.ujtype.imm, 0);
}
void test_load() {
    Byte mem[] = {0x08, 0x09, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15};
/*
*		-----------------------------
*		| 0x15 | 0x14 | 0x13 | 0x12 |
*	Memory:	-----------------------------
*		| 0x11 | 0x10 | 0x09 | 0x08 |
*		-----------------------------
*/
    CU_ASSERT_EQUAL(load(mem, 4, LENGTH_WORD), 0x15141312);
    CU_ASSERT_EQUAL(load(mem, 4, LENGTH_HALF_WORD), 0x1312);
    CU_ASSERT_EQUAL(load(mem, 4, LENGTH_BYTE), 0x12);
    /*printf("\n|0x%x|\n", load(mem, 4, LENGTH_WORD));       // output: 0x15141312
    printf("|0x%x|\n", load(mem, 4, LENGTH_HALF_WORD));  // output: 0x1312
    printf("|0x%x|\n", load(mem, 4, LENGTH_BYTE));       // output: 0x12
     */
}

void test_store() {
    Byte mem[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    int i = 0;
    int sizeofmem = 8;
/* This is what we want the memory to look like!
*		-----------------------------
*		| 0x15 | 0x14 | 0x13 | 0x12 |
*	Memory:	-----------------------------
*		| 0x11 | 0x10 | 0x09 | 0x08 |
*		-----------------------------
*/
    store(mem, 4, LENGTH_WORD, (Word) 0x15141312);
    Byte refmem1[] = {0x00, 0x00, 0x00, 0x00, 0x12, 0x13, 0x14, 0x15};
    //fprintf(stderr, "\n||FIRST||\n");
    for (; i < sizeofmem; i++) {
        //fprintf(stderr, "|0x%x|0x%x|\n", mem[i], refmem1[i]);
        CU_ASSERT_EQUAL(mem[i], refmem1[i]);
    }
    //fprintf(stderr, "\n||SECOND||\n");
    store(mem, 2, LENGTH_HALF_WORD, (Word) 0x1110);
    Byte refmem2[] = {0x00, 0x00, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15};
    for (i = 0; i < sizeofmem; i++) {
        //fprintf(stderr, "|0x%x|0x%x|\n", mem[i], refmem2[i]);
        CU_ASSERT_EQUAL(mem[i], refmem2[i]);
    }
    //fprintf(stderr, "\n||THIRD||\n");
    store(mem, 1, LENGTH_BYTE, (Word) 0x09);
    store(mem, 0, LENGTH_BYTE, (Word) 0x08);
    Byte refmem3[] = {0x08, 0x09, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15};
    for (i = 0; i < sizeofmem; i++) {
        //fprintf(stderr, "|0x%x|0x%x|\n", mem[i], refmem3[i]);
        CU_ASSERT_EQUAL(mem[i], refmem3[i]);
    }
    /*printf("\n|0x%x|\n", load(mem, 4, LENGTH_WORD));       // output: 0x15141312
    printf("|0x%x|\n", load(mem, 4, LENGTH_HALF_WORD));  // output: 0x1312
    printf("|0x%x|\n", load(mem, 4, LENGTH_BYTE));       // output: 0x12
     */
}