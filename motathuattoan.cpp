#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include<sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#define max 100

using namespace std;

// config
void resizeConsole(int width, int height);
void DisableResizeWindow();
void ShowCur(bool CursorVisibility);

void SetColor(int backgound_color, int text_color);
void gotoXY(int x, int y);

// thanh phan
void box(int x, int y, int w, int h, int t_color, int b_color, string text, bool border, int border_color, int type);
void n_box(int x, int y, int w, int h, int t_color, int b_color, string *texts, bool border, int border_color, int n);
string convertString(int x);

void swap(int &x, int &y);
void swapTransition(int A[], int i, int min, int y);
int random(int minN, int maxN);

int movementOrSteps();

void quickSort(int A[], int count, int l, int r, int x, int &y, string type, int &dem);
void vundong(int A[], int count, int n, int r, int x, int &y, string type, int &dem);

// chuc nang
void mainMenu(int A[], int &count, int chooseActive);
void xuatInfo(int A[], int count, int x, int y);
void docFileFunc(int A[], int &count);
void nhapFunc(int A[], int &count);
void xuatFunc(int A[], int count);

void selectionSortFunc(int A[], int count);
void bubbleSortFunc(int A[], int count);
void insertionSortFunc(int A[], int count);
void quickSortFunc(int A[], int count);
void heapSortFunc(int A[], int count);

void backOrExit(int A[], int count, int chooseActive, int x, int y);

int main(){
	// thay doi kich thuoc console
	resizeConsole(1500, 750);
	
	// vo hieu hoa thay doi kich thuoc man hinh
	DisableResizeWindow();
	
	int A[max];
	int count;
	
	mainMenu(A, count, 0);
	return 0;
}

// config
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void DisableResizeWindow()
{
    HWND hWnd = GetConsoleWindow();
    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}

void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}

void SetColor(int backgound_color, int text_color)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    int color_code = backgound_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
}

void gotoXY(int x, int y)
{
  HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = x;
    Position.Y = y;

	SetConsoleCursorPosition(hStdout, Position);
}

// thanh phan
void box(int x, int y, int w, int h, int t_color, int b_color, string text, bool border, int border_color, int type){
	if(border && h > 0 && w > 0){ // tao border
		// doi mau border
		SetColor(b_color, border_color);
		
		// tang kich thuoc
		h++;
		w++;
		
		// in chieu ngang
		for(int ix = x; ix <= x + w; ix++){
			gotoXY(ix, y);
			cout << char(196);
			gotoXY(ix, y + h);
			cout << char(196);
		}
		
		// in chieu doc
		for(int iy = y; iy <= y + h; iy++){
			gotoXY(x, iy);
			cout << char(179);
			gotoXY(x + w, iy);
			cout << char(179);
		}
		
		// in goc
		if(type == 0 || type == 1){
			gotoXY(x, y);
			cout << char(218); // trai tren
			gotoXY(x + w, y);
			cout << char(191); // phai tren
		}else{
			gotoXY(x, y); // trai tren
			cout << char(195);
			gotoXY(x + w, y); // phai tren
			cout << char(180);
		}
		
		if(type == 0 || type == 3){
			gotoXY(x, y + h);
			cout << char(192); // trai duoi
			gotoXY(x + w, y + h);
			cout << char(217); // phai duoi
		}else{
			gotoXY(x, y + h); // trai duoi
			cout << char(195);
			gotoXY(x + w, y + h); // phai duoi
			cout << char(180);
		}
		
		// tang khoang cach text
		x++;
		y++;
	}
	
	int textLength = text.length();
	string newText = "";
	for(int i = 0; i < (w - textLength - 2)/2; i++){
		newText += " ";
		text += " ";
	}
	
	if((w - textLength - 2) % 2 == 1){
		text += " ";
	}
	
	// doi mau background, text
	SetColor(b_color, t_color);
	gotoXY(x, y);
	cout << newText + text;
	
	// doi mau ve mac dinh
	SetColor(0, 7);
}

void n_box(int x, int y, int w, int h, int t_color, int b_color, string *texts, bool border, int border_color, int n){
	int h_border = h, w_border = w;
	if(border){
		h_border++;
		w_border++;
	}
	
	for(int i = 0; i < n; i++){
		// in cac goc
		box(x, y + (i * h_border), w, h, t_color, b_color, texts[i], border, border_color, i == 0 ? 1 : (i == n - 1 ? 3 : 2));
	}
	
	SetColor(0, 7);
}

string convertString(int x){
	stringstream ss;
	ss<<x;
	string s;  
	ss>>s;
	return s;
}

void swap(int &x, int &y){
	int temp = x;
	x = y;
	y = temp;
}

void swapTransition(int A[], int a, int b, int y){
	int ix = 55 + a * 15;
	for(int iy = y; iy <= y + 6; iy += 3){
		Sleep(100);
		if(iy == y){// xoa vi tri dau
			for(int k = iy; k <= iy + 2; k++){
				gotoXY(ix, k);
				cout << "              ";
			}
		}else{
			for(int k = iy - 3; k <= iy - 1; k++){
				gotoXY(ix, k);
				cout << "              ";
			}
			Sleep(100);
			box(ix, iy, 10, 1, 10, 0, convertString(A[a]), true, 10, 0);
		}
	}
	
	int mx = 55 + b * 15;
	for(int iy = y; iy <= y + 3; iy += 3){
		Sleep(100);
		if(iy == y){// xoa vi tri dau
			for(int k = iy; k <= iy + 2; k++){
				gotoXY(mx, k);
				cout << "              ";
			}
		}else{
			for(int k = iy - 3; k <= iy - 1; k++){
				gotoXY(mx, k);
				cout << "              ";
			}
			Sleep(100);
			box(mx, iy, 10, 1, 10, 0, convertString(A[b]), true, 10, 0);
		}
	}
	
	for(int tempx = mx; tempx >= ix; tempx -= 15){
		Sleep(100);
		for(int k = y + 3; k <= y + 5; k++){
			gotoXY(tempx + 15, k);
			cout << "              ";
		}
		Sleep(100);
		box(tempx, y + 3, 10, 1, 10, 0, convertString(A[b]), true, 10, 0);
	}
	
	Sleep(100);
	for(int k = y + 3; k <= y + 5; k++){
		gotoXY(ix, k);
		cout << "              ";
	}
	Sleep(100);
	box(ix, y, 10, 1, 10, 0, convertString(A[b]), true, 10, 0);
	
	for(int tempx = ix; tempx <= mx; tempx += 15){
		Sleep(100);
		for(int k = y + 6; k <= y + 8; k++){
			gotoXY(tempx - 15, k);
			cout << "              ";
		}
		Sleep(100);
		box(tempx, y + 6, 10, 1, 10, 0, convertString(A[a]), true, 10, 0);
	}
	
	for(int tempy = 2; tempy >= 1; tempy--){
		Sleep(100);
		for(int k = y + tempy * 3; k <= y + tempy * 3 + 2; k++){
			gotoXY(mx, k);
			cout << "              ";
		}
		Sleep(100);
		box(mx, y + (tempy - 1) * 3, 10, 1, 10, 0, convertString(A[a]), true, 10, 0);
	}
	
	// rest mau
	Sleep(500);
	box(ix, y, 10, 1, 7, 0, convertString(A[b]), true, 7, 0);
	box(mx, y, 10, 1, 7, 0, convertString(A[a]), true, 7, 0);
}

int random(int minN, int maxN){
    return minN + rand() % (maxN + 1 - minN);
}

int movementOrSteps(){
	// config
	int x = 62;
	int y = 10;
	
	string movementOrStepsTexts[2] = {"Chuyen dong.", "Cac buoc."};
	
	box(x, y, 25, 1, 7, 0, movementOrStepsTexts[0], true, 7, 0);
	box(x + 32, y, 25, 1, 7, 0, movementOrStepsTexts[1], true, 7, 0);
	
	// active
	box(x, y, 25, 1, 11, 0, movementOrStepsTexts[0], true, 11, 0);
	
	// toa do active
	int xp = x;
	int yp = y;
	
	// toa do cu
	int xcu = xp;
	int ycu = yp;
	
	while(true){
		// an nhap lieu
		ShowCur(false);
		
		// index
		int box_index_cu = (xcu - x)/32;
		int box_index_active = (xp - x)/32;
		
		// deactive
		box(xcu, ycu, 25, 1, 7, 0, movementOrStepsTexts[box_index_cu], true, 7, 0);
		xcu = xp;
		ycu = yp;
		
		// active
		box(xp, yp, 25, 1, 11, 0, movementOrStepsTexts[box_index_active], true, 11, 0);
		
		// dieu khien
		char key_press = getch();
		int key_value = (int)key_press;
		if(key_value == 75){
			if(xp == x){
				xp = x + 32;
			}else {
				xp -= 32;
			}
		} else if(key_value == 77){
			if(xp == x + 32){
				xp = x;
			}else {
				xp += 32;
			}
		} else if(key_value == 13){
			for(int iy = y; iy <= y + 2; iy++){
				gotoXY(62, iy);
				cout << "                                                                      ";
			}
			
			return box_index_active;
			break;
		}
	}
}

