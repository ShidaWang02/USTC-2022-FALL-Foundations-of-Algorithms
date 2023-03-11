#include <bits/stdc++.h>

using namespace std;

double code_length = 0;

// Huffman树的节点类
typedef struct node
{
    char value;            //节点的字符值
    double freq;           //节点字符出现的频度
    vector<int> code;      //节点字符对应的编码
    node *lchild, *rchild; //节点的左右孩子
} HFMNode, *pHFMNode;

struct CMP
{
    bool operator()(const pHFMNode &p, const pHFMNode &q)
    {
        return p->freq > q->freq;
    }
};

void Huffman(priority_queue<pHFMNode, vector<pHFMNode>, CMP> &vctNode)
{
    while (vctNode.size() > 1)
    {
        pHFMNode first = vctNode.top(); //取vctNode森林中频度最小的树根
        vctNode.pop();
        pHFMNode second = vctNode.top(); //取vctNode森林中频度第二小的树根
        vctNode.pop();
        pHFMNode merge = new HFMNode; //合并上面两个树
        merge->freq = first->freq + second->freq;
        merge->lchild = first;  //小的放左子树
        merge->rchild = second; //大的放右子树
        vctNode.push(merge);    //向vctNode森林中添加合并后的merge树
    }
    return;
}

void PrintHuffman(pHFMNode node, vector<int> &vctCode, ofstream &outfile)
{
    if ((node->lchild == NULL) && (node->rchild == NULL))
    {
        node->code.assign(vctCode.begin(), vctCode.end()); //复制vctCode到code
        outfile << node->value << "    " << left << setw(8) << node->freq;
        for (vector<int>::iterator iter = node->code.begin(); iter != node->code.end(); iter++)
        {
            outfile << *iter;
        }
        outfile << endl;
        code_length += vctCode.size() * node->freq;
    }
    else
    {
        vctCode.push_back(0); //遇到左子树时给vctCode中加一个0
        PrintHuffman(node->lchild, vctCode, outfile);
        vctCode.pop_back();   //回溯，删除刚刚加进去的1
        vctCode.push_back(1); //遇到右子树时给vctCode中加一个1
        PrintHuffman(node->rchild, vctCode, outfile);
        vctCode.pop_back(); //回溯，删除刚刚加进去的0
    }
    return;
}

int main()
{
    priority_queue<pHFMNode, vector<pHFMNode>, CMP> vctNode; //存放Node结点的vector容器vctNode
    ifstream original("original.txt");
    // ifstream original("test.txt");
    stringstream buffer;
    buffer << original.rdbuf();
    string data(buffer.str());
    original.close();
    set<char> ss;
    int length = 0;
    for (int i = 0; i < (int)data.length(); i++)
    {
        if ((data[i] != ' ') && (data[i] != '\n'))
        {
            ss.insert(data[i]);
            length++;
        }
    }
    int count = 0; // 记录频度
    for (set<char>::iterator it = ss.begin(); it != ss.end(); it++)
    {
        count = 0;
        for (int i = 0; i < (int)data.length(); i++)
        {
            if (data[i] == *it)
            {
                count++;
            }
        }
        pHFMNode temp = new HFMNode;
        temp->value = *it;
        temp->lchild = temp->rchild = NULL;
        temp->freq = count;
        vctNode.push(temp); //将新的节点插入到优先队列vctNode中
        // cout << *it;
    }
    Huffman(vctNode);
    ofstream outfile("table.txt", ios_base::out);
    outfile << "字符 出现频率 编码" << endl;
    vector<int> vctCode;
    PrintHuffman(vctNode.top(), vctCode, outfile);
    outfile.close();
    cout << code_length / (((int)log2(ss.size()) + 1) * length) << endl;
    return 0;
}