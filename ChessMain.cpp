#include"ChessBoard.h"

#include<iostream>

using namespace std;

int main() {

	ChessBoard cb;
	cout << '\n';

	cout << '\n';
	cb.submitMove("D2", "D4");
	cb.submitMove("D7", "D5");
	cout << '\n';
	cb.submitMove("C1", "F4");
	cb.submitMove("B8", "C6");
	cout << '\n';
	cb.submitMove("E2", "E3");
	cb.submitMove("C8", "F5");
	cout << '\n';
	cb.submitMove("G1", "F3");
	cb.submitMove("E7", "E6");
	cout << '\n';
	cb.submitMove("A2", "A3");
	cb.submitMove("G8", "F6");
	cout << '\n';
	cb.submitMove("C2", "C4");
	cb.submitMove("F8", "E7");
	cout << '\n';
	cb.submitMove("B1", "C3");
	cb.submitMove("E8", "G8"); // castling O-O
	cout << '\n';
	cb.submitMove("F1", "E2");
	cb.submitMove("D8", "D6");
	cout << '\n';
	cb.submitMove("E1", "G1"); // white castling
	cb.submitMove("F8", "D8");
	cout << '\n';
	cb.submitMove("F1", "E1");
	cb.submitMove("G8", "F8");
	cout << '\n';
	cb.submitMove("G1", "H1");
	cb.submitMove("F8", "E8");
	cout << '\n';
	cb.submitMove("H1", "G1");
	cb.submitMove("D8", "D7");
	cout << '\n';
	cb.submitMove("G1", "H1");
	cb.submitMove("E8", "C8"); // black castling again
	cout << '\n';


	return 0;
}
