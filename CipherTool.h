#include <string>
#include <iostream>

class CipherTool
{
public:
    CipherTool();
    ~CipherTool() = default;
    void runCipher();
    void determineCipherType();
    void determineEncodeOrDecode();
    void readInText();
    void runShiftCipher();

private:
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

    // enums
    enum cipherType { cipher_UNKNOWN, cipher_SHIFT };
    enum encodeOrDecode { direction_UNKNOWN, Encode, Decode };
};