void quickSort(int A[], int count, int l, int r, int x, int &y, string type, int &dem){
	if(l >= r) return;
	
	int i = l, j = r;
	int vtc = random(l, r);
	int chot = A[vtc];
	
	if(type == "movement"){
		Sleep(300);
		SetColor(0, 7);
		gotoXY(8, 23);
		cout << "quickSortFunc(A, l, j);";
		
		Sleep(300);
		SetColor(0, 7);
		gotoXY(8, 24);
		cout << "quickSortFunc(A, i, r);";
		
		Sleep(200);
		SetColor(11, 0);
		gotoXY(8, 5);
		cout << "if(l >= r) return;";
		SetColor(0, 7);
		
		Sleep(200);
		SetColor(0, 7);
		gotoXY(14, 10);
		cout << "i++;";
		
		Sleep(200);
		SetColor(0, 7);
		gotoXY(14, 20);
		cout << "j--;";
		
		Sleep(500);
		SetColor(11, 0);
		gotoXY(8, 6);
		cout << "int i = l, j = r;";
		SetColor(0, 7);
		
		Sleep(200);
		SetColor(0, 7);
		gotoXY(8, 5);
		cout << "if(l >= r) return;";
		
		for(int k = l; k <= r; k++){
			// active
			x = 55 + k * 15;
			box(x, y, 10, 1, 7, 0, convertString(A[k]), true, 7, 0);
		}
		
		gotoXY(72, y - 7);
		cout << "                                                   ";
		
		Sleep(200);
		gotoXY(72, y - 7);
		cout << "tao ngau nhien gia tri chot";
		
		Sleep(200);
		SetColor(11, 0);
		gotoXY(8, 7);
		cout << "int chot = A[random(l, r)];";
		SetColor(0, 7);
		
		Sleep(200);
		SetColor(0, 7);
		gotoXY(8, 6);
		cout << "int i = l, j = r;";
		
		// active
		Sleep(500);
		x = 55 + vtc * 15;
		box(x, y, 10, 1, 14, 0, convertString(chot), true, 14, 0);
		
		Sleep(200);
		SetColor(11, 0);
		gotoXY(8, 8);
		cout << "while(i <= j){";
		SetColor(0, 7);
		
		Sleep(200);
		SetColor(0, 7);
		gotoXY(8, 7);
		cout << "int chot = A[random(l, r)];";
		
		while(i <= j){
			// active
			Sleep(500);
			x = 55 + i * 15;
			gotoXY(x + 5, y - 1);
			cout << "i";
			if(i != vtc){
				box(x, y, 10, 1, 12, 0, convertString(A[i]), true, 12, 0);
			}
			
			Sleep(200);
			SetColor(11, 0);
			gotoXY(11, 9);
			cout << "while(A[i] < chot){";
			SetColor(0, 7);
			
			Sleep(200);
			SetColor(0, 7);
			gotoXY(8, 8);
			cout << "while(i <= j){";
			
			while(A[i] < chot){
				gotoXY(72, y - 7);
				cout << "                                                   ";
				
				Sleep(200);
				gotoXY(72, y - 7);
				cout << "tim gia tri lon hon chot (" << i << "->" << vtc << ")";
				
				i++;
				
				Sleep(200);
				SetColor(11, 0);
				gotoXY(14, 10);
				cout << "i++;";
				SetColor(0, 7);
				
				Sleep(200);
				SetColor(0, 7);
				gotoXY(11, 9);
				cout << "while(A[i] < chot){";
				
				/// deactive
				Sleep(500);
				x = 55 + (i - 1) * 15;
				gotoXY(x + 5, y - 1);
				cout << " ";
				if(i - 1 == vtc){
					box(x, y, 10, 1, 14, 0, convertString(A[i - 1]), true, 14, 0);
				}else if(i - 1 != j){
					box(x, y, 10, 1, 7, 0, convertString(A[i - 1]), true, 7, 0);
				}
				
				// active
				Sleep(500);
				x = 55 + i * 15;
				gotoXY(x + 5, y - 1);
				cout << "i";
				if(i != vtc){
					box(x, y, 10, 1, 12, 0, convertString(A[i]), true, 12, 0);
				}
				
				Sleep(200);
				SetColor(11, 0);
				gotoXY(11, 9);
				cout << "while(A[i] < chot){";
				SetColor(0, 7);
				
				Sleep(200);
				SetColor(0, 7);
				gotoXY(14, 10);
				cout << "i++;";
			}
			
			gotoXY(72, y - 7);
			cout << "                                                   ";
			
			Sleep(200);
			gotoXY(72, y - 7);
			cout << "gia tri lon hon chot A["  << i << "] (" << A[i] << ")";
			Sleep(500);
			
			// active
			Sleep(500);
			x = 55 + j * 15;
			gotoXY(x + 5, y + 3);
			cout << "j";
			if(j != vtc){
				box(x, y, 10, 1, 12, 0, convertString(A[j]), true, 12, 0);
			}
			
			Sleep(200);
			SetColor(11, 0);
			gotoXY(11, 12);
			cout << "while(A[j] > chot){";
			SetColor(0, 7);
			
			Sleep(200);
			SetColor(0, 7);
			gotoXY(11, 9);
			cout << "while(A[i] < chot){";
			
			while(A[j] > chot){
				gotoXY(72, y - 7);
				cout << "                                                   ";
				
				Sleep(200);
				gotoXY(72, y - 7);
				cout << "tim gia tri nho hon chot (" << j << "->" << vtc << ")";
				
				j--;
				
				Sleep(200);
				SetColor(11, 0);
				gotoXY(14, 13);
				cout << "j--;";
				SetColor(0, 7);
				
				Sleep(200);
				SetColor(0, 7);
				gotoXY(11, 12);
				cout << "while(A[j] > chot){";
				
				// deactive
				Sleep(500);
				x = 55 + (j + 1) * 15;
				gotoXY(x + 5, y + 3);
				cout << " ";
				if(j + 1 == vtc){
					box(x, y, 10, 1, 14, 0, convertString(A[j + 1]), true, 14, 0);
				}else if(j + 1 != i) {
					box(x, y, 10, 1, 7, 0, convertString(A[j + 1]), true, 7, 0);
				}
				
				// active
				Sleep(500);
				x = 55 + j * 15;
				gotoXY(x + 5, y + 3);
				cout << "j";
				if(j != vtc){
					box(x, y, 10, 1, 12, 0, convertString(A[j]), true, 12, 0);
				}
				
				Sleep(200);
				SetColor(11, 0);
				gotoXY(11, 12);
				cout << "while(A[j] > chot){";
				SetColor(0, 7);
				
				Sleep(200);
				SetColor(0, 7);
				gotoXY(14, 13);
				cout << "j--;";
			}
			
			gotoXY(72, y - 7);
			cout << "                                                   ";
			
			Sleep(200);
			gotoXY(72, y - 7);
			cout << "gia tri nho hon chot A["  << j << "] (" << A[j] << ")";
			Sleep(500);
			
			Sleep(200);
			SetColor(11, 0);
			gotoXY(11, 15);
			cout << "if(i < j){";
			SetColor(0, 7);
			
			Sleep(200);
			SetColor(0, 7);
			gotoXY(11, 12);
			cout << "while(A[j] > chot){";
			
			if(i < j){		
				gotoXY(72, y - 7);
				cout << "                                                   ";
				
				Sleep(200);
				gotoXY(72, y - 7);
				cout << "doi cho A["  << i << "] (" << A[i] << ") va A[" << j << "] (" << A[j] << ")";
				
				Sleep(200);
				SetColor(11, 0);
				gotoXY(14, 16);
				cout << "swap(A[i], A[j]);";
				SetColor(0, 7);
				
				Sleep(200);
				SetColor(0, 7);
				gotoXY(11, 15);
				cout << "if(i < j){";
				
				if(i == vtc){
					vtc = j;
				}else if(j == vtc){
					vtc = i;
				}
				swapTransition(A, i, j, y);
				swap(A[i], A[j]);
				
				// active
				Sleep(500);
				x = 55 + vtc * 15;
				box(x, y, 10, 1, 14, 0, convertString(A[vtc]), true, 14, 0);
			}
			
			Sleep(200);
			SetColor(11, 0);
			gotoXY(11, 18);
			cout << "if(i <= j){";
			SetColor(0, 7);
			
			Sleep(200);
			SetColor(0, 7);
			gotoXY(11, 15);
			cout << "if(i < j){";
			
			Sleep(200);
			SetColor(0, 7);
			gotoXY(14, 16);
			cout << "swap(A[i], A[j]);";
			
			if(i <= j){	
				i++;
				
				// deactive
				Sleep(500);
				x = 55 + (i - 1) * 15;
				gotoXY(x + 5, y - 1);
				cout << " ";
				if(i - 1 == vtc){
					box(x, y, 10, 1, 14, 0, convertString(A[i - 1]), true, 14, 0);
				}else if(i - 1 != j){
					box(x, y, 10, 1, 7, 0, convertString(A[i - 1]), true, 7, 0);
				}
				
				// active
				Sleep(500);
				x = 55 + i * 15;
				gotoXY(x + 5, y - 1);
				cout << "i";
				if(i > r){
					box(x, y, 10, 1, 8, 0, convertString(A[i]), true, 8, 0);
				}else if(i != vtc){
					box(x, y, 10, 1, 12, 0, convertString(A[i]), true, 12, 0);
				}
				
				Sleep(200);
				SetColor(11, 0);
				gotoXY(14, 19);
				cout << "i++;";
				SetColor(0, 7);
				
				Sleep(200);
				SetColor(0, 7);
				gotoXY(11, 18);
				cout << "if(i <= j){";
				
				j--;
				
				// deactive
				Sleep(500);
				x = 55 + (j + 1) * 15;
				gotoXY(x + 5, y + 3);
				cout << " ";
				if(j + 1 == vtc){
					box(x, y, 10, 1, 14, 0, convertString(A[j + 1]), true, 14, 0);
				}else if(j + 1 != i) {
					box(x, y, 10, 1, 7, 0, convertString(A[j + 1]), true, 7, 0);
				}
				
				// active
				Sleep(500);
				x = 55 + j * 15;
				gotoXY(x + 5, y + 3);
				cout << "j";
				if(j < l){
					box(x, y, 10, 1, 8, 0, convertString(A[j]), true, 8, 0);
				}else if(j != vtc){
					box(x, y, 10, 1, 12, 0, convertString(A[j]), true, 12, 0);
				}
				
				Sleep(500);
				SetColor(11, 0);
				gotoXY(14, 20);
				cout << "j--;";
				SetColor(0, 7);
				
				Sleep(200);
				SetColor(0, 7);
				gotoXY(14, 19);
				cout << "i++;";
			}
			
			if(i > 0){
				// deactive
				Sleep(500);
				x = 55 + (i - 1) * 15;
				gotoXY(x + 5, y - 1);
				cout << " ";
				if(i - 1 != vtc){
					box(x, y, 10, 1, 7, 0, convertString(A[i - 1]), true, 7, 0);
				}
			}
			
			if(j < r){
				// deactive
				Sleep(500);
				x = 55 + (j + 1) * 15;
				gotoXY(x + 5, y + 3);
				cout << " ";
				if(j + 1 != vtc){
					box(x, y, 10, 1, 7, 0, convertString(A[j + 1]), true, 7, 0);
				}
			}
			
			if(i > r){
				x = 55 + i * 15;
				gotoXY(x + 5, y - 1);
				cout << " ";
			}
			
			if(j < l){
				x = 55 + j * 15;
				gotoXY(x + 5, y + 3);
				cout << " ";
			}
			
			Sleep(200);
			SetColor(11, 0);
			gotoXY(8, 8);
			cout << "while(i <= j){";
			SetColor(0, 7);
			
			Sleep(200);
			SetColor(0, 7);
			gotoXY(11, 18);
			cout << "if(i <= j){";
			
			Sleep(200);
			SetColor(0, 7);
			gotoXY(14, 20);
			cout << "j--;";
		}
		
		// deactive
		Sleep(500);
		x = 55 + vtc * 15;
		box(x, y, 10, 1, 7, 0, convertString(A[vtc]), true, 7, 0);
		
		for(int k = l; k <= r; k++){
			// active
			x = 55 + k * 15;
			gotoXY(x + 5, y - 1);
			cout << " ";
			gotoXY(x + 5, y + 3);
			cout << " ";
			box(x, y, 10, 1, 8, 0, convertString(A[k]), true, 8, 0);
		}
	}else {		
		y += 9;
		gotoXY(40, y - 4);
		cout << "Buoc " << dem << ": tao ngau nhien gia tri chot A[" << vtc << "] (" << chot << ") trong doan " << l << "->" << r;
		xuatInfo(A, count, 40, y);
		int acx = 55 + vtc * 15;
		box(acx, y, 10, 1, 14, 0, convertString(chot), true, 14, 0);
		dem++;
		
		for(int k = 0; k < l; k++){
			int kx = 55 + k * 15;
			gotoXY(kx + 5, y - 1);
			cout << " ";
			box(kx, y, 10, 1, 8, 0, convertString(A[k]), true, 8, 0);
			gotoXY(kx + 5, y + 3);
			cout << " ";
		}
		
		for(int k = r + 1; k < count; k++){
			int kx = 55 + k * 15;
			gotoXY(kx + 5, y - 1);
			cout << " ";
			box(kx, y, 10, 1, 8, 0, convertString(A[k]), true, 8, 0);
			gotoXY(kx + 5, y + 3);
			cout << " ";
		}
		
		while(i <= j){
			y += 9;
			gotoXY(40, y - 4);
			cout << "Buoc " << dem << ": tim kiem gia tri lon hon hoac bang va nho hon hoac bang chot A[" << vtc << "] (" << A[vtc] << ") trong doan " << l << "->" << r;
			xuatInfo(A, count, 40, y);
			int acx = 55 + vtc * 15;
			box(acx, y, 10, 1, 14, 0, convertString(A[vtc]), true, 14, 0);
			dem++;
			
			while(A[i] < chot){
				i++;
			}
			
			int ix = 55 + i * 15;
			gotoXY(ix + 5, y - 1);
			cout << "i";
			box(ix, y, 10, 1, 12, 0, convertString(A[i]), true, 12, 0);
			
			while(A[j] > chot){
				j--;
			}
			
			int jx = 55 + j * 15;
			gotoXY(jx + 5, y + 3);
			cout << "j";
			box(jx, y, 10, 1, 12, 0, convertString(A[j]), true, 12, 0);
			
			for(int k = 0; k < l; k++){
				int kx = 55 + k * 15;
				box(kx, y, 10, 1, 8, 0, convertString(A[k]), true, 8, 0);
			}
			
			for(int k = r + 1; k < count; k++){
				int kx = 55 + k * 15;
				box(kx, y, 10, 1, 8, 0, convertString(A[k]), true, 8, 0);
			}
			
			if(i < j){
				y += 9;
				gotoXY(40, y - 4);
				cout << "Buoc " << dem << ": doi cho A[" << i << "] (" << A[i] << ") va A[" << j << "] (" << A[j] << ")";
				xuatInfo(A, count, 40, y);
				int jx = 55 + j * 15;
				box(jx, y, 10, 1, 10, 0, convertString(A[i]), true, 10, 0);
				int ix = 55 + i * 15;
				box(ix, y, 10, 1, 10, 0, convertString(A[j]), true, 10, 0);
				dem++;
				
				for(int k = 0; k < l; k++){
					int kx = 55 + k * 15;
					box(kx, y, 10, 1, 8, 0, convertString(A[k]), true, 8, 0);
				}
				
				for(int k = r + 1; k < count; k++){
					int kx = 55 + k * 15;
					box(kx, y, 10, 1, 8, 0, convertString(A[k]), true, 8, 0);
				}
				
				swap(A[i], A[j]);
			}
			
			if(i <= j){
				i++;
				j--;
			}
		}
	}
	
	if(type == "movement"){
		Sleep(500);
		SetColor(11, 0);
		gotoXY(8, 23);
		cout << "quickSortFunc(A, l, j);";
		SetColor(0, 7);
		
		Sleep(200);
		SetColor(0, 7);
		gotoXY(8, 8);
		cout << "while(i <= j){";
	}
	
	quickSort(A, count, l, j, x, y, type, dem);
	
	if(type == "movement"){
		Sleep(500);
		SetColor(11, 0);
		gotoXY(8, 24);
		cout << "quickSortFunc(A, i, r);";
		SetColor(0, 7);
		
		Sleep(300);
		SetColor(0, 7);
		gotoXY(8, 23);
		cout << "quickSortFunc(A, l, j);";
	}
	
	quickSort(A, count, i, r, x, y, type, dem);
}

