#include<bits/stdc++.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <cstdlib>
using namespace std;
void clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
void displayCountdown(int minutes,int seconds,int totalSeconds){
    clearScreen();
    cout<<"==============================\n";
    cout<<"       倒计时程序\n";
    cout<<"==============================\n\n";
    int barWidth=50;
    float progress=1.0f-(static_cast<float>(minutes*60+seconds)/totalSeconds);
    cout<<"剩余时间: ";
    cout<<setfill('0')<<setw(2)<<minutes<<":";
    cout<<setfill('0')<<setw(2)<<seconds<<"\n\n";
    
    cout<<"进度: [";
    int pos=barWidth*progress;
    for(int i=0; i<barWidth;i++){
        if(i<pos)cout<<"=";
        else if(i==pos)cout<<">";
        else cout<<" ";
    }
    cout<<"] "<<int(progress*100.0)<<"%\n\n";
    cout<<"按 Ctrl+C 终止程序\n";
    cout<<"==============================\n";
}
void startCountdown(int totalMinutes,int totalSeconds){
    int totalTime=totalMinutes*60+totalSeconds;
    int remainingTime=totalTime;
    displayCountdown(totalMinutes,totalSeconds,totalTime);
    while (remainingTime>0){
        this_thread::sleep_for(std::chrono::seconds(1));
        remainingTime--;
        int minutes=remainingTime/60;
        int seconds=remainingTime%60;
        displayCountdown(minutes,seconds,totalTime);
        if (remainingTime <= 10){
            cout<<"\n警告: 时间即将结束！\n";
        }
    }
    clearScreen();
    cout<<"!!! 时间到 !!!\n";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout<<"\n倒计时已结束。\n";
}
void getUserInput(int &minutes, int &seconds){
    clearScreen();
    while(true){
        cout<<"请输入分钟数 (0-60): ";
        cin>>minutes;
        if(cin.fail()||minutes<0||minutes>60){
            cin.clear();
            cin.ignore(10000,'\n');
            cout<<"输入无效，请重新输入！\n";
        } 
		else{
            break;
        }
    }
    while(true){
        cout<<"请输入秒数 (0-59): ";
        cin>>seconds;
        if(cin.fail()||seconds<0||seconds>=60){
            cin.clear();
            cin.ignore(10000,'\n');
            cout<<"输入无效，请重新输入！\n";
        }
		else{
            break;
        }
    }
    if(minutes==0&&seconds==0){
        cout<<"\n错误: 倒计时时间必须大于0！\n";
        cout<<"使用默认值: 1分钟\n";
        minutes=1;
        seconds=0;
    }
	cout<<"\n设置完成: "<<minutes<<"分"<<seconds<<"秒\n";
    cout<<"按 Enter 键开始倒计时...";
    cin.ignore();
    cin.get();
}
int main() {
    char choice;
    do{
		int minutes,seconds;
        getUserInput(minutes,seconds);
        startCountdown(minutes,seconds);
        cout<<"\n是否开始新的倒计时？(y/n): ";
        cin>>choice;
        cin.ignore(10000,'\n');
    }
	while(choice=='y'||choice=='Y');
    cout<<"\n感谢使用倒计时程序！\n";
    return 0;
}
