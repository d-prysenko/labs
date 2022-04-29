#include "Bubble.h"

void Bubble::sort()
{
    for (int i = 0; i < m_size; ++i)
    {
        for (int j = m_size - 1; j > i; --j)
        {
            if (m_data[i] > m_data[j])
            {
                std::swap(m_data[i], m_data[j]);
            }
        }
    }
}

void Bubble::foreach()
{
    for (int i = 0; i < m_size; i++)
        m_data[i] = sqrt(m_data[i]);
}