void vundong(int A[], int count, int n, int r, int x, int &y, string type, int &dem){
	int j = r;
	int v = A[r];
	
	if(type == "movement"){
		Sleep(500);
		SetColor(11, 0);
		gotoXY(8, 5);
		cout << "int j = r;";
		SetColor(0, 7);
		
		Sleep(200);
		SetColor(0, 7);
		gotoXY(11, 27);
		cout << "vundong(A, count, i);";
		
		Sleep(200);
		SetColor(0, 7);
		gotoXY(11, 32);
		cout << "vundong(A, i, 0);";
		
		Sleep(500);
		SetColor(11, 0);
		gotoXY(8, 6);
		cout << "int v = A[r];";
		SetColor(0, 7);
		
		Sleep(200);
		SetColor(0, 7);
		gotoXY(8, 5);
		cout << "int j = r;";
		
		Sleep(500);
		SetColor(11, 0);
		gotoXY(8, 7);
		cout << "while(2*j + 1 < n){";
		SetColor(0, 7);
		
		Sleep(200);
		SetColor(0, 7);
		gotoXY(8, 6);
		cout << "int v = A[r];";
		
		while(2*j + 1 < n){
			gotoXY(72, y - 7);
			cout << "                                                   ";
			
			Sleep(200);
			gotoXY(72, y - 7);
			cout << "khoa cha A[" << j << "] (" << v << ")";
			
			// active
			Sleep(500);
			x = 55 + j * 15;
			box(x, y, 10, 1, 14, 0, convertString(v), true, 14, 0);
			
			int m = 2*j + 1;
			
			Sleep(200);
			SetColor(11, 0);
			gotoXY(11, 8);
			cout << "int m = 2*j + 1;";
			SetColor(0, 7);
			
			Sleep(200);
			SetColor(0, 7);
			gotoXY(8, 7);
			cout << "while(2*j + 1 < n){";
			
			Sleep(200);
			SetColor(11, 0);
			gotoXY(11, 9);
			cout << "if(m + 1 < n && A[m+1] > A[m]){";
			SetColor(0, 7);
			
			Sleep(200);
			SetColor(0, 7);
			gotoXY(11, 8);
			cout << "int m = 2*j + 1;";
			
			if(m + 1 < n && A[m+1] > A[m]){
				m++;
				
				Sleep(200);
				SetColor(11, 0);
				gotoXY(14, 10);
				cout << "m++;";
				SetColor(0, 7);
			
				Sleep(200);
				SetColor(0, 7);
				gotoXY(11, 9);
				cout << "if(m + 1 < n && A[m+1] > A[m]){";
			}
			
			gotoXY(72, y - 7);
			cout << "                                                   ";
			
			Sleep(200);
			gotoXY(72, y - 7);
			cout << "khoa con lon nhat A[" << m << "] (" << A[m] << ")";
			
			// active
			Sleep(500);
			x = 55 + m * 15;
			box(x, y, 10, 1, 12, 0, convertString(A[m]), true, 12, 0);
			
			Sleep(200);
			SetColor(11, 0);
			gotoXY(11, 12);
			cout << "if(A[m] > v){";
			SetColor(0, 7);
			
			Sleep(200);
			SetColor(0, 7);
			gotoXY(14, 10);
			cout << "m++;";
		
			Sleep(200);
			SetColor(0, 7);
			gotoXY(11, 9);
			cout << "if(m + 1 < n && A[m+1] > A[m]){";
			
			if(A[m] > v){
				gotoXY(72, y - 7);
				cout << "                                                   ";
				
				Sleep(200);
				gotoXY(72, y - 7);
				cout << "doi cho A[" << j << "] (" << v << ") va A[" << m << "] (" << A[m] << ")";
				
				Sleep(200);
				SetColor(11, 0);
				gotoXY(14, 13);
				cout << "A[j] = A[m];";
				SetColor(0, 7);
				
				Sleep(200);
				SetColor(0, 7);
				gotoXY(11, 12);
				cout << "if(A[m] > v){";
				
				Sleep(200);
				SetColor(11, 0);
				gotoXY(14, 14);
				cout << "A[m] = v;";
				SetColor(0, 7);
				
				Sleep(200);
				SetColor(0, 7);
				gotoXY(14, 13);
				cout << "A[j] = A[m];";
				
				Sleep(200);
				SetColor(11, 0);
				gotoXY(14, 15);
				cout << "j = m;";
				SetColor(0, 7);
				
				Sleep(200);
				SetColor(0, 7);
				gotoXY(14, 14);
				cout << "A[m] = v;";
				
				swapTransition(A, j, m, y);
				A[j] = A[m];
				A[m] = v;
				j = m;
			}else{
				// deactive
				Sleep(500);
				x = 55 + j * 15;
				box(x, y, 10, 1, 7, 0, convertString(v), true, 7, 0);
				
				// deactive
				Sleep(500);
				x = 55 + m * 15;
				box(x, y, 10, 1, 7, 0, convertString(A[m]), true, 7, 0);
				
				Sleep(200);
				SetColor(11, 0);
				gotoXY(14, 17);
				cout << "return;";
				SetColor(0, 7);
				
				Sleep(200);
				SetColor(0, 7);
				gotoXY(11, 12);
				cout << "if(A[m] > v){";
				
				return;
			}
			
			Sleep(500);
			SetColor(11, 0);
			gotoXY(8, 7);
			cout << "while(2*j + 1 < n){";
			SetColor(0, 7);
			
			Sleep(200);
			SetColor(0, 7);
			gotoXY(14, 15);
			cout << "j = m;";
		}
	}else {
		while(2*j + 1 < n){
			y += 9;
			gotoXY(40, y - 4);
			cout << "Buoc " << dem << ": tim kiem khoa con lon nhat cua khoa cha A[" << j << "] (" << A[j] << ")";
			xuatInfo(A, count, 40, y);
			int jx = 55 + j * 15;
			box(jx, y, 10, 1, 14, 0, convertString(v), true, 14, 0);
			dem++;
			
			for(int k = n; k < count; k++){
				int kx = 55 + k * 15;
				box(kx, y, 10, 1, 11, 0, convertString(A[k]), true, 11, 0);
			}
			
			int m = 2*j + 1;
			if(m + 1 < n && A[m+1] > A[m]){
				m++;
			}
			
			int mx = 55 + m * 15;
			box(mx, y, 10, 1, 12, 0, convertString(A[m]), true, 12, 0);
			
			if(A[m] > v){
				y += 9;
				gotoXY(40, y - 4);
				cout << "Buoc " << dem << ": doi cho khoa cha A[" << j << "] (" << A[j] << ") va khoa con lon nhat A[" << m << "] (" << A[m] << ")";
				xuatInfo(A, count, 40, y);
				box(mx, y, 10, 1, 10, 0, convertString(v), true, 10, 0);
				box(jx, y, 10, 1, 10, 0, convertString(A[m]), true, 10, 0);
				dem++;
				
				for(int k = n; k < count; k++){
					int kx = 55 + k * 15;
					box(kx, y, 10, 1, 11, 0, convertString(A[k]), true, 11, 0);
				}
				
				A[j] = A[m];
				A[m] = v;
				j = m;
			}else{
				return;
			}
		}
	}
}


