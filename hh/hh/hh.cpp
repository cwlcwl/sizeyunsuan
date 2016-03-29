#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>

using namespace std;
class A
{
public:
	A();	
	~A();
	void Create(int num);
	int Count(int range);
	void Display();
	
private:
	bool OperatorsIsHigher();
	int Getyunsuanfuqz(const char Operators);
private:
	int Result;
	char operators;
	A *zjd;
	A *yjd;
	bool isEX;
	A *Parent;
	bool isLeft;
};


A::A()
: Result(0)
, operators('\0')
, zjd(NULL)
, yjd(NULL)
, Parent(NULL)
, isLeft(false)
{
	
}

A::~A()
{
	if(zjd != NULL)
	{
		delete zjd;
	}

	if (yjd != NULL)
	{
		delete yjd;
	}
}
// 生成含有num个运算数字的随机表达式框架
void A::Create(int num)
{
	if ( num==1 )
	{
		return ;
	}
	else
	{
		int fuhao = rand() % 4;//随机生成0-3的数来代表对应的四种运算符号的下标
		if (fuhao == 0)
		{
			operators = '+';
		}
		else if (  fuhao==1)
		{
			operators = '-';
		}
		else if ( fuhao==2 )
		{
			operators= '*';
		}
		else
		{
			operators = '/';
		}

		zjd = new A();
		yjd = new A();
		zjd->Parent = this;
		zjd->isLeft = true;
		yjd->Parent = this;
		yjd->isLeft = false;

		int numOfNodeLeft = num - rand() % num;
		if (numOfNodeLeft == num)
		{
			numOfNodeLeft = 1;
		}

		zjd->Create(numOfNodeLeft);
		yjd->Create(num - numOfNodeLeft);
	}
}


int A::Count(int range)
{
	if (zjd != NULL && yjd != NULL)
	{
		int zResult = 0;
		int yResult = 0;

		zResult = zjd->Count( range);
		yResult = yjd->Count( range);

		while (zResult >= range || zResult <= 0)
		{
			zResult = zjd->Count( range);
		}

		while (yResult >= range|| yResult <= 0)
		{
			yResult = yjd->Count( range);
		}

		if (operators == '+')
		{
			Result = zResult + yResult;
		}

		else if ( operators=='-' )
		{
			Result = zResult - yResult;
			if (Result < 0)//防止运算结果为负数
			{
				A *t = zjd;
				zjd = yjd;
				zjd->isLeft = true;
				yjd = t;
				yjd->isLeft = false;
				Result = yResult - zResult;
			}
		}

		else if ( operators=='*' )
		{
			int getNum = 0;
			Result = zResult * yResult;
			while(Result >= 100)
			{
				zResult = zjd->Count(range);
				yResult = yjd->Count(range);
				getNum++;

				if (getNum > 100)
				{
					int fuhao = rand() % 2;
					if (fuhao ==0 )
					{
						operators = '+';
						Result = zResult + yResult;
					}
					else if ( fuhao==1 )
					{
						operators = '-';
						Result = zResult - yResult;
						if (Result < 0)
						{
							A *temp = zjd;
							zjd = yjd;
							zjd->isLeft = true;
							yjd = temp;
							yjd->isLeft = false;
							Result = yResult -zResult;
						}
					}

					return Result;
				}

				Result = zResult * yResult;
			}
		}

		else if ( operators=='/' )
		{
			int getNum = 0;
			while ( zResult==0  ||  yResult== 0 || zResult % yResult != 0)
			{
				zResult = zjd->Count(range);
				yResult = yjd->Count(range);
				getNum++;
				if(getNum > 2000)
				{
					int fuhao = rand() % 2;
					if ( fuhao==0 )
					{
						operators = '+';
						Result = zResult + yResult;
					}
					else if ( fuhao== 1)
					{
						operators = '-';
						Result = zResult - yResult;
						if (Result < 0)
						{
							A *temp = zjd;
							zjd = yjd;
							zjd->isLeft = true;
							yjd = temp;
							yjd->isLeft = false;
							Result = yResult - zResult;
						}
					}

					return Result;
				}
			}

			Result = zResult / yResult;
		}
	}
	else
	{
		Result = rand() % range;
		while (Result == 0)
		{
			Result = rand() % range;
		}
	}

	return Result;
}

void A::Display()
{
	if(zjd != NULL && yjd != NULL)
	{
		if (!OperatorsIsHigher())
		{
			cout << '(';
		}
		zjd->Display();
		cout << " " << operators << " ";
		yjd->Display();
		if (!OperatorsIsHigher())
		{
			cout << ')';
		}
	}
	else
	{
		cout << Result;
	}
	
	
}

bool A::OperatorsIsHigher()
{
	if (Parent ==NULL )
	{
		return true;
	}
	if (isLeft)
	{
		return Getyunsuanfuqz(this->operators) >= Getyunsuanfuqz(Parent->operators);
	}
	else
	{
		return Getyunsuanfuqz(this->operators) > Getyunsuanfuqz(Parent->operators);
	}
}

int A::Getyunsuanfuqz(const char operators)
{
	if (operators =='\0' )
	{
		return 3;
	}
	else if (operators =='/'  || operators == '*')
	{
		return 2;
	}
	else if ( operators=='+'  || operators== '-')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int main()
{
	while(1)
	{
	A *pEX = NULL;

	int numtimu = 0;

	int num = 0;

	cout << "题目个数:" << endl;

	cin >> numtimu;
	int range,answer;
	cout<<"参数范围:"<< endl;
	cin>>range;

	int Result = 0;
	srand((int)time(0));

	for (int i = 0; i < numtimu; i++)
	{
		
		pEX = new A();
		num = rand() % 2+2;
		pEX->Create(num);
		Result = pEX->Count( range);
		while (Result >= range || Result <= 0)
		{
			Result = pEX->Count( range);
		}
		pEX->Display();
		cout << " = "<<endl;
		cout<<"是否输出答案(1是 0否):";
		cin>>answer;
		if(answer==1)
		{
		   cout<<"答案"<<i+1<< ":"<<"  "<<Result;
		   
		}

		cout << endl;
		delete pEX;
		getchar();
	}

	system("pause");
	}
	return 0;
	
}