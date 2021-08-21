#include "CipherTool.h"

CipherTool::CipherTool() {
    // initialize general variables
    cipherType = cipher_UNKNOWN;
    encodeOrDecode = direction_UNKNOWN;
    plainText = "";
    cipherText = "";
    keepRunningTool = true;
    validInput = false;
    firstRun = true;

    // initialize shift cipher specific variables
    shiftSize = 0;

    // initialize mono-alphabetic cipher specific variables
    monoKey = "";
}

void CipherTool::runCipher() {
    while (keepRunningTool) {
        determineCipherType();
        determineEncodeOrDecode();
        readInText();

        // switch to run cipher func based on cipherType
        switch (cipherType) {
            case (cipher_SHIFT): { runShiftCipher(); break; }
            case (cipher_MONO): { runMonoCipher(); break; }
            case (cipher_UNKNOWN):
            default: {
                // should never get here bc cipherType is checked when read in
                printf("Oops, looks like something went wrong. Exiting the Cipher Tool now.\n\n");
                exit(0);
            }
        }

        // prompt user to decide to keep going or quit
        printf("\n\nWould you like to run the Cipher Tool again? (y/n): ");
        std::string input;
        std::getline(std::cin, input);
        if (input.find('n') != std::string::npos || input.find('N') != std::string::npos) {
            keepRunningTool = false;
        }
        // running again, so clear text strings
        plainText = "";
        cipherText = "";
    }

    // exiting program
    printf("\nThanks for using the Cipher Tool!\n\n");
    exit(0);
}

void CipherTool::determineCipherType() {
    validInput = false;
    firstRun = true;
    while (!validInput) {
        std::system("clear");
        printf("****************************************\n");
        if (!firstRun) {
            printf("Selection invalid. Please enter a number from the list below.\n\n");
        }
        printf("1) Shift Cipher\n");
        printf("2) Monoalphabetic Substitution\n");
        printf("999) Quit\n");
        printf("Enter your selection for cipher type: ");

        std::string input;
        std::getline(std::cin, input);
        int val = atoi(input.c_str());

        firstRun = false;
        if (val > cipher_UNKNOWN && val <= cipher_MONO) {
            cipherType = val;
            validInput = true;
        }
        else if (val == 999) {
            printf("\nThanks for using the Cipher Tool!\n\n");
            exit(0);
        }
    }
}

void CipherTool::determineEncodeOrDecode() {
    validInput = false;
    firstRun = true;
    while (!validInput) {
        std::system("clear");
        printf("****************************************\n");
        if (!firstRun) {
            printf("Selection invalid. Please enter a number from the list below.\n\n");
        }
        printf("1) Encode\n");
        printf("2) Decode\n");
        printf("999) Quit\n");
        printf("Enter your selection for whether you want to encode or decode: ");

        std::string input;
        std::getline(std::cin, input);
        int val = atoi(input.c_str());

        firstRun = false;
        if (val >= Encode && val <= Decode) {
            encodeOrDecode = val;
            validInput = true;
        }
        else if (val == 999) {
            printf("\nThanks for using the Cipher Tool!\n\n");
            exit(0);
        }
    }
}

void CipherTool::readInText() {
    std::system("clear");
    printf("****************************************\n");
    printf("Enter the text you would like ");
    if (encodeOrDecode == Encode) {
        printf("encoded (a-z & A-Z): ");
        std::getline(std::cin, plainText);
    }
    else if (encodeOrDecode == Decode) {
        printf("decoded (a-z & A-Z): ");
        std::getline(std::cin, cipherText);
    }
    else {
        // encodeOrDecode should always be set, but just in case
        printf("Oops, looks like something went wrong. Exiting the Cipher Tool now.\n\n");
        exit(0);
    }
}

