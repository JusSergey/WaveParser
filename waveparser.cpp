#include "waveparser.h"
#include <iostream>

using namespace std;

WaveParser::WaveParser(const char *pathToFile)
{
    ifstream source(pathToFile);

    readHead(source);
    readBody(source);

    printHead();

    cout << "deconding complete...\n";

    cout.flush();
}

void WaveParser::readHead(ifstream &source)
{
    source.read((char *)&head, sizeof(head));
}

void WaveParser::readBody(ifstream &source)
{
    const int oneSecondBytes = head.sampleRate * head.blockAlign;
    ContainerObj block;
    block.first.resize(oneSecondBytes);
    char *begin = &block.first[0];

    size_t size_file = -1;

    {   // get size file
        int curr_pos = source.tellg();
        source.seekg(0, std::ios::end);
        size_file = source.tellg();
        source.seekg(curr_pos);
    }

    while (source.tellg() < size_file) {
        block.second = source.readsome(begin, oneSecondBytes);
        blocksBody.push_back(block);
    }
}

void print4byte(const char *buffer) {
    for (int i = 0; i < 4; i++)
        cout.put(buffer[i]);

    cout.put('\n').flush();
}

void WaveParser::printHead()
{
    cout << '\n';
    cout << "chunkSize:     " << head.chunkSize << '\n';

    cout << "format:        "; print4byte(head.format);
    cout << "subchunk1Id:   "; print4byte(head.subchunk1Id);

    cout << "subchunk1Size: " << head.subchunk1Size << '\n'
         << "subchunk2Size: " << head.subchunk2Size << '\n'
         << "audioFormat:   " << head.audioFormat << '\n'
         << "numChannels:   " << head.numChannels << '\n'
         << "sampleRate:    " << head.sampleRate << '\n'
         << "byteRate:      " << head.byteRate << '\n'
         << "blockAlign:    " << head.blockAlign << '\n'
         << "bitsPerSample: " << head.bitsPerSample << '\n'
         << '\n';

    print4byte(head.subchunk2Id);

    cout << head.subchunk2Size << '\n';

    cout.flush();
}

WaveParser::FXBody WaveParser::getAllShanels()
{
    const int step = head.bitsPerSample/8;

    WaveParser::FXBody fxbody;

    __uint32_t insertBytes = 0;

    const __uint32_t sz = head.byteRate / step * head.numChannels;

    for (auto &obj : blocksBody) {

        const __uint32_t reserveSize = (head.subchunk2Size - insertBytes > sz ? sz : head.subchunk2Size - insertBytes);
        insertBytes += sz;

        Channel r, l;
        r.reserve(reserveSize);
        l.reserve(reserveSize);

        BlockType &block = obj.first;

        for (int i = 0, ispair = 0; i < reserveSize; i += step, ++ispair)
            (ispair & 1 ? r : l).push_back(*((Channel::value_type*)&block[i]));

        fxbody.push_back( std::move(WaveParser::LeftRightScannels( std::move(l), std::move(r) )) );

    }

    return fxbody;
}

//WaveParser::LeftRightScannels WaveParser::getScannels()
//{
//    const int step = head.bitsPerSample/8;

//    BlockType &block = blocksBody.begin()->first;

//    Channel r, l;
//    r.reserve(head.byteRate/step + 8);
//    l.reserve(head.byteRate/step + 8);

//    for (int i = 0; i < head.byteRate; i += step)
//        ((i / step) & 1 ? r : l).push_back(*((Channel::value_type*)&block[i]));

//    return WaveParser::LeftRightScannels(std::move(l), std::move(r));
//}

//std::vector<__int32_t> WaveParser::getSample()
//{
//    int step = head.bitsPerSample/8;

//    BlockType &block = blocksBody.begin()->first;

//    int mask = ((1 << (head.bitsPerSample)) - 1);

//    std::vector<__int32_t> result;
//    result.reserve(head.byteRate/step + 8);

//    for (int i = 0; i < head.byteRate; i += step)
//        result.push_back(*((int*)&block[i]));

//    return result;
//}
