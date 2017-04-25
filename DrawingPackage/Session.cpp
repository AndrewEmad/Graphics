#include<vector>
#include"Session.h"

void Session::setBackColor(int color){
	BG_Color = color;
}


void Session::setForeColor(int color){
	FG_Color = color;
}
void Session::AddCommand(Command c){
	Commands.push_back(c);
}
void Session::AddCommand(int algorithm, int numberOfPoints,Point *points, int color){
	Commands.push_back(Command(algorithm, color, numberOfPoints, points));
}
void Session::save(){}
void Session::load(){}