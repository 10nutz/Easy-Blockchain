#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <string>

using namespace std;
class Transaction {
public:
    Transaction()
    {
        txSender = "";
        txRecipient = "";
        txQuantity = 0;
    }
    Transaction(string sender, string recipient, double quantity)
    {
        txSender = sender;
        txRecipient = recipient;
        txQuantity = quantity;
    }
    string getTxSender()
    {
        return txSender;
    }
    string getTxRecipient()
    {
        return txRecipient;
    }
    double getTxQuantity()
    {
        return txQuantity;
    }
private:
    string txSender;
    string txRecipient;
    double txQuantity;
};
class CryptoBlock {
public:
    CryptoBlock(int ix, string prevHash, string sender, string recipient, double quantity)
    {
        index = ix;
        previousBlockHash = prevHash;
        Transaction t(sender,recipient,quantity);
        tx = t;
        timeStamp = now();
        blockHash = calculateHash();
        
    }
    int getIndex()
    {
        return index;
    }
    string getTimeStamp()
    {
        return timeStamp;
    }
    string getPreviousBlockHash()
    {
        return previousBlockHash;
    }
    string getBlockHash()
    {
        return blockHash;
    }
    Transaction getTx()
    {
        return tx;
    }
private:
    string calculateHash()
    {
        hash<string> str_hash;
        return to_string(str_hash(timeStamp + previousBlockHash + getTx().getTxSender() + getTx().getTxRecipient() + to_string(getTx().getTxQuantity())));
    }
    string now() {
        time_t t = time(0);
        string str = ctime(&t);
        str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
        return str;
    }
    int index;
    string timeStamp;
    string previousBlockHash;
    string blockHash;
    Transaction tx;
};
class CryptoBlockchain {
public:
    CryptoBlockchain()
    {
        CryptoBlock genesis(0,"0","","",0);
        chain.push_back(genesis);
    }
    void addNewBlock(string sender, string recipient, double quantity)
    {
        CryptoBlock block(chain.back().getIndex() + 1, chain.back().getBlockHash(), sender, recipient, quantity);
        chain.push_back(block);
    }
    vector<CryptoBlock> getChain()
    {
        return chain;
    }
private:
    vector<CryptoBlock> chain;
    string getLastHash();
    int getLastIndex();
};
ostream& operator<<(ostream& o, CryptoBlock& b) {
    o << "{" << endl << "  BlockID:" << b.getIndex()<<"," << endl << "  Time_Stamp:" << b.getTimeStamp()<<"," << endl
      <<"  Previous_Block_Hash:"<<b.getPreviousBlockHash()<<","<<endl<<"  Block_Hash:"<<b.getBlockHash()<<","<<endl
      <<"  Sender:"<<b.getTx().getTxSender()<<","<<endl<<"  Recipient:"<<b.getTx().getTxRecipient()<<","<<endl
      <<"  Quantity:"<<b.getTx().getTxQuantity()<<endl<<"},"<<endl;
    return o;

}
ostream& operator<<(ostream& o, CryptoBlockchain& bc) {
    for (int i = 0; i < bc.getChain().size(); i++)
        o << bc.getChain()[i];
        return o;
    
}
int main()
{
    CryptoBlockchain myChain;
    myChain.addNewBlock("John", "Bob", 10);
    myChain.addNewBlock("Bob", "Sandra", 15.5);
    cout << myChain;
    return 0;
}
