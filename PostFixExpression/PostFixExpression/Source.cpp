// Post-Fix Expression
// Austin Andrews
// Visual Studio 2013
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
using namespace std;

const string IN = "postfix.in";
const string OUT = "postfix.out";

stack<float> Stack;

string define(string readline, char& key)
{
	string op;

	key = readline[1];
	int start = readline.find("\"");
	int end = readline.find_last_of("\"");

	op = readline.substr(start, end);

	//cout << "define() : " << op << endl;

	return op;
}

float convertToNumber(char x)
{
	float result = x - (float)48;
	return result;
}

float convertStringToNumber(string x);
{
	float result = strtof(x);
	return result;
}

string cleanUpString(string equation)
{
	for (int i = 0; i < equation.length(); i++)
	{
		if (equation[i] == '\"')
		{
			equation = equation.erase(i, 1);
			i--;
		}
	}
	return equation;
}

float evaluate(string readline, string op , char key)
{
	float result;
	float convertedNumber;
	float temp;
	
	// puts both the definition and the equation strings together
	readline = readline.substr(1, readline.length());
	int keyPosition = readline.find(key);
	string sTemp = readline.substr(0, keyPosition);
	string fullEquation = sTemp + op + readline.substr(keyPosition + 1);
	fullEquation = cleanUpString(fullEquation);
	string partialNum;

	for (unsigned int i = 0; i < fullEquation.length(); i++)
	{
		// if a number is larger that 9
		if (fullEquation[i] >= 48 && fullEquation[i] <= 57 &&
			(fullEquation[i + 1] >= 48 && fullEquation[i + 1] <= 57))
		{
			partialNum = fullEquation.substr(i, 1);
			for (unsigned int j = i; j < fullEquation.length() - i; j++)
			{
				if (fullEquation[j + 1] >= 48 && fullEquation[j + 1] <= 57)
					partialNum.append(fullEquation.substr(j + 1, 1));
				else
					break;
			}
			convertedNumber = convertStringToNumber(partialNum);
			Stack.push(convertedNumber);
		}
		// if readline[i] is a between ascii 48-57 (a number)
		else if (fullEquation[i] >= 48 && fullEquation[i] <= 57)
		{
			// function returns a float that is the value of the operator string
			convertedNumber = convertToNumber(fullEquation[i]);
			Stack.push(convertedNumber);
		}
		else
		{
			if (fullEquation[i] != '%' && fullEquation[i] != '!' && fullEquation[i] != ' ')
			{
				temp = Stack.top();
				Stack.pop();

				if (fullEquation[i] == '+')
				{
					temp = Stack.top() + temp;
					Stack.pop();
					Stack.push(temp);
				}
				else if (fullEquation[i] == '-')
				{
					temp = Stack.top() - temp;
					Stack.pop();
					Stack.push(temp);
				}
				else if (fullEquation[i] == '*')
				{
					temp = Stack.top() * temp;
					Stack.pop();
					Stack.push(temp);
				}
				else if (fullEquation[i] == '/')
				{
					temp = Stack.top() / temp;
					Stack.pop();
					Stack.push(temp);
				}
			}
			else
			{
				if (fullEquation[i] == '!')
					Stack.push(Stack.top());
				else if (fullEquation[i] == '%')
				{
					temp = Stack.top();
					Stack.pop();
					float temp2 = Stack.top();
					Stack.pop();
					Stack.push(temp);
					Stack.push(temp2);
				}
			}
		}
	}

	result = Stack.top();
	Stack.pop();

	cout << "evaluate() : " << result << endl;

	return result;
}

void main()
{
	ifstream fin(IN);
	if (fin)
	{
		ofstream fout(OUT);
		string readline;
		string op;
		float result;
		char key;

		getline(fin, readline);
		while (readline[0] != 'Q')
		{
			if (readline[0] == 'D')
				op = define(readline, key);
			else if (readline[0] == 'E')
				if (op != "")
				{
					result = evaluate(readline, op, key);
					fout << result << endl;
					cout << result << endl;
				}

			getline(fin, readline);
		}


		fout.close();
		fin.close();
	}
	else
	{
		cout << "Input file not found." << endl;
	}
}