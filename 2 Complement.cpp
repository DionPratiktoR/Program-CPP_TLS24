#include <iostream>     // Include the iostream library for input and output
#include <bitset>       // Include the bitset library for binary conversion
#include <string>       // Include the string library for string manipulation
#include <vector>       // Include the vector library for using vectors
#include <sstream>      // Include the sstream library for string stream operations
#include <iomanip>      // Include the iomanip library for input/output manipulations
using namespace std;

// Function to convert decimal to binary and remove leading zeros
string decimalToBinary(int decimal) {
    string binary = bitset<32>(decimal).to_string(); // Convert decimal to 32-bit binary string
    return binary.erase(0, binary.find_first_not_of('0')); // Remove leading zeros
}

// Function to convert hexadecimal to binary and remove leading zeros
string hexToBinary(string hex) {
    string binary = ""; // Initialize an empty string for binary representation
    for (char digit : hex) { // Loop through each character in the hexadecimal string
        switch (digit) { // Convert each hexadecimal digit to its binary equivalent
            case '0': binary += "0000"; break;
            case '1': binary += "0001"; break;
            case '2': binary += "0010"; break;
            case '3': binary += "0011"; break;
            case '4': binary += "0100"; break;
            case '5': binary += "0101"; break;
            case '6': binary += "0110"; break;
            case '7': binary += "0111"; break;
            case '8': binary += "1000"; break;
            case '9': binary += "1001"; break;
            case 'A': case 'a': binary += "1010"; break;
            case 'B': case 'b': binary += "1011"; break;
            case 'C': case 'c': binary += "1100"; break;
            case 'D': case 'd': binary += "1101"; break;
            case 'E': case 'e': binary += "1110"; break;
            case 'F': case 'f': binary += "1111"; break;
            default: binary += "????"; // Handle invalid hexadecimal digits
        }
    }
    return binary.erase(0, binary.find_first_not_of('0')); // Remove leading zeros
}

// Function to convert binary to decimal
int binaryToDecimal(string binary) {
    return stoi(binary, nullptr, 2); // Convert binary string to decimal integer
}

// Function to convert decimal to hexadecimal with capital letters
string decimalToHex(int decimal) {
    stringstream ss;
    ss << uppercase << hex << decimal; // Convert decimal to uppercase hexadecimal string
    return ss.str();
}

// Function to subtract using 2's complement with step-by-step process
int subtractUsingTwosComplement(string binaryA, string binaryB) {
    cout << "Step-by-step process of 2's complement subtraction:" << endl;
    cout << "1. Convert the numbers to binary:" << endl;
    cout << "   " << binaryA << " (input)" << endl;
    cout << "   " << binaryB << " (input)" << endl;

    cout << "2. Find the 2's complement of the subtrahend (" << binaryB << "):" << endl; //subtrahend is the number that is being subtracted
    int decimalB = binaryToDecimal(binaryB);
    int onesComplement = ~decimalB;
    string binaryOnesComplement = bitset<8>(onesComplement).to_string();
    cout << "   1's complement: " << binaryOnesComplement << endl;
    int twosComplement = onesComplement + 1;
    string binaryTwosComplement = bitset<8>(twosComplement).to_string();
    cout << "   Add 1: " << binaryTwosComplement << endl;

    cout << "3. Add the minuend (" << binaryA << ") to the 2's complement of the subtrahend:" << endl; //minuend is the number from which another number is subtracted
    int decimalA = binaryToDecimal(binaryA);
    int result = decimalA + twosComplement;
    string binaryResult = bitset<9>(result).to_string();
    cout << "   Binary addition result: " << binaryResult << endl;

    cout << "4. Handle the carry (if any):" << endl;
    result = result & 0xFF; // Discard the carry out
    binaryResult = bitset<8>(result).to_string();
    cout << "   Result after discarding carry: " << binaryResult << endl;

    cout << "5. Interpret the result:" << endl;
    cout << "   Final result in decimal: " << result << endl;

    return result;
}

