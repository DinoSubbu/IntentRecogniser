//#include "intent_recogniser.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

typedef std::vector<std::string> words_vector;
typedef struct {
    std::vector<std::string> userInput;
    std::string intent;
} intentDataset;

intentDataset intent_dataset[] = {
    {
        {
            "weather",
            "rain",
            "cloudy",
            "sunny"
        },
        "Get Weather"
    },
    {
        {
            "weather",
            ""
        },
        "Get Weather City"
    },
    {
        {
            "",
            ""
        },
        "Check Calendar"
    },
    {
        {
            "fact"
        },
        "Get Fact"
    }
};

class IntentRecogniser {
    private:
        std::string articles[3] = {"a", "an", "the"};
    public:
        void getIntent(std::string input_text);
        void processInput(std::string& input_text);
        void removeArticles(words_vector& input_text);
        void removePunctuations(std::string& input_text);
        void convertToLowerCase(std::string& input_text);
        words_vector tokenize(std::string input_text);
        void removeExtraSpaces(std::string& input_text);

};

// Removes extra spaces from input string and returns updated string
void IntentRecogniser::removeExtraSpaces(std::string& input_text) {
    auto new_end_position = std::unique(input_text.begin(), input_text.end(), [] (char left, char right) {
        return ((left == right) && (left == ' '));
    });
    input_text.erase(new_end_position, input_text.end());
}

// Removes punctuation marks from input string and returns updated string
void IntentRecogniser::removePunctuations(std::string& input_text) {
    auto new_end_position = std::remove_if(input_text.begin(), input_text.end(), ispunct);
    input_text.erase(new_end_position, input_text.end());
}

// Converts upper case alphabets to lower case and returns updated string
void IntentRecogniser::convertToLowerCase(std::string& input_text) {
    std::for_each(input_text.begin(), input_text.end(), [] (char& alphabet) {
        alphabet = std::tolower(alphabet);
    });
}

// Breaks down the input string to words and returns a vector of words
words_vector IntentRecogniser::tokenize(std::string input_text) {
    words_vector input_words;
    std::string word = "";
    for(auto alphabet: input_text) {
        if(alphabet == ' ') {
            if(word!="") {
            input_words.push_back(word);
            word = "";
            }
        }
        else {
            word += alphabet;
        }
    }
    if(word!="")
        input_words.push_back(word);
    return input_words;
}

// Remove articles from the input string and returns updated string
void IntentRecogniser::removeArticles(words_vector& input_words) {
    for(std::string article: articles) {
        auto new_end_position = std::remove(input_words.begin(), input_words.end(), article);
        input_words.erase(new_end_position, input_words.end());
    }
}

// Processes input string
void IntentRecogniser::processInput(std::string& input_text) {
    removePunctuations(input_text);
    removeExtraSpaces(input_text);
    convertToLowerCase(input_text);
    std::vector<std::string> tokenized_words = tokenize(input_text);
    removeArticles(tokenized_words);
    for(words_vector::const_iterator i = tokenized_words.begin(); i != tokenized_words.end(); ++i)
        std::cout << *i;
}


void IntentRecogniser::getIntent(std::string input_text) {
    processInput(input_text);
    //std::cout<<input_text.c_str()<<std::endl;
}

int main() {
    IntentRecogniser intentrecogniser;
    std::string input_text = " What   is the the  weather like today ? ";
    intentrecogniser.getIntent(input_text);
    return 0;
}