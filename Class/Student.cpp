#include<iostream>
class Student {
private:
	std::string name;
	std::string surname;
	int group;
	int xp; /*от 0 до 100*/
	int money; /*от 0*/
	float Time; /*от 0 до 24*/
public:
	int getgroup(int group) {
		return group;
	}
	int getxp(int xp) {
		return xp;
	}
	int getmoney(int money) {
		return money;
	}
	float gettime(float time) {
		return time;
	}
	std::string getname(std::string name) {
		return name;
	}
	std::string getsurname(std::string surname) {
		return surname;
	}

	int group1 = getgroup(group);
	int xp1 = getxp(xp);
	int money1 = getmoney(money);
	float time1 = gettime(time);
	std::string name1 = getname(name);
	std::string surname1 = getsurname(surname);

	int mark;
	void XPNorm(){
		if (xp1 < 0) {
			xp1 = 0;
			std::cout << "Gone to akadem"<<std::endl;
		}
		if (xp1 > 100) {
			xp1 = 100;
		}
	}
	void MoneyNorm() {
		if (money1 < 0) {
			money1 = 0;
		}
	}
	void TimeNorm() {
		if (Time1 < 0) {
			Time1 = 0;
			std::cout << "R.I.P."<<std::endl;
		}
		if (Time1 > 24) {
			Time1 = 24;
		}
	}
	void Food() {
		money1 -= 300;
		xp1 += 10;
		Time1 -= 0.5;
		MoneyNorm();
		XPNorm();
		TimeNorm();
	}
	void Study(int timeofstudy) {
		xp1 -= 100 / 24 * timeofstudy;
		Time1 -= timeofstudy;
		XPNorm();
		TimeNorm();
	}
	void Sleep(int timeofsleep) {
		xp1 += 10 * timeofsleep;
		Time1 -= timeofsleep;
		XPNorm();
		TimeNorm();
	}
	void Work(int timeofwork) {
		xp1 -= 10 * timeofwork;
		money1 += 1000 * timeofwork;
		XPNorm();
		MoneyNorm();
	}
	void Entertainment(int timeofentertainment) {
		xp1 += 15 * timeofentertainment;
		money1 -= 500 * timeofentertainment;
		XPNorm();
		MoneyNorm();
	}
};
int main()
{
	Student s{ "AAAAAA"; "BBBBB"; 304; 100; 10000; 24.0; };
}