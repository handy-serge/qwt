#include "Deframer.hpp"

#include <stdio.h>

Deframer::Deframer(int cChannels, int cSamplesPerFrame)
    : m_cChannels(cChannels)
    , m_cSamplesPerFrame(cSamplesPerFrame)
    , m_iFrame(0)
    , m_timestamp(0)
    , m_nextTimestamp(0)
{
}


void Deframer::ValidateNextWord(unsigned short value)
{
    ++m_cwTotal;

    switch (m_iFrame)
    {
    case -1: /* End of frame */

        if (value != 0xFFFE)
        {
            fprintf(stderr, "Expected EOF but got %d (0x%04X)",
                    value, value);
            ++m_cErrorFrame;
        }
        else
        {
            ++m_cFrames;
        }

        ++m_iFrame;

        break;

    case 0: /* Start of frame */

        if (value != 0x0001)
        {
            ++m_cwSkipped;
        }
        else
        {
            if (0 != m_cwSkipped)
            {
                fprintf(stderr, "Skipped %lld (0x%0llX) words searching for SOF\n",
                        m_cwSkipped, m_cwSkipped);
                m_cwSkipped = 0;
            }

            ++m_iFrame;
        }

        break;

    case 1: /* Timestamp */
        /* Timestamp reset in two lines to be more explicit */
        m_timestamp = 0;
        m_timestamp = m_timestamp | (long long)(value & 0x7FFF) << 0;
        ++m_iFrame;
        break;

    case 2:
        m_timestamp = m_timestamp | (long long)(value & 0x7FFF) << 15;
        ++m_iFrame;
        break;

    case 3:
        m_timestamp = m_timestamp | (long long)(value & 0x7FFF) << 30;
        ++m_iFrame;
        break;

    case 4:
        m_timestamp = m_timestamp | (long long)(value & 0x7FFF) << 45;
        ++m_iFrame;

        if (m_timestamp != m_nextTimestamp && m_nextTimestamp != 0)
        {
            fprintf(stderr, "Expected timestamp offset %d (0x%X) but got %lld (0x%llX)\n",
                    m_cSamplesPerFrame, m_cSamplesPerFrame,
                    m_timestamp - m_nextTimestamp, m_timestamp - m_nextTimestamp);
            ++m_cErrorTimestamp;
        }

        m_nextTimestamp = m_timestamp + m_cSamplesPerFrame;

        break;

    default: /* Payload */

        //write_out(value);
        ++m_iFrame;

        /* Check if we should get EOF */
        if (m_iFrame > (m_cChannels * m_cSamplesPerFrame + 4))
        {
            m_iFrame = -1;
        }

        break;
    }
}
