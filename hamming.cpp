/**
 * @file hamming.cpp
 */
#include "hamming.h"
/**
* @brief Кодирование кодом Хемминга
* @param text строка для кодирования
* @return Закодированная последовательность
*/
vector<int> Hamming::encode(string text){
	vector<int> code;

	// Перевод текста в бинарный код
	for(int i = 0; i < text.length(); i++) {
		vector<int> vecChar = toBin(text[i]);
		code.insert(code.end(), vecChar.begin(), vecChar.end());
	}
    
	// Дополнение недостающих символов
	if(text.length() % 4 != 0)
		for(int i = 0; i < 4 - (text.length() % 4); i++)
			for(int j = 0; j < 8; j++)
				code.push_back(0);
				
	// Вставка контролирующих битов
	int code_size = code.size();
	for(int i = 0; i < code_size / 32; i++) {
		for(int j = 0; j < 6; j++) {
			code.insert(code.begin() + i * 38 + pow(2,j)-1, 1, 0);
		}
	}
	// Вычисление контролирующих битов
	for(int i = 0; i < code.size() / 38; i++) {
		for(int j = 0; j < 6; j++) {
			int sum = 0;
			for(int g = 1; g < 39; g++){
				
				if(g % (int)(pow(2,j) * 2) >= pow(2,j))
					sum += code[i * 38 + g - 1];
			}
			code[i * 38 + pow(2,j)-1] = sum % 2;
			sum = 0;
		}
	}
	
	return code;
}
/**
* @brief Декодирование кодом Хемминга
* @param code вектор для декодирования
* @return Исходный текст
*/
string Hamming::decode(vector<int> code){
	string text;
	vector<int> code_control = code;

	// Обнуление контрольных битов
	for(int i = 0; i < code.size() / 38; i++)
		for(int j = 0; j < 6; j++)
			code[38 * i + pow(2,j) - 1] = 0;
	
	int pos = 0;
	// Вычисление битов и кореекция
	for(int i = 0; i < code.size() / 38; i++) {
		for(int j = 0; j < 6; j++) {
			int sum = 0;
			for(int g = 1; g < 39; g++)
				if(g % (int)(pow(2,j) * 2) >= pow(2,j))
					sum += code[i * 38 + g - 1];
			if(code_control[i * 38 + pow(2,j)-1] != sum % 2)
				pos += pow(2,j);
			sum = 0;
		}
		if(pos != 0){
			code[i * 38 + pos - 1] = (2 - code[i * 38 + pos - 1]) / 2; //Инверсия
			pos = 0;
		}
	}
	
	vector<int> new_vec;
	// Удаление коректирующих бит
	for(int i = 0; i < code.size() / 38; i++) {
		for(int j = 0; j < 38; j++) {
			if(j != 0 && j != 1 && j!= 3 && j != 7 && j != 15 && j != 31){
				new_vec.push_back(code[38 * i + j]);
			}
		}
	}
	
	// Перевод из двоичной в символы
	for(int i = 0; i < new_vec.size() / 8; i++) {
		vector<int> tmp;
		for(int j = 0; j < 8; j++)
			tmp.push_back(new_vec[i * 8 + j]);
		text += toDec(tmp) - 1;
		tmp.clear();
	}
	
	string text_clean;
	for(auto s : text)
		if(s != 0)
			text_clean += s;
	
	return text_clean;
}
/**
* @brief Перевод числа в двоичный вид с записью в вектор
* @param num число для перевода
* @return Вектор из нулей и единиц
*/
vector<int> Hamming::toBin(int num){
	vector<int> bin;
	while(num != 0) {
		bin.push_back(num % 2);
		num /= 2;
	}
	for(int i = bin.size(); i < 8; i++)
		bin.push_back(0);
	reverse(bin.begin(), bin.end());
	return bin;
}
/**
* @brief Перевод вектора из нулей и единиц в число
* @param vec вектор для перевода
* @return Число полученное из вектора
*/
int Hamming::toDec(vector<int> vec){
	int num;
	for(int i = 0; i < 8; i++)
		num += (char)vec[i] * pow(2, 7-i);
	return num;
}
/**
* @brief Вывод вектора в консоль
* @param vec вектор для вывода
*/
void Hamming::print_vec(vector<int> vec){
	for(int i = 0; i < vec.size(); i++)
		cout << vec[i];
	cout << endl;
}
/**
* @brief Перевод строки из чисел в вектор
* @param str строка для перевода
* @return Вектор полученный из строки
*/
vector<int> Hamming::stringToVec(string str){
	vector<int> vec;
	for(auto s : str){
		vec.push_back(s - 48);
	}
	return vec;
}
