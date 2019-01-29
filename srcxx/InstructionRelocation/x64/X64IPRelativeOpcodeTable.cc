
#include "./X64IPRelativeOpcodeTable.h"

// clang-format on

static void _DecodeOp(InstrMnemonic *instr, addr_t p, OpcodeType OpTy) {
  instr->OpTy          = OpTy;
  instr->instr.opcode1 = *(byte *)p;
  instr->len++;
}

void _DecodeModM(InstrMnemonic *instr, addr_t p) {
  instr->instr.ModRM = *(byte *)p;
  instr->len++;
}

void _DecodeModRM(InstrMnemonic *instr, addr_t p) {
  instr->instr.ModRM = *(byte *)p;
  instr->len++;
}

void _DecodeSIB(InstrMnemonic *instr, addr_t p) {
  instr->instr.SIB = *(byte *)p;
  instr->len++;
}

void _DecodeImmedite(InstrMnemonic *instr, addr_t p) {
}

void _DecodeOpEn_RM(InstrMnemonic *instr, addr_t p) {
  _DecodeOp(instr, p, OpTy_Op1);
  _DecodeModRM(instr, p);
}

void _DecodeOpEn_I(InstrMnemonic *instr, addr_t p) {
  _DecodeOp(instr, p, OpTy_Op1);
  _DecodeImmedite(instr, p);
}

void _DecodeOpEn_OI(InstrMnemonic *instr, addr_t p) {
  _DecodeOp(instr, p, OpTy_RegInOp1);
  _DecodeImmedite(instr, p);
}

void _DecodeOpEn_RMI(InstrMnemonic *instr, addr_t p) {
  _DecodeOp(instr, p, OpTy_Op1);
  _DecodeModRM(instr, p);
  _DecodeImmedite(instr, p);
}

void _DecodeOpEn_MI(InstrMnemonic *instr, addr_t p) {
  _DecodeOp(instr, p, OpTy_Op1ExtraOp);
  _DecodeModM(instr, p);
  _DecodeImmedite(instr, p);
}

void _DecodeOpEn_M(InstrMnemonic *instr, addr_t p) {
}

#define _xUnknownOpHanlder 0, 0, 0, _UnknownOpHanlder
void _UnknownOpHanlder(InstrMnemonic *instr, addr_t p) {
}

#define _xInvalidOpHanlder 0, 0, 0, _InValidOpHanlder
void _InValidOpHanlder(InstrMnemonic *instr, addr_t p) {
}

#define _xDecodeOpEn_ZO 1, OpEn_ZO, 0, _DecodeOpEn_ZO
void _DecodeOpEn_ZO(InstrMnemonic *instr, addr_t p) {
  _DecodeOp(instr, p, OpTy_Op1);
}

#define _xDecodeOpEn_O 1, OpEn_O, 0, _DecodeOpEn_O
void _DecodeOpEn_O(InstrMnemonic *instr, addr_t p) {
  _DecodeOp(instr, p, OpTy_RegInOp1);
}

#define _xDecodePrefix_0F 1, 0, 0, _DecodePrefix
#define _xDecodePrefix_66 1, 0, 0, _DecodePrefix
#define _xDecodePrefix_67 1, 0, 0, _DecodePrefix
#define _xDecodeREXPrefix 1, 0, 0, _DecodePrefix
#define _xDecodePrefix 1, 0, 0, _DecodePrefix
#define _xDecodeSegPrefix 1, 0, 0, _DecodePrefix
void _DecodePrefix(InstrMnemonic *instr, addr_t p) {
  instr->instr.prefix = *(byte *)p;
  instr->len++;
}

void _DecodeOpEn_D(InstrMnemonic *instr, addr_t p) {
  _DecodeOp(instr, p, OpTy_Op1);
  _DecodeImmedite(instr, p);
}

void _DecodeOpEn_MR(InstrMnemonic *instr, addr_t p) {
}

