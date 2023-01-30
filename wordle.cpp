#include <set>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include<iomanip>
using namespace std;
// 此类读入并存储了候选词和可用词集合
// 调用此类的两个成员函数可以判断一个单词是否属于候选词/可用词集合
class WordSet {
public:

    // 在构造时，从文件读入候选集和可用集。
    // 你需要在代码中实例化一个 WordSet 类型变量。
    WordSet() {
        std::ifstream FINAL_FILE;
        FINAL_FILE.open("./FINAL.txt", std::ifstream::in);
        while (!FINAL_FILE.eof()) {
            std::string str;
            FINAL_FILE >> str;
            final_set.insert(str);
        }

        std::ifstream ACCEPTABLE_FILE;
        ACCEPTABLE_FILE.open("./ACC.txt", std::ifstream::in);
        while (!ACCEPTABLE_FILE.eof()) {
            std::string str;
            ACCEPTABLE_FILE >> str;
            acceptable_set.insert(str);
        }

    }

    // 判断输入参数 word 是否属于候选集合
    bool in_final_set(std::string word) {
        return final_set.find(word) != final_set.end();
    }

    // 判断输入参数 word 是否属于可用集合
    bool in_acceptable_set(std::string word) {
        return acceptable_set.find(word) != acceptable_set.end();
    }

private:
    std::set<std::string> final_set;
    std::set<std::string> acceptable_set;
};
//Word类，此类整合了每次输入单词对应的单词字符串、5个字母各自的颜色分布、字母表的颜色分布
class Word
{
private:



public:
    Word()
    {
        _word = "xxxxx";
        _result = "XXXXX";
        _alphabet = "XXXXXXXXXXXXXXXXXXXXXXXXXX";

    }
    Word(const string& word, const string& ACC, string alphabet)
    {
        setWord(word, ACC, alphabet);

    }
    //setWord函数，基于输入的单词和答案词来给5个字母各自的颜色分布(_result)赋值，同时再基于之前输入的所有单词给字母表的颜色分布(_alphabet)赋值
    void setWord(const string& word, const string& ACC, string alphabet)
    {

        _word = word;
        _result = "XXXXX";
        if (alphabet.size() != 26)
            _alphabet = "XXXXXXXXXXXXXXXXXXXXXXXXXX";
        else
            _alphabet = alphabet;
        //位置相同的字母颜色赋G
        for (int i = 0; i < 5; i++)
        {
            if (word[i] == ACC[i])
            {
                _result[i] = 'G';
            }
            
        }
        //未被赋G或Y（即初始X）且在答案词中出现的同种的第一个字母赋Y
        for (int i = 0; i < 5; i++)
        {
            if (_result[i] != 'G')
            {
                for (int j = 0; j < 5; j++)
                {
                    if (_result[j] =='X' && ACC[i] == word[j])
                    {
                        _result[j] = 'Y';
                        break;
                    }
                }
            }
        }
        //剩下的字母全部赋R
        for (int i = 0; i < 5; i++)
        {
            if (_result[i] =='X')
                _result[i] = 'R';
        }
        //基于五个字母的颜色分布为字母表分配颜色
        for (int i = 0; i < 5; i++)
        {
            
            switch (_alphabet[_word[i] - 'a'])
            {
            case 'X':
                if (_result[i] == 'R')
                    _alphabet[_word[i] - 'a'] = _result[i];
            case 'R':
                if (_result[i] == 'Y')
                    _alphabet[_word[i] - 'a'] = _result[i];
            case 'Y':
                if (_result[i] == 'G')
                    _alphabet[_word[i] - 'a'] = _result[i];
            case 'G':
                break;
            }

        }


    }
    //展示颜色分布结果函数
    void ShowResult()
    {
        cout << _result << " " << _alphabet << endl;

    }
    ~Word() {}

    string _word;//单词字符串
    string _result;//5个字母各自的颜色分布
    string _alphabet;//所有单词给字母表的颜色分布
};

//TODO：你可以添加类或者函数

