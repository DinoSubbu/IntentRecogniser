//#include "intent_recogniser.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <numeric>
typedef std::vector<std::string> words_vector;
typedef struct {
    std::vector<std::string> referenceTexts;
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
            "weather in",
            ""
        },
        "Get Weather City"
    },
    {
        {
            "free",
            ""
        },
        "Check Calendar"
    },
    {
        {
            "tell me a fact for today"
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
        unsigned int levenshteinDistance(std::string input, std::string reference);
        std::string bestIntentMatch(std::string input_text);
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

unsigned int IntentRecogniser::levenshteinDistance(std::string input, std::string reference) {
    const int input_length = input.length();
    const int reference_length = reference.length();

    if(input_length == 0) 
        return reference_length;
    if(reference_length == 0) 
        return input_length;
    
    std::vector<std::vector<unsigned int>> distanceMatrix;
    distanceMatrix.resize(input_length+1, std::vector<unsigned int>(reference_length+1));
    /*for (size_t i = 0; i < input_length; i++ )
        std::iota(distanceMatrix[i].begin(), distanceMatrix[i].end(), i* reference_length);*/
    
    for(int i=0; i<= input_length; i++) {
        for(int j=0; j<= reference_length; j++) {
            // Empty input string
            if(i==0)
                distanceMatrix[i][j] = j;
            // Empty reference string
            else if(j==0)
                distanceMatrix[i][j] = i;
            // Same last character
            else if(input[i-1] == reference[j-1])
                distanceMatrix[i][j] = distanceMatrix[i-1][j-1];
            // Different last character, find minimum possibility
            else {
                distanceMatrix[i][j] = std::min({
                    distanceMatrix[i][j-1],  // Insertion operation
                    distanceMatrix[i-1][j],  // Deletion operation
                    distanceMatrix[i-1][j-1] // Replace Operation
                }) + 1;
            }
        }
    }

    // Return the last element of the matrix
    return distanceMatrix[input_length][reference_length];
}

std::string IntentRecogniser::bestIntentMatch(std::string input_text){
    std::unordered_map<std::string, unsigned int> minLevDistances;
    for(auto intent: intent_dataset) {
        for(auto reference_text : intent.referenceTexts) {
            unsigned int levDist = levenshteinDistance(input_text, reference_text);
            if((minLevDistances.find(intent.intent) == minLevDistances.end()) || (levDist < minLevDistances[intent.intent]))
                minLevDistances[intent.intent] = levDist;
        }
    }
    auto lowestValueIndex = std::min_element(minLevDistances.begin(), minLevDistances.end(), 
        [] (auto& left, auto& right) -> bool { return left.second < right.second; });
    return lowestValueIndex->first;
}

// Processes input string
void IntentRecogniser::processInput(std::string& input_text) {
    removePunctuations(input_text);
    removeExtraSpaces(input_text);
    convertToLowerCase(input_text);
    /*std::vector<std::string> tokenized_words = tokenize(input_text);
    removeArticles(tokenized_words);
    for(words_vector::const_iterator i = tokenized_words.begin(); i != tokenized_words.end(); ++i)
        std::cout << *i;*/
}


void IntentRecogniser::getIntent(std::string input_text) {
    processInput(input_text);
    std::cout<<bestIntentMatch(input_text)<<std::endl;
    //std::cout<<input_text.c_str()<<std::endl;
}

int main() {
    IntentRecogniser intentrecogniser;
    std::string input_text = " Tell me a fact for today ? ";
    intentrecogniser.getIntent(input_text);
    return 0;
}