// chuc nang
void mainMenu(int A[], int &count, int chooseActive){
	// cai dat box
	int x = 65;
	int y = 8;
	int w = 50;
	int h = 1;
	int t_color = 15;
	int t_color_active = 11;
	int b_color = 0;
	int b_color_active = 11;
	bool border = true;
	int border_color = 7;
	int border_color_active = 11;
	int n = 9;
	
	string texts[n];
	texts[0] = "1. Doc file day khoa.";
	texts[1] = "2. Nhap day khoa.";
	texts[2] = "3. Hien thi day khoa.";
	texts[3] = "4. Thuat toan sap xep chon (Selection Sort).";
	texts[4] = "5. Thuat toan sap xep noi bot (Bubble Sort).";
	texts[5] = "6. Thuat toan sap xep chen (Insertion sort).";
	texts[6] = "7. Thuat toan sap xep phan doan (Quick Sort).";
	texts[7] = "8. Thuat toan sap xep vun dong (Heap Sort).";
	texts[8] = "9. Thoat.";
	
	// title
	SetColor(0, 14);
	gotoXY(73, 5);
	cout << "CHUONG TRINH MO TA THUAT TOAN SAP XEP";
	SetColor(0, 7);
	
	// luu y
	SetColor(0, 14);
	gotoXY(55, h + 2 + n *3);
	cout << "Luu y:" << endl;
	gotoXY(55, h + 3 + n *3);
	cout << "       + Bam phim mui ten len, xuong hoac phim so (1->9) de chon chuc nang." << endl;
	gotoXY(55, h + 4 + n *3);
	cout << "       + Bam phim enter de thuc hien chuc nang." << endl;
	SetColor(0, 7);
	
	// chuc nang
	n_box(x, y, w, h, t_color, b_color, texts, border, border_color, n);
	
	// active
	box(x, y + (chooseActive * (h + 1)), w, h, t_color_active, b_color, texts[chooseActive], border, border_color_active, chooseActive == 0 ? 1 : (chooseActive == n - 1 ? 3 : 2));
	
	// toa do active
	int xp = x;
	int yp = y + (chooseActive * (h + 1));
	
	// toa do cu
	int xcu = xp;
	int ycu = yp;
	
	while(true){
		// an nhap lieu
		ShowCur(false);
		
		// index
		int box_index_cu = (ycu - y)/(h + 1);
		int box_index_active = (yp - y)/(h + 1);
		
		// deactive
		box(xcu, ycu, w, h, t_color, b_color, texts[box_index_cu], border, border_color, box_index_cu == 0 ? 1 : (box_index_cu == n - 1 ? 3 : 2));
		xcu = xp;
		ycu = yp;
		
		// active
		box(xp, yp, w, h, t_color_active, b_color, texts[box_index_active], border, border_color_active, box_index_active == 0 ? 1 : (box_index_active == n - 1 ? 3 : 2));
		
		// dieu khien
		char key_press = getch();
		int key_value = (int)key_press;
		if(key_value == 72){
			if(yp != y){
				yp -= h + 1;
			}else {
				yp = y + (h + 1) * (n - 1);
			}
		} else if(key_value == 80){
			if(yp != y + (h + 1) * (n - 1)){
				yp += h + 1;
			}else {
				yp = y;
			}
		} else if(key_value >= 49 && key_value <= (n + 48)){
			yp = y + (h + 1) * (key_value - 49);
		} else if(key_value == 13){
			system("cls"); // xoa man hinh console
			
			switch(box_index_active){
				case 0: // doc file
					docFileFunc(A, count);
					break;
				case 1: // nhap
					nhapFunc(A, count);
					break;
				case 2: // xuat
					xuatFunc(A, count);
					break;
				case 3: // chon
					selectionSortFunc(A, count);
					break;
				case 4: // noi bot
					bubbleSortFunc(A, count);
					break;
				case 5: // chen
					insertionSortFunc(A, count);
					break;
				case 6: // phan doan
					quickSortFunc(A, count);
					break;
				case 7: // vun dong
					heapSortFunc(A, count);
					break;
				case 8: // ket thuc
					SetColor(0, 12);
					gotoXY(80, 18);
					cout << "CHUONG TRINH KET THUC ...";
					SetColor(0, 7);
					gotoXY(0, 34);
					break;
			}
			break;
		}
	}
}

void backOrExit(int A[], int count, int chooseActive, int x, int y){	
	string backOrEditTexts[2] = {"Quay lai.", "Thoat."};
	
	box(x, y, 15, 1, 7, 0, backOrEditTexts[0], true, 7, 0);
	box(x + 32, y, 15, 1, 7, 0, backOrEditTexts[1], true, 7, 0);
	
	// active
	box(x, y, 15, 1, 11, 0, backOrEditTexts[0], true, 11, 0);
	
	// toa do active
	int xp = x;
	int yp = y;
	
	// toa do cu
	int xcu = xp;
	int ycu = yp;
	
	while(true){
		// an nhap lieu
		ShowCur(false);
		
		// index
		int box_index_cu = (xcu - x)/32;
		int box_index_active = (xp - x)/32;
		
		// deactive
		box(xcu, ycu, 15, 1, 7, 0, backOrEditTexts[box_index_cu], true, 7, 0);
		xcu = xp;
		ycu = yp;
		
		// active
		box(xp, yp, 15, 1, box_index_active == 0 ? 11 : 12, 0, backOrEditTexts[box_index_active], true, box_index_active == 0 ? 11 : 12, 0);
		
		// dieu khien
		char key_press = getch();
		int key_value = (int)key_press;
		if(key_value == 75){
			if(xp == x){
				xp = x + 32;
			}else {
				xp -= 32;
			}
		} else if(key_value == 77){
			if(xp == x + 32){
				xp = x;
			}else {
				xp += 32;
			}
		} else if(key_value == 13){
			system("cls");
			switch(box_index_active){
				case 0:
					mainMenu(A, count, chooseActive);
					break;
				case 1:
					SetColor(0, 12);
					gotoXY(80, 18);
					cout << "CHUONG TRINH KET THUC ...";
					SetColor(0, 7);
					gotoXY(0, 34);
					break;
			}
			break;
		}
	}
}

void xuatInfo(int A[], int count, int x, int y){	
	gotoXY(x, y + 1);
	cout << "Mang: ";
	for(int i = 0; i < count; i++){
		x += 15;
		box(x + 2, y - 2, 10, 1, 7, 0, convertString(i), false, 7, 0);
		box(x, y, 10, 1, 7, 0, convertString(A[i]), true, 7, 0);
	}
}

void docFileFunc(int A[], int &count){
	count = 0;
	// config
	int x = 85;
	int y = 1;
	
	// title
	SetColor(0, 14);
	gotoXY(x, y);
	cout << "DOC FILE DAY KHOA";
	SetColor(0, 7);
	
	string linkFile = "./daykhoa_input.txt";
	gotoXY(60, y + 5);
	cout << "Duong dan den File can doc mac dinh la: " << linkFile << endl;
	ifstream fileIn; // chi doc file
	fileIn.open(linkFile.c_str()); // mo file va chuyen kieu string link file qua const char* ham .c_str()
	if(fileIn.fail()){
		SetColor(0, 12);
		gotoXY(60, y + 7);
		cout << "Khong tim thay File :(" << endl;
		SetColor(0, 7);
	}else{
		char x;
		while(true)
		{
			fileIn >> A[count++];
			fileIn >> x; // bo dau ','
			if(fileIn.eof()) break;
		}
		
		SetColor(0, 10);
		gotoXY(60, y + 7);
		cout << "Doc file thanh cong." << endl;
		SetColor(0, 7);
		//	end
	}
	// dong file
	
	fileIn.close();
	
	xuatInfo(A, count, 40, y + 15);
	backOrExit(A, count, 0, 70, y + 20);
}

void nhapFunc(int A[], int &count){
	// config
	int x = 85;
	int y = 1;
	
	// title
	SetColor(0, 14);
	gotoXY(x, y);
	cout << "NHAP DAY KHOA";
	SetColor(0, 7);
	
	x = 75;
	y += 5;
	gotoXY(x, y);
	cout << "Nhap so luong khoa:";
	box(x + 25, y - 1, 10, 1, 7, 0, "", true, 7, 0);
	
	ShowCur(true); // hien thi nhap lieu
	gotoXY(x + 30, y);
	cin >> count;
	
	y += 3;
	gotoXY(x, y);
	cout << "Nhap khoa:" << endl;
	
	for(int i = 0; i < count; i++){
		y += 3;
		gotoXY(x, y);
		cout << "A[" << i << "]:";
		box(x + 25, y - 1, 10, 1, 7, 0, "", true, 7, 0);
	}
	
	y = 9;
	for(int i = 0; i < count; i++){
		y += 3;
		gotoXY(x + 30, y);
		cin >> A[i];
	}
	
	xuatInfo(A, count, 40, y + 5);
	
	backOrExit(A, count, 1, 70, y + 10);
}

void xuatFunc(int A[], int count){
	// config
	int x = 85;
	int y = 1;
	
	// title
	SetColor(0, 14);
	gotoXY(x, y);
	cout << "HIEN THI DAY KHOA";
	SetColor(0, 7);
	
	if(count == 0){
		SetColor(0, 12);
		gotoXY(85, y + 5);
		cout << "DAY KHOA RONG ...";
		SetColor(0, 7);
	}else{
		xuatInfo(A, count, 40, y + 5);
	}
	
	backOrExit(A, count, 2, 70, y + 10);
}

