#include <string>
#include <iostream>

class CipherTool
{
public:
    CipherTool();
    ~CipherTool() = default;
    void runCipher();

private:
    // cipher functions
    void determineCipherType();
    void determineEncodeOrDecode();
    void readInText();
    void runShiftCipher();
    void runMonoCipher();

    // general variables
    int cipherType;
    int encodeOrDecode;
    std::string plainText;
    std::string cipherText;
    bool keepRunningTool;
    bool validInput;
    bool firstRun;

    // shift cipher specific variables
    int shiftSize;

    // mono-alphabetic substitution cipher variables
    std::string monoKey;

    // enums
    enum cipherType { cipher_UNKNOWN, cipher_SHIFT, cipher_MONO };
    enum encodeOrDecode { direction_UNKNOWN, Encode, Decode };
};
