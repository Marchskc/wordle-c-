#include <set>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include<iomanip>
using namespace std;
// ������벢�洢�˺�ѡ�ʺͿ��ôʼ���
// ���ô����������Ա���������ж�һ�������Ƿ����ں�ѡ��/���ôʼ���
class WordSet {
public:

    // �ڹ���ʱ�����ļ������ѡ���Ϳ��ü���
    // ����Ҫ�ڴ�����ʵ����һ�� WordSet ���ͱ�����
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

    // �ж�������� word �Ƿ����ں�ѡ����
    bool in_final_set(std::string word) {
        return final_set.find(word) != final_set.end();
    }

    // �ж�������� word �Ƿ����ڿ��ü���
    bool in_acceptable_set(std::string word) {
        return acceptable_set.find(word) != acceptable_set.end();
    }

private:
    std::set<std::string> final_set;
    std::set<std::string> acceptable_set;
};
//Word�࣬����������ÿ�����뵥�ʶ�Ӧ�ĵ����ַ�����5����ĸ���Ե���ɫ�ֲ�����ĸ�����ɫ�ֲ�
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
    //setWord��������������ĵ��ʺʹ𰸴�����5����ĸ���Ե���ɫ�ֲ�(_result)��ֵ��ͬʱ�ٻ���֮ǰ��������е��ʸ���ĸ�����ɫ�ֲ�(_alphabet)��ֵ
    void setWord(const string& word, const string& ACC, string alphabet)
    {

        _word = word;
        _result = "XXXXX";
        if (alphabet.size() != 26)
            _alphabet = "XXXXXXXXXXXXXXXXXXXXXXXXXX";
        else
            _alphabet = alphabet;
        //λ����ͬ����ĸ��ɫ��G
        for (int i = 0; i < 5; i++)
        {
            if (word[i] == ACC[i])
            {
                _result[i] = 'G';
            }
            
        }
        //δ����G��Y������ʼX�����ڴ𰸴��г��ֵ�ͬ�ֵĵ�һ����ĸ��Y
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
        //ʣ�µ���ĸȫ����R
        for (int i = 0; i < 5; i++)
        {
            if (_result[i] =='X')
                _result[i] = 'R';
        }
        //���������ĸ����ɫ�ֲ�Ϊ��ĸ�������ɫ
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
    //չʾ��ɫ�ֲ��������
    void ShowResult()
    {
        cout << _result << " " << _alphabet << endl;

    }
    ~Word() {}

    string _word;//�����ַ���
    string _result;//5����ĸ���Ե���ɫ�ֲ�
    string _alphabet;//���е��ʸ���ĸ�����ɫ�ֲ�
};

//TODO��������������ߺ���

//Сд�ַ���ת��д�ַ�������
string transform(string lowcase)
{
    string uppercase="XXXXX";
    for (int i = 0; i < 5; i++)
    {
        uppercase[i] = lowcase[i]-'a'+'A';
    }
    return uppercase;
}

//TASK1���ֶ�Ӧ����
int task1()
{
    string ACC;//����𰸴�
    getline(cin, ACC);
    string word;//��������ĵ���
    WordSet wordset;
    string temp;//��ʱ����˴����뵥�ʵ���ĸ����ɫ�ֲ�
   //�ж�������Ƿ��������ʼ�����
    if (wordset.in_final_set(ACC) == 0)
    {
        cout << "INVALID" << endl;
        return 0;
    }
    
    for (int i = 0; i < 6; i++)
    {

        getline(cin,word);
        //�ж�������Ƿ��ڿ��ôʼ�����
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
        //������Ч������ɺ���δ����CORRECT�жϣ������FAIL�ж�
        if (i == 5)
            cout << "FAILED" << " " << transform(ACC) << endl;

    }

    return 0;

}
int task2()
{
    char choice = 'Y';//���� �Ƿ������Ϸ
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
        //����������Y ��N���ж��Ƿ������һ����Ϸ
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
        vector<Word>wordstring;//����ÿһ������ĵ��ʶ�Ӧ��word�����
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

                bool judge = 0;//�����жϣ�����

                //����ģʽ��������ʵ��
                if (i > 0)
                {
                    vector<char>Yletter;
                    for (int k = 0; k < 5; k++)
                    {
                        //������һ�����������б����ΪY����ĸ
                        if (wordstring[times - 1]._result[k] == 'Y')
                        {
                            Yletter.push_back(wordstring[times - 1]._word[k]);
                        }
                    }
                    
                    for (int j = 0; j < 5; j++)
                    {
                        if (wordstring[times - 1]._result[j] == 'G')
                        {
                            //�����һ�������б����ΪG����ĸλ�÷����ı䣬�����INVALID
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
                    //judge==0��ʾͨ����G���顱(��һע�ʹ��ļ��飩����ʼ��Y���顱
                    //Y����ԭ�����������ϴ������б��ΪY����ĸȡ�������˴�δ�����ΪG����ĸ��֮һһ�ȶԣ������ִ����ϴα����ΪY����ĸδ����Ӧ�ģ������INVALID
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
    int success = 0, total = 0,failure = 0;//�ɹ��������ܴ�����ʧ�ܴ���
    char choice = 'Y';
    WordSet wordset;
    vector<double>attempt;//�ɹ�����
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
                    success++;//�ɹ�������һ
                    attempt.push_back(times);
                    break;
                }
                if (i == 5)
                {
                    std::cout << "FAILED" << " " << transform(ACC) << endl;
                    failure++;//ʧ�ܴ�����һ
                }
            }
            total++;//�ܾ�����һ
            //�ɹ�����Ϊ0��������������
            if (attempt.size() == 0)
                cout << success << " " << failure << " " << "0" << endl;
            else
            {
                double sum = 0;//�ܳ��Դ���
                for (int i = 0; i < attempt.size(); i++)
                {
                    sum += attempt[i];
                }
                double average = sum / attempt.size();//�ɹ���Ϸƽ�����Դ���
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
{    //TODO����������￪ʼ����

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
