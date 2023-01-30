//����ѡ�����߲���Ϊ����easyxͼ�ο��GUI����
//�˴���߲��ֻ����ۺ�����ߵ�Task4���ִ���
//���������Ѿ�ע�͹��ĵط�����߲���ע���в���׸��

#include<iostream>
#include<graphics.h>
#include<easyx.h>
#include<vector>
#include<string>
#include <set>
#include <fstream>
using namespace std;
//ö���ඨ�岿����Ҫsize����
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
		final_set_size = final_set.size();
	}

	// �ж�������� word �Ƿ����ں�ѡ����
	bool in_final_set(std::string word) {
		return final_set.find(word) != final_set.end();
	}

	// �ж�������� word �Ƿ����ڿ��ü���
	bool in_acceptable_set(std::string word) {
		return acceptable_set.find(word) != acceptable_set.end();
	}
	//��ȡfinal_set������size
	int Getfinal_set_size()
	{
		return final_set_size;
	}
	//��ȡfinal_set�����ĵ�n��Ԫ�أ�ʵ������𰸵���Ҫ����
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
//��������ĸ���ֶ�Ӧ����
class Key
{
public:
	Key(RECT &rec,string &alphabet,int order):_rec(rec)
	{
		_order = order;
		_color = alphabet[_order];
		_letter = 'A' + _order ;		
	}
	//����Word���alphabet���ļ�����ɫ
	void Changecolor(string& alphabet)
	{
		_color = alphabet[_order];
	}
	void Recovercolor()
	{
		_color = 'X';
	}
	//���Ƽ�������ĸ��
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
//���������Ƽ���
class Ctrlkey
{
public:
	Ctrlkey(RECT &rec,string &str):_rec(rec),_ctrl(str){}
	//���ƿ��Ƽ�
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
//������ʾ����
class Wordkey
{
public:
	Wordkey(RECT *rec, char letter,int order) :_rec(rec),_letter(letter),_order(order),_color('X') {}
	//����Word���_result�ı���ɫ
	void Changecolor(string& result)
	{
		_color = result[_order];
	}
	//����������ʾ��
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
//�ж���������Ƿ��ھ�����
bool if_inrec(RECT&rec,int x,int y)
{
	if (x >= rec.left && x <= rec.right && y >= rec.top && y <= rec.bottom)
		return TRUE;
	else
		return FALSE;
}
//��ȡ�����Ϣ
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
//Сдת��д
string Utransform(string lowcase)
{
	string uppercase = "XXXXX";
	for (int i = 0; i < 5; i++)
	{
		uppercase[i] = lowcase[i] - 'a' + 'A';
	}
	return uppercase;
}
//��дתСд
string Ltransform(string uppercase)
{
	string lowcase = "xxxxx";
	for (int i = 0; i < 5; i++)
	{
		lowcase[i] = uppercase[i] - 'A' + 'a';
	}
	return lowcase;
}
//�����м�30����ɫ����
void Showhouse(vector<RECT>&rec)
{
	setlinecolor(RGB(236, 239, 241));
	for (int i = 0; i < 30; i++)
	{
		rectangle(rec[i].left, rec[i].top, rec[i].right, rec[i].bottom);
	}
}
//���Ƽ�������������ʾ��
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
//�����뱻�ж�ΪINVALIDʱ�����������ʾ��
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
//�Զ��嵯��ѡ��
HHOOK   hHook;
LRESULT  __stdcall  CBTHookProc(long  nCode, WPARAM  wParam, LPARAM   lParam)
{
	if (nCode == HCBT_ACTIVATE)
	{
		SetDlgItemText((HWND)wParam, IDYES, TEXT("����"));//YSE��Ϊ����
		SetDlgItemText((HWND)wParam, IDNO, TEXT("�˳�"));//NO��Ϊ�˳�
		SetDlgItemText((HWND)wParam, IDOK, TEXT("ȷ��"));//OK��Ϊȷ��
		SetDlgItemText((HWND)wParam, IDCANCEL, TEXT("ȡ��"));//cancle��Ϊȡ�� 
		UnhookWindowsHookEx(hHook);
	}
	return  0;
}
//���뱻�ж�ΪINVALIDʱ��������ʾ����
void Invalidwarn1()
{
	HWND hnd = GetHWnd();
	hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc, NULL, GetCurrentThreadId());
	MessageBox(hnd, "���벻����Ҫ��        ", "INVALID", MB_OK);
}
void Invalidwarn2()
{
	HWND hnd = GetHWnd();
	hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc, NULL, GetCurrentThreadId());
	MessageBox(hnd, "����û�Ǽ������ʣ�", "INVALID", MB_OK);
}
//ʧ��ʱ��������ʾ����
char Failurebox()
{
	HWND hnd = GetHWnd();
	hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc, NULL, GetCurrentThreadId());
	int result =MessageBox(hnd, "�˾���Ϸʧ�ܡ�       ", "FAIL", MB_YESNO);
	if (result == IDYES)
		return 'Y';
	else if (result == IDNO)
		return 'N';
}
//�ɹ�ʱ��������ʾ����
char Winbox()
{
	HWND hnd = GetHWnd();
	hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc, NULL, GetCurrentThreadId());
	int result = MessageBox(hnd, "��ϲ�㣡�˾���Ϸ�ɹ��� ", "WIN", MB_YESNO);
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

	//�������������
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
	//������ʾ���������
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
	//��������ĸ���Ϳ��Ƽ�������
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
		//����ʱ������������ɴ�
		srand((int)time(0));
		int Randomnum = rand() % wordset.Getfinal_set_size();
		ACC = wordset.Getfinal_set_word(Randomnum);
		cout << "�˴λ���ʱ���������ɵ�������ǣ�" << endl;
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
				char tc = Keymessage(place);//��ȡ�����Ϣ

				if (tc >= 'A' && tc <= 'A' + 25 && word.size() < 5)//��ȡ�����ĸ��ʱ���صļ�ֵ��ͬʱ����������ʾ����Ԫ��
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
				else if (tc == 'A' + 26)//���enter��ʱ�˳�ѭ��ʵ������
				{
					break;
				}
				else if (tc == 'A' + 27 && word.size() >= 1)//���back��ʱ���������ɵ�Ԫ��
				{
					word.erase(word.end() - 1);
					keyhouse.erase(keyhouse.end() - 1);
					BeginBatchDraw();
					cleardevice();
					Drawkey(Keyboard, Two, house, keyhouse);
					EndBatchDraw();
				}


			}
			cout << "����Ϊ" << endl;
			cout << word << endl;
			if (wordset.in_acceptable_set(word) == 0)
			{
				cout << "INVALID" << endl;
				Invalidwarn1();//INVALID,����+���������ʾ��
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
							Invalidwarn1();//INVALID,����+���������ʾ��
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
						Invalidwarn1();//INVALID,����+���������ʾ��
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
				for (int j = 0; j < 5; j++)//����Ϸ�ʱ���ı�������ʾ��������ɫ
				{
					keyhouse[5 * i + j].Changecolor(test._result);
				}

				for (int j = 0; j < 26; j++)//����Ϸ�ʱ���ı��������ĸ������ɫ
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
				choice = Winbox();//�õ���ѡ��Ϊchoice��ֵ
				break;
			}
			if (i == 5)
			{
				std::cout << "FAILED" << " " << Utransform(ACC) << endl;
				failure++;
				choice = Failurebox();//�õ���ѡ��Ϊchoice��ֵ
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