void selectionSortFunc(int A[], int count){
	// config
	int x = 70;
	int y = 1;
	
	// title
	SetColor(0, 14);
	gotoXY(x, y);
	cout << "MO TA THUAT TOAN SAP XEP CHON (SELECTION SORT)";
	SetColor(0, 7);
	
	if(count == 0){
		SetColor(0, 12);
		gotoXY(85, y + 5);
		cout << "DAY KHOA RONG ...";
		SetColor(0, 7);
	}else{
		int choose = movementOrSteps();
		
		if(choose == 0){
			gotoXY(5, 4);
			cout << "void selectionSortFunc(int A[], int count){";
			gotoXY(8, 5);
			cout << "for(int i = 0; i < count - 1; i++){";
			gotoXY(11, 6);
			cout << "int min = i;";
			gotoXY(11, 7);
			cout << "for(int j = i + 1; j < count; j++){";
			gotoXY(14, 8);
			cout << "if(A[j] < A[min]){";
			gotoXY(17, 9);
			cout << "min = j;";
			gotoXY(14, 10);
			cout << "}";
			gotoXY(11, 11);
			cout << "}";
			gotoXY(11, 12);
			cout << "if(min != i){";
			gotoXY(14, 13);
			cout << "swap(A[i], A[min]);";
			gotoXY(11, 14);
			cout << "}";
			gotoXY(8, 15);
			cout << "}";
			gotoXY(5, 16);
			cout << "}";
			
			gotoXY(60, y + 5);
			cout << "Ghi chu:";
			
			gotoXY(60, y + 6);
			cout << "        + ";
			SetColor(0, 12);
			cout << "Mau do: ";
			SetColor(0, 7);
			cout << "tim kiem gia tri nho nhat (min).";
			
			gotoXY(60, y + 7);
			cout << "        + ";
			SetColor(0, 14);
			cout << "Mau vang: ";
			SetColor(0, 7);
			cout << "gia tri nho nhat (min).";
			
			gotoXY(60, y + 8);
			cout << "        + ";
			SetColor(0, 11);
			cout << "Mau xanh duong: ";
			SetColor(0, 7);
			cout << "gia tri da sap xep dung vi tri.";
			
			gotoXY(60, y + 9);
			cout << "        + ";
			SetColor(0, 10);
			cout << "Mau xanh la cay: ";
			SetColor(0, 7);
			cout << "gia tri duoc doi cho.";
			
			gotoXY(60, y + 13);
			cout << "Hanh dong: ";
					
			y += 20;
			xuatInfo(A, count, 40, y);
			
			gotoXY(72, y - 7);
			cout << "bat dau";
			Sleep(500);
			
			Sleep(200);
			SetColor(11, 0);
			gotoXY(8, 5);
			cout << "for(int i = 0; i < count - 1; i++){";
			SetColor(0, 7);
		
			for(int i = 0; i < count; i++){
				Sleep(200);
				// vi tri hien tai
				x = 55 + i * 15;
				gotoXY(x + 2, y - 1);
				cout << char(175) << char(175) << char(175) << char(175) << char(175) << char(175) << char(175);
				
				if(i > 0){
					Sleep(200);
					x = 55 + (i - 1) * 15;
					gotoXY(x + 2, y - 1);
					cout << "       ";
					
					box(x, y, 10, 1, 11, 0, convertString(A[i - 1]), true, 11, 0);
				}
				
				int min = i;
				gotoXY(72, y - 7);
				cout << "                                                   ";
				
				Sleep(200);
				gotoXY(72, y - 7);
				cout << "min: A[" << min << "] (" << A[min] << ")";
				
				Sleep(500);
				SetColor(11, 0);
				gotoXY(11, 6);
				cout << "int min = i;";
				SetColor(0, 7);
				
				Sleep(200);
				SetColor(0, 7);
				gotoXY(8, 5);
				cout << "for(int i = 0; i < count - 1; i++){";
				
				Sleep(200);
				SetColor(11, 0);
				gotoXY(11, 7);
				cout << "for(int j = i + 1; j < count; j++){";
				SetColor(0, 7);
				
				Sleep(200);
				SetColor(0, 7);
				gotoXY(11, 6);
				cout << "int min = i;";
				
				for(int j = i + 1; j < count; j++){				
					gotoXY(72, y - 7);
					cout << "                                                   ";
					
					Sleep(200);
					gotoXY(72, y - 7);
					cout << "tim min (" << j << "->" << count - 1 << ")";
					
					Sleep(500);
					if(j - 1 != min){
						// deactive
						x = 55 + (j - 1) * 15;
						box(x, y, 10, 1, 7, 0, convertString(A[j - 1]), true, 7, 0);
					}else {
						// deactive
						x = 55 + (j - 1) * 15;
						box(x, y, 10, 1, 14, 0, convertString(A[j - 1]), true, 14, 0);
					}
					
					Sleep(500);
					// active
					x = 55 + j * 15;
					box(x, y, 10, 1, 12, 0, convertString(A[j]), true, 12, 0);
					
					Sleep(200);
					SetColor(11, 0);
					gotoXY(14, 8);
					cout << "if(A[j] < A[min]){";
					SetColor(0, 7);
					
					Sleep(200);
					SetColor(0, 7);
					gotoXY(11, 7);
					cout << "for(int j = i + 1; j < count; j++){";
						
					if(A[j] < A[min]){					
						Sleep(500);
						// deactive
						x = 55 + min * 15;
						box(x, y, 10, 1, 7, 0, convertString(A[min]), true, 7, 0);
						
						min = j;
						
						gotoXY(72, y - 7);
						cout << "                                                   ";
						
						Sleep(200);
						gotoXY(72, y - 7);
						cout << "min: A[" << min << "] (" << A[min] << ")";
						
						Sleep(200);
						SetColor(11, 0);
						gotoXY(17, 9);
						cout << "min = j;";
						SetColor(0, 7);
						
						Sleep(200);
						SetColor(0, 7);
						gotoXY(14, 8);
						cout << "if(A[j] < A[min]){";
						
						Sleep(500);
						// active
						x = 55 + min * 15;
						box(x, y, 10, 1, 14, 0, convertString(A[min]), true, 14, 0);
					}
					
					Sleep(500);
					SetColor(11, 0);
					gotoXY(11, 7);
					cout << "for(int j = i + 1; j < count; j++){";
					SetColor(0, 7);
					
					Sleep(200);
					SetColor(0, 7);
					gotoXY(14, 8);
					cout << "if(A[j] < A[min]){";
					
					Sleep(200);
					SetColor(0, 7);
					gotoXY(17, 9);
					cout << "min = j;";
					
					Sleep(200);
					SetColor(0, 7);
					gotoXY(11, 6);
					cout << "int min = i;";
				}
				
				Sleep(500);
				if(count - 1 != min){
					// deactive
					x = 55 + (count - 1) * 15;
					box(x, y, 10, 1, 7, 0, convertString(A[count - 1]), true, 7, 0);
				}else {
					// deactive
					x = 55 + (count - 1) * 15;
					box(x, y, 10, 1, 14, 0, convertString(A[count - 1]), true, 14, 0);
					
					Sleep(200);
					SetColor(0, 7);
					gotoXY(11, 7);
					cout << "for(int j = i + 1; j < count; j++){";
				}

				Sleep(500);			
				SetColor(11, 0);
				gotoXY(11, 12);
				cout << "if(min != i){";
				SetColor(0, 7);
				
				Sleep(300);
				SetColor(0, 7);
				gotoXY(11, 7);
				cout << "for(int j = i + 1; j < count; j++){";
				
				if(min != i){
					gotoXY(72, y - 7);
					cout << "                                                   ";
					
					Sleep(200);
					gotoXY(72, y - 7);
					cout << "doi cho A[" << i << "] (" << A[i] << ") va A[" << min << "] (" << A[min] << ")";
					
					Sleep(200);
					SetColor(11, 0);
					gotoXY(14, 13);
					cout << "swap(A[i], A[min]);";
					SetColor(0, 7);
					
					Sleep(200);	
					SetColor(0, 7);
					gotoXY(11, 12);
					cout << "if(min != i){";
					
					swapTransition(A, i, min, y);
					swap(A[i], A[min]);
				}
				
				Sleep(200);
				SetColor(11, 0);
				gotoXY(8, 5);
				cout << "for(int i = 0; i < count - 1; i++){";
				SetColor(0, 7);
				
				Sleep(200);
				SetColor(0, 7);
				gotoXY(11, 12);
				cout << "if(min != i){";
				
				Sleep(200);
				SetColor(0, 7);
				gotoXY(14, 13);
				cout << "swap(A[i], A[min]);";
			}
			
			Sleep(200);
			SetColor(0, 7);
			gotoXY(8, 5);
			cout << "for(int i = 0; i < count - 1; i++){";
			
			Sleep(200);
			x = 55 + (count - 1) * 15;
			gotoXY(x + 2, y - 1);
			cout << "       ";
			box(x, y, 10, 1, 11, 0, convertString(A[count - 1]), true, 11, 0);
			
			gotoXY(72, y - 7);
			cout << "                                                   ";
			
			Sleep(200);
			gotoXY(72, y - 7);
			cout << "hoan thanh";
		}else {
			gotoXY(60, y + 5);
			cout << "Ghi chu:";
			
			gotoXY(60, y + 6);
			cout << "        + ";
			SetColor(0, 12);
			cout << "Mau do: ";
			SetColor(0, 7);
			cout << "gia tri nho nhat (min).";
			
			gotoXY(60, y + 7);
			cout << "        + ";
			SetColor(0, 11);
			cout << "Mau xanh duong: ";
			SetColor(0, 7);
			cout << "gia tri da sap xep dung vi tri.";
			
			gotoXY(60, y + 8);
			cout << "        + ";
			SetColor(0, 10);
			cout << "Mau xanh la cay: ";
			SetColor(0, 7);
			cout << "gia tri duoc doi cho.";
			
			y += 15;
			xuatInfo(A, count, 40, y);
			
			int dem = 1;
			for(int i = 0; i < count - 1; i++){
				int min = i;
				for(int j = i + 1; j < count; j++){
					if(A[j] < A[min]){
						min = j;
					}
				}
				if(min != i){
					y += 9;
					gotoXY(40, y - 4);
					cout << "Buoc " << dem << ": tim min trong doan " << i << "->" << count - 1;
					xuatInfo(A, count, 40, y);
					int mx = 55 + min * 15;
					box(mx, y, 10, 1, 12, 0, convertString(A[min]), true, 12, 0);
					dem++;
					
					y += 9;
					gotoXY(40, y - 4);
					cout << "Buoc " << dem << ": doi cho A[" << i << "] (" << A[i] << ") va A[" << min << "] (" << A[min] << ")";
					xuatInfo(A, count, 40, y);
					int ix = 55 + i * 15;
					box(ix, y, 10, 1, 10, 0, convertString(A[min]), true, 10, 0);
					box(mx, y, 10, 1, 10, 0, convertString(A[i]), true, 10, 0);
					dem++;
					
					swap(A[i], A[min]);
				}
				
				int vtActive = (dem - 3)/2 - 1;
				for(int iac = 0; iac <= vtActive; iac++){
					int ix = 55 + iac * 15;
					box(ix, y - 9, 10, 1, 11, 0, convertString(A[iac]), true, 11, 0);
					box(ix, y, 10, 1, 11, 0, convertString(A[iac]), true, 11, 0);
				}
			}
			
			y += 9;
			gotoXY(40, y - 4);
			cout << "Hoan thanh";
			xuatInfo(A, count, 40, y);
		}
	}

	backOrExit(A, count, 3, 70, y + 10);
}

