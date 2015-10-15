#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstring>
#include <string>
#include <emscripten/bind.h>

using std::vector;
using namespace emscripten;



enum BillType {normal, icash, network, oil};

EMSCRIPTEN_BINDINGS(BillType) {
enum_<BillType>("BillType")
	.value("normal", normal)
	.value("icash", icash)
	.value("network", network)
	.value("oil", oil);
}
class Bill
{
    public:
        Bill(int p_year, int p_month, int p_day, int p_amount, enum BillType p_type, std::string p_comment)
            :m_year(p_year), m_month(p_month), m_day(p_day), m_amount(p_amount), m_type(p_type)
        {
        	m_comment = p_comment; 
        }


        int getAmount() { return m_amount; }
        enum BillType getType() { return m_type;}
        void info()
        {
            printf("year = %d, month = %d, day = %d, amount = %d, type = %d, comment = %s\n",
                    m_year, m_month, m_day, m_amount, m_type, m_comment.c_str());
        }
        int getYear() { return m_year; }
        int getMonth() { return m_month; }
        int getDay() { return m_day; }
        std::string getComment() { return m_comment; }
    private:
        int m_year;
        int m_month;
        int m_day;
        int m_amount;
        enum BillType m_type;
	    std::string m_comment;
};

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
}

class CreditCardBase
{
    public:
        CreditCardBase(std::string p_name, int p_dueDate)
            : m_dueDate(p_dueDate), m_commitDisCount(0)
        {
	    m_name = p_name;
        }
	CreditCardBase(std::string p_name)
	{
	    CreditCardBase(p_name, 1);
	}
        virtual ~CreditCardBase()
        {}

        virtual int getDisCount() {return 0;};

        void addPreAssignBill(Bill* b)
        {
            m_preAssignBillList.push_back(b);
        }

        void addAssignBill(Bill* b)
        {
            m_assignBillList.push_back(b);
        }

        void clearAssignBill()
        {
            m_assignBillList.clear();
        }

        int getDisCountForCommit() 
        {
            return m_commitDisCount;
        }
        void commitCurrentAssign()
        {
            m_bestAssignBillList.clear();
            for (size_t i = 0; i < m_preAssignBillList.size(); i++) {
                m_bestAssignBillList.push_back(m_preAssignBillList[i]);
            }
            for (size_t i = 0; i < m_assignBillList.size(); i++) {
                m_bestAssignBillList.push_back(m_assignBillList[i]);
            }
            m_commitDisCount = getDisCount();
        }

        void dumpBestAssign()
        {
            printf("credit card = %s\n", m_name.c_str());
            printf("disCount = %d\n", getDisCountForCommit());
            for (size_t i = 0; i < m_bestAssignBillList.size(); i++) {
                m_bestAssignBillList[i]->info();
            }
        }
        
        void getBestAssignBill(vector<Bill*>& billList)
        {
            billList.clear();
            for (size_t i = 0; i < m_bestAssignBillList.size(); i++) {
                billList.push_back(m_bestAssignBillList[i]);
            }
        }
    protected:

        void _getMergeList(vector<Bill*>& mergeList)
        {
            mergeList.clear();
            for (size_t i = 0; i < m_preAssignBillList.size(); i++) {
                mergeList.push_back(m_preAssignBillList[i]);
            }
            for (size_t i = 0; i < m_assignBillList.size(); i++) {
                mergeList.push_back(m_assignBillList[i]);
            }
        }

        int m_dueDate;
        int m_commitDisCount;
        
        vector<Bill*> m_preAssignBillList;
        vector<Bill*> m_assignBillList;
        vector<Bill*> m_bestAssignBillList;
	    std::string m_name;
};

class CreditCardHN : public CreditCardBase
{
    public:
	CreditCardHN(std::string p_name)
            : CreditCardBase(p_name, 1)
        {}
        int getDisCount() ;
};

