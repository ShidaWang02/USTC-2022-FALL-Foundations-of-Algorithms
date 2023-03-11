@import "D:\USR\vue.css"

# <center>ALG LAB6</center>


**<center>王世炟 PB20151796**</center>
**<center>2022/11/19</center>**

<center>Huffman 编码问题</center>

---

## 实验内容

编程实现 Huffman 编码问题，并理解其核心思想。

对文件 `original.txt` 中所有的大小写字母、数字（0-9）以及标点符号（即：除空格 换行
等之外的所有字符）按照 `Huffman` 编码方式编码为 01 序列，输出如下格式的 `table.txt` 文件,
并在控制台打印压缩率。

## 算法设计思路

首先，将所有的字符以及它们出现的频率存在结点中，并将这些结点放入优先队列，形成森林。

每一次将优先队列的前两个结点（频率最小的两个结点）出队，并合并成为一个新的结点，之后再将此结点加入优先队列，并维护优先队列的性质。

当优先队列中只剩下一个结点的时候，树便建立成功。

之后从根节点开始向下遍历，依次添加编码。

## 源码+注释

**结点结构：**

```c++
// Huffman树的节点类
typedef struct node
{
    char value;            //节点的字符值
    double freq;           //节点字符出现的频度
    vector<int> code;      //节点字符对应的编码
    node *lchild, *rchild; //节点的左右孩子
} HFMNode, *pHFMNode;
```

**优先队列比较方法：**

```c++
struct CMP
{
    bool operator()(const pHFMNode &p, const pHFMNode &q)
    {
        return p->freq > q->freq;
    }
};
```

**建立哈夫曼树：**

```c++
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
```

**输出编码：**

```c++
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
```


## 算法测试结果

可得到编码如下：

@import "table.txt"

**压缩率：** 0.641293