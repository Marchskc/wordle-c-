//本人选择的提高部分为基于easyx图形库的GUI绘制
//此次提高部分基于综合性最高的Task4部分代码
//基础部分已经注释过的地方在提高部分注释中不再赘述

#include<iostream>
#include<graphics.h>
#include<easyx.h>
#include<vector>
#include<string>
#include <set>
#include <fstream>
using namespace std;
//枚举类定义部分重要size参数
enum Size
{
	WIDTH = 1000,
	HEIGHT = 800,
	_recwidth = 50,
	_recheigh  = 60,
	_sidelength = 80,
	_space = 6
};
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
		final_set_size = final_set.size();
	}

	// 判断输入参数 word 是否属于候选集合
	bool in_final_set(std::string word) {
		return final_set.find(word) != final_set.end();
	}

	// 判断输入参数 word 是否属于可用集合
	bool in_acceptable_set(std::string word) {
		return acceptable_set.find(word) != acceptable_set.end();
	}
	//获取final_set容器的size
	int Getfinal_set_size()
	{
		return final_set_size;
	}
	//获取final_set容器的第n个元素，实现随机答案的重要部分
	string Getfinal_set_word(int n)
	{
		set<string>::iterator it = final_set.begin();
		for (int i = 0; i < n; i++)
		{
			it++;
		}
		return *it;
	}
private:
	std::set<std::string> final_set;
	std::set<std::string> acceptable_set;
	int final_set_size;
};
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
	void setWord(const string& word, const string& ACC, string alphabet)
	{

		_word = word;
		_result = "XXXXX";
		if (alphabet.size() != 26)
			_alphabet = "XXXXXXXXXXXXXXXXXXXXXXXXXX";
		else
			_alphabet = alphabet;
		for (int i = 0; i < 5; i++)
		{
			if (word[i] == ACC[i])
			{
				_result[i] = 'G';
			}

		}
		for (int i = 0; i < 5; i++)
		{
			if (_result[i] != 'G')
			{
				for (int j = 0; j < 5; j++)
				{
					if (_result[j] == 'X' && ACC[i] == word[j])
					{
						_result[j] = 'Y';
						break;
					}
				}
			}
		}
		for (int i = 0; i < 5; i++)
		{
			if (_result[i] == 'X')
				_result[i] = 'R';
		}
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
	void ShowResult()
	{
		cout << _result << " " << _alphabet << endl;

	}
	~Word() {}

	string _word;
	string _result;
	string _alphabet;
};
//键盘区字母部分对应的类
class Key
{
public:
	Key(RECT &rec,string &alphabet,int order):_rec(rec)
	{
		_order = order;
		_color = alphabet[_order];
		_letter = 'A' + _order ;		
	}
	//基于Word类的alphabet更改键盘颜色
	void Changecolor(string& alphabet)
	{
		_color = alphabet[_order];
	}
	void Recovercolor()
	{
		_color = 'X';
	}
	//绘制键盘区字母键
	void Showkey()
	{
	
		switch (_color)
		{
		case 'X':
			setfillcolor(RGB(236, 239, 241));
			settextcolor(BLACK);
			break;
		case'R':
			setfillcolor(RGB(244, 67, 54));
			settextcolor(WHITE);
			break;
		case'Y':
			setfillcolor(RGB(255, 215, 64));
			settextcolor(WHITE);
			break;
		case'G':
			setfillcolor(RGB(139, 195, 74));
			settextcolor(WHITE);
			break;
		}
		setlinecolor(WHITE);
		fillroundrect(_rec.left, _rec.top, _rec.right, _rec.bottom, 10, 15);		
		settextstyle(_recheigh/2,0,"MS PGothic");
		setbkmode(1);
		outtextxy((_rec.left+_rec.right)/2-textwidth(_letter)/2, _rec.top + _recheigh / 4, _letter);
	}

private:
	RECT &_rec;
	char _color;
	char _letter;
	int _order;
};
//键盘区控制键类
class Ctrlkey
{
public:
	Ctrlkey(RECT &rec,string &str):_rec(rec),_ctrl(str){}
	//绘制控制键
	void Showkey()
	{
		LPCTSTR st = _ctrl.c_str();
		setfillcolor(RGB(236, 239, 241));
		fillroundrect(_rec.left, _rec.top, _rec.right, _rec.bottom, 10, 15);
		settextstyle(_recheigh / 2, 0, "MS PGothic");
		setbkmode(1);
		settextcolor(BLACK);
		outtextxy((_rec.left + _rec.right) / 2 - textwidth(st) / 2, _rec.top + _recheigh / 4, st);
	}
private:
	RECT& _rec;
	string _ctrl;
};
//输入显示键类
class Wordkey
{
public:
	Wordkey(RECT *rec, char letter,int order) :_rec(rec),_letter(letter),_order(order),_color('X') {}
	//基于Word类的_result改变颜色
	void Changecolor(string& result)
	{
		_color = result[_order];
	}
	//绘制输入显示键
	void Showkey()
	{
		switch (_color)
		{
		case 'X':
			setfillcolor(RGB(236, 239, 241));
			settextcolor(BLACK);
			break;
		case'R':
			setfillcolor(RGB(244, 67, 54));
			settextcolor(WHITE);
			break;
		case'Y':
			setfillcolor(RGB(255, 215, 64));
			settextcolor(WHITE);
			break;
		case'G':
			setfillcolor(RGB(139, 195, 74));
			settextcolor(WHITE);
			break;
		}
		fillrectangle(_rec->left, _rec->top, _rec->right, _rec->bottom);
		settextstyle(_sidelength / 2, 0, "MS PGothic");
		setbkmode(1);
		outtextxy((_rec->left + _rec->right) / 2 - textwidth(_letter) / 2, _rec->top + _sidelength / 4, _letter);
	}
private:
	RECT *_rec;
	char _color;
	char _letter;

