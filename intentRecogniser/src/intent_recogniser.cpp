#include "intent_recogniser.hpp"

intentDataset intent_dataset[] = {
    {
        {
            "what is the weather like today",
            "will it rain today",
            "will it rain tomorrow",
            "is it raining now",
            "is it cloudy",
            "is it sunny",
            "is it hot today",
            "what is the temperature like today"
        },
        "Get Weather"
    },
    {
        {
            "what is the weather in paris today",
            "what is the weather in stuttgart today",
            "what is the weather like today in new york",
            "Will it rain in paris today",
            "is it raining in paris today",
            "is it cloudy in new york",
            "is it sunny in Paris",
            "what is the temperature in paris"
        },
        "Get Weather City"
    },
    {
        {
            "am i free at 13:00 pm tomorrow",
            "do i have a meeting",
            "do i have an appointment",
            "is there a meeting",
            "is my calendar free tomorrow"
        },
        "Check Calendar"
    },
    {
        {
            "tell me a fact",
            "tell an interesting fact",
            "tell something about Germany"
        },
        "Get Fact"
    }
};


// Removes extra spaces from input string and returns updated string
void IntentRecogniser::removeExtraSpaces(std::string& input_text) {
    auto new_end_position = std::unique(input_text.begin(), input_text.end(), [] (char left, char right) {
        return ((left == right) && (left == ' '));
    });
    input_text.erase(new_end_position, input_text.end());
    while (input_text[0] == ' ') {
        input_text.erase(0,1);
    }
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
// Reserved for future use
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

// Calculates Levenshtein distance between two strings and returns the distance value
unsigned int IntentRecogniser::levenshteinDistance(std::string input, std::string reference) {
    const int input_length = input.length();
    const int reference_length = reference.length();

    if(input_length == 0) 
        return reference_length;
    if(reference_length == 0) 
        return input_length;
    
    std::vector<std::vector<unsigned int>> distanceMatrix;
    distanceMatrix.resize(input_length+1, std::vector<unsigned int>(reference_length+1));
    for (size_t i = 0; i < input_length; i++ )
        std::iota(distanceMatrix[i].begin(), distanceMatrix[i].end(), i* reference_length);
    
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


// Finds best matching intent for the input string and returns the intent
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

// Processes input string by removing uppercases, punctuations & extra spaces
void IntentRecogniser::processInput(std::string& input_text) {
    removePunctuations(input_text);
    convertToLowerCase(input_text);
    removeExtraSpaces(input_text);
    /*std::vector<std::string> tokenized_words = tokenize(input_text);*/
}


std::string IntentRecogniser::getIntent(std::string input_text) {
    processInput(input_text);
    return bestIntentMatch(input_text);
}