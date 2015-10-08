
// Bindings utilities

function WrapperObject() {
}
WrapperObject.prototype = Object.create(WrapperObject.prototype);
WrapperObject.prototype.constructor = WrapperObject;
WrapperObject.prototype.__class__ = WrapperObject;
WrapperObject.__cache__ = {};
Module['WrapperObject'] = WrapperObject;

function getCache(__class__) {
  return (__class__ || WrapperObject).__cache__;
}
Module['getCache'] = getCache;

function wrapPointer(ptr, __class__) {
  var cache = getCache(__class__);
  var ret = cache[ptr];
  if (ret) return ret;
  ret = Object.create((__class__ || WrapperObject).prototype);
  ret.ptr = ptr;
  return cache[ptr] = ret;
}
Module['wrapPointer'] = wrapPointer;

function castObject(obj, __class__) {
  return wrapPointer(obj.ptr, __class__);
}
Module['castObject'] = castObject;

Module['NULL'] = wrapPointer(0);

function destroy(obj) {
  if (!obj['__destroy__']) throw 'Error: Cannot destroy object. (Did you create it yourself?)';
  obj['__destroy__']();
  // Remove from cache, so the object can be GC'd and refs added onto it released
  delete getCache(obj.__class__)[obj.ptr];
}
Module['destroy'] = destroy;

function compare(obj1, obj2) {
  return obj1.ptr === obj2.ptr;
}
Module['compare'] = compare;

function getPointer(obj) {
  return obj.ptr;
}
Module['getPointer'] = getPointer;

function getClass(obj) {
  return obj.__class__;
}
Module['getClass'] = getClass;

// Converts a value into a C-style string.
function ensureString(value) {
  if (typeof value == 'string') return allocate(intArrayFromString(value), 'i8', ALLOC_STACK);
  return value;
}


// CredictCardMgr
function CredictCardMgr() {
  this.ptr = _emscripten_bind_CredictCardMgr_CredictCardMgr_0();
  getCache(CredictCardMgr)[this.ptr] = this;
};;
CredictCardMgr.prototype = Object.create(WrapperObject.prototype);
CredictCardMgr.prototype.constructor = CredictCardMgr;
CredictCardMgr.prototype.__class__ = CredictCardMgr;
CredictCardMgr.__cache__ = {};
Module['CredictCardMgr'] = CredictCardMgr;

CredictCardMgr.prototype['addBill'] = CredictCardMgr.prototype.addBill = function(arg0, arg1) {
  var self = this.ptr;
  if (arg0 && typeof arg0 === 'object') arg0 = arg0.ptr;
  else arg0 = ensureString(arg0);
  if (arg1 && typeof arg1 === 'object') arg1 = arg1.ptr;
  else arg1 = ensureString(arg1);
  _emscripten_bind_CredictCardMgr_addBill_2(self, arg0, arg1);
};;

CredictCardMgr.prototype['addCard'] = CredictCardMgr.prototype.addCard = function(arg0) {
  var self = this.ptr;
  if (arg0 && typeof arg0 === 'object') arg0 = arg0.ptr;
  else arg0 = ensureString(arg0);
  _emscripten_bind_CredictCardMgr_addCard_1(self, arg0);
};;

CredictCardMgr.prototype['assignCard'] = CredictCardMgr.prototype.assignCard = function() {
  var self = this.ptr;
  _emscripten_bind_CredictCardMgr_assignCard_0(self);
};;

  CredictCardMgr.prototype['__destroy__'] = CredictCardMgr.prototype.__destroy__ = function() {
  var self = this.ptr;
  _emscripten_bind_CredictCardMgr___destroy___0(self);
};
// Bill
function Bill(arg0, arg1, arg2, arg3, arg4, arg5) {
  if (arg0 && typeof arg0 === 'object') arg0 = arg0.ptr;
  else arg0 = ensureString(arg0);
  if (arg1 && typeof arg1 === 'object') arg1 = arg1.ptr;
  else arg1 = ensureString(arg1);
  if (arg2 && typeof arg2 === 'object') arg2 = arg2.ptr;
  else arg2 = ensureString(arg2);
  if (arg3 && typeof arg3 === 'object') arg3 = arg3.ptr;
  else arg3 = ensureString(arg3);
  if (arg4 && typeof arg4 === 'object') arg4 = arg4.ptr;
  else arg4 = ensureString(arg4);
  if (arg5 && typeof arg5 === 'object') arg5 = arg5.ptr;
  else arg5 = ensureString(arg5);
  this.ptr = _emscripten_bind_Bill_Bill_6(arg0, arg1, arg2, arg3, arg4, arg5);
  getCache(Bill)[this.ptr] = this;
};;
Bill.prototype = Object.create(WrapperObject.prototype);
Bill.prototype.constructor = Bill;
Bill.prototype.__class__ = Bill;
Bill.__cache__ = {};
Module['Bill'] = Bill;

