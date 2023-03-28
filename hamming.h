/**
* @file Hamming.h
* @author Иноземцева А.М.
* @version 1.0
* @date 28.03.2023
* @copyright ИБСТ ПГУ
* @brief Заголовочный файл для модуля Hamming
*/
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
/**
* @brief Программа кодирования / декодирования Hamming
*/
class Hamming
{
private:
	vector<int> toBin(int num); // Переводит в двоичную и дополняет до 8 символов
	int toDec(vector<int> vec); // Переводит в десятичную вектор из 8 символов 
public:
	vector<int> encode(string text); // Кодирует
	string decode(vector<int> code); // Декодирует
	void print_vec(vector<int> vec); // Печатет вектор
	vector<int> stringToVec(string str); // Переводит строку в вектор
};
