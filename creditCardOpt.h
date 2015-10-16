#ifndef _CREDITCARDOPT_H_
#define _CREDITCARDOPT_H_
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstring>
#include <string>

using std::vector;

enum BillType {normal, icash, network, oil};

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

class CreditCardHNICash : public CreditCardBase
{
    public:
        CreditCardHNICash(std::string p_name)
            : CreditCardBase(p_name, 1)
        {}
        int getDisCount();
};

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

#endif
