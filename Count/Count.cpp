#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum Curency
{
	euro = 0, usd, grn
};
ostream& operator<<(ostream& os, const Curency& dt)
{
	switch (dt)
	{
	case(euro):
		os << "euro";
		break;
	case(usd):
		os << "usd";
		break;
	case(grn):
		os << "grn";
		break;
	default:
		break;
	}
	return os;
}

enum Type
{
	current = 0, card, credit, deposit
};

ostream& operator<<(ostream& os, const Type& dt)
{
	switch (dt)
	{
	case(current):
		os << "current";
		break;
	case(card):
		os << "card";
		break;
	case(credit):
		os << "credit";
		break;
	case(deposit):
		os << "deposit";
		break;
	default:
		break;
	}
	return os;
}

class Count
{
public:
	Count(string name, string bank,double balance,Type type, Curency cur) : name(name), bank(bank),type(type),cur(cur), balance(balance) {
		identificator++;
	}

	void balance_plus(double num) {
		balance += num;
	}
	void balance_minus(double num) {
		if (balance >=num && type==credit)
		{
			balance -= num;
			return;
		}
		cout << "Balance can`t be negative!\n";
	}
	virtual void info() {
		cout << "ID -> " << id << endl;
		cout << "Name -> " << name << endl;
		cout << "Curency -> " << cur << endl;
		cout << "Bank -> " << bank << endl;
		cout << "Type -> " << type << endl;
		cout << "Balance -> " << balance << endl;
	}



protected:
	static int identificator;
	string name,bank;
	Curency cur;
	Type type;
	const int id = identificator;
	double balance;
};



class Credit : public Count
{
public:
	Credit(string name, string bank, double balance, Curency cur) : Count(name, bank,balance, credit, cur)
	{
		string buf;
		cout << "Write current date(example:26 06 2022)\n";
		cin >> buf;
		end_date += buf;
		end_date += ".";
		start_date += buf;
		start_date += ".";

		cin >> buf;
		start_date += buf;
		start_date += ".";
		buf[1] = buf[1] + 1;
		end_date += buf;
		end_date += ".";

		cin >> buf;
		end_date += buf;
		start_date += buf;

	}

	void info() override {
		cout << "ID -> " << id << endl;
		cout << "Name -> " << name << endl;
		cout << "Curency -> " << cur << endl;
		cout << "Bank -> " << bank << endl;
		cout << "Type -> " << type << endl;
		cout << "Balance -> " << balance << endl;
		cout << "Date of start credit -> " << start_date << endl;
		cout << "Date of end credit -> " << end_date << endl;
		cout << "credit percentage -> " << procent << "%" << endl;
		cout << "arrear after 1 month with percents -> " << get_credit_arrear() << endl;
	}

	double get_credit_arrear() {
		if (balance<0)
		{
			return  balance - ((abs(balance) / 100) * procent);
		}
		return 0;
	}

private:
	string start_date = "";
	string end_date="";
	int procent = 5;
};

class Deposit : public Count
{
public:
	Deposit(string name, string bank, double balance, Curency cur) : Count(name, bank, balance, deposit, cur)
	{
		string buf;
		cout << "Write current date(example:26 06 2022)\n";
		cin >> buf;
		end_date += buf;
		end_date += ".";
		start_date += buf;
		start_date += ".";

		cin >> buf;
		end_date += buf;
		end_date += ".";
		start_date += buf;
		start_date += ".";

		cin >> buf;
		start_date += buf;
		buf[3] = buf[3] + 1;
		end_date += buf;

	}

	void info() override {
		cout << "ID -> " << id << endl;
		cout << "Name -> " << name << endl;
		cout << "Curency -> " << cur << endl;
		cout << "Bank -> " << bank << endl;
		cout << "Type -> " << type << endl;
		cout << "Balance -> " << balance << endl;
		cout << "Date of start deposit -> " << start_date << endl;
		cout << "Date of end deposit -> " << end_date << endl;
		cout << "deposit percentage -> " << procent << "%" << endl;
		cout << "balance after 1 year -> " << balance + (balance / 100) * 5 << endl;
	}

	double inline get_deposit_bal() {
		return balance + (balance / 100) * 5;
	}

private:
	string start_date = "";
	string end_date = "";
	int procent = 7;
};

int Count::identificator = 0;

int main()
{
	Count cnt("Vova","MonoBank",100,current,euro);
	cnt.info();
	cout << "\n\n";
	Credit crd("Sanya", "PrivatBank", 1250, usd);
	crd.info();
	cout << "\n\n";
	Deposit dps("Andrey", "RaiffeisenBank", 27300, grn);
	dps.info();
	cout << "\n\n";
	Credit crd2("Sanya", "PrivatBank", -1115, grn);
	crd2.info();
	cout << "\n\n";

}