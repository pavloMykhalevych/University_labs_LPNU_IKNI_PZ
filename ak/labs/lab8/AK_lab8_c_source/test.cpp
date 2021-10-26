#include <iostream>
#include <string>

void RemoveSpaces(std::string& myString) {
    for (size_t i = 1; i < myString.size(); ++i) {
        if (myString[i - 1] == ' ' && (myString[i] == ' ' || myString[i] == '\0')) {
            myString.erase(myString.begin() + (i - 1));
            myString.shrink_to_fit();
            i--;
        }
    }
}

int main() {
    std::string str = "Remove     additional    spaces   ";
    RemoveSpaces(str);
    std::cout << str << "\nEnd.";
	return 0;
}