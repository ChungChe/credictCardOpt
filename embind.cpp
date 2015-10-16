#include "creditCardOpt.h"
#include <emscripten/bind.h>
using namespace emscripten;

EMSCRIPTEN_BINDINGS(BillType) {
enum_<BillType>("BillType")
	.value("normal", normal)
	.value("icash", icash)
	.value("network", network)
	.value("oil", oil);
}

EMSCRIPTEN_BINDINGS(Bill) {
    class_<Bill>("Bill")
        .constructor<int, int, int, int, enum BillType, std::string>()
        .function("getAmount", &Bill::getAmount)
        .function("getType", &Bill::getType)
        .function("info", &Bill::info)
        .function("getYear", &Bill::getYear)
        .function("getMonth", &Bill::getMonth)
        .function("getDay", &Bill::getDay)
        .function("getComment", &Bill::getComment);
    register_vector<Bill*>("vectorBill");
    register_vector<int>("vectorInt");
}

EMSCRIPTEN_BINDINGS(CreditCardBase) {
    class_<CreditCardBase>("CreditCardBase")
	.constructor<std::string, int>()
	.function("getDiscount", &CreditCardBase::getDisCount, pure_virtual())
	.function("addPreAssignBill", &CreditCardBase::addPreAssignBill, allow_raw_pointers())
	.function("addAssignBill", &CreditCardBase::addAssignBill, allow_raw_pointers())
	.function("clearAssignBill", &CreditCardBase::clearAssignBill)
	.function("getDisCountForCommit", &CreditCardBase::getDisCountForCommit)
	.function("commitCurrentAssign", &CreditCardBase::commitCurrentAssign)
	.function("dumpBestAssign", &CreditCardBase::dumpBestAssign)
	.function("getBestAssignBill", &CreditCardBase::getBestAssignBill);
    class_<CreditCardHN, base<CreditCardBase>>("CreditCardHN")
	 .constructor<std::string>()
	 .function("getDisCount", &CreditCardHN::getDisCount);
    class_<CreditCardYS, base<CreditCardBase>>("CreditCardYS")
	 .constructor<std::string>()
	 .function("getDisCount", &CreditCardYS::getDisCount);
    class_<CreditCardHNICash, base<CreditCardBase>>("CreditCardHNICash")
	 .constructor<std::string>();
}

EMSCRIPTEN_BINDINGS(CreditCardMgr) {
    class_<CreditCardMgr>("CreditCardMgr")
	.constructor()
	.function("addBill", &CreditCardMgr::addBill, allow_raw_pointers())
	.function("addCard", &CreditCardMgr::addCard, allow_raw_pointers())
	.function("assignCard", &CreditCardMgr::assignCard)
	.function("getMaxDisCount", &CreditCardMgr::getMaxDisCount)
	.function("getChartX", &CreditCardMgr::getChartX)
	.function("getChartY", &CreditCardMgr::getChartY);
};
