// Post-Fix Expression
// Austin Andrews
// Visual Studio 2013
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

const string IN = "postfix.in";
const string OUT = "postfix.out";

stack<float> Stack;
vector<char> Operators;
vector<string> Values;

void define(string readline, char& key)
{
	string op;

	key = readline[1];
	// add the key to the list of operators
	// add the values to the list of values
	// associated with the keys
	Operators.push_back(key);

	int start = readline.find("\"");
	int end = readline.find_last_of("\"");

	op = readline.substr(start, end);
	Values.push_back(op);
}

string cleanUpString(string equation)
{
	for (unsigned int i = 0; i < equation.length(); i++)
	{
		if (equation[i] == '\"')
		{
			equation = equation.erase(i, 1);
			i--;
		}
	}
	return equation;
}

void main()
{
	ifstream fin(IN);
	if (fin)
	{
		ofstream fout(OUT);
		string readline;
		float result;
		char key;

		getline(fin, readline);
		while (readline[0] != 'Q')
		{
			if (readline[0] == 'D')
				define(readline, key);
			else if (readline[0] == 'E')
			{
				float temp;

				// puts both the definition and the equation strings together
				readline = readline.substr(1, readline.length());
				string sTemp; 
				string fullEquation = readline; 
					
				// find all expamples of keys in readline
				int keyPosition;
				for (unsigned int i = 0; i < Operators.size(); i++)
				{
					for (unsigned int j = 0; j < fullEquation.length(); j++)
					{
						if (fullEquation[j] == Operators.at(i))
						{
							keyPosition = j;

							sTemp = fullEquation.substr(0, keyPosition);
							fullEquation = sTemp + Values.at(i) + fullEquation.substr(keyPosition + 1);
							i = 0;
						}
					}
				}

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
							{
								i += j;
								break;
							}
						}
						Stack.push(stof(partialNum));
					}
					// if readline[i] is a between ascii 48-57 (a number)
					else if (fullEquation[i] >= 48 && fullEquation[i] <= 57)
						Stack.push((float)fullEquation[i] - (float)48);
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

				fout << fixed;
				fout << setprecision(3) << result << endl;
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