#include <iostream>
#include <string>
#include <ctime>      // For date/time operations
#include <fstream>    // For file operations
#include <sstream>    // For string stream operations
#include <iomanip>    // For formatting output
#include <map>        // Included but not used in this code
using namespace std;

// Custom exception class for credit card related errors
class CardException : public exception {
    string msg;  // Error message storage
public:
    // Constructor that accepts error message
    CardException(string m) : msg(m) {}
    
    // Override the what() method from std::exception
    const char* what() const noexcept override {
        return msg.c_str();
    }
};

// Base class for credit card operations
class CreditCard {
protected:
    string cardNumber;   // Full card number
    string expiryDate;   // Expiry date in MM/YY format
    string cardHolder;   // Name of the card holder
    string cardType;     // Type of card (Visa, MasterCard, etc.)
    int cvv;            // Card Verification Value
    
public:
    // Constructor to initialize card details
    CreditCard(string number, string expiry, string holder, int cvv)
        : cardNumber(number), expiryDate(expiry), cardHolder(holder), cvv(cvv) {}

    // Masks the card number showing only last 4 digits for security
    string maskCardNumber() {
        return "XXXX-XXXX-XXXX-" + cardNumber.substr(cardNumber.length() - 4);
    }

    // Validates card number using Luhn algorithm (also known as mod-10 algorithm)
    virtual bool validateCardNumber() {
        int sum = 0;
        bool alternate = false;  // Flag to alternate between operations
        
        // Process digits from right to left
        for (int i = cardNumber.length() - 1; i >= 0; --i) {
            if (isdigit(cardNumber[i])) {
                int n = cardNumber[i] - '0';  // Convert char to int
                
                // Double every second digit from right
                if (alternate) {
                    n *= 2;
                    // If result is > 9, subtract 9 (equivalent to adding digits)
                    if (n > 9) n -= 9;
                }
                sum += n;
                alternate = !alternate;  // Toggle for next iteration
            }
        }
        // Valid if sum is divisible by 10
        return (sum % 10 == 0);
    }

    // Detects card type based on first few digits (IIN - Issuer Identification Number)
    virtual string detectCardType() {
        if (cardNumber[0] == '4')
            return "Visa";                    // Visa cards start with 4
        else if (cardNumber.substr(0, 2) == "51" || cardNumber.substr(0, 2) == "52")
            return "MasterCard";              // MasterCard starts with 51-52
        else if (cardNumber.substr(0, 2) == "34" || cardNumber.substr(0, 2) == "37")
            return "American Express";        // Amex starts with 34 or 37
        else
            return "Unknown";                 // Unrecognized card type
    }

    // Validates CVV length based on card type
    bool isCVVValid() {
        // American Express uses 4-digit CVV, others use 3-digit
        if ((cardType == "American Express" && to_string(cvv).length() == 4) ||
            (cardType != "American Express" && to_string(cvv).length() == 3)) {
            return true;
        }
        return false;
    }

    // Checks if the card is expired or expiring soon
    void checkExpiry() {
        // Parse month and year from expiry date
        int month = stoi(expiryDate.substr(0, 2));           // Extract MM
        int year = stoi("20" + expiryDate.substr(3, 2));     // Extract YY and convert to 20YY
        
        // Get current date
        time_t t = time(0);
        tm* now = localtime(&t);
        int currentMonth = now->tm_mon + 1;      // tm_mon is 0-based
        int currentYear = now->tm_year + 1900;   // tm_year is years since 1900
        
        // Check expiry status
        if (year < currentYear || (year == currentYear && month < currentMonth)) {
            cout << "🔴 Status: Card is **Expired**!" << endl;
        } else if ((year == currentYear && month - currentMonth <= 6) || 
                  (year == currentYear + 1 && currentMonth > month)) {
            cout << "🟡 Status: Card is expiring **soon**!" << endl;
        } else {
            cout << "🟢 Status: Card is **Valid**." << endl;
        }
    }

    // Logs card information to a file for record keeping
    void logToFile() {
        ofstream file("card_log.txt", ios::app);  // Open in append mode
        file << "Card Holder: " << cardHolder << "\n";
        file << "Card Type: " << cardType << "\n";
        file << "Masked Card: " << maskCardNumber() << "\n";
        file << "Expiry: " << expiryDate << "\n\n";
        file.close();
    }

    // Main function to display all card information and perform validations
    void displayCardInfo() {
        cout << "\nCard Holder: " << cardHolder << endl;
        cout << "Card Number (masked): " << maskCardNumber() << endl;
        
        cardType = detectCardType();  // Detect and set card type
        cout << "Card Type: " << cardType << endl;
        cout << "CVV Status: " << (isCVVValid() ? "Valid" : "Invalid") << endl;
        
        checkExpiry();  // Check expiry status
        logToFile();    // Log to file
    }
};

// Enhanced derived class with additional features
class EnhancedCard : public CreditCard {
public:
    // Constructor that calls parent constructor
    EnhancedCard(string number, string expiry, string holder, int cvv)
        : CreditCard(number, expiry, holder, cvv) {}

    // Generates a random risk score for demonstration purposes
    // In real applications, this would use actual fraud detection algorithms
    void cardRiskScore() {
        srand(time(0));  // Seed random number generator with current time
        float risk = (rand() % 100) / 100.0;  // Generate random float between 0-1
        cout << "AI Risk Score (0=Safe, 1=High Risk): " << fixed << setprecision(2) << risk << endl;
    }
};

// Main function - entry point of the program
int main() {
    try {
        // Display welcome message
        cout << "💳 Welcome to Credit Card Validator 💳\n\n";
        
        // Declare variables for user input
        string number, expiry, holder;
        int cvv;

        // Get user input for card details
        cout << "Enter Card Number (no spaces or dashes): ";
        cin >> number;

        cout << "Enter Expiry Date (MM/YY): ";
        cin >> expiry;

        cout << "Enter Card Holder Name: ";
        cin.ignore();  // Clear input buffer before getline
        getline(cin, holder);  // Use getline to handle spaces in name

        cout << "Enter CVV: ";
        cin >> cvv;

        // Validate card number length (standard range is 13-19 digits)
        if (number.length() < 13 || number.length() > 19)
            throw CardException("❌ Invalid card number length!");

        // Create enhanced card object with user input
        EnhancedCard card(number, expiry, holder, cvv);

        // Validate card number using Luhn algorithm
        if (!card.validateCardNumber())
            throw CardException("❌ Card number failed Luhn check! Invalid.");

        // Display card information and perform all validations
        card.displayCardInfo();
        
        // Display AI-generated risk score
        card.cardRiskScore();

    } catch (CardException& e) {
        // Handle custom card exceptions
        cerr << e.what() << endl;
    } catch (...) {
        // Handle any other unexpected exceptions
        cerr << "Unexpected error occurred!" << endl;
    }

    return 0;  // Program executed successfully
}
