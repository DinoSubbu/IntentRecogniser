#include <gtest/gtest.h>
#include "../include/intent_recogniser.hpp"

TEST(InputPreprocessing, RemoveRedundantSpacesCheck) {
	IntentRecogniser intent_recogniser;
	std::string test_input = " What is   the weather   today?";
	intent_recogniser.removeExtraSpaces(test_input);
	ASSERT_EQ(test_input, "What is the weather today?");
}

TEST(InputPreprocessing, RemovePunctuationsCheck) {
	IntentRecogniser intent_recogniser;
	std::string test_input = "What is the weather, today??";
	intent_recogniser.removePunctuations(test_input);
	ASSERT_EQ(test_input, "What is the weather today");
}

TEST(InputPreprocessing, ToLowerCaseCheck) {
	IntentRecogniser intent_recogniser;
	std::string test_input = "What is the weather Today?";
	intent_recogniser.convertToLowerCase(test_input);
	ASSERT_EQ(test_input, "what is the weather today?");
}

TEST(InputPreprocessing, LevDistanceStringEqualCheck) {
	IntentRecogniser intent_recogniser;
	std::string test_input = "what is the weather today?";
	int levDistance = intent_recogniser.levenshteinDistance(test_input, test_input);
	ASSERT_EQ(levDistance, 0);
}

TEST(InputPreprocessing, LevDistanceStringUnequalCheck) {
	IntentRecogniser intent_recogniser;
	std::string test_input = "what is the weather today?";
	std::string test_reference = "Tell me an interesting fact?";
	int levDistance = intent_recogniser.levenshteinDistance(test_input, test_reference);
	ASSERT_NE(levDistance, 1);
}

TEST(InputPreprocessing, BestIntentMatchFunctionCheck) {
	IntentRecogniser intent_recogniser;
	std::string test_input = "what is the weather today?";
	std::string intent = intent_recogniser.bestIntentMatch(test_input);
	ASSERT_EQ(intent, "Get Weather");
}

TEST(InputPreprocessing, GetIntentFunctionCheck) {
	IntentRecogniser intent_recogniser;
	std::string test_input = " what is a the    weather today ? ";
	std::string intent = intent_recogniser.getIntent(test_input);
	ASSERT_EQ(intent, "Get Weather");

	test_input = " tell an interesting fact ? ";
	intent = intent_recogniser.getIntent(test_input);
	ASSERT_EQ(intent, "Get Fact");

	test_input = " what is a the    weather today in Paris ? ";
	intent = intent_recogniser.getIntent(test_input);
	ASSERT_EQ(intent, "Get Weather City");

	test_input = "Do I have a meeting at 11 am tomorrow? ";
	intent = intent_recogniser.getIntent(test_input);
	ASSERT_EQ(intent, "Check Calendar");

	test_input = "Doo I haave a meedting at 11 am tommorrow? ";
	intent = intent_recogniser.getIntent(test_input);
	ASSERT_EQ(intent, "Check Calendar");
}


int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}