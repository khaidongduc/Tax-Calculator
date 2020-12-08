#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *buffer;
int buffsize;

/**
 * @brief prepare the buffer for the input
 *
 * @param size the size of the buffer
 */
void setBufferSize(int size) {
    buffer = (char *)malloc(size * sizeof(char));
    buffsize = size;
}

/**
 * @brief Validate if the buffer can be converted to double
 *
 * @param buffer the buffer
 * @return true if the buffer can be converted to double
 * @return false otherwise
 */
bool validateDouble(char *buffer) {
    int length = strlen(buffer);
    int dotCount = 0;
    for (int i = 0; i < length - 1; ++i) {
        if (('0' > buffer[i] || buffer[i] > '9') && buffer[i] != '.')
            return false;
        dotCount += (buffer[i] == '.');
    }
    return (dotCount <= 1);
}

/**
 * @brief Validate if the buffer can be converted to int
 *
 * @param buffer the buffer
 * @return true if the buffer can be converted to int
 * @return false otherwise
 */
bool validateInt(char *buffer) {
    int length = strlen(buffer);
    for (int i = 0; i < length - 1; ++i)
        if ('0' > buffer[i] || buffer[i] > '9') return false;
    return true;
}

/**
 * @brief Validate if the buffer can be converted to y/n
 *
 * @param buffer the buffer
 * @return true if the buffer can be converted to y/n
 * @return false otherwise
 */
bool validateYN(char *buffer) {
    int length = strlen(buffer);
    return length == 2 && (buffer[0] == 'y' || buffer[0] == 'n');
}

/**
 * @brief Get the Input object, return a pointer char* that contain the buffer
 * that satisfy validate
 *
 * @param validate validation function to validate the buffer.
 * @param askMsg the message to ask user to input
 * @param errMsg the error message
 * @return char* the inputted buffer that satisfy validate
 */
char *getInput(bool (*validate)(char *buffer), char *askMsg, char *errMsg) {
    printf("%s ", askMsg);
    fgets(buffer, buffsize, stdin);
    while (!validate(buffer)) {
        printf("%s\n%s ", errMsg, askMsg);
        fgets(buffer, buffsize, stdin);
    }
    return buffer;
}