int main() {
    const int numInputs = 2; // Define the number of inputs
    vector<int> decimals(numInputs); // Vector to store decimal inputs
    vector<string> hexadecimals(numInputs); // Vector to store hexadecimal inputs
    vector<string> binaries(numInputs); // Vector to store binary inputs
    char choice; // Variable to store user's choice
    string exitCommand = "exit"; // Command to exit the program

    while (true) { // Infinite loop to keep the program running until exit command
        cout << "Do you want to input binary, decimal, or hexadecimal numbers? (b/d/h): ";
        cin >> choice; // Get user's choice

        if (choice == 'b' || choice == 'B') { // If user chooses binary
            cout << "Enter exactly 2 binary numbers:" << endl;
            for (int i = 0; i < numInputs; ++i) {
                cin >> binaries[i]; // Get binary inputs
            }

            cout << "\nBinary to Decimal and Hexadecimal:" << endl;
            for (string binary : binaries) {
                int decimal = binaryToDecimal(binary);
                cout << "Binary: " << binary << ", Decimal: " << decimal << ", Hexadecimal: " << decimalToHex(decimal) << endl; // Display binary, decimal, and hexadecimal
            }

            int result = subtractUsingTwosComplement(binaries[0], binaries[1]); // Subtract using 2's complement
            cout << "\nResult of " << binaries[0] << " - " << binaries[1] << " using 2's complement:" << endl;
            cout << "Binary: " << decimalToBinary(result) << ", Decimal: " << result << ", Hexadecimal: " << decimalToHex(result) << endl; // Display result in binary, decimal, and hexadecimal

        } else if (choice == 'd' || choice == 'D') { // If user chooses decimal
            cout << "Enter exactly 2 decimal numbers:" << endl;
            for (int i = 0; i < numInputs; ++i) {
                cin >> decimals[i]; // Get decimal inputs
            }

            cout << "\nDecimal to Binary and Hexadecimal:" << endl;
            for (int decimal : decimals) {
                cout << "Decimal: " << decimal << ", Binary: " << decimalToBinary(decimal) << ", Hexadecimal: " << decimalToHex(decimal) << endl; // Display decimal, binary, and hexadecimal
            }

            int result = subtractUsingTwosComplement(decimalToBinary(decimals[0]), decimalToBinary(decimals[1])); // Subtract using 2's complement
            cout << "\nResult of " << decimals[0] << " - " << decimals[1] << " using 2's complement:" << endl;
            cout << "Binary: " << decimalToBinary(result) << ", Decimal: " << result << ", Hexadecimal: " << decimalToHex(result) << endl; // Display result in binary, decimal, and hexadecimal

        } else if (choice == 'h' || choice == 'H') { // If user chooses hexadecimal
            cout << "Enter exactly 2 hexadecimal numbers:" << endl;
            for (int i = 0; i < numInputs; ++i) {
                cin >> hexadecimals[i]; // Get hexadecimal inputs
            }

            cout << "\nHexadecimal to Binary and Decimal:" << endl;
            for (string hex : hexadecimals) {
                int decimal = stoi(hex, nullptr, 16);
                cout << "Hexadecimal: " << hex << ", Binary: " << hexToBinary(hex) << ", Decimal: " << decimal << endl; // Display hexadecimal, binary, and decimal
            }

            int decimal1 = stoi(hexadecimals[0], nullptr, 16); // Convert first hexadecimal to decimal
            int decimal2 = stoi(hexadecimals[1], nullptr, 16); // Convert second hexadecimal to decimal
            int result = subtractUsingTwosComplement(decimalToBinary(decimal1), decimalToBinary(decimal2)); // Subtract using 2's complement
            cout << "\nResult of " << hexadecimals[0] << " - " << hexadecimals[1] << " using 2's complement:" << endl;
            cout << "Binary: " << decimalToBinary(result) << ", Decimal: " << result << ", Hexadecimal: " << decimalToHex(result) << endl; // Display result in binary, decimal, and hexadecimal

        } else { // If user enters an invalid choice
            cout << "Invalid choice. Please enter 'b' for binary, 'd' for decimal, or 'h' for hexadecimal." << endl;
        }

        string input;
        cout << "To continue, press any key. To exit, type 'exit': ";
        cin >> input; // Get user's input to continue or exit
        if (input == exitCommand) { // If user types 'exit'
            cout << "Exiting program." << endl;
            break; // Exit the loop and end the program
        }
    }

    return 0; // Return 0 to indicate successful execution
}