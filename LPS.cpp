#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

std::pair<std::string, std::string> SplitData(const std::string& str, const std::string& divider) {
	std::string login = str.substr(0, str.find(divider));
	std::string password = str.substr(str.find(divider) + 1);

	return std::make_pair(login, password);
}

std::vector<std::pair<std::string, std::pair<std::string, std::string>>> ReadData(const std::string& dataName, const std::string& divider = ":") {
	std::ifstream data(dataName);
	std::vector<std::pair<std::string, std::pair<std::string, std::string>>> dataSet;

	if (data.is_open()) {
		std::string line;
		while (std::getline(data, line)) {
			std::string siteName = line.substr(0, line.find(' '));
			std::string other = line.substr(siteName.length(), line.length());

			dataSet.push_back(std::make_pair(siteName, SplitData(other, divider)));
		}
		data.close();
	}
	else {
		std::cout << "Failed to open file" << std::endl;
	}
	return dataSet;
}

int ListData(const std::vector<std::pair<std::string, std::pair<std::string, std::string>>>& dataSet) {
	std::cout << "L-P Database" << std::endl;
	int count = 1;
	for (const auto& pair : dataSet) {
		std::cout << count << ". ";
		std::cout << pair.first << pair.second.first << " " << pair.second.second << std::endl;
		count++;
	}
	std::cout << "\n";
	return 1;
}

int AskNewData(std::string &site, std::string &login, std::string &password) {
	std::cout << "Enter new site" << std::endl;
	std::cin >> site;
	std::cout << "\nEnter new login" << std::endl;
	std::cin >> login;
	std::cout << "\nEnter new password" << std::endl;
	std::cin >> password;
	system("cls");
	return 1;
}

std::vector<std::pair<std::string, std::pair<std::string, std::string>>> ReadNewData() {
	std::string site;
	std::string login;
	std::string password;
	AskNewData(site, login, password);

	std::vector<std::pair<std::string, std::pair<std::string, std::string>>> newData;
	std::string dataPair = login + ":" + password;
	newData.push_back(std::make_pair(site + ": ", SplitData(dataPair, ":")));
	return newData;
}

std::vector<std::pair<std::string, std::pair<std::string, std::string>>> AddNewData(const std::vector<std::pair<std::string, std::pair<std::string, std::string>>>& newData, std::vector<std::pair<std::string, std::pair<std::string, std::string>>>& dataSet) {
	for (const auto& pair : newData) {
		dataSet.push_back(pair);
	}
	return dataSet;
}

int WriteNewData (std::string& dataName, std::string& divider, const std::vector<std::pair<std::string, std::pair<std::string, std::string>>>& dataSet) {
	

	std::ofstream data(dataName);
	if (data.is_open()) {
		auto sortedData = dataSet;
		std::sort(sortedData.begin(), sortedData.end(), [](const auto& a, const auto& b) {
			return a.first < b.first;
			});
		for (const auto& pair : sortedData) {	
			data << pair.first << pair.second.first << divider << pair.second.second << std::endl;
		}
		data.close();
	}
	else {
		std::cout << "Failed to open file" << std::endl;
		return 0;
	}
	return 1;
}

std::vector<std::pair<std::string, std::pair<std::string, std::string>>> DeleteData(int& lineNumber, std::vector<std::pair<std::string, std::pair<std::string, std::string>>>& dataSet) {
	std::cout << "Enter line number which you want to delete: ";
	std::cin >> lineNumber;
	if (lineNumber < 1 || lineNumber > dataSet.size()) {
		std::cout << "Invalid line number" << std::endl;
		system("pause");
		system("cls");
		return dataSet;
	}
	dataSet.erase(dataSet.begin() + lineNumber - 1);
	std::cout << "Data is successfully deleted" << std::endl;
	system("pause");
	system("cls");
	return dataSet;
}



int main() {
	//Initialisation
	system("cls");
	std::string dataName = "data.txt";
	std::string divider = ":";

	//Read data from file
	std::vector<std::pair<std::string, std::pair<std::string, std::string>>> dataSet = ReadData(dataName, divider);
	ListData(dataSet);

	//Delete data
	//int lineNumber;
	//DeleteData(lineNumber, dataSet);
	//WriteNewData(dataName, divider, dataSet);
	//ListData(dataSet);

	int userChoice = 0;
	do {
		std::cout << "0. Exit" << std::endl;
		std::cout << "1. Add new data" << std::endl;
		std::cout << "2. Delete data" << std::endl;

		std::cout << "Please select an option: ";
		std::cin >> userChoice;
		std::cout << std::endl;

		if (userChoice == 1) {
			std::cout << "You chose option 1." << std::endl;
			//Read&Write new data
			std::vector<std::pair<std::string, std::pair<std::string, std::string>>> newData = ReadNewData();
			dataSet = AddNewData(newData, dataSet);
			WriteNewData(dataName, divider, dataSet);
			ListData(dataSet);
			continue;
		}
		else if (userChoice == 2) {
			std::cout << "You chose option 2." << std::endl;
			int lineNumber;	
			dataSet = DeleteData(lineNumber, dataSet);
			WriteNewData(dataName, divider, dataSet);
			ListData(dataSet);
			continue;
		}
		else if (userChoice == 0) {
			break;
		}
		else {
			std::cout << "Invalid option. Please choose again." << std::endl;
			continue;
		}
	} while (userChoice != 0);

	return 0;
}
