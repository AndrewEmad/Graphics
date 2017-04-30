#include<vector>
#include"Session.h"
#include "Colors.h"
COLORREF Session::BG_Color=C_WHITE;
COLORREF Session::FG_Color=C_BLACK;
std::vector<Command>Session::Commands;

void Session::setBackColor(COLORREF color){
	BG_Color = color;
}


void Session::setForeColor(COLORREF color){
	FG_Color = color;
}


COLORREF Session::getBackColor(){
	return BG_Color;
}


COLORREF Session::getForeColor(){
	return FG_Color;
}


void Session::AddCommand(Command c){
	Commands.push_back(c);
}
void Session::AddCommand(int algorithm, int numberOfPoints, Point *points, COLORREF color){
	Commands.push_back(Command(algorithm, color, numberOfPoints, points));
}
void Session::save(){}
void Session::load(){}
