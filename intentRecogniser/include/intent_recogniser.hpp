#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <numeric>
#include <cctype>
#include <string>

typedef std::vector<std::string> words_vector;
typedef struct {
    std::vector<std::string> referenceTexts;
    std::string intent;
} intentDataset;

class IntentRecogniser {
private:
    std::string articles[3] = { " a", " an", " the" };
public:
    void removeExtraSpaces(std::string& input_text);
    void removePunctuations(std::string& input_text);
    void convertToLowerCase(std::string& input_text);
    void processInput(std::string& input_text);

    unsigned int levenshteinDistance(std::string input, std::string reference);
    std::string bestIntentMatch(std::string input_text);
    std::string getIntent(std::string input_text);
    
    words_vector tokenize(std::string input_text);
};