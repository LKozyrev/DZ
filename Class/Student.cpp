#include<iostream>
class Student {
public:
	std::string name;
	std::string surname;
	int group;
	int xp; /*от 0 до 100*/
	int money; /*от 0*/
	float Time; /*от 0 до 24*/

	int mark;
	void XPNorm(){
		if (xp < 0) {
			xp = 0;
			std::cout << "Gone to akadem"<<std::endl;
		}
		if (xp > 100) {
			xp = 100;
		}
	}
	void MoneyNorm() {
		if (money < 0) {
			money = 0;
		}
	}
	void TimeNorm() {
		if (Time < 0) {
			Time = 0;
			std::cout << "R.I.P."<<std::endl;
		}
		if (Time > 24) {
			Time = 24;
		}
	}
	void Food() {
		money -= 300;
		xp += 10;
		Time -= 0.5;
		MoneyNorm();
		XPNorm();
		TimeNorm();
	}
	void Study(int timeofstudy) {
		xp -= 100 / 24 * timeofstudy;
		Time -= timeofstudy;
		XPNorm();
		TimeNorm();
	}
	void Sleep(int timeofsleep) {
		xp += 10 * timeofsleep;
		Time -= timeofsleep;
		XPNorm();
		TimeNorm();
	}
	void Work(int timeofwork) {
		xp -= 10 * timeofwork;
		money += 1000 * timeofwork;
		XPNorm();
		MoneyNorm();
	}
	void Entertainment(int timeofentertainment) {
		xp += 15 * timeofentertainment;
		money -= 500 * timeofentertainment;
		XPNorm();
		MoneyNorm();
	}
};
int main()
{
	
}