Bill.prototype['getAmount'] = Bill.prototype.getAmount = function() {
  var self = this.ptr;
  return _emscripten_bind_Bill_getAmount_0(self);
};;

Bill.prototype['getType'] = Bill.prototype.getType = function() {
  var self = this.ptr;
  return _emscripten_bind_Bill_getType_0(self);
};;

Bill.prototype['info'] = Bill.prototype.info = function() {
  var self = this.ptr;
  _emscripten_bind_Bill_info_0(self);
};;

  Bill.prototype['__destroy__'] = Bill.prototype.__destroy__ = function() {
  var self = this.ptr;
  _emscripten_bind_Bill___destroy___0(self);
};
// CredictCardBase
function CredictCardBase(arg0, arg1) {
  if (arg0 && typeof arg0 === 'object') arg0 = arg0.ptr;
  else arg0 = ensureString(arg0);
  if (arg1 && typeof arg1 === 'object') arg1 = arg1.ptr;
  else arg1 = ensureString(arg1);
  if (arg1 === undefined) { this.ptr = _emscripten_bind_CredictCardBase_CredictCardBase_1(arg0); getCache(CredictCardBase)[this.ptr] = this;return }
  this.ptr = _emscripten_bind_CredictCardBase_CredictCardBase_2(arg0, arg1);
  getCache(CredictCardBase)[this.ptr] = this;
};;
CredictCardBase.prototype = Object.create(Base.prototype);
CredictCardBase.prototype.constructor = CredictCardBase;
CredictCardBase.prototype.__class__ = CredictCardBase;
CredictCardBase.__cache__ = {};
Module['CredictCardBase'] = CredictCardBase;

CredictCardBase.prototype['getDisCount'] = CredictCardBase.prototype.getDisCount = function() {
  var self = this.ptr;
  return _emscripten_bind_CredictCardBase_getDisCount_0(self);
};;

CredictCardBase.prototype['addPreAssignBill'] = CredictCardBase.prototype.addPreAssignBill = function(arg0) {
  var self = this.ptr;
  if (arg0 && typeof arg0 === 'object') arg0 = arg0.ptr;
  else arg0 = ensureString(arg0);
  _emscripten_bind_CredictCardBase_addPreAssignBill_1(self, arg0);
};;

CredictCardBase.prototype['addAssignBill'] = CredictCardBase.prototype.addAssignBill = function(arg0) {
  var self = this.ptr;
  if (arg0 && typeof arg0 === 'object') arg0 = arg0.ptr;
  else arg0 = ensureString(arg0);
  _emscripten_bind_CredictCardBase_addAssignBill_1(self, arg0);
};;

CredictCardBase.prototype['clearAssignBill'] = CredictCardBase.prototype.clearAssignBill = function() {
  var self = this.ptr;
  _emscripten_bind_CredictCardBase_clearAssignBill_0(self);
};;

CredictCardBase.prototype['getDisCountForCommit'] = CredictCardBase.prototype.getDisCountForCommit = function() {
  var self = this.ptr;
  return _emscripten_bind_CredictCardBase_getDisCountForCommit_0(self);
};;

CredictCardBase.prototype['commitCurrentAssign'] = CredictCardBase.prototype.commitCurrentAssign = function() {
  var self = this.ptr;
  _emscripten_bind_CredictCardBase_commitCurrentAssign_0(self);
};;

CredictCardBase.prototype['dumpBestAssign'] = CredictCardBase.prototype.dumpBestAssign = function() {
  var self = this.ptr;
  _emscripten_bind_CredictCardBase_dumpBestAssign_0(self);
};;

  CredictCardBase.prototype['__destroy__'] = CredictCardBase.prototype.__destroy__ = function() {
  var self = this.ptr;
  _emscripten_bind_CredictCardBase___destroy___0(self);
};
// CredictCardYS
function CredictCardYS(arg0) {
  if (arg0 && typeof arg0 === 'object') arg0 = arg0.ptr;
  else arg0 = ensureString(arg0);
  this.ptr = _emscripten_bind_CredictCardYS_CredictCardYS_1(arg0);
  getCache(CredictCardYS)[this.ptr] = this;
};;
CredictCardYS.prototype = Object.create(CredictCardBase.prototype);
CredictCardYS.prototype.constructor = CredictCardYS;
CredictCardYS.prototype.__class__ = CredictCardYS;
CredictCardYS.__cache__ = {};
Module['CredictCardYS'] = CredictCardYS;

