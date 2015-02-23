class Deframer
{
public:
    Deframer(const int cChannels = 1, const int cSamplesPerFrame = 1600);

    void ValidateNextWord(unsigned short value);

    long long ErrorCountTimestamp();
    long long ErrorCountFrame();

    void ResetCounters();

    long long m_cwTotal;
    long long m_cwSkipped; // Count of words skipped.
    long long m_cFrames;

    long long m_cErrorTimestamp;
    long long m_cErrorFrame;

private:
    const int m_cChannels;
    const int m_cSamplesPerFrame;

    int m_iFrame; // Where deframer is, in a frame.

    unsigned long long m_timestamp;
    unsigned long long m_nextTimestamp;

};
