#include "creditCardOpt.h"

int CreditCardHN::getDisCount() 
{
    vector<Bill*> tmpList;
    _getMergeList(tmpList);

    int normalSum = 0;
    const unsigned int cnt888 = 5;
    double sum888DisCount = 0;
    double list888[cnt888];
    int unsigned idx = 0;
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

static int g_iter = -1;


void CreditCardMgr::assignCard()
{
#if 0
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
            m_betterIterX.push_back(iter);
            m_betterIterY.push_back(totalDisCount);
            for (size_t i = 0; i < m_creditCardList.size(); i++) {
                m_creditCardList[i]->commitCurrentAssign();
            }
        }
    }
    m_betterIterX.push_back(maxIter);
    m_betterIterY.push_back(m_maxDisCount);

    printf("max disCount = %d\n", m_maxDisCount);

    printf("==================================\n");
    for (size_t i = 0; i < m_creditCardList.size(); i++) {
        m_creditCardList[i]->dumpBestAssign();
        printf("==================================\n");
    }
#else
    _assignCardKernel(0);

    printf("max disCount = %d\n", m_maxDisCount);

    printf("==================================\n");
    for (size_t i = 0; i < m_creditCardList.size(); i++) {
        m_creditCardList[i]->dumpBestAssign();
        printf("==================================\n");
    }

#endif
}



void CreditCardMgr::_assignCardKernel(size_t billIdx)
{
    g_iter++;

    if (billIdx >= m_billList.size()) {
        int totalDisCount = 0;
        for (size_t i = 0; i < m_creditCardList.size(); i++) {
            totalDisCount += m_creditCardList[i]->getDisCount();
        }
        
        if (totalDisCount > m_maxDisCount) {
            m_maxDisCount = totalDisCount;
            m_betterIterX.push_back(g_iter);
            m_betterIterY.push_back(totalDisCount);
            for (size_t i = 0; i < m_creditCardList.size(); i++) {
                m_creditCardList[i]->commitCurrentAssign();
            }
        }
    }
    else {
        for (size_t i = 0; i < m_creditCardList.size(); i++) {
            m_creditCardList[i]->addAssignBill(m_billList[billIdx]);
            _assignCardKernel(billIdx + 1);
            m_creditCardList[i]->popAssignBill();
        }
    }
}



// remove the main, let javascript do it!
#if _GPLUSPLUS_
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