CredictCardYS.prototype['getDisCount'] = CredictCardYS.prototype.getDisCount = function() {
  var self = this.ptr;
  return _emscripten_bind_CredictCardYS_getDisCount_0(self);
};;

CredictCardYS.prototype['addPreAssignBill'] = CredictCardYS.prototype.addPreAssignBill = function(arg0) {
  var self = this.ptr;
  if (arg0 && typeof arg0 === 'object') arg0 = arg0.ptr;
  else arg0 = ensureString(arg0);
  _emscripten_bind_CredictCardYS_addPreAssignBill_1(self, arg0);
};;

CredictCardYS.prototype['addAssignBill'] = CredictCardYS.prototype.addAssignBill = function(arg0) {
  var self = this.ptr;
  if (arg0 && typeof arg0 === 'object') arg0 = arg0.ptr;
  else arg0 = ensureString(arg0);
  _emscripten_bind_CredictCardYS_addAssignBill_1(self, arg0);
};;

CredictCardYS.prototype['clearAssignBill'] = CredictCardYS.prototype.clearAssignBill = function() {
  var self = this.ptr;
  _emscripten_bind_CredictCardYS_clearAssignBill_0(self);
};;

CredictCardYS.prototype['getDisCountForCommit'] = CredictCardYS.prototype.getDisCountForCommit = function() {
  var self = this.ptr;
  return _emscripten_bind_CredictCardYS_getDisCountForCommit_0(self);
};;

CredictCardYS.prototype['commitCurrentAssign'] = CredictCardYS.prototype.commitCurrentAssign = function() {
  var self = this.ptr;
  _emscripten_bind_CredictCardYS_commitCurrentAssign_0(self);
};;

CredictCardYS.prototype['dumpBestAssign'] = CredictCardYS.prototype.dumpBestAssign = function() {
  var self = this.ptr;
  _emscripten_bind_CredictCardYS_dumpBestAssign_0(self);
};;

  CredictCardYS.prototype['__destroy__'] = CredictCardYS.prototype.__destroy__ = function() {
  var self = this.ptr;
  _emscripten_bind_CredictCardYS___destroy___0(self);
};
// CredictCardHNICash
function CredictCardHNICash(arg0) {
  if (arg0 && typeof arg0 === 'object') arg0 = arg0.ptr;
  else arg0 = ensureString(arg0);
  this.ptr = _emscripten_bind_CredictCardHNICash_CredictCardHNICash_1(arg0);
  getCache(CredictCardHNICash)[this.ptr] = this;
};;
CredictCardHNICash.prototype = Object.create(CredictCardBase.prototype);
CredictCardHNICash.prototype.constructor = CredictCardHNICash;
CredictCardHNICash.prototype.__class__ = CredictCardHNICash;
CredictCardHNICash.__cache__ = {};
Module['CredictCardHNICash'] = CredictCardHNICash;

CredictCardHNICash.prototype['getDisCount'] = CredictCardHNICash.prototype.getDisCount = function() {
  var self = this.ptr;
  return _emscripten_bind_CredictCardHNICash_getDisCount_0(self);
};;

CredictCardHNICash.prototype['addPreAssignBill'] = CredictCardHNICash.prototype.addPreAssignBill = function(arg0) {
  var self = this.ptr;
  if (arg0 && typeof arg0 === 'object') arg0 = arg0.ptr;
  else arg0 = ensureString(arg0);
  _emscripten_bind_CredictCardHNICash_addPreAssignBill_1(self, arg0);
};;

CredictCardHNICash.prototype['addAssignBill'] = CredictCardHNICash.prototype.addAssignBill = function(arg0) {
  var self = this.ptr;
  if (arg0 && typeof arg0 === 'object') arg0 = arg0.ptr;
  else arg0 = ensureString(arg0);
  _emscripten_bind_CredictCardHNICash_addAssignBill_1(self, arg0);
};;

CredictCardHNICash.prototype['clearAssignBill'] = CredictCardHNICash.prototype.clearAssignBill = function() {
  var self = this.ptr;
  _emscripten_bind_CredictCardHNICash_clearAssignBill_0(self);
};;

CredictCardHNICash.prototype['getDisCountForCommit'] = CredictCardHNICash.prototype.getDisCountForCommit = function() {
  var self = this.ptr;
  return _emscripten_bind_CredictCardHNICash_getDisCountForCommit_0(self);
};;