	int _order;
};
//判断鼠标坐标是否在矩形内
bool if_inrec(RECT&rec,int x,int y)
{
	if (x >= rec.left && x <= rec.right && y >= rec.top && y <= rec.bottom)
		return TRUE;
	else
		return FALSE;
}
//获取鼠标信息
char Keymessage(vector<RECT>&vec)
{
	int arr[28] = { 17,23,5,18,20,25,21,9,15,16,1,19,4,6,7,8,10,11,12,26,24,3,22,2,14,13,27,28 };
	ExMessage mes;
	getmessage(&mes, EX_MOUSE);
	for (int i = 0; i < 28; i++)
	{
		if (mes.message == WM_LBUTTONDOWN && if_inrec(vec[i], mes.x, mes.y))
		{
			return arr[i] - 1 + 'A';			
		}
	}
	return 0;
}
//小写转大写
string Utransform(string lowcase)
{
	string uppercase = "XXXXX";
	for (int i = 0; i < 5; i++)
	{
		uppercase[i] = lowcase[i] - 'a' + 'A';
	}
	return uppercase;
}
//大写转小写
string Ltransform(string uppercase)
{
	string lowcase = "xxxxx";
	for (int i = 0; i < 5; i++)
	{
		lowcase[i] = uppercase[i] - 'A' + 'a';
	}
	return lowcase;
}
//绘制中间30个灰色方框
void Showhouse(vector<RECT>&rec)
{
	setlinecolor(RGB(236, 239, 241));
	for (int i = 0; i < 30; i++)
	{
		rectangle(rec[i].left, rec[i].top, rec[i].right, rec[i].bottom);
	}
}
//绘制键盘区，输入显示区
void Drawkey(vector<Key>&Keyboard,vector<Ctrlkey>&Two,vector<RECT>&house,vector<Wordkey>&keyhouse)
{

	for (int i = 0; i < 26; i++)
	{
		Keyboard[i].Showkey();
	}
	for (int i = 0; i < 2; i++)
	{
		Two[i].Showkey();
	}
	for (int i = 0; i < keyhouse.size(); i++)
	{
		keyhouse[i].Showkey();
	}
	Showhouse(house);
}
//当输入被判断为INVALID时，清除输入显示区
void Invalidclear(int i,vector<RECT>& house, vector<Wordkey>& keyhouse)
{
	while (keyhouse.size() > 5 * i)
	{
		keyhouse.pop_back();
	}
	BeginBatchDraw();
	for (int j = 0; j < 5; j++)
	{
		setfillcolor(WHITE);
		fillrectangle(house[5 * i + j].left, house[5 * i + j].top, house[5 * i + j].right, house[5 * i + j].bottom);
	}
	EndBatchDraw();
}
//自定义弹窗选项
HHOOK   hHook;
LRESULT  __stdcall  CBTHookProc(long  nCode, WPARAM  wParam, LPARAM   lParam)
{
	if (nCode == HCBT_ACTIVATE)
	{
		SetDlgItemText((HWND)wParam, IDYES, TEXT("再来"));//YSE改为再来
		SetDlgItemText((HWND)wParam, IDNO, TEXT("退出"));//NO改为退出
		SetDlgItemText((HWND)wParam, IDOK, TEXT("确认"));//OK改为确认
		SetDlgItemText((HWND)wParam, IDCANCEL, TEXT("取消"));//cancle改为取消 
		UnhookWindowsHookEx(hHook);
	}
	return  0;
}
//输入被判断为INVALID时，弹出提示窗口
void Invalidwarn1()
{
	HWND hnd = GetHWnd();
	hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc, NULL, GetCurrentThreadId());
	MessageBox(hnd, "输入不符合要求。        ", "INVALID", MB_OK);
}
void Invalidwarn2()
{
	HWND hnd = GetHWnd();
	hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc, NULL, GetCurrentThreadId());
	MessageBox(hnd, "你真没记几个单词？", "INVALID", MB_OK);
}
//失败时，弹出提示窗口
char Failurebox()
{
	HWND hnd = GetHWnd();
	hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc, NULL, GetCurrentThreadId());
	int result =MessageBox(hnd, "此局游戏失败。       ", "FAIL", MB_YESNO);
	if (result == IDYES)
		return 'Y';
	else if (result == IDNO)
		return 'N';
}
//成功时，弹出提示窗口
char Winbox()
{
	HWND hnd = GetHWnd();
	hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc, NULL, GetCurrentThreadId());
	int result = MessageBox(hnd, "恭喜你！此局游戏成功。 ", "WIN", MB_YESNO);
	if (result == IDYES)
		return 'Y';
	else if (result == IDNO)
		return 'N';
}
int main()
{

	initgraph(WIDTH, HEIGHT, SHOWCONSOLE);
	setbkcolor(WHITE);
	cleardevice();
	setfillcolor(BLACK);
	vector<RECT>place;
	vector<RECT>house;
	string tempalpha = "XXXXXXXXXXXXXXXXXXXXXXXXXX";

	//键盘区布局设计
	int arr[26] = { 17,23,5,18,20,25,21,9,15,16,1,19,4,6,7,8,10,11,12,26,24,3,22,2,14,13 };
	for (int i = 0; i < 10; i++)
	{
		RECT temprec;
		temprec.left = WIDTH / 2 - _space / 2 - _space * 4 - _recwidth * 5 + i * (_recwidth + _space);
		temprec.right = temprec.left + _recwidth;
		temprec.top = 580;
		temprec.bottom = temprec.top + _recheigh;
		place.push_back(temprec);
	}
	for (int i = 0; i < 9; i++)
	{
		RECT temprec;
		temprec.left = WIDTH / 2 - _space / 2 - _space * 4 - _recwidth * 5 + i * (_recwidth + _space) + _recwidth/2;
		temprec.right = temprec.left + _recwidth;
		temprec.top = 580+_recheigh+_space;
		temprec.bottom = temprec.top + _recheigh;
		place.push_back(temprec);
	}
	for (int i = 0; i < 7; i++)
	{
		RECT temprec;
		temprec.left = WIDTH / 2 - _space / 2 - _space * 3 - _recwidth * 4 + i * (_recwidth + _space) + _recwidth / 2;
		temprec.right = temprec.left + _recwidth;
		temprec.top = 580 + _recheigh*2 + 2*_space;
		temprec.bottom = temprec.top + _recheigh;
		place.push_back(temprec);
	}
	for (int i = 0; i < 2; i++)
	{
		RECT temprec;
		temprec.left = WIDTH / 2 - _space / 2 - _space * 4 - _recwidth * 6 + _recwidth / 2 + i * (_recwidth + _space) * 8 + i * _recwidth;
		temprec.right = temprec.left + 2*_recwidth;
		temprec.top = 580 + _recheigh * 2 + 2 * _space;
		temprec.bottom = temprec.top + _recheigh;
		place.push_back(temprec);
	}
	//输入显示区布局设计
	for (int j = 0; j < 6; j++)
	{
		for (int i = 0; i < 5; i++)
		{
			RECT temprec;
			temprec.left = WIDTH / 2 - _sidelength / 2 - _sidelength * 2 - _space * 2 + i * (_space + _sidelength);
			temprec.right = temprec.left + _sidelength;
			temprec.top = 30+j*(_space+_sidelength);
			temprec.bottom = temprec.top + _sidelength;
			house.push_back(temprec);
		}

	}
	//键盘区字母键和控制键类生成
	vector<Key>Keyboard;
	vector<Ctrlkey>Two;
	for (int i = 0; i < 26; i++)
	{
		Key tempk(place[i], tempalpha, arr[i]-1);
		Keyboard.push_back(tempk);
	}
	vector<string>tempstr;
	tempstr.push_back("ENTER");
	tempstr.push_back("BACK");
	for (int i = 0; i < 2; i++)
	{
		Ctrlkey tempck(place[26 + i], tempstr[i]);
		Two.push_back(tempck);
	}
	vector<Wordkey>keyhouse;
	
	int success = 0, total = 0, failure = 0;
	char choice = 'Y';
	WordSet wordset;
	vector<double>attempt;
	do
	{
		for (int i = 0; i < 26; i++)
		{
			Keyboard[i].Recovercolor();
		}
		keyhouse.clear();
		BeginBatchDraw();
		cleardevice();
		Drawkey(Keyboard, Two, house, keyhouse);
		EndBatchDraw();
		vector<Word>wordstring;
		string ACC;
		WordSet wordset;
		int times = 0;
		string temp;
		//基于时间种子随机生成答案
		srand((int)time(0));
		int Randomnum = rand() % wordset.Getfinal_set_size();
		ACC = wordset.Getfinal_set_word(Randomnum);
		cout << "此次基于时间种子生成的随机答案是：" << endl;
		cout << ACC << endl;
		if (wordset.in_final_set(ACC) == 0)
		{
			
			cout << "INVALID" << endl;
			return 0;
		}

		for (int i = 0; i < 6; i++)
		{
			string word;

			while (1)
			{
				string ts;
				char tc = Keymessage(place);//获取鼠标信息

				if (tc >= 'A' && tc <= 'A' + 25 && word.size() < 5)//获取点击字母区时返回的键值，同时生成输入显示键类元素
				{

					ts.push_back(tc - 'A' + 'a');
					word = word + ts;
					int order = static_cast<int>(word.size() - 1);
					Wordkey tempwk(&house[order + 5 * i], tc, order);
					keyhouse.push_back(tempwk);
					BeginBatchDraw();
					Drawkey(Keyboard, Two, house, keyhouse);
					EndBatchDraw();
				}
				else if (tc == 'A' + 26)//点击enter键时退出循环实现输入
				{
					break;
				}
				else if (tc == 'A' + 27 && word.size() >= 1)//点击back键时清除最近生成的元素
				{
					word.erase(word.end() - 1);
					keyhouse.erase(keyhouse.end() - 1);
					BeginBatchDraw();
					cleardevice();
					Drawkey(Keyboard, Two, house, keyhouse);
					EndBatchDraw();
				}


			}
			cout << "输入为" << endl;
			cout << word << endl;
			if (wordset.in_acceptable_set(word) == 0)
			{
				cout << "INVALID" << endl;
				Invalidwarn1();//INVALID,弹窗+清除输入显示区
				Invalidclear(i,house,keyhouse);
				word = "";
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
							Invalidwarn1();//INVALID,弹窗+清除输入显示区
							Invalidclear(i, house, keyhouse);
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
						Invalidwarn1();//INVALID,弹窗+清除输入显示区
						Invalidclear(i, house, keyhouse);
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
				for (int j = 0; j < 5; j++)//输入合法时，改变输入显示区键的颜色
				{
					keyhouse[5 * i + j].Changecolor(test._result);
				}

				for (int j = 0; j < 26; j++)//输入合法时，改变键盘区字母键的颜色
				{
					Keyboard[j].Changecolor(temp);
				}
			}
			times++;

			Drawkey(Keyboard, Two, house, keyhouse);
			if (test._result == "GGGGG")
			{
				std::cout << "CORRECT" << " " << times << endl;
				success++;
				attempt.push_back(times);
				choice = Winbox();//用弹窗选项为choice赋值
				break;
			}
			if (i == 5)
			{
				std::cout << "FAILED" << " " << Utransform(ACC) << endl;
				failure++;
				choice = Failurebox();//用弹窗选项为choice赋值
			}
			//
			

		}
		total++;
		if (attempt.size() == 0)
			cout << success << " " << failure << " " << "0" << endl;
		else
		{
			double sum = 0;
			for (int i = 0; i < attempt.size(); i++)
			{
				sum += attempt[i];
			}
			double average = sum / attempt.size();
			cout << success << " " << failure << " ";
			std::cout.setf(std::ios::fixed);
			std::cout.precision(2);
			cout << average << endl;
		}
		
	} while (choice == 'Y');
	closegraph();
}