void bubbleSortFunc(int A[], int count){
	// config
	int x = 70;
	int y = 1;
	
	// title
	SetColor(0, 14);
	gotoXY(x, y);
	cout << "MO TA THUAT TOAN SAP XEP NOI BOT (BUBBLE SORT)";
	SetColor(0, 7);
	
	if(count == 0){
		SetColor(0, 12);
		gotoXY(85, y + 5);
		cout << "DAY KHOA RONG ...";
		SetColor(0, 7);
	}else{
		int choose = movementOrSteps();
		
		if(choose == 0){
			gotoXY(5, 4);
			cout << "void bubbleSortFunc(int A[], int count){";
			gotoXY(8, 5);
			cout << "for(int i = 0; i < count - 1; i++){";
			gotoXY(11, 6);
			cout << "for(int j = count - 1; j > i; j--){";
			gotoXY(14, 7);
			cout << "if(A[j] < A[j - 1]){";
			gotoXY(17, 8);
			cout << "swap(A[j], A[j - 1]);";
			gotoXY(14, 9);
			cout << "}";
			gotoXY(11, 10);
			cout << "}";
			gotoXY(8, 11);
			cout << "}";
			gotoXY(5, 12);
			cout << "}";
			
			gotoXY(60, y + 5);
			cout << "Ghi chu:";
			
			gotoXY(60, y + 6);
			cout << "        + ";
			SetColor(0, 12);
			cout << "Mau do: ";
			SetColor(0, 7);
			cout << "tim kiem cap gia tri sai vi tri.";
			
			gotoXY(60, y + 7);
			cout << "        + ";
			SetColor(0, 11);
			cout << "Mau xanh duong: ";
			SetColor(0, 7);
			cout << "gia tri da sap xep dung vi tri.";
			
			gotoXY(60, y + 8);
			cout << "        + ";
			SetColor(0, 10);
			cout << "Mau xanh la cay: ";
			SetColor(0, 7);
			cout << "gia tri duoc doi cho.";
			
			gotoXY(60, y + 13);
			cout << "Hanh dong: ";
					
			y += 20;
			xuatInfo(A, count, 40, y);
			
			gotoXY(72, y - 7);
			cout << "bat dau";
			Sleep(500);
			
			Sleep(200);
			SetColor(11, 0);
			gotoXY(8, 5);
			cout << "for(int i = 0; i < count - 1; i++){";
			SetColor(0, 7);
			
			for(int i = 0; i < count - 1; i++){
				Sleep(500);
				SetColor(11, 0);
				gotoXY(11, 6);
				cout << "for(int j = count - 1; j > i; j--){";
				SetColor(0, 7);
				
				Sleep(200);
				SetColor(0, 7);
				gotoXY(8, 5);
				cout << "for(int i = 0; i < count - 1; i++){";
				
				for(int j = count - 1; j > i; j--){
					gotoXY(72, y - 7);
					cout << "                                                   ";
					
					Sleep(200);
					gotoXY(72, y - 7);
					cout << "tim kiem cap gia tri sai vi tri (" << j << "->" << i + 1 << ")";
							
					Sleep(200);
					// vi tri hien tai
					x = 55 + j * 15;
					gotoXY(x + 2, y - 1);
					cout << char(174) << char(174) << char(174) << char(174) << char(174) << char(174) << char(174);
					
					if(j + 1 < count){
						Sleep(200);
						// deactive
						x = 55 + (j + 1) * 15;
						gotoXY(x + 2, y - 1);
						cout << "       ";
						box(x, y, 10, 1, 7, 0, convertString(A[j + 1]), true, 7, 0);
						
						Sleep(200);
						// deactive
						x = 55 + (j) * 15;
						box(x, y, 10, 1, 7, 0, convertString(A[j]), true, 7, 0);
					}
					
					Sleep(500);
					// active
					x = 55 + j * 15;
					box(x, y, 10, 1, 12, 0, convertString(A[j]), true, 12, 0);
					
					Sleep(500);
					// active
					x = 55 + (j - 1) * 15;
					box(x, y, 10, 1, 12, 0, convertString(A[j - 1]), true, 12, 0);
					
					Sleep(200);
					SetColor(11, 0);
					gotoXY(14, 7);
					cout << "if(A[j] < A[j - 1]){";
					SetColor(0, 7);
					
					Sleep(200);
					SetColor(0, 7);
					gotoXY(11, 6);
					cout << "for(int j = count - 1; j > i; j--){";
					
					if(A[j] < A[j - 1]){
						gotoXY(72, y - 7);
						cout << "                                                   ";
						
						Sleep(200);
						gotoXY(72, y - 7);
						cout << "cap gia tri sai vi tri A[" << j - 1 << "] (" << A[j - 1] << ") va A[" << j << "] (" << A[j] << ")";
						
						Sleep(700);
						gotoXY(72, y - 7);
						cout << "                                                   ";
						
						Sleep(200);
						gotoXY(72, y - 7);
						cout << "doi cho A[" << j - 1 << "] (" << A[j - 1] << ") va A[" << j << "] (" << A[j] << ")";
						
						Sleep(200);
						SetColor(11, 0);
						gotoXY(17, 8);
						cout << "swap(A[j], A[j - 1]);";
						SetColor(0, 7);
						
						Sleep(200);
						SetColor(0, 7);
						gotoXY(14, 7);
						cout << "if(A[j] < A[j - 1]){";
						
						swapTransition(A, j - 1, j, y);
						swap(A[j], A[j - 1]);
					}
					
					Sleep(500);
					SetColor(11, 0);
					gotoXY(11, 6);
					cout << "for(int j = count - 1; j > i; j--){";
					SetColor(0, 7);
					
					Sleep(200);
					SetColor(0, 7);
					gotoXY(14, 7);
					cout << "if(A[j] < A[j - 1]){";
					
					Sleep(200);
					SetColor(0, 7);
					gotoXY(17, 8);
					cout << "swap(A[j], A[j - 1]);";
				}
				
				Sleep(200);
				// deactive
				x = 55 + (i + 1) * 15;
				gotoXY(x + 2, y - 1);
				cout << "       ";
				box(x, y, 10, 1, 7, 0, convertString(A[i + 1]), true, 7, 0);
				
				Sleep(500);
				// active
				x = 55 + i * 15;
				box(x, y, 10, 1, 11, 0, convertString(A[i]), true, 11, 0);
				
				Sleep(500);
				SetColor(11, 0);
				gotoXY(8, 5);
				cout << "for(int i = 0; i < count - 1; i++){";
				SetColor(0, 7);
				
				Sleep(500);
				SetColor(0, 7);
				gotoXY(11, 6);
				cout << "for(int j = count - 1; j > i; j--){";
			}
			
			Sleep(500);
			SetColor(0, 7);
			gotoXY(8, 5);
			cout << "for(int i = 0; i < count - 1; i++){";
			
			Sleep(500);
			// active
			x = 55 + (count - 1) * 15;
			box(x, y, 10, 1, 11, 0, convertString(A[count - 1]), true, 11, 0);
			
			gotoXY(72, y - 7);
			cout << "                                                   ";
			
			Sleep(200);
			gotoXY(72, y - 7);
			cout << "hoan thanh";
		}else{
			gotoXY(60, y + 5);
			cout << "Ghi chu:";
			
			gotoXY(60, y + 6);
			cout << "        + ";
			SetColor(0, 12);
			cout << "Mau do: ";
			SetColor(0, 7);
			cout << "cap gia tri sai vi tri.";
			
			gotoXY(60, y + 7);
			cout << "        + ";
			SetColor(0, 11);
			cout << "Mau xanh duong: ";
			SetColor(0, 7);
			cout << "gia tri da sap xep dung vi tri.";
			
			gotoXY(60, y + 8);
			cout << "        + ";
			SetColor(0, 10);
			cout << "Mau xanh la cay: ";
			SetColor(0, 7);
			cout << "gia tri duoc doi cho.";
			
			y += 15;
			xuatInfo(A, count, 40, y);
			
			int dem = 1;
			for(int i = 0; i < count - 1; i++){
				for(int j = count - 1; j > i; j--){
					if(A[j] < A[j - 1]){
						y += 9;
						gotoXY(40, y - 4);
						cout << "Buoc " << dem << ": tim cap gia tri sai vi tri trong doan " << count - 1 << "->" << i + 1;
						xuatInfo(A, count, 40, y);
						int j1x = 55 + (j - 1) * 15;
						box(j1x, y, 10, 1, 12, 0, convertString(A[j - 1]), true, 12, 0);
						int j2x = 55 + j * 15;
						box(j2x, y, 10, 1, 12, 0, convertString(A[j]), true, 12, 0);
						dem++;
						Sleep(200);
						
						y += 9;
						gotoXY(40, y - 4);
						cout << "Buoc " << dem << ": doi cho A[" << j << "] (" << A[j] << ") va A[" << j - 1 << "] (" << A[j - 1] << ")";
						xuatInfo(A, count, 40, y);
						box(j1x, y, 10, 1, 10, 0, convertString(A[j]), true, 10, 0);
						box(j2x, y, 10, 1, 10, 0, convertString(A[j - 1]), true, 10, 0);
						dem++;
						
						if(i != 0){
							for(int iac = 0; iac <= i; iac++){
								int ix = 55 + iac * 15;
								box(ix, y - 9, 10, 1, 11, 0, convertString(A[iac]), true, 11, 0);
								box(ix, y, 10, 1, 11, 0, convertString(A[iac]), true, 11, 0);
							}
						}
						
						swap(A[j], A[j - 1]);
					}
				}
			}
			
			y += 9;
			gotoXY(40, y - 4);
			cout << "Hoan thanh";
			xuatInfo(A, count, 40, y);
		}
	}
	
	backOrExit(A, count, 4, 70, y + 10);
}