CredictCardHNICash.prototype['commitCurrentAssign'] = CredictCardHNICash.prototype.commitCurrentAssign = function() {
  var self = this.ptr;
  _emscripten_bind_CredictCardHNICash_commitCurrentAssign_0(self);
};;

CredictCardHNICash.prototype['dumpBestAssign'] = CredictCardHNICash.prototype.dumpBestAssign = function() {
  var self = this.ptr;
  _emscripten_bind_CredictCardHNICash_dumpBestAssign_0(self);
};;

  CredictCardHNICash.prototype['__destroy__'] = CredictCardHNICash.prototype.__destroy__ = function() {
  var self = this.ptr;
  _emscripten_bind_CredictCardHNICash___destroy___0(self);
};
// VoidPtr
function VoidPtr() { throw "cannot construct a VoidPtr, no constructor in IDL" }
VoidPtr.prototype = Object.create(WrapperObject.prototype);
VoidPtr.prototype.constructor = VoidPtr;
VoidPtr.prototype.__class__ = VoidPtr;
VoidPtr.__cache__ = {};
Module['VoidPtr'] = VoidPtr;

  VoidPtr.prototype['__destroy__'] = VoidPtr.prototype.__destroy__ = function() {
  var self = this.ptr;
  _emscripten_bind_VoidPtr___destroy___0(self);
};
// CredictCardHN
function CredictCardHN(arg0) {
  if (arg0 && typeof arg0 === 'object') arg0 = arg0.ptr;
  else arg0 = ensureString(arg0);
  this.ptr = _emscripten_bind_CredictCardHN_CredictCardHN_1(arg0);
  getCache(CredictCardHN)[this.ptr] = this;
};;
CredictCardHN.prototype = Object.create(CredictCardBase.prototype);
CredictCardHN.prototype.constructor = CredictCardHN;
CredictCardHN.prototype.__class__ = CredictCardHN;
CredictCardHN.__cache__ = {};
Module['CredictCardHN'] = CredictCardHN;

CredictCardHN.prototype['getDisCount'] = CredictCardHN.prototype.getDisCount = function() {
  var self = this.ptr;
  return _emscripten_bind_CredictCardHN_getDisCount_0(self);
};;

CredictCardHN.prototype['addPreAssignBill'] = CredictCardHN.prototype.addPreAssignBill = function(arg0) {
  var self = this.ptr;
  if (arg0 && typeof arg0 === 'object') arg0 = arg0.ptr;
  else arg0 = ensureString(arg0);
  _emscripten_bind_CredictCardHN_addPreAssignBill_1(self, arg0);
};;

CredictCardHN.prototype['addAssignBill'] = CredictCardHN.prototype.addAssignBill = function(arg0) {
  var self = this.ptr;
  if (arg0 && typeof arg0 === 'object') arg0 = arg0.ptr;
  else arg0 = ensureString(arg0);
  _emscripten_bind_CredictCardHN_addAssignBill_1(self, arg0);
};;

CredictCardHN.prototype['clearAssignBill'] = CredictCardHN.prototype.clearAssignBill = function() {
  var self = this.ptr;
  _emscripten_bind_CredictCardHN_clearAssignBill_0(self);
};;

CredictCardHN.prototype['getDisCountForCommit'] = CredictCardHN.prototype.getDisCountForCommit = function() {
  var self = this.ptr;
  return _emscripten_bind_CredictCardHN_getDisCountForCommit_0(self);
};;

CredictCardHN.prototype['commitCurrentAssign'] = CredictCardHN.prototype.commitCurrentAssign = function() {
  var self = this.ptr;
  _emscripten_bind_CredictCardHN_commitCurrentAssign_0(self);
};;

CredictCardHN.prototype['dumpBestAssign'] = CredictCardHN.prototype.dumpBestAssign = function() {
  var self = this.ptr;
  _emscripten_bind_CredictCardHN_dumpBestAssign_0(self);
};;

  CredictCardHN.prototype['__destroy__'] = CredictCardHN.prototype.__destroy__ = function() {
  var self = this.ptr;
  _emscripten_bind_CredictCardHN___destroy___0(self);
};
(function() {
  function setupEnums() {
    

    // BillType

    Module['normal'] = _emscripten_enum_BillType_normal();

    Module['icash'] = _emscripten_enum_BillType_icash();

    Module['network'] = _emscripten_enum_BillType_network();

    Module['oil'] = _emscripten_enum_BillType_oil();

  }
  if (Module['calledRun']) setupEnums();
  else addOnPreMain(setupEnums);
})();