void CipherTool::runShiftCipher() {
    validInput = false;
    firstRun = true;
    while (!validInput) {
        std::system("clear");
        printf("****************************************\n");
        if (!firstRun) {
            printf("Entry invalid. Please enter a number within the prescribed bounds.\n\n");
        }
        printf("Enter the shift size (-26 to +26): ");

        std::string input;
        std::getline(std::cin, input);
        shiftSize = atoi(input.c_str());

        firstRun = false;
        if (shiftSize >= -26 && shiftSize <= 26) {
            validInput = true;
        }
    }

    std::system("clear");
    printf("****************************************\n");
    if (encodeOrDecode == Encode) {
        for (int i = 0; i < plainText.length(); i++) {
            signed char c = plainText[i];
            // operation if char is lowercase
            if (c >= 'a' && c <= 'z') {
                // check if shift will exceed upper bound, if so, subtract before adding shift
                if (c + shiftSize > 'z' + 4) {
                    c = c - 'z' + 'a' - 1;
                }
                c += shiftSize;
                // fix any bounds issues (below 'a' or above 'z')
                if (c < 'a') {
                    c = c - 'a' + 'z' + 1;
                }
                else if (c > 'z'){
                    c = c - 'z' + 'a' - 1;
                }
            }
            // operation if char is uppercase
            else if (c >= 'A' && c <= 'Z') {
                c += shiftSize;
                // fix any bounds issues (below 'A' or above 'Z')
                if (c < 'A') {
                    c = c - 'A' + 'Z' + 1;
                }
                else if (c > 'Z'){
                    c = c - 'Z' + 'A' - 1;
                }
            }
            cipherText.push_back(c);
        }
        std::cout << "Plaintext:  " + plainText << std::endl;
        std::cout << "Ciphertext: " + cipherText << std::endl;
    }
    else if (encodeOrDecode == Decode) {
        for (int i = 0; i < cipherText.length(); i++) {
            signed char c = cipherText[i];
            // operation if char is lowercase
            if (c >= 'a' && c <= 'z') {
                // check if shift will exceed upper bound, if so, subtract before subtracting shift
                if (c - shiftSize > 'z' + 4) {
                    c = c - 'z' + 'a' - 1;
                }
                c -= shiftSize;
                // fix any bounds issues (below 'a' or above 'z')
                if (c < 'a') {
                    c = c - 'a' + 'z' + 1;
                }
                else if (c > 'z'){
                    c = c - 'z' + 'a' - 1;
                }
            }
            // operation if char is uppercase
            else if (c >= 'A' && c <= 'Z') {
                c -= shiftSize;
                // fix any bounds issues (below 'A' or above 'Z')
                if (c < 'A') {
                    c = c - 'A' + 'Z' + 1;
                }
                else if (c > 'Z'){
                    c = c - 'Z' + 'A' - 1;
                }
            }
            plainText.push_back(c);
        }
        std::cout << "Ciphertext: " + cipherText << std::endl;
        std::cout << "Plaintext:  " + plainText << std::endl;
    }
    else {
        // encodeOrDecode should always be set, but just in case
        printf("Oops, looks like something went wrong. Exiting the Cipher Tool now.\n\n");
        exit(0);
    }
}

void CipherTool::runMonoCipher() {
    validInput = false;
    firstRun = true;
    while (!validInput) {
        std::system("clear");
        printf("****************************************\n");
        if (!firstRun) {
            printf("Entry invalid. Please enter exactly 26 letters with no spaces\n\n");
        }
        printf("Enter the mono-alphabetic cipher key alphabet with no spaces.\n");
        printf("Meaning, enter exactly 26 letters, in order, of what 'a' maps to,\n");
        printf("what 'b' maps to, all the way up to what 'z' maps to (a-z & A-Z): ");

        std::getline(std::cin, monoKey);

        firstRun = false;
        // check for valid key input
        // set to true, and if we find an issue change it to false and break
        validInput = true;
        if (monoKey.length() == 26) {
            for (int i = 0; i < monoKey.length(); i++) {
                signed char c = monoKey[i];
                if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
                    validInput = false;
                    break;
                }
            }
        } else {
            validInput = false;
        }
    }

    std::system("clear");
    printf("****************************************\n");
    if (encodeOrDecode == Encode) {
        for (int i = 0; i < plainText.length(); i++) {
            signed char c = plainText[i];
            // operation if char is lowercase
            if (c >= 'a' && c <= 'z') {
                c = monoKey[c - 'a'];
            }
            // operation if char is uppercase
            else if (c >= 'A' && c <= 'Z') {
                c = monoKey[c - 'A'];
            }
            cipherText.push_back(c);
        }
        std::cout << "Plaintext:  " + plainText << std::endl;
        std::cout << "Ciphertext: " + cipherText << std::endl;
    }
    else if (encodeOrDecode == Decode) {
        for (int i = 0; i < cipherText.length(); i++) {
            // make all lowercase for ease of decoding
            // and so two keys aren't needed (one for upper, one for lower)
            signed char c = tolower(cipherText[i]);
            // for each letter, run through key and decipher based on index where letter is found
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                for (int j = 0; j < monoKey.length(); j++) {
                    if (c == tolower(monoKey[j])) {
                        c = 'a' + j;
                        break;
                    }
                }
            }
            plainText.push_back(c);
        }
        std::cout << "Ciphertext: " + cipherText << std::endl;
        std::cout << "Plaintext:  " + plainText << std::endl;
    }
    else {
        // encodeOrDecode should always be set, but just in case
        printf("Oops, looks like something went wrong. Exiting the Cipher Tool now.\n\n");
        exit(0);
    }
}
