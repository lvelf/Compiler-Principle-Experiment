#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

class State {
public:
    std::unordered_map<char, State*> transitions;
    bool isAccepting;

    State() : isAccepting(false) {}
};

class FiniteAutomaton {


public:
    State* startState;
    FiniteAutomaton() {
        startState = new State();
    }

    void addTransition(State* from, char symbol, State* to) {
        from->transitions[symbol] = to;
    }

    void setAccepting(State* state) {
        state->isAccepting = true;
    }

    bool match(const std::string& str) {
        State* currentState = startState;

        for (char c : str) {
            if (currentState->transitions.count(c) > 0) {
                currentState = currentState->transitions[c];
            } else {
                return false;
            }
        }
        return currentState->isAccepting;
    }

    ~FiniteAutomaton() {
        // Cleanup logic can be added here
    }
};

// Function to create a finite automaton for each regex pattern
FiniteAutomaton createAutomatonForPattern(int patternID) {
    FiniteAutomaton automaton;

    State* s0 = automaton.startState;
    State* s1 = new State();
    State* s2 = new State();
    State* s3 = new State();
    State* s4 = new State();
    State* s5 = new State();
    State* s6 = new State();

    switch (patternID) {
        case 1: // "int"
            automaton.addTransition(s0, 'i', s1);
            automaton.addTransition(s1, 'n', s2);
            automaton.addTransition(s2, 't', s3);
            automaton.setAccepting(s3);
            break;
        case 2: // "while"
            automaton.addTransition(s0, 'w', s1);
            automaton.addTransition(s1, 'h', s2);
            automaton.addTransition(s2, 'i', s3);
            automaton.addTransition(s3, 'l', s4);
            automaton.addTransition(s4, 'e', s5);
            automaton.setAccepting(s5);
            break;
        case 3: // "if"
            automaton.addTransition(s0, 'i', s1);
            automaton.addTransition(s1, 'f', s2);
            automaton.setAccepting(s2);
            break;
        case 4: // "else"
            automaton.addTransition(s0, 'e', s1);
            automaton.addTransition(s1, 'l', s2);
            automaton.addTransition(s2, 's', s3);
            automaton.addTransition(s3, 'e', s4);
            automaton.setAccepting(s4);
            break;
        case 5: // "return"
            automaton.addTransition(s0, 'r', s1);
            automaton.addTransition(s1, 'e', s2);
            automaton.addTransition(s2, 't', s3);
            automaton.addTransition(s3, 'u', s4);
            automaton.addTransition(s4, 'r', s5);
            automaton.addTransition(s5, 'n', s6);
            automaton.setAccepting(s6);
            break;
        case 50: // "^[a-zA-Z_][a-zA-Z0-9_]*$"
            automaton.addTransition(s0, 'a', s1);
            automaton.addTransition(s0, 'b', s1);
            automaton.addTransition(s0, 'c', s1);
            automaton.addTransition(s0, 'd', s1);
            automaton.addTransition(s0, 'e', s1);
            automaton.addTransition(s0, 'f', s1);
            automaton.addTransition(s0, 'g', s1);
            automaton.addTransition(s0, 'h', s1);
            automaton.addTransition(s0, 'i', s1);
            automaton.addTransition(s0, 'j', s1);
            automaton.addTransition(s0, 'k', s1);
            automaton.addTransition(s0, 'l', s1);
            automaton.addTransition(s0, 'm', s1);
            automaton.addTransition(s0, 'n', s1);
            automaton.addTransition(s0, 'o', s1);
            automaton.addTransition(s0, 'p', s1);
            automaton.addTransition(s0, 'q', s1);
            automaton.addTransition(s0, 'r', s1);
            automaton.addTransition(s0, 's', s1);
            automaton.addTransition(s0, 't', s1);
            automaton.addTransition(s0, 'u', s1);
            automaton.addTransition(s0, 'v', s1);
            automaton.addTransition(s0, 'w', s1);
            automaton.addTransition(s0, 'x', s1);
            automaton.addTransition(s0, 'y', s1);
            automaton.addTransition(s0, 'z', s1);
            automaton.addTransition(s0, '_', s1);

            for (char ch = '0'; ch <= '9'; ++ch) {
                automaton.addTransition(s1, ch, s1);
            }
            automaton.setAccepting(s1);
            break;
        case 51: // "^[0-9]+$"
            for (char ch = '0'; ch <= '9'; ++ch) {
                automaton.addTransition(s0, ch, s1);
            }
            automaton.setAccepting(s1);
            break;
        case 60: // "+"
            automaton.addTransition(s0, '+', s1);
            automaton.setAccepting(s1);
            break;
        case 61: // "-"
            automaton.addTransition(s0, '-', s1);
            automaton.setAccepting(s1);
            break;
        case 62: // "*"
            automaton.addTransition(s0, '*', s1);
            automaton.setAccepting(s1);
            break;
        case 63: // "/"
            automaton.addTransition(s0, '/', s1);
            automaton.setAccepting(s1);
            break;
        case 64: // "="
            automaton.addTransition(s0, '=', s1);
            automaton.setAccepting(s1);
            break;
        case 65: // "<"
            automaton.addTransition(s0, '<', s1);
            automaton.setAccepting(s1);
            break;
        case 66: // "<="
            automaton.addTransition(s0, '<', s1);
            automaton.addTransition(s1, '=', s2);
            automaton.setAccepting(s2);
            break;
        case 67: // ">"
            automaton.addTransition(s0, '>', s1);
            automaton.setAccepting(s1);
            break;
        case 68: // ">="
            automaton.addTransition(s0, '>', s1);
            automaton.addTransition(s1, '=', s2);
            automaton.setAccepting(s2);
            break;
        case 69: // "=="
            automaton.addTransition(s0, '=', s1);
            automaton.addTransition(s1, '=', s2);
            automaton.setAccepting(s2);
            break;
        case 70: // "!="
            automaton.addTransition(s0, '!', s1);
            automaton.addTransition(s1, '=', s2);
            automaton.setAccepting(s2);
            break;
        case 71: // "{"
            automaton.addTransition(s0, '{', s1);
            automaton.setAccepting(s1);
            break;
        case 72: // "}"
            automaton.addTransition(s0, '}', s1);
            automaton.setAccepting(s1);
            break;
        case 73: // "("
            automaton.addTransition(s0, '(', s1);
            automaton.setAccepting(s1);
            break;
        case 74: // ")"
            automaton.addTransition(s0, ')', s1);
            automaton.setAccepting(s1);
            break;
        case 75: // ","
            automaton.addTransition(s0, ',', s1);
            automaton.setAccepting(s1);
            break;
        case 76: // ";"
            automaton.addTransition(s0, ';', s1);
            automaton.setAccepting(s1);
            break;
        case 0: // Whitespace
            for (char ch = 0; ch < 256; ++ch) {
                if (isspace(ch)) {
                    automaton.addTransition(s0, ch, s1);
                }
            }
            automaton.setAccepting(s1);
            break;
        default:
            break;
    }

    return automaton;
}