void insertionSortFunc(int A[], int count) {
	// config
	int x = 70;
	int y = 1;
	
	// title
	SetColor(0, 14);
	gotoXY(x, y);
	cout << "MO TA THUAT TOAN SAP XEP CHEN (INSERTION SORT)";
	SetColor(0, 7);
	
	if(count == 0){
		SetColor(0, 12);
		gotoXY(85, y + 5);
		cout << "DAY KHOA RONG ...";
		SetColor(0, 7);
	}else{
		int choose = movementOrSteps();
		
		if(choose == 0){
			gotoXY(5, 4);
			cout << "void insertionSortFunc(int A[], int count){";
			gotoXY(8, 5);
			cout << "for(int i = 1; i < count; i++){";
			gotoXY(11, 6);
			cout << "int temp = A[i];";
			gotoXY(11, 7);
			cout << "int j = i - 1;";
			gotoXY(11, 8);
			cout << "while(j >= 0 && temp < A[j]){";
			gotoXY(14, 9);
			cout << "A[j + 1] = A[j];";
			gotoXY(14, 10);
			cout << "j -= 1;";
			gotoXY(11, 11);
			cout << "}";
			gotoXY(11, 12);
			cout << "A[j + 1] = temp;";
			gotoXY(8, 13);
			cout << "}";
			gotoXY(5, 14);
			cout << "}";
			
			gotoXY(60, y + 5);
			cout << "Ghi chu:";
			
			gotoXY(60, y + 6);
			cout << "        + ";
			SetColor(0, 12);
			cout << "Mau do: ";
			SetColor(0, 7);
			cout << "tim kiem gia tri nho hon gia tri truoc do.";
			
			gotoXY(60, y + 7);
			cout << "        + ";
			SetColor(0, 14);
			cout << "Mau vang: ";
			SetColor(0, 7);
			cout << "gia tri lon hon gia tri chen.";
			
			gotoXY(60, y + 8);
			cout << "        + ";
			SetColor(0, 10);
			cout << "Mau xanh la cay: ";
			SetColor(0, 7);
			cout << "gia tri chen.";
					
			gotoXY(60, y + 13);
			cout << "Hanh dong: ";
					
			y += 20;
			xuatInfo(A, count, 40, y);
			
			gotoXY(72, y - 7);
			cout << "bat dau";
			Sleep(500);
			
			Sleep(200);
			SetColor(11, 0);
			gotoXY(8, 5);
			cout << "for(int i = 1; i < count; i++){";
			SetColor(0, 7);
			
			for(int i = 1; i < count; i++){		
				int temp = A[i];
				
				Sleep(500);
				SetColor(11, 0);
				gotoXY(11, 6);
				cout << "int temp = A[i];";
				SetColor(0, 7);
				
				Sleep(200);
				SetColor(0, 7);
				gotoXY(8, 5);
				cout << "for(int i = 1; i < count; i++){";
				
				int j = i - 1;
				
				Sleep(500);
				SetColor(11, 0);
				gotoXY(11, 7);
				cout << "int j = i - 1;";
				SetColor(0, 7);
				
				Sleep(200);
				SetColor(0, 7);
				gotoXY(11, 6);
				cout << "int temp = A[i];";
				
				// active
				Sleep(500);
				x = 55 + i * 15;
				box(x, y, 10, 1, 12, 0, convertString(temp), true, 12, 0);
				
				gotoXY(72, y - 7);
				cout << "                                                   ";
					
				Sleep(200);
				gotoXY(72, y - 7);
				cout << "tim kiem gia tri nho gia tri truoc do (" << i << "->" << count - 1 << ")";
				
				Sleep(200);
				SetColor(11, 0);
				gotoXY(11, 8);
				cout << "while(j >= 0 && temp < A[j]){";
				SetColor(0, 7);
				
				Sleep(200);
				SetColor(0, 7);
				gotoXY(11, 7);
				cout << "int j = i - 1;";
				
				if(j >= 0 && temp < A[j]){			
					Sleep(500);
					x = 55 + i * 15;
					box(x, y + 3, 10, 1, 10, 0, convertString(temp), true, 10, 0);
					
					Sleep(100);
					for(int iy = y; iy <= y + 2; iy++){
						gotoXY(x, iy);
						cout << "              ";
					}
					
					gotoXY(72, y - 7);
					cout << "                                                   ";
					
					Sleep(200);
					gotoXY(72, y - 7);
					cout << "gia tri nho gia tri truoc do A[" << i << "] (" << A[i] << ")";
					Sleep(500);
				}
				
				Sleep(500);
				SetColor(11, 0);
				gotoXY(11, 8);
				cout << "while(j >= 0 && temp < A[j]){";
				SetColor(0, 7);
				
				while(j >= 0 && temp < A[j]){		
					gotoXY(72, y - 7);
					cout << "                                                   ";
					
					Sleep(200);
					gotoXY(72, y - 7);
					cout << "day gia tri A[" << j << "] (" << A[j] << ") len truoc 1 vi tri";
					
					Sleep(500);
					x = 55 + j * 15;
					box(x, y, 10, 1, 14, 0, convertString(A[j]), true, 14, 0);
					
					Sleep(200);
					SetColor(11, 0);
					gotoXY(14, 9);
					cout << "A[j + 1] = A[j];";
					SetColor(0, 7);
					
					Sleep(200);
					SetColor(0, 7);
					gotoXY(11, 8);
					cout << "while(j >= 0 && temp < A[j]){";
								
					// tao khoang trong
					Sleep(500);
					x = 55 + (j + 1) * 15;
					box(x, y, 10, 1, 14, 0, convertString(A[j]), true, 14, 0);
					
					Sleep(500);
					x = 55 + j * 15;
					for(int iy = y; iy <= y + 2; iy++){
						gotoXY(x, iy);
						cout << "              ";
					}
					
					Sleep(500);
					x = 55 + (j + 1) * 15;
					box(x, y, 10, 1, 7, 0, convertString(A[j]), true, 7, 0);
					
					A[j + 1] = A[j];
					
					j -= 1;
					
					Sleep(500);
					SetColor(11, 0);
					gotoXY(14, 10);
					cout << "j -= 1;";
					SetColor(0, 7);
					
					Sleep(200);
					SetColor(0, 7);
					gotoXY(14, 9);
					cout << "A[j + 1] = A[j];";
					
					Sleep(500);
					SetColor(11, 0);
					gotoXY(11, 8);
					cout << "while(j >= 0 && temp < A[j]){";
					SetColor(0, 7);
					
					Sleep(200);
					SetColor(0, 7);
					gotoXY(14, 10);
					cout << "j -= 1;";
				}
				
				Sleep(500);
				SetColor(11, 0);
				gotoXY(11, 12);
				cout << "A[j + 1] = temp;";
				SetColor(0, 7);
				
				if(j < 0 || temp > A[j]){
					Sleep(200);
					SetColor(0, 7);
					gotoXY(11, 8);
					cout << "while(j >= 0 && temp < A[j]){";
				}
				
				Sleep(200);
				SetColor(0, 7);
				gotoXY(14, 10);
				cout << "j -= 1;";
				
				if(A[j + 1] != temp){
					gotoXY(72, y - 7);
					cout << "                                                   ";
					
					Sleep(200);
					gotoXY(72, y - 7);
					cout << "chen A[" << i << "] (" << A[i] << ") vao vi tri trong";
					
					x = 55 + (j + 1) * 15;
					int tempx = 55 + i * 15;
					for(int ix = tempx; ix >= x; ix -= 15){
						Sleep(100);
						for(int k = y + 3; k <= y + 5; k++){
							gotoXY(ix + 15, k);
							cout << "              ";
						}
						Sleep(100);
						box(ix, y + 3, 10, 1, 10, 0, convertString(temp), true, 10, 0);
					}
					
					Sleep(100);
					box(x, y, 10, 1, 10, 0, convertString(temp), true, 10, 0);
					
					Sleep(100);
					for(int k = y + 3; k <= y + 5; k++){
						gotoXY(x, k);
						cout << "              ";
					}
					
					Sleep(500);
					box(x, y, 10, 1, 7, 0, convertString(temp), true, 7, 0);
				}
				
				A[j + 1] = temp;
				
				// deactive
				Sleep(500);
				x = 55 + i * 15;
				box(x, y, 10, 1, 7, 0, convertString(A[i]), true, 7, 0);
				
				Sleep(500);
				SetColor(11, 0);
				gotoXY(8, 5);
				cout << "for(int i = 1; i < count; i++){";
				SetColor(0, 7);
				
				Sleep(200);
				SetColor(0, 7);
				gotoXY(11, 12);
				cout << "A[j + 1] = temp;";
			}
			
			Sleep(200);
			SetColor(0, 7);
			gotoXY(8, 5);
			cout << "for(int i = 1; i < count; i++){";
		
			gotoXY(72, y - 7);
			cout << "                                                   ";
			
			Sleep(200);
			gotoXY(72, y - 7);
			cout << "hoan thanh";
		}else {
			gotoXY(60, y + 5);
			cout << "Ghi chu:";
			
			gotoXY(60, y + 6);
			cout << "        + ";
			SetColor(0, 12);
			cout << "Mau do: ";
			SetColor(0, 7);
			cout << "gia tri nho hon gia tri truoc no.";
			
			gotoXY(60, y + 7);
			cout << "        + ";
			SetColor(0, 14);
			cout << "Mau vang: ";
			SetColor(0, 7);
			cout << "gia tri lon hon gia tri chen.";
			
			gotoXY(60, y + 8);
			cout << "        + ";
			SetColor(0, 10);
			cout << "Mau xanh la cay: ";
			SetColor(0, 7);
			cout << "gia tri chen.";
			
			y += 15;
			xuatInfo(A, count, 40, y);
			
			int dem = 1;
			for(int i = 1; i < count; i++){
				int temp = A[i];
				int j = i - 1;
				
				if(j >= 0 && temp < A[j]){
					y += 9;
					gotoXY(40, y - 4);
					cout << "Buoc " << dem << ": tim gia tri nho hon gia tri truoc no trong doan " << i << "->" << count - 1;
					xuatInfo(A, count, 40, y);
					int ix = 55 + i * 15;
					box(ix, y, 10, 1, 12, 0, convertString(A[i]), true, 12, 0);
					dem++;
					
					y += 9;
					gotoXY(40, y - 4);
					cout << "Buoc " << dem << ": day cac gia tri lon hon gia tri chen A["  << i << "] (" << temp << ") len 1 vi tri va chen A["  << i << "] (" << temp << ") vao vi tri trong";
					xuatInfo(A, count, 40, y);
					dem++;
				}
				
				while(j >= 0 && temp < A[j]){
					int jx = 55 + (j + 1) * 15;
					box(jx, y, 10, 1, 14, 0, convertString(A[j]), true, 14, 0);
					
					A[j + 1] = A[j];
					j -= 1;
				}
				
				if(j + 1 >= 0 && temp < A[j + 1]){
					int jx = 55 + (j + 1) * 15;
					box(jx, y, 10, 1, 10, 0, convertString(temp), true, 10, 0);
				}

				A[j + 1] = temp;
			}
			
			y += 9;
			gotoXY(40, y - 4);
			cout << "Hoan thanh";
			xuatInfo(A, count, 40, y);
		}
	}
	
	backOrExit(A, count, 5, 70, y + 10);
}

void quickSortFunc(int A[], int count){
	// config
	int x = 70;
	int y = 1;
	
	// title
	SetColor(0, 14);
	gotoXY(x, y);
	cout << "MO TA THUAT TOAN SAP XEP PHAN DOAN (QUICK SORT)";
	SetColor(0, 7);
	
	int dem = 1;
	if(count == 0){
		SetColor(0, 12);
		gotoXY(85, y + 5);
		cout << "DAY KHOA RONG ...";
		SetColor(0, 7);
	}else{
		int choose = movementOrSteps();
		
		if(choose == 0){
			gotoXY(5, 4);
			cout << "void quickSortFunc(int A[], int l, int r){";
			gotoXY(8, 5);
			cout << "if(l >= r) return;";
			gotoXY(8, 6);
			cout << "int i = l, j = r;";
			gotoXY(8, 7);
			cout << "int chot = A[random(l, r)];";
			gotoXY(8, 8);
			cout << "while(i <= j){";
			gotoXY(11, 9);
			cout << "while(A[i] < chot){";
			gotoXY(14, 10);
			cout << "i++;";
			gotoXY(11, 11);
			cout << "}";
			gotoXY(11, 12);
			cout << "while(A[j] > chot){";
			gotoXY(14, 13);
			cout << "j--;";
			gotoXY(11, 14);
			cout << "}";
			gotoXY(11, 15);
			cout << "if(i < j){";
			gotoXY(14, 16);
			cout << "swap(A[i], A[j]);";
			gotoXY(11, 17);
			cout << "}";
			gotoXY(11, 18);
			cout << "if(i <= j){";
			gotoXY(14, 19);
			cout << "i++;";
			gotoXY(14, 20);
			cout << "j--;";
			gotoXY(11, 21);
			cout << "}";
			gotoXY(8, 22);
			cout << "}";
			gotoXY(8, 23);
			cout << "quickSortFunc(A, l, j);";
			gotoXY(8, 24);
			cout << "quickSortFunc(A, i, r);";				
			gotoXY(5, 25);
			cout << "}";
			
			gotoXY(60, y + 5);
			cout << "Ghi chu:";
			
			gotoXY(60, y + 6);
			cout << "        + ";
			SetColor(0, 12);
			cout << "Mau do: ";
			SetColor(0, 7);
			cout << "tim kiem gia tri sai vi tri so voi chot.";
			
			gotoXY(60, y + 7);
			cout << "        + ";
			SetColor(0, 14);
			cout << "Mau vang: ";
			SetColor(0, 7);
			cout << "gia tri dat lam chot.";
			
			gotoXY(60, y + 8);
			cout << "        + ";
			SetColor(0, 10);
			cout << "Mau xanh la cay: ";
			SetColor(0, 7);
			cout << "gia tri duoc doi cho.";
			
			gotoXY(60, y + 9);
			cout << "        + ";
			SetColor(0, 8);
			cout << "Mau xam: ";
			SetColor(0, 7);
			cout << "cac gia tri khong duoc xet.";
					
			gotoXY(60, y + 13);
			cout << "Hanh dong: ";
					
			y += 20;
			xuatInfo(A, count, 40, y);
			
			gotoXY(72, y - 7);
			cout << "bat dau";
			Sleep(500);
			
			quickSort(A, count, 0, count - 1, x, y, "movement", dem);
			
			Sleep(300);
			SetColor(0, 7);
			gotoXY(8, 24);
			cout << "quickSortFunc(A, i, r);";
			
			xuatInfo(A, count, 40, y);
			
			gotoXY(72, y - 7);
			cout << "                                                   ";
			
			Sleep(200);
			gotoXY(72, y - 7);
			cout << "hoan thanh";
		}else {
			gotoXY(60, y + 5);
			cout << "Ghi chu:";
			
			gotoXY(60, y + 6);
			cout << "        + ";
			SetColor(0, 12);
			cout << "Mau do: ";
			SetColor(0, 7);
			cout << "gia tri sai vi tri so voi chot.";
			
			gotoXY(60, y + 7);
			cout << "        + ";
			SetColor(0, 14);
			cout << "Mau vang: ";
			SetColor(0, 7);
			cout << "gia tri dat lam chot.";
			
			gotoXY(60, y + 8);
			cout << "        + ";
			SetColor(0, 10);
			cout << "Mau xanh la cay: ";
			SetColor(0, 7);
			cout << "gia tri duoc doi cho.";
			
			gotoXY(60, y + 9);
			cout << "        + ";
			SetColor(0, 8);
			cout << "Mau xam: ";
			SetColor(0, 7);
			cout << "cac gia tri khong duoc xet.";
			
			y += 15;
			xuatInfo(A, count, 40, y);
			
			quickSort(A, count, 0, count - 1, x, y, "steps", dem);
			
			y += 9;
			gotoXY(40, y - 4);
			cout << "Hoan thanh";
			xuatInfo(A, count, 40, y);
		}
	}
	
	backOrExit(A, count, 6, 70, y + 10);
}