int CreditCardHN::getDisCount() 
{
    vector<Bill*> tmpList;
    _getMergeList(tmpList);

    int normalSum = 0;
    const int cnt888 = 5;
    double sum888DisCount = 0;
    double list888[cnt888];
    int idx = 0;
    const int th = 12000;
    for (size_t i = 0; i < tmpList.size(); i++) {
        int val = tmpList[i]->getAmount();
        normalSum += val;
        // for special event
        const double maxEach = 100;
        const double maxTotal = 500;
        if (val >= 888 && val < th) {
            list888[idx] = val;
            idx++;
            if (idx == cnt888) {
                idx = 0;
                double n = 0;
                for (size_t j = 0; j < cnt888; j++) {
                    n += 0.007 * list888[j];
                    list888[j] = 0;
                }
                if (n > maxEach) {
                    n = maxEach;
                }
                sum888DisCount += n;
            }
            else {
                // check if subtotal > th
                double subtotal = 0;
                for (size_t j = 0; j < idx; j++) {
                    subtotal += list888[j];
                }
                double n = 0;
                if (subtotal >= th) {
                    n += 0.007 * subtotal;
                    if (n > maxEach) {
                        n = maxEach;
                    }
                    for (size_t j = 0; j < idx; j++) {
                        list888[j] = 0;
                    }
                    idx = 0;
                }
                sum888DisCount += n;
            }
        }
        else if (val >= th) {
            double n = 0.007 * val;
            if (n > maxEach) {
                n = maxEach;
            }
            sum888DisCount += n;
        }
    
        if (sum888DisCount > maxTotal) {
            sum888DisCount = maxTotal;
        }
    }
    
    double disCount = 0;
    disCount += sum888DisCount;
    disCount += 0.008 * normalSum;

    //   printf("disCount of hn = %g\n", disCount);

    return (int) disCount;
}
;

class CreditCardYS : public CreditCardBase
{
    public:
        CreditCardYS(std::string p_name)
            : CreditCardBase(p_name, 1)
        {}
        int getDisCount();
    protected:
        int _check699();
};
int CreditCardYS::_check699()
{
    vector<Bill*> tmpList;
    _getMergeList(tmpList);
    int cnt = 0;
    for (size_t i = 0; i < tmpList.size(); i++) {
        if (tmpList[i]->getAmount() >= 699 && tmpList[i]->getType() != icash) {
            cnt++;
        }
    }
    return cnt;
}

int CreditCardYS::getDisCount()
{
    vector<Bill*> tmpList;
    _getMergeList(tmpList);

    int cnt699 = _check699();
    double icashDisCount = 0;
    double netDisCount = 0;
    if (cnt699 >= 5) {
        for (size_t i = 0; i < tmpList.size(); i++) {
            if (tmpList[i]->getType() == icash) {
                icashDisCount += tmpList[i]->getAmount();
            }
            if (tmpList[i]->getType() == network) {
                netDisCount += tmpList[i]->getAmount();
            }
        }
        icashDisCount = 0.05 * icashDisCount;
        if (icashDisCount > 100) {
            icashDisCount = 100;
        }
        netDisCount = 0.05 * netDisCount;
        if (netDisCount > 300) {
            netDisCount = 300;
        }
    }

    double normalDisCount = 0;
    for (size_t i = 0; i < tmpList.size(); i++) {
        if (tmpList[i]->getType() == oil) {
            continue;
        }
        normalDisCount += tmpList[i]->getAmount();
    }
    normalDisCount = 0.007 * normalDisCount;
//        printf("disCount of ys= %g (normal = %g, icash = %g, net = %g)\n", 
//            normalDisCount + icashDisCount + netDisCount,
//            normalDisCount, icashDisCount, netDisCount);
    return (int) (normalDisCount + icashDisCount + netDisCount);
}


class CreditCardHNICash : public CreditCardBase
{
    public:
        CreditCardHNICash(std::string p_name)
            : CreditCardBase(p_name, 1)
        {}
        int getDisCount();
};

