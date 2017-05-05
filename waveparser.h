#ifndef WAVEPARSER_H
#define WAVEPARSER_H

#include <fstream>
#include <vector>
#include <array>
#include <list>

#define SIZE_HEAD_DATA 44

class WaveParser
{
public:
    WaveParser(const char *pathToFile);

public:
    struct WaveHead {
    #define lenstr 4

        char chunkId [lenstr];

        __uint32_t chunkSize;

        char format[lenstr];
        char subchunk1Id[lenstr];

        __uint32_t subchunk1Size;
        __uint16_t audioFormat;
        __uint16_t numChannels;
        __uint32_t sampleRate;
        __uint32_t byteRate;
        __uint16_t blockAlign;
        __uint16_t bitsPerSample;

        char subchunk2Id[lenstr];

        __uint32_t subchunk2Size;

    } head;

private:
    void readHead(std::ifstream &source);
    void readBody(std::ifstream &source);

public:
    void printHead();

    typedef std::vector<__int16_t> Channel;
    typedef std::pair<Channel, Channel> LeftRightScannels;
    typedef std::list<LeftRightScannels> FXBody;

    FXBody getAllShanels();

    LeftRightScannels getScannels();

    std::vector<__int32_t> getSample();


private:
#define BLOCK_SIZE 32*1024
    typedef std::vector<char> BlockType;
//    typedef std::array<char, BLOCK_SIZE> BlockType;
    typedef std::pair<BlockType, int/*use bytes*/> ContainerObj;
    std::list<ContainerObj> blocksBody;
};

#endif // WAVEPARSER_H