#define _xDecodeOpC8 1, 0, 0, _DecodeOpC8
void _DecodeOpC8(InstrMnemonic *instr, addr_t p) {
  _DecodeOp(instr, p, OpTy_Op1);

  instr->len = instr->len + 2 + 1;
}

void _DecodeOpEn_M1(InstrMnemonic *instr, addr_t p) {
}

void _DecodeOpEn_MC(InstrMnemonic *instr, addr_t p) {
}

// http://ref.x86asm.net/coder.html#x04
OpcodeDecodeItem OpcodeDecodeTable[257] = {{0x00, 2, OpEn_MR, OpSz_8, &_DecodeOpEn_MR},
                                           {0x01, 2, OpEn_MR, OpSz_16or32, &_DecodeOpEn_MR},
                                           {0x02, 2, OpEn_RM, OpSz_8, &_DecodeOpEn_RM},
                                           {0x03, 2, OpEn_RM, OpSz_16or32, _DecodeOpEn_RM},
                                           {0x04, 1, OpEn_I, ImmSz_8, _DecodeOpEn_I},
                                           {0x05, 1, OpEn_I, ImmSz_16or32, _DecodeOpEn_I},
#ifdef DETOURS_X64
                                           {0x06, _xInvalidOpHanlder},
                                           {0x07, _xInvalidOpHanlder},
#else
                                           {0x06, _xDecodeOpEn_ZO},
                                           {0x07, _xDecodeOpEn_ZO},
#endif
                                           {0x08, 2, OpEn_MR, OpSz_8, _DecodeOpEn_MR},
                                           {0x09, 2, OpEn_MR, OpSz_16or32, _DecodeOpEn_MR},
                                           {0x0A, 2, OpEn_RM, OpSz_8, _DecodeOpEn_RM},
                                           {0x0B, 2, OpEn_RM, OpSz_16or32, _DecodeOpEn_RM},
                                           {0x0C, 1, OpEn_I, ImmSz_8, _DecodeOpEn_I},
                                           {0x0D, 1, OpEn_I, ImmSz_16or32, _DecodeOpEn_I},
#ifdef DETOURS_X64
                                           {0x0E, _xInvalidOpHanlder},
#else
                                           {0x0E, _xDecodeOpEn_ZO},
#endif
                                           {0x0F, _xDecodePrefix_0F},
                                           {0x10, 2, OpEn_MR, OpSz_8, _DecodeOpEn_MR},
                                           {0x11, 2, OpEn_MR, OpSz_16or32, _DecodeOpEn_MR},
                                           {0x12, 2, OpEn_RM, OpSz_8, _DecodeOpEn_RM},
                                           {0x13, 2, OpEn_RM, OpSz_16or32, _DecodeOpEn_RM},
                                           {0x14, 1, OpEn_I, ImmSz_8, _DecodeOpEn_I},
                                           {0x15, 1, OpEn_I, ImmSz_16or32, _DecodeOpEn_I},
#ifdef DETOURS_X64
                                           {0x16, _xInvalidOpHanlder},
                                           {0x17, _xInvalidOpHanlder},
#else
                                           {0x16, _xDecodeOpEn_ZO},
                                           {0x17, _xDecodeOpEn_ZO},
#endif
                                           {0x18, 2, OpEn_MR, OpSz_8, _DecodeOpEn_MR},
                                           {0x19, 2, OpEn_MR, OpSz_16or32, _DecodeOpEn_MR},
                                           {0x1A, 2, OpEn_RM, OpSz_8, _DecodeOpEn_RM},
                                           {0x1B, 2, OpEn_RM, OpSz_16or32, _DecodeOpEn_RM},
                                           {0x1C, 1, OpEn_I, ImmSz_8, _DecodeOpEn_I},
                                           {0x1D, 1, OpEn_I, ImmSz_16or32, _DecodeOpEn_I},
#ifdef DETOURS_X64
                                           {0x1E, _xInvalidOpHanlder},
                                           {0x1F, _xInvalidOpHanlder},
#else
                                           {0x1E, _xDecodeOpEn_ZO},
                                           {0x1F, _xDecodeOpEn_ZO},
#endif
                                           {0x20, 2, OpEn_MR, OpSz_8, _DecodeOpEn_MR},
                                           {0x21, 2, OpEn_MR, OpSz_16or32, _DecodeOpEn_MR},
                                           {0x22, 2, OpEn_RM, OpSz_8, _DecodeOpEn_RM},
                                           {0x23, 2, OpEn_RM, OpSz_16or32, _DecodeOpEn_RM},
                                           {0x24, 1, OpEn_I, ImmSz_8, _DecodeOpEn_I},
                                           {0x25, 1, OpEn_I, ImmSz_16or32, _DecodeOpEn_I},
                                           {0x26, _xDecodeSegPrefix},
#ifdef DETOURS_X64
                                           {0x27, _xInvalidOpHanlder},
#else
                                           {0x27, _xDecodeOpEn_ZO},
#endif
                                           {0x28, 2, OpEn_MR, OpSz_8, _DecodeOpEn_MR},
                                           {0x29, 2, OpEn_MR, OpSz_16or32, _DecodeOpEn_MR},
                                           {0x2A, 2, OpEn_RM, OpSz_8, _DecodeOpEn_RM},
                                           {0x2B, 2, OpEn_RM, OpSz_16or32, _DecodeOpEn_RM},
                                           {0x2C, 1, OpEn_I, ImmSz_8, _DecodeOpEn_I},
                                           {0x2D, 1, OpEn_I, ImmSz_16or32, _DecodeOpEn_I},
                                           {0x2E, _xDecodeSegPrefix},
#ifdef DETOURS_X64
                                           {0x2F, _xInvalidOpHanlder},
#else
                                           {0x2F, _xDecodeOpEn_ZO},
#endif
                                           {0x30, 2, OpEn_MR, OpSz_8, _DecodeOpEn_MR},
                                           {0x31, 2, OpEn_MR, OpSz_16or32, _DecodeOpEn_MR},
                                           {0x32, 2, OpEn_RM, OpSz_8, _DecodeOpEn_RM},
                                           {0x33, 2, OpEn_RM, OpSz_16or32, _DecodeOpEn_RM},
                                           {0x34, 1, OpEn_I, ImmSz_8, _DecodeOpEn_I},
                                           {0x35, 1, OpEn_I, ImmSz_16or32, _DecodeOpEn_I},
                                           {0x36, _xDecodeSegPrefix},
#ifdef DETOURS_X64
                                           {0x37, _xInvalidOpHanlder},
#else
                                           {0x37, _xDecodeOpEn_ZO},
#endif
                                           {0x38, 2, OpEn_MR, OpSz_8, _DecodeOpEn_MR},
                                           {0x39, 2, OpEn_MR, OpSz_16or32, _DecodeOpEn_MR},
                                           {0x3A, 2, OpEn_RM, OpSz_8, _DecodeOpEn_RM},
                                           {0x3B, 2, OpEn_RM, OpSz_16or32, _DecodeOpEn_RM},
                                           {0x3C, 1, OpEn_I, ImmSz_8, _DecodeOpEn_I},
                                           {0x3D, 1, OpEn_I, ImmSz_16or32, _DecodeOpEn_I},
                                           {0x3E, _xDecodeSegPrefix},
#ifdef DETOURS_X64
                                           {0x3F, _xInvalidOpHanlder},
#else
                                           {0x3F, _xDecodeOpEn_ZO},
#endif
#ifdef DETOURS_X64 // For REX Prefix
                                           {0x40, _xDecodeREXPrefix},
                                           {0x41, _xDecodeREXPrefix},
                                           {0x42, _xDecodeREXPrefix},
                                           {0x43, _xDecodeREXPrefix},
                                           {0x44, _xDecodeREXPrefix},
                                           {0x45, _xDecodeREXPrefix},
                                           {0x46, _xDecodeREXPrefix},
                                           {0x47, _xDecodeREXPrefix},
                                           {0x48, _xDecodeREXPrefix},
                                           {0x49, _xDecodeREXPrefix},
                                           {0x4A, _xDecodeREXPrefix},
                                           {0x4B, _xDecodeREXPrefix},
                                           {0x4C, _xDecodeREXPrefix},
                                           {0x4D, _xDecodeREXPrefix},
                                           {0x4E, _xDecodeREXPrefix},
                                           {0x4F, _xDecodeREXPrefix},
#else
                                           {0x40, _xDecodeOpEn_O},
                                           {0x41, _xInvalidOpHanlder},
                                           {0x42, _xInvalidOpHanlder},
                                           {0x43, _xInvalidOpHanlder},
                                           {0x44, _xInvalidOpHanlder},
                                           {0x45, _xInvalidOpHanlder},
                                           {0x46, _xInvalidOpHanlder},
                                           {0x47, _xInvalidOpHanlder},
                                           {0x48, _xDecodeOpEn_O},
                                           {0x49, _xInvalidOpHanlder},
                                           {0x4A, _xInvalidOpHanlder},
                                           {0x4B, _xInvalidOpHanlder},
                                           {0x4C, _xInvalidOpHanlder},
                                           {0x4D, _xInvalidOpHanlder},
                                           {0x4E, _xInvalidOpHanlder},
                                           {0x4F, _xInvalidOpHanlder},
#endif
                                           {0x50, _xDecodeOpEn_O},
                                           {0x51, _xInvalidOpHanlder},
                                           {0x52, _xInvalidOpHanlder},
                                           {0x53, _xInvalidOpHanlder},
                                           {0x54, _xInvalidOpHanlder},
                                           {0x55, _xInvalidOpHanlder},
                                           {0x56, _xInvalidOpHanlder},
                                           {0x57, _xInvalidOpHanlder},
                                           {0x58, _xDecodeOpEn_O},
                                           {0x59, _xInvalidOpHanlder},
                                           {0x5A, _xInvalidOpHanlder},
                                           {0x5B, _xInvalidOpHanlder},
                                           {0x5C, _xInvalidOpHanlder},
                                           {0x5D, _xInvalidOpHanlder},
                                           {0x5E, _xInvalidOpHanlder},
                                           {0x5F, _xInvalidOpHanlder},
#ifdef DETOURS_X64
                                           {0x60, _xInvalidOpHanlder},
                                           {0x61, _xInvalidOpHanlder},
                                           {0x62, _xInvalidOpHanlder},
#else
                                           {0x60, _xDecodeOpEn_ZO},
                                           {0x61, _xDecodeOpEn_ZO},
                                           {0x62, 2, OpEn_RM, OpSz_16or32, _DecodeOpEn_RM},
#endif
                                           {0x63, 2, OpEn_RM, OpSz_16or32, _DecodeOpEn_RM},
                                           {0x64, _xDecodeSegPrefix},
                                           {0x65, _xDecodeSegPrefix},
                                           {0x66, _xDecodePrefix_66},
                                           {0x67, _xDecodePrefix_67},
                                           {0x68, 1, OpEn_I, ImmSz_16or32, _DecodeOpEn_I},
                                           {0x69, 2, OpEn_RMI, OpSz_16or32 | ImmSz_16or32, _DecodeOpEn_RMI},
                                           {0x6A, 1, OpEn_I, ImmSz_8, _DecodeOpEn_I},
                                           {0x6B, 1, OpEn_RMI, OpSz_16or32 | ImmSz_8, _DecodeOpEn_RMI},
                                           {0x6C, _xDecodeOpEn_ZO},
                                           {0x6D, _xDecodeOpEn_ZO},
                                           {0x6E, _xDecodeOpEn_ZO},
                                           {0x6F, _xDecodeOpEn_ZO},
                                           {0x70, 1, OpEn_D, ImmSz_8, _DecodeOpEn_D},
                                           {0x71, 1, OpEn_D, ImmSz_8, _DecodeOpEn_D},
                                           {0x72, 1, OpEn_D, ImmSz_8, _DecodeOpEn_D},
                                           {0x73, 1, OpEn_D, ImmSz_8, _DecodeOpEn_D},
                                           {0x74, 1, OpEn_D, ImmSz_8, _DecodeOpEn_D},
                                           {0x75, 1, OpEn_D, ImmSz_8, _DecodeOpEn_D},
                                           {0x76, 1, OpEn_D, ImmSz_8, _DecodeOpEn_D},
                                           {0x77, 1, OpEn_D, ImmSz_8, _DecodeOpEn_D},
                                           {0x78, 1, OpEn_D, ImmSz_8, _DecodeOpEn_D},
                                           {0x79, 1, OpEn_D, ImmSz_8, _DecodeOpEn_D},
                                           {0x7A, 1, OpEn_D, ImmSz_8, _DecodeOpEn_D},
                                           {0x7B, 1, OpEn_D, ImmSz_8, _DecodeOpEn_D},
                                           {0x7C, 1, OpEn_D, ImmSz_8, _DecodeOpEn_D},
                                           {0x7D, 1, OpEn_D, ImmSz_8, _DecodeOpEn_D},
                                           {0x7E, 1, OpEn_D, ImmSz_8, _DecodeOpEn_D},
                                           {0x7F, 1, OpEn_D, ImmSz_8, _DecodeOpEn_D},
                                           {0x80, 2, OpEn_MI, OpSz_8 | ImmSz_8, _DecodeOpEn_MI},
                                           {0x81, 2, OpEn_MI, ImmSz_16or32, _DecodeOpEn_MI},
#ifdef DETOURS_X64
                                           {0x82, _xInvalidOpHanlder},
#else
                                           {0x82, _xUnknownOpHanlder},
#endif
                                           {0x83, 2, OpEn_MI, OpSz_16or32 | ImmSz_16or32, _DecodeOpEn_MI},
                                           {0x84, 2, OpEn_MR, OpSz_8, _DecodeOpEn_MR},
                                           {0x85, 2, OpEn_MR, OpSz_16or32, _DecodeOpEn_MR},
                                           {0x86, 2, OpEn_RM, OpSz_16or32, _DecodeOpEn_RM},
                                           {0x87, 2, OpEn_RM, OpSz_16or32, _DecodeOpEn_RM},
                                           {0x88, 2, OpEn_MR, OpSz_8, _DecodeOpEn_MR},
                                           {0x89, 2, OpEn_MR, OpSz_16or32, _DecodeOpEn_MR},
                                           {0x8A, 2, OpEn_RM, OpSz_16or32, _DecodeOpEn_RM},
                                           {0x8B, 2, OpEn_RM, OpSz_16or32, _DecodeOpEn_RM},
                                           {0x8C, 2, OpEn_MR, OpSz_16or32, _DecodeOpEn_MR},
                                           {0x8D, 2, OpEn_RM, OpSz_16or32, _DecodeOpEn_RM},
                                           {0x8E, 2, OpEn_RM, OpSz_16or32, _DecodeOpEn_RM},
                                           {0x8F, 2, OpEn_M, OpSz_16or32, _DecodeOpEn_M},
                                           {0x90, _xDecodeOpEn_ZO},
                                           {0x91, _xInvalidOpHanlder},
                                           {0x92, _xInvalidOpHanlder},
                                           {0x93, _xInvalidOpHanlder},
                                           {0x94, _xInvalidOpHanlder},
                                           {0x95, _xInvalidOpHanlder},
                                           {0x96, _xInvalidOpHanlder},
                                           {0x97, _xInvalidOpHanlder},
                                           {0x98, _xDecodeOpEn_ZO},
                                           {0x99, _xDecodeOpEn_ZO},
#ifdef DETOURS_X64
                                           {0x9A, _xInvalidOpHanlder},
#else
                                           {0x9A, _xDecodeOpEn_ZO},
#endif
                                           {0x9B, _xDecodeOpEn_ZO},
                                           {0x9C, _xDecodeOpEn_ZO},
                                           {0x9D, _xDecodeOpEn_ZO},
                                           {0x9E, _xDecodeOpEn_ZO},
                                           {0x9F, _xDecodeOpEn_ZO},
                                           {0xA0, _xUnknownOpHanlder},
                                           {0xA1, _xUnknownOpHanlder},
                                           {0xA2, _xUnknownOpHanlder},
                                           {0xA3, _xUnknownOpHanlder},
                                           {0xA4, _xDecodeOpEn_ZO},
                                           {0xA5, _xDecodeOpEn_ZO},
                                           {0xA6, _xDecodeOpEn_ZO},
                                           {0xA7, _xDecodeOpEn_ZO},
                                           {0xA8, 1, OpEn_I, ImmSz_8, _DecodeOpEn_I},
                                           {0xA9, 1, OpEn_I, ImmSz_16or32, _DecodeOpEn_I},
                                           {0xAA, _xDecodeOpEn_ZO},
                                           {0xAB, _xDecodeOpEn_ZO},
                                           {0xAC, _xDecodeOpEn_ZO},
                                           {0xAD, _xDecodeOpEn_ZO},
                                           {0xAE, _xDecodeOpEn_ZO},
                                           {0xAF, _xDecodeOpEn_ZO},
                                           {0xB0, 1, OpEn_OI, ImmSz_8, _DecodeOpEn_OI},
                                           {0xB1, _xInvalidOpHanlder},
                                           {0xB2, _xInvalidOpHanlder},
                                           {0xB3, _xInvalidOpHanlder},
                                           {0xB4, _xInvalidOpHanlder},
                                           {0xB5, _xInvalidOpHanlder},
                                           {0xB6, _xInvalidOpHanlder},
                                           {0xB7, _xInvalidOpHanlder},
                                           {0xB8, 1, OpEn_OI, ImmSz_16or32, _DecodeOpEn_OI},
                                           {0xB9, _xInvalidOpHanlder},
                                           {0xBA, _xInvalidOpHanlder},
                                           {0xBB, _xInvalidOpHanlder},
                                           {0xBC, _xInvalidOpHanlder},
                                           {0xBD, _xInvalidOpHanlder},
                                           {0xBE, _xInvalidOpHanlder},
                                           {0xBF, _xInvalidOpHanlder},
                                           {0xC0, 2, OpEn_MI, OpSz_8 | ImmSz_8, _DecodeOpEn_MI},
                                           {0xC1, 2, OpEn_MI, OpSz_16or32 | ImmSz_16or32, _DecodeOpEn_MI},
                                           {0xC2, 1, OpEn_I, ImmSz_16, _DecodeOpEn_I},
                                           {0xC3, _xDecodeOpEn_ZO},
                                           {0xC4, _xInvalidOpHanlder},
                                           {0xC5, _xInvalidOpHanlder},
                                           {0xC6, _xUnknownOpHanlder},
                                           {0xC7, 2, OpEn_MI, ImmSz_16or32, _DecodeOpEn_MI},
                                           {0xC8, _xDecodeOpC8},
                                           {0xC9, _xDecodeOpEn_ZO},
                                           {0xCA, 1, OpEn_I, ImmSz_16, _DecodeOpEn_I},
                                           {0xCB, _xDecodeOpEn_ZO},
                                           {0xCC, _xDecodeOpEn_ZO},
                                           {0xCD, 1, OpEn_I, ImmSz_8, _DecodeOpEn_I},
#ifdef DETOURS_X64
                                           {0xCE, _xInvalidOpHanlder},
#else
                                           {0xCE, _xDecodeOpEn_ZO},
#endif
                                           {0xCF, _xDecodeOpEn_ZO},
                                           {0xD0, 1, OpEn_M1, OpSz_8, _DecodeOpEn_M1},
                                           {0xD1, 1, OpEn_M1, OpSz_16or32, _DecodeOpEn_M1},
                                           {0xD2, 1, OpEn_MC, OpSz_8, _DecodeOpEn_MC},
                                           {0xD3, 1, OpEn_MC, OpSz_16or32, _DecodeOpEn_MC},
#ifdef DETOURS_X64
                                           {0xD4, _xInvalidOpHanlder},
                                           {0xD5, _xInvalidOpHanlder},
#else
                                           {0xD4, 1, OpEn_I, ImmSz_8, _DecodeOpEn_I},
                                           {0xD5, 1, OpEn_I, ImmSz_8, _DecodeOpEn_I},
#endif
                                           {0xD6, _xInvalidOpHanlder},
                                           {0xD7, _xDecodeOpEn_ZO},
                                           {0xD8, _xUnknownOpHanlder},
                                           {0xD9, _xUnknownOpHanlder},
                                           {0xDA, _xUnknownOpHanlder},
                                           {0xDB, _xUnknownOpHanlder},
                                           {0xDC, _xUnknownOpHanlder},
                                           {0xDD, _xUnknownOpHanlder},
                                           {0xDE, _xUnknownOpHanlder},
                                           {0xDF, _xUnknownOpHanlder},
                                           {0xE0, 1, OpEn_D, ImmSz_8, _DecodeOpEn_D},
                                           {0xE1, 1, OpEn_D, ImmSz_8, _DecodeOpEn_D},
                                           {0xE2, 1, OpEn_D, ImmSz_8, _DecodeOpEn_D},
                                           {0xE3, 1, OpEn_D, ImmSz_8, _DecodeOpEn_D},
                                           {0xE4, 1, OpEn_I, ImmSz_8, _DecodeOpEn_I},
                                           {0xE5, 1, OpEn_I, ImmSz_8, _DecodeOpEn_I},
                                           {0xE6, 1, OpEn_I, ImmSz_8, _DecodeOpEn_I},
                                           {0xE7, 1, OpEn_I, ImmSz_8, _DecodeOpEn_I},
                                           {0xE8, 1, OpEn_I, ImmSz_16or32, _DecodeOpEn_I},
                                           {0xE9, 1, OpEn_I, ImmSz_16or32, _DecodeOpEn_I},
#ifdef DETOURS_X64
                                           {0xEA, _xInvalidOpHanlder},
#else
                                           {0xEA, _xUnknownOpHanlder},
#endif
                                           {0xEB, 1, OpEn_I, ImmSz_8, _DecodeOpEn_I},
                                           {0xEC, _xDecodeOpEn_ZO},
                                           {0xED, _xDecodeOpEn_ZO},
                                           {0xEE, _xDecodeOpEn_ZO},
                                           {0xEF, _xDecodeOpEn_ZO},
                                           {0xF0, _xDecodePrefix},
                                           {0xF1, _xDecodeOpEn_ZO},
                                           {0xF2, _xDecodeOpEn_ZO},
#ifdef DETOURS_X86
                                           {0xF3, _CopyF3},
#else
                                           {0xF3, _xDecodeOpEn_ZO},
#endif
                                           {0xF4, _xDecodeOpEn_ZO},
                                           {0xF5, _xDecodeOpEn_ZO},
                                           {0xF6, 2, OpEn_MI, OpSz_8 | ImmSz_8, _DecodeOpEn_MI},
                                           {0xF7, 2, OpEn_MI, OpSz_16or32 | ImmSz_16or32, _DecodeOpEn_MI},
                                           {0xF8, _xDecodeOpEn_ZO},
                                           {0xF9, _xDecodeOpEn_ZO},
                                           {0xFA, _xDecodeOpEn_ZO},
                                           {0xFB, _xDecodeOpEn_ZO},
                                           {0xFC, _xDecodeOpEn_ZO},
                                           {0xFD, _xDecodeOpEn_ZO},
                                           {0xFE, 2, OpEn_M, OpSz_8, _DecodeOpEn_M},
                                           {0xFF, 2, OpEn_M, OpSz_16or32, _DecodeOpEn_M},
                                           {0, 0, 0, 0, 0}};