int CreditCardHNICash::getDisCount()
{
    vector<Bill*> tmpList;
    _getMergeList(tmpList);
    double sum = 0;
    for (size_t i = 0; i < tmpList.size(); i++) {
        if (tmpList[i]->getType() != network) {
            continue;
        }
        sum += tmpList[i]->getAmount();
    }
    
    return (int) (0.025 * sum);
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

class CreditCardMgr
{
    public:
        CreditCardMgr()
            : m_maxDisCount(0)
        {
            srand(0);
        }
        void addBill(Bill *b, CreditCardBase *card);
        void addCard(CreditCardBase *card);
        void assignCard();
	int  getMaxDisCount() {return m_maxDisCount;};
    private:
        vector<CreditCardBase*> m_creditCardList;
        vector<Bill*> m_billList;
        int m_maxDisCount;
};

EMSCRIPTEN_BINDINGS(CreditCardMgr) {
    class_<CreditCardMgr>("CreditCardMgr")
	.constructor()
	.function("addBill", &CreditCardMgr::addBill, allow_raw_pointers())
	.function("addCard", &CreditCardMgr::addCard, allow_raw_pointers())
	.function("assignCard", &CreditCardMgr::assignCard)
	.function("getMaxDisCount", &CreditCardMgr::getMaxDisCount);
};

void CreditCardMgr::addBill(Bill *b, CreditCardBase *card)
{
    if (card == NULL) {
        m_billList.push_back(b);
    }
    else {
        for (size_t i = 0; i < m_creditCardList.size(); i++) {
            if (m_creditCardList[i] == card) {
                m_creditCardList[i]->addPreAssignBill(b);
                return;
            }
        }

        assert(0);
    }
}

void CreditCardMgr::addCard(CreditCardBase *card)
{
    m_creditCardList.push_back(card);
}

void CreditCardMgr::assignCard()
{
    size_t maxIter = (size_t) (2 * pow(m_creditCardList.size(), m_billList.size()));
    //    printf("maxIter = %d (base = %d, exp = %d)\n", maxIter, m_creditCardList.size(), m_billList.size());

    for (size_t iter = 0; iter < maxIter ; iter++) {
        for (size_t i = 0; i < m_creditCardList.size(); i++) {
            m_creditCardList[i]->clearAssignBill();
        }
        for (size_t i = 0; i < m_billList.size(); i++) {

            int randIdx = rand() % m_creditCardList.size();
            m_creditCardList[randIdx]->addAssignBill(m_billList[i]);
        }
        int totalDisCount = 0;
        for (size_t i = 0; i < m_creditCardList.size(); i++) {
            totalDisCount += m_creditCardList[i]->getDisCount();
        }
        if (totalDisCount > m_maxDisCount) {
            m_maxDisCount = totalDisCount;
            for (size_t i = 0; i < m_creditCardList.size(); i++) {
                m_creditCardList[i]->commitCurrentAssign();
            }
        }
    }
    printf("max disCount = %d\n", m_maxDisCount);

    printf("==================================\n");
    for (size_t i = 0; i < m_creditCardList.size(); i++) {
        m_creditCardList[i]->dumpBestAssign();
        printf("==================================\n");
    }

}
//#include "glue.cpp"
// remove the main, let javascript do it!
#if 0
int main()
{
    CreditCardMgr cardMgr;
    
    CreditCardHN hnCard("hnCard");
//    CreditCardHNICash hnICashCard("hnICashCard");
    CreditCardYS ysCard("ys icash");

    cardMgr.addCard(&hnCard);
//    cardMgr.addCard(&hnICashCard);
    cardMgr.addCard(&ysCard);

    Bill a1(2015, 9, 20, 500, icash, "regular icash");
    Bill a2(2015, 9, 25, 1317, network, "pchome");
    Bill a3(2015, 9, 30, 528, normal, "baby1");
    Bill a4(2015, 9, 30, 853, normal, "baby2");
    Bill a5(2015, 9, 100, 1000, oil, "regular oil1");
    Bill a6(2015, 9, 100, 1000, oil, "regular oil2");
    Bill a7(2015, 9, 100, 1000, oil, "regular oil3");
    Bill a8(2015, 9, 100, 1000, oil, "regular oil4");
    Bill a9(2015, 9, 100, 1490, network, "baby3");
    Bill a0(2015, 9, 100, 25000, network, "iphone");

    cardMgr.addBill(&a1, &ysCard);
    cardMgr.addBill(&a2, &ysCard);
    cardMgr.addBill(&a3, &ysCard);
    cardMgr.addBill(&a4, &ysCard);
    cardMgr.addBill(&a5, NULL);
    cardMgr.addBill(&a6, NULL);
    cardMgr.addBill(&a7, NULL);
    cardMgr.addBill(&a8, NULL);
    cardMgr.addBill(&a9, NULL);
    cardMgr.addBill(&a0, NULL);

    cardMgr.assignCard();

    return 0;
}
#endif
