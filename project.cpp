#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// Chatbot class to encapsulate functionalities
class Chatbot {
private:
    unordered_map<string, vector<string>> responses;
    string userName;

public:
    // Constructor to initialize responses and random seed
    Chatbot() {
        initializeResponses();
        srand(static_cast<unsigned int>(time(0)));
    }

    // Function to initialize response map
    void initializeResponses() {
        // Greetings
        responses["hello"] = {"Hello!", "Hi there!", "Hey!", "Howdy!", "Greetings!"};
        responses["hi"] = responses["hello"];
        responses["hey"] = responses["hello"];

        // Basic Questions
        responses["how are you"] = {"I'm doing great, thanks!", "I'm here and ready to assist!", "Feeling ready to chat!"};
        responses["what is your name"] = {"I'm Chatbot, your assistant!", "I go by Chatbot, here to help!"};

        // Programming Questions
        responses["programming"] = {"Programming opens up many possibilities!", "I'm made of code myself!", "I love coding conversations!"};
        responses["python"] = {"Python is versatile and popular!", "Python is great for data science.", "Python is known for its simplicity."};
        responses["c++"] = {"C++ is powerful for systems programming.", "C++ is known for performance.", "I respect C++ for its efficiency."};

        // Fun and Small Talk
        responses["hobbies"] = {"I enjoy learning new things!", "Helping people is my favorite thing to do!", "Chatting is my main hobby!"};
        responses["what do you like"] = {"I like assisting you!", "I'm a fan of conversations!", "Learning is my hobby!"};
        responses["tell me a joke"] = {"Why did the computer go to the doctor? It had a virus!", "Why do programmers prefer dark mode? Because light attracts bugs!", "I love binary jokes, they have two meanings!"};

        // Advice and Motivation
        responses["advice"] = {"Stay curious and keep learning!", "Believe in yourself!", "Never stop exploring new things!"};
        responses["motivate me"] = {"You can achieve anything with persistence!", "Keep going, you're doing great!", "Stay positive and keep pushing forward!"};

        // Farewell
        responses["goodbye"] = {"Goodbye! Have a great day!", "See you later!", "Take care!"};
        responses["bye"] = responses["goodbye"];

        // Fallback for unknown responses
        responses["fallback"] = {"I'm not sure about that.", "Could you rephrase?", "I don't understand that, but I'm learning!"};
    }

    // Function to convert input to lowercase
    string toLowerCase(const string &input) {
        string lowerInput;
        for (char c : input) {
            lowerInput += tolower(c);
        }
        return lowerInput;
    }

    // Function to get a random response
    string getRandomResponse(const vector<string> &responses) {
        return responses[rand() % responses.size()];
    }

    // Function to handle basic sentiment analysis
    string handleSentiment(const string &input) {
        if (input.find("sad") != string::npos || input.find("not well") != string::npos) {
            return "I'm sorry to hear that. If there's anything I can do to help, just ask!";
        } else if (input.find("happy") != string::npos || input.find("great") != string::npos) {
            return "That's wonderful! I'm glad you're feeling good.";
        }
        return "";  // Return empty if no sentiment detected
    }

    // Function to handle remembering user's name
    void handleUserName(const string &input) {
        size_t pos = input.find("my name is ");
        if (pos != string::npos) {
            userName = input.substr(pos + 11);  // Extract name after "my name is "
            cout << "Chatbot: Nice to meet you, " << userName << "!" << endl;
        }
    }

    // Function to find response for input
    string getResponse(const string &userInput) {
        string lowerInput = toLowerCase(userInput);

        // Name detection
        if (lowerInput.find("my name is") != string::npos) {
            handleUserName(lowerInput);
            return "";  // Early return since response is handled
        }

        // Sentiment analysis
        string sentimentResponse = handleSentiment(lowerInput);
        if (!sentimentResponse.empty()) {
            return sentimentResponse;
        }

        // Check for keyword matches
        for (const auto &pair : responses) {
            if (lowerInput.find(pair.first) != string::npos) {
                return getRandomResponse(pair.second);
            }
        }
        // Fallback if no match found
        return getRandomResponse(responses["fallback"]);
    }

    // Function to start the conversation
    void start() {
        cout << "Chatbot: " << getRandomResponse(responses["hello"]) << " Type 'exit' to end the conversation." << endl;

        string userInput;
        while (true) {
            cout << "You: ";
            getline(cin, userInput);

            // Exit condition
            if (toLowerCase(userInput) == "exit") {
                cout << "Chatbot: Goodbye! Take care!" << endl;
                break;
            }

            // Generate response
            string response = getResponse(userInput);
            if (!response.empty()) {  // Avoid empty responses
                cout << "Chatbot: " << response << endl;
            }
        }
    }
};

// Main function
int main() {
    Chatbot chatbot;
    chatbot.start();
    return 0;
}