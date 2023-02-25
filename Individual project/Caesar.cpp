#include <iostream>
#include <fstream>
#include <string>
#include <locale>

using namespace std;

string crypt(string text, int key, bool encrypt) {
	string result = "";
	int alphabetSize = 0;
	int shift = 0;
	if (encrypt) {
		shift = key;
	}
	else {
		shift = -key;
	}
	for (int i = 0; i < text.length(); i++) {
		// Шифрование или дешифрование букв русского алфавита
		if (text[i] >= 'А' && text[i] <= 'Я') {
			alphabetSize = 32;
			result += (text[i] - 'А' + shift + alphabetSize) % alphabetSize + 'А';
		}
		else if (text[i] >= 'а' && text[i] <= 'я') {
			alphabetSize = 32;
			result += (text[i] - 'а' + shift + alphabetSize) % alphabetSize + 'а';
		}
		// Шифрование или дешифрование букв английского алфавита
		else if (text[i] >= 'A' && text[i] <= 'Z') {
			alphabetSize = 26;
			result += (text[i] - 'A' + shift + alphabetSize) % alphabetSize + 'A';
		}
		else if (text[i] >= 'a' && text[i] <= 'z') {
			alphabetSize = 26;
			result += (text[i] - 'a' + shift + alphabetSize) % alphabetSize + 'a';
		}
		else {
			result += text[i];
		}
	}
	return result;
}

// Функция для чтения текста из файла
string readFile(string fileName) {
	string text = "";
	ifstream inputFile(fileName);
	if (inputFile.is_open()) {
		char c;
		while (inputFile.get(c)) {
			text += c;
		}
		inputFile.close();
	}
	else {
		throw runtime_error("Unable to open file");
	}
	return text;
}

// Функция для записи текста в файл
void writeFile(string fileName, string text) {
	ofstream outputFile(fileName);
	if (outputFile.is_open()) {
		outputFile << text;
		outputFile.close();
	}
	else {
		throw runtime_error("Unable to open file");
	}
}

int main() {
	setlocale(LC_ALL, "RUS");
	int key;
	char choice, outputChoice;
	string input, output, text;

	// Запрос выбора действия
	cout << "Выберите дейтсвие (e для шифрования, d для дешифрования): ";
	cin >> choice;

	if (choice == 'e') {
		// Запрос выбора источника ввода информации
		cout << "Выберите способ ввода (k для ввода с клавиатуры, f для ввода из файла): ";
		cin >> input;
		while (input != "k" && input != "f") {
			cout << "Ошибка! Попробуйте еще раз." << endl;
			cout << "Выберите способ ввода (k для ввода с клавиатуры, f для ввода из файла): ";
			cin >> input;
		}
		if (input == "k") {
			// Чтение текста с клавиатуры
			cout << "Введите текст для шифрования: ";
			cin.ignore();
			getline(cin, text);
		}
		else if (input == "f") {
			// Чтение текста из файла
			cout << "Введите название файла для ввода: ";
			cin >> text;
			text = readFile(text);
		}

		// Запрос ключа шифрования
		cout << "Введите ключ шифрования (1 - 25): ";
		cin >> key;
		while (key > 25 || key < 1) {
			cout << "Неверный ключ шифрования! Попробуйте еще раз." << endl;
			cout << "Введите ключ шифрования (1 - 25): ";
			cin >> key;
		}

		// Шифрование текста
		text = crypt(text, key, true);

		// Запрос выбора источника вывода информации
		cout << "Выберите способ вывода (k для вывода на экран, f для вывода в файл): ";
		cin >> output;

		while (output != "k" && output != "f") {
			cout << "Ошибка! Попробуйте еще раз." << endl;
			cout << "Выберите способ вывода (k для вывода на экран, f для вывода в файл): ";
			cin >> output;
		}
		if (output == "k") {
			// Вывод текста на экран
			cout << "Зашифрованный текст: " << text << endl;
		}
		else if (output == "f") {
			// Запись текста в файл
			cout << "Введите названия файла для вывода: ";
			cin >> text;
			writeFile(text, text);
			cout << "Текст был успешно записан в файл." << endl;
		}

		return 0;
	}
	if (choice == 'd') {
		// Запрос выбора источника ввода информации
		cout << "Выберите способ ввода (k для ввода с клавиатуры, f для ввода из файла): ";
		cin >> input;

		while (input != "k" && input != "f") {
			cout << "Ошибка! Попробуйте еще раз." << endl;
			cout << "Выберите способ ввода (k для ввода с клавиатуры, f для ввода из файла): ";
			cin >> input;
		}

		if (input == "k") {
			// Чтение текста с клавиатуры
			cout << "Введите текст для дешифрования: ";
			cin.ignore();
			getline(cin, text);
		}
		else if (input == "f") {
			// Чтение текста из файла
			cout << "Введите название файла для ввода: ";
			cin >> text;
			text = readFile(text);
		}

		// Запрос ключа дешифрования
		cout << "Введите ключ дешифрования (1 - 25): ";
		cin >> key;

		while (key > 25 || key < 1) {
			cout << "Неверный код дешифрования! Попробуйте еще раз." << endl;
			cout << "Введите ключ дешифрования (1 - 25): ";
			cin >> key;
		}

		// Дешифрование текста
		text = crypt(text, key, false);

		// Запрос выбора источника вывода информации
		cout << "Выберите способ вывода (k для вывода на экран, f для вывода в файл): ";
		cin >> output;

		while (output != "k" && output != "f") {
			cout << "Ошибка! Попробуйте еще раз." << endl;
			cout << "Выберите способ вывода (k для вывода на экран, f для вывода в файл): ";
			cin >> output;
		}

		if (output == "k") {
			// Вывод текста на экран
			cout << "Расшифрованный текст: " << text << endl;
		}
		else if (output == "f") {
			// Запись текста в файл
			cout << "Введите названия файла для вывода: ";
			cin >> output;
			writeFile(output, text);
			cout << "Текст был успешно записан в файл." << endl;
		}
		return 0;

	}
}