//小写字符串转大写字符串函数
string transform(string lowcase)
{
    string uppercase="XXXXX";
    for (int i = 0; i < 5; i++)
    {
        uppercase[i] = lowcase[i]-'a'+'A';
    }
    return uppercase;
}

//TASK1部分对应代码
int task1()
{
    string ACC;//储存答案词
    getline(cin, ACC);
    string word;//储存输入的单词
    WordSet wordset;
    string temp;//暂时储存此次输入单词的字母表颜色分布
   //判断输入答案是否在所给词集合中
    if (wordset.in_final_set(ACC) == 0)
    {
        cout << "INVALID" << endl;
        return 0;
    }
    
    for (int i = 0; i < 6; i++)
    {

        getline(cin,word);
        //判断输入答案是否在可用词集合中
        if (wordset.in_acceptable_set(word) == 0)
        {
            cout << "INVALID" << endl;
            i--;
            continue;
        }
        Word test(word, ACC, temp);
        test.ShowResult();
        temp = test._alphabet;
        if (test._result == "GGGGG")
        {
            cout << "CORRECT" << " " << i + 1 << endl;
            break;
        }
        //六次有效输入完成后且未进入CORRECT判断，则进入FAIL判断
        if (i == 5)
            cout << "FAILED" << " " << transform(ACC) << endl;

    }

    return 0;

}
int task2()
{
    char choice = 'Y';//储存 是否进行游戏
    WordSet wordset;
    do
    {
        string ACC;
        string word;
        string temp;
        
        getline(cin, ACC);

        if (wordset.in_final_set(ACC) == 0)
            cout << "INVALID" << endl;
        else
        {
            for (int i = 0; i < 6; i++)
            {

                getline(cin, word);

                if (wordset.in_acceptable_set(word) == 0)
                {
                    cout << "INVALID" << endl;
                    i--;
                    continue;
                }
                Word test(word, ACC, temp);
                test.ShowResult();
                temp = test._alphabet;
                if (test._result == "GGGGG")
                {
                    cout << "CORRECT" << " " << i + 1 << endl;
                    break;
                }
                if (i == 5)
                    cout << "FAILED" << " " << transform(ACC) << endl;
            }
        }
        //结束后输入Y 或N来判断是否进入下一局游戏
        std::cin >> choice;
        cin.get();
    } while (choice == 'Y');
    
    return 0;


}
int task3()
{
    char choice = 'Y';
    WordSet wordset;
    do
    {
        vector<Word>wordstring;//储存每一次输入的单词对应的word类变量
        string ACC;
        string word;
        int times = 0;
        string temp;
        getline(cin, ACC);
        if (wordset.in_final_set(ACC) == 0)
        {
            cout << "INVALID" << endl;
        }
        else 
        {
            for (int i = 0; i < 6; i++)
            {

                getline(cin, word);
                if (wordset.in_acceptable_set(word) == 0)
                {
                    std::cout << "INVALID" << endl;
                    i--;
                    continue;
                }
                Word test(word, ACC, temp);

                bool judge = 0;//方便判断，后释

                //困难模式附加条件实现
                if (i > 0)
                {
                    vector<char>Yletter;
                    for (int k = 0; k < 5; k++)
                    {
                        //储存上一次输入中所有被标记为Y的字母
                        if (wordstring[times - 1]._result[k] == 'Y')
                        {
                            Yletter.push_back(wordstring[times - 1]._word[k]);
                        }
                    }
                    
                    for (int j = 0; j < 5; j++)
                    {
                        if (wordstring[times - 1]._result[j] == 'G')
                        {
                            //如果上一个单词中被标记为G的字母位置发生改变，则输出INVALID
                            if (test._result[j] != 'G')
                            {

                                cout << "INVALID" << endl;
                                i--;
                                judge = 1;
                                times--;
                                break;
                            }
                            
                        }           
                        else
                        {

                            vector<char>::iterator iter = find(Yletter.begin(), Yletter.end(), test._word[j]);
                            if (iter != Yletter.end())Yletter.erase(iter);

                        }
                    }
                    //judge==0表示通过“G检验”(上一注释处的检验），开始“Y检验”
                    //Y检验原理：将所有在上次输入中标记为Y的字母取出，将此次未被标记为G的字母与之一一比对，若发现存在上次被标记为Y的字母未被对应的，则输出INVALID
                    if (judge == 0)
                    {
                        
                        if (Yletter.size() != 0)
                        {

                            std::cout << "INVALID" << endl;
                            i--;
                            judge = 1;
                            times--;
                        }
                    }

                }
                if (judge == 0)
                {
                    wordstring.push_back(test);
                    temp = test._alphabet;
                    test.ShowResult();
                }
                times++;

                if (test._result == "GGGGG")
                {
                    std::cout << "CORRECT" << " " << times << endl;
                    break;
                }
                if (i == 5)
                    std::cout << "FAILED" << " " << transform(ACC) << endl;
            }
            
            
        } 
        std::cin >> choice;
        cin.get();
    } while (choice == 'Y');
    return 0;
}
int task4()
{
    int success = 0, total = 0,failure = 0;//成功次数，总次数，失败次数
    char choice = 'Y';
    WordSet wordset;
    vector<double>attempt;//成功局数
    do
    {
        vector<Word>wordstring;
        string ACC;
        string word;
        int times = 0;
        string temp;
        
        std::getline(cin, ACC);
        if (wordset.in_final_set(ACC) == 0)
        {
            cout << "INVALID" << endl;
            
        }
        else
        {
            for (int i = 0; i < 6; i++)
            {

                std::getline(cin, word);

                if (wordset.in_acceptable_set(word)== 0)
                {
                    std::cout << "INVALID" << endl;
                    i--;
                    continue;
                }
                Word test(word, ACC, temp);

                bool judge = 0;

                if (i > 0)
                {
                    vector<char>Yletter;
                    for (int k = 0; k < 5; k++)
                    {
                        if (wordstring[times - 1]._result[k] == 'Y')
                        {
                            Yletter.push_back(wordstring[times - 1]._word[k]);
                        }
                    }
                    for (int j = 0; j < 5; j++)
                    {
                        if (wordstring[times - 1]._result[j] == 'G')
                        {

                            if (test._result[j] != 'G')
                            {

                                std::cout << "INVALID" << endl;
                                i--;
                                judge = 1;
                                times--;
                                break;
                            }

                        }
                        else
                        {
                            vector<char>::iterator iter = find(Yletter.begin(), Yletter.end(), test._word[j]);
                            if (iter != Yletter.end())
                                Yletter.erase(iter);
                        }

                    }

                    if (judge == 0)
                    {

                        if (Yletter.size() != 0)
                        {

                            std::cout << "INVALID" << endl;
                            i--;
                            judge = 1;
                            times--;
                        }
                    }
                }
                if (judge == 0)
                {
                    wordstring.push_back(test);
                    temp = test._alphabet;
                    test.ShowResult();

                }
                times++;
                if (test._result == "GGGGG")
                {
                    std::cout << "CORRECT" << " " << times << endl;
                    success++;//成功次数加一
                    attempt.push_back(times);
                    break;
                }
                if (i == 5)
                {
                    std::cout << "FAILED" << " " << transform(ACC) << endl;
                    failure++;//失败次数加一
                }
            }
            total++;//总局数加一
            //成功次数为0的特殊情况的输出
            if (attempt.size() == 0)
                cout << success << " " << failure << " " << "0" << endl;
            else
            {
                double sum = 0;//总尝试次数
                for (int i = 0; i < attempt.size(); i++)
                {
                    sum += attempt[i];
                }
                double average = sum / attempt.size();//成功游戏平均尝试次数
                cout << success << " " << failure << " ";
                std::cout.setf(std::ios::fixed);
                std::cout.precision(2);
                cout << average << endl;

            }
        }

        std::cin >> choice;
        cin.get();
    } while (choice == 'Y');
    return 0;
}

int main() 
{    //TODO：程序从这里开始运行

    int task = 0;
    cin >> task;
    cin.get();
    switch(task)
    {
    case 1:
        task1();
        break;
    case 2:
        task2();
        break;
    case 3:
        task3();
        break;
    case 4:
        task4();
        break;
    }

}
