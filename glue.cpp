
#include <emscripten.h>

extern "C" {

// Not using size_t for array indices as the values used by the javascript code are signed.
void array_bounds_check(const int array_size, const int array_idx) {
  if (array_idx < 0 || array_idx >= array_size) {
    EM_ASM_INT({
      throw 'Array index ' + $0 + ' out of bounds: [0,' + $1 + ')';
    }, array_idx, array_size);
  }
}

// CredictCardMgr

CredictCardMgr* EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardMgr_CredictCardMgr_0() {
  return new CredictCardMgr();
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardMgr_addBill_2(CredictCardMgr* self, Bill* arg0, CredictCardBase* arg1) {
  self->addBill(arg0, arg1);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardMgr_addCard_1(CredictCardMgr* self, CredictCardBase* arg0) {
  self->addCard(arg0);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardMgr_assignCard_0(CredictCardMgr* self) {
  self->assignCard();
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardMgr___destroy___0(CredictCardMgr* self) {
  delete self;
}

// Bill

Bill* EMSCRIPTEN_KEEPALIVE emscripten_bind_Bill_Bill_6(int arg0, int arg1, int arg2, int arg3, BillType arg4, char* arg5) {
  return new Bill(arg0, arg1, arg2, arg3, arg4, arg5);
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_Bill_getAmount_0(Bill* self) {
  return self->getAmount();
}

BillType EMSCRIPTEN_KEEPALIVE emscripten_bind_Bill_getType_0(Bill* self) {
  return self->getType();
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_Bill_info_0(Bill* self) {
  self->info();
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_Bill___destroy___0(Bill* self) {
  delete self;
}

// CredictCardBase

CredictCardBase* EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardBase_CredictCardBase_1(char* arg0) {
  return new CredictCardBase(arg0);
}

CredictCardBase* EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardBase_CredictCardBase_2(char* arg0, int arg1) {
  return new CredictCardBase(arg0, arg1);
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardBase_getDisCount_0(CredictCardBase* self) {
  return self->getDisCount();
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardBase_addPreAssignBill_1(CredictCardBase* self, Bill* arg0) {
  self->addPreAssignBill(arg0);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardBase_addAssignBill_1(CredictCardBase* self, Bill* arg0) {
  self->addAssignBill(arg0);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardBase_clearAssignBill_0(CredictCardBase* self) {
  self->clearAssignBill();
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardBase_getDisCountForCommit_0(CredictCardBase* self) {
  return self->getDisCountForCommit();
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardBase_commitCurrentAssign_0(CredictCardBase* self) {
  self->commitCurrentAssign();
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardBase_dumpBestAssign_0(CredictCardBase* self) {
  self->dumpBestAssign();
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardBase___destroy___0(CredictCardBase* self) {
  delete self;
}

// CredictCardYS

CredictCardYS* EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardYS_CredictCardYS_1(char* arg0) {
  return new CredictCardYS(arg0);
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardYS_getDisCount_0(CredictCardYS* self) {
  return self->getDisCount();
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardYS_addPreAssignBill_1(CredictCardYS* self, Bill* arg0) {
  self->addPreAssignBill(arg0);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardYS_addAssignBill_1(CredictCardYS* self, Bill* arg0) {
  self->addAssignBill(arg0);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardYS_clearAssignBill_0(CredictCardYS* self) {
  self->clearAssignBill();
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardYS_getDisCountForCommit_0(CredictCardYS* self) {
  return self->getDisCountForCommit();
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardYS_commitCurrentAssign_0(CredictCardYS* self) {
  self->commitCurrentAssign();
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardYS_dumpBestAssign_0(CredictCardYS* self) {
  self->dumpBestAssign();
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardYS___destroy___0(CredictCardYS* self) {
  delete self;
}

// CredictCardHNICash

CredictCardHNICash* EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardHNICash_CredictCardHNICash_1(char* arg0) {
  return new CredictCardHNICash(arg0);
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardHNICash_getDisCount_0(CredictCardHNICash* self) {
  return self->getDisCount();
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardHNICash_addPreAssignBill_1(CredictCardHNICash* self, Bill* arg0) {
  self->addPreAssignBill(arg0);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardHNICash_addAssignBill_1(CredictCardHNICash* self, Bill* arg0) {
  self->addAssignBill(arg0);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardHNICash_clearAssignBill_0(CredictCardHNICash* self) {
  self->clearAssignBill();
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardHNICash_getDisCountForCommit_0(CredictCardHNICash* self) {
  return self->getDisCountForCommit();
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardHNICash_commitCurrentAssign_0(CredictCardHNICash* self) {
  self->commitCurrentAssign();
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardHNICash_dumpBestAssign_0(CredictCardHNICash* self) {
  self->dumpBestAssign();
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardHNICash___destroy___0(CredictCardHNICash* self) {
  delete self;
}

// VoidPtr

void EMSCRIPTEN_KEEPALIVE emscripten_bind_VoidPtr___destroy___0(void** self) {
  delete self;
}

// CredictCardHN

CredictCardHN* EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardHN_CredictCardHN_1(char* arg0) {
  return new CredictCardHN(arg0);
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardHN_getDisCount_0(CredictCardHN* self) {
  return self->getDisCount();
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardHN_addPreAssignBill_1(CredictCardHN* self, Bill* arg0) {
  self->addPreAssignBill(arg0);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardHN_addAssignBill_1(CredictCardHN* self, Bill* arg0) {
  self->addAssignBill(arg0);
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardHN_clearAssignBill_0(CredictCardHN* self) {
  self->clearAssignBill();
}

int EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardHN_getDisCountForCommit_0(CredictCardHN* self) {
  return self->getDisCountForCommit();
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardHN_commitCurrentAssign_0(CredictCardHN* self) {
  self->commitCurrentAssign();
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardHN_dumpBestAssign_0(CredictCardHN* self) {
  self->dumpBestAssign();
}

void EMSCRIPTEN_KEEPALIVE emscripten_bind_CredictCardHN___destroy___0(CredictCardHN* self) {
  delete self;
}

// BillType
BillType EMSCRIPTEN_KEEPALIVE emscripten_enum_BillType_normal() {
  return normal;
}
BillType EMSCRIPTEN_KEEPALIVE emscripten_enum_BillType_icash() {
  return icash;
}
BillType EMSCRIPTEN_KEEPALIVE emscripten_enum_BillType_network() {
  return network;
}
BillType EMSCRIPTEN_KEEPALIVE emscripten_enum_BillType_oil() {
  return oil;
}

}

