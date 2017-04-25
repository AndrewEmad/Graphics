#include<vector>
#include"Session.h"

COLORREF Session::BG_Color=0;
COLORREF Session::FG_Color=0;
std::vector<Command>Session::Commands;

void Session::setBackColor(COLORREF color){
	BG_Color = color;
}


void Session::setForeColor(COLORREF color){
	FG_Color = color;
}
void Session::AddCommand(Command c){
	Commands.push_back(c);
}
void Session::AddCommand(int algorithm, int numberOfPoints, Point *points, COLORREF color){
	Commands.push_back(Command(algorithm, color, numberOfPoints, points));
}
void Session::save(){}
void Session::load(){}