// Regex match function
bool regex_match(const std::string& str, int patternID) {
    std::cout<<"ready to match ";
    //FiniteAutomaton automaton = createAutomatonForPattern(patternID);
    std::cout<<"create ok ";
    //return automaton.match(str);
    return true;
}

int main() {
    std::unordered_map<int, std::string> patterns = {
        {1, "int"},
        {2, "while"},
        {3, "if"},
        {4, "else"},
        {5, "return"},
        {50, "^[a-zA-Z_][a-zA-Z0-9_]*$"},
        {51, "^[0-9]+$"},
        {60, R"(\\+)"},
        {61, R"(-)"},
        {62, R"(*)"},
        {63, R"(\/)"},
        {64, R"(=)"},
        {65, R"(>)"},
        {66, R"(<=)"},
        {67, R"(>)"},
        {68, R"(>=)"},
        {69, R"(==)"},
        {70, R"(!=)"},
        {71, R"(\{)"},
        {72, R"(\})"},
        {73, R"(\()"},
        {74, R"(\))"},
        {75, R"(,)"}, 
        {76, R"(;)"}, 
        {0, R"([\s]+)"}
    };

    std::string testStr;

    // Example tests
    printf("ready to for");
   
    int id = 0;
    std::cin>>testStr;
    std::cout<<"okok"<<std::endl;
    if (regex_match(testStr, id)) {
        std::cout << "Matched!\n";
    } else {
        std::cout << "Not matched!\n";
    }
    

    return 0;
}
