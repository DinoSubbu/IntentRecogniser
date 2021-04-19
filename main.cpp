#include "intent_recogniser.hpp"
#include <iostream>

int main() {
    IntentRecogniser intentrecogniser;
    std::cout << "Intent Finder Tool" << std::endl << std::endl;
    while(true) {
        std::string input_text;
        std::cout<<"Enter your question: ";
        std::getline(std::cin, input_text);
        std::cout<< "Intent:: "<<intentrecogniser.getIntent(input_text)<<std::endl<<std::endl;
    }
    return 0;
}