void heapSortFunc(int A[], int count){
	// config
	int x = 70;
	int y = 1;
	
	// title
	SetColor(0, 14);
	gotoXY(x, y);
	cout << "MO TA THUAT TOAN SAP XEP VUN DONG (HEAP SORT)";
	SetColor(0, 7);
	
	int dem = 1;
	if(count == 0){
		SetColor(0, 12);
		gotoXY(85, y + 5);
		cout << "DAY KHOA RONG ...";
		SetColor(0, 7);
	}else{
		int choose = movementOrSteps();
		
		if(choose == 0){
			gotoXY(5, 4);
			cout << "void vundong(int A[], int n, int r){";
			gotoXY(8, 5);
			cout << "int j = r;";
			gotoXY(8, 6);
			cout << "int v = A[r];";
			gotoXY(8, 7);
			cout << "while(2*j + 1 < n){";
			gotoXY(11, 8);
			cout << "int m = 2*j + 1;";
			gotoXY(11, 9);
			cout << "if(m + 1 < n && A[m+1] > A[m]){";
			gotoXY(14, 10);
			cout << "m++;";
			gotoXY(11, 11);
			cout << "}";		
			gotoXY(11, 12);
			cout << "if(A[m] > v){";
			gotoXY(14, 13);
			cout << "A[j] = A[m];";
			gotoXY(14, 14);
			cout << "A[m] = v;";
			gotoXY(14, 15);
			cout << "j = m;";
			gotoXY(11, 16);
			cout << "}else{";
			gotoXY(14, 17);
			cout << "return;";
			gotoXY(11, 18);
			cout << "}";
			gotoXY(8, 19);
			cout << "}";
			gotoXY(5, 20);
			cout << "}";
			
			gotoXY(5, 25);
			cout << "void heapSortFunc(int A[], int count){";
			gotoXY(8, 26);
			cout << "for(int i = (count - 1)/2; i >= 0; i--){";
			gotoXY(11, 27);
			cout << "vundong(A, count, i);";
			gotoXY(8, 28);
			cout << "}";
			gotoXY(8, 30);
			cout << "for(int i = count - 1; i >= 1; i--){";
			gotoXY(11, 31);
			cout << "swap(A[0], A[i]);";
			gotoXY(11, 32);
			cout << "vundong(A, i, 0);";
			gotoXY(8, 33);
			cout << "}";
			gotoXY(5, 34);
			cout << "}";
			
			gotoXY(60, y + 5);
			cout << "Ghi chu:";
			
			gotoXY(60, y + 6);
			cout << "        + ";
			SetColor(0, 12);
			cout << "Mau do: ";
			SetColor(0, 7);
			cout << "gia tri lon nhat trong 2 khoa con.";
			
			gotoXY(60, y + 7);
			cout << "        + ";
			SetColor(0, 14);
			cout << "Mau vang: ";
			SetColor(0, 7);
			cout << "gia tri khoa cha.";
			
			gotoXY(60, y + 8);
			cout << "        + ";
			SetColor(0, 10);
			cout << "Mau xanh la cay: ";
			SetColor(0, 7);
			cout << "gia tri duoc doi cho.";
			
			gotoXY(60, y + 9);
			cout << "        + ";
			SetColor(0, 11);
			cout << "Mau xanh duong: ";
			SetColor(0, 7);
			cout << "gia tri da sap xep dung vi tri.";
					
			gotoXY(60, y + 13);
			cout << "Hanh dong: ";
					
			y += 20;
			xuatInfo(A, count, 40, y);
			
			gotoXY(72, y - 7);
			cout << "bat dau";
			Sleep(500);
			
			Sleep(500);
			SetColor(11, 0);
			gotoXY(8, 26);
			cout << "for(int i = (count - 1)/2; i >= 0; i--){";
			SetColor(0, 7);
			
			for(int i = (count-1)/2; i >= 0; i--){
				Sleep(500);
				SetColor(11, 0);
				gotoXY(11, 27);
				cout << "vundong(A, count, i);";
				SetColor(0, 7);
				
				Sleep(200);
				SetColor(0, 7);
				gotoXY(8, 26);
				cout << "for(int i = (count - 1)/2; i >= 0; i--){";
				
				vundong(A, count, count, i, x, y, "movement", dem);
				
				Sleep(500);
				SetColor(11, 0);
				gotoXY(8, 26);
				cout << "for(int i = (count - 1)/2; i >= 0; i--){";
				SetColor(0, 7);
				
				Sleep(200);
				SetColor(0, 7);
				gotoXY(8, 7);
				cout << "while(2*j + 1 < n){";
				
				Sleep(200);
				SetColor(0, 7);
				gotoXY(14, 17);
				cout << "return;";
			}
			
			Sleep(500);
			SetColor(11, 0);
			gotoXY(8, 30);
			cout << "for(int i = count - 1; i >= 1; i--){";
			SetColor(0, 7);
			
			Sleep(200);
			SetColor(0, 7);
			gotoXY(8, 26);
			cout << "for(int i = (count - 1)/2; i >= 0; i--){";
			
			for(int i = count-1; i >= 1; i--){
				gotoXY(72, y - 7);
				cout << "                                                   ";
				
				Sleep(200);
				gotoXY(72, y - 7);
				cout << "doi cho A[" << 0 << "] (" << A[0] << ") va A[" << i << "] (" << A[i] << ")";
				
				Sleep(500);
				SetColor(11, 0);
				gotoXY(11, 31);
				cout << "swap(A[0], A[i]);";
				SetColor(0, 7);
				
				Sleep(200);
				SetColor(0, 7);
				gotoXY(8, 30);
				cout << "for(int i = count - 1; i >= 1; i--){";
				
				swapTransition(A, 0, i, y);
				swap(A[0], A[i]);
				
				// active
				Sleep(500);
				x = 55 + i * 15;
				box(x, y, 10, 1, 11, 0, convertString(A[i]), true, 11, 0);
				
				Sleep(500);
				SetColor(11, 0);
				gotoXY(11, 32);
				cout << "vundong(A, i, 0);";
				SetColor(0, 7);
				
				Sleep(200);
				SetColor(0, 7);
				gotoXY(11, 31);
				cout << "swap(A[0], A[i]);";
				
				vundong(A, count, i, 0, x, y, "movement", dem);
				
				Sleep(500);
				SetColor(11, 0);
				gotoXY(8, 30);
				cout << "for(int i = count - 1; i >= 1; i--){";
				SetColor(0, 7);
				
				Sleep(200);
				SetColor(0, 7);
				gotoXY(8, 7);
				cout << "while(2*j + 1 < n){";
				
				Sleep(200);
				SetColor(0, 7);
				gotoXY(14, 17);
				cout << "return;";
			}
			
			Sleep(200);
			SetColor(0, 7);
			gotoXY(8, 30);
			cout << "for(int i = count - 1; i >= 1; i--){";
			
			// active
			Sleep(500);
			x = 55 + 0 * 15;
			box(x, y, 10, 1, 11, 0, convertString(A[0]), true, 11, 0);
			
			gotoXY(72, y - 7);
			cout << "                                                   ";
			
			Sleep(200);
			gotoXY(72, y - 7);
			cout << "hoan thanh";
		}else {
			gotoXY(60, y + 5);
			cout << "Ghi chu:";
			
			gotoXY(60, y + 6);
			cout << "        + ";
			SetColor(0, 12);
			cout << "Mau do: ";
			SetColor(0, 7);
			cout << "gia tri lon nhat trong 2 khoa con.";
			
			gotoXY(60, y + 7);
			cout << "        + ";
			SetColor(0, 14);
			cout << "Mau vang: ";
			SetColor(0, 7);
			cout << "gia tri khoa cha.";
			
			gotoXY(60, y + 8);
			cout << "        + ";
			SetColor(0, 10);
			cout << "Mau xanh la cay: ";
			SetColor(0, 7);
			cout << "gia tri duoc doi cho.";
			
			gotoXY(60, y + 9);
			cout << "        + ";
			SetColor(0, 11);
			cout << "Mau xanh duong: ";
			SetColor(0, 7);
			cout << "gia tri da sap xep dung vi tri.";
			
			y += 15;
			xuatInfo(A, count, 40, y);
			
			for(int i = (count-1)/2; i >= 0; i--){
				vundong(A, count, count, i, x, y, "steps", dem);
			}
			
			for(int i = count-1; i >= 1; i--){
				y += 9;
				gotoXY(40, y - 4);
				cout << "Buoc " << dem << ": doi cho A[" << 0 << "] (" << A[0] << ") va A[" << i << "] (" << A[i] << ")";
				xuatInfo(A, count, 40, y);
				int mx = 55 + 0 * 15;
				box(mx, y, 10, 1, 10, 0, convertString(A[i]), true, 10, 0);
				int ix = 55 + i * 15;
				box(ix, y, 10, 1, 10, 0, convertString(A[0]), true, 10, 0);
				dem++;
				
				for(int k = i + 1; k < count; k++){
					int kx = 55 + k * 15;
					box(kx, y, 10, 1, 11, 0, convertString(A[k]), true, 11, 0);
				}
				
				swap(A[0], A[i]);
				vundong(A, count, i, 0, x, y, "steps", dem);
			}
		
			y += 9;
			gotoXY(40, y - 4);
			cout << "Hoan thanh";
			xuatInfo(A, count, 40, y);	
		}
	}
	
	backOrExit(A, count, 7, 70, y + 10);
}
