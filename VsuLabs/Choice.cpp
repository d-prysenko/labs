#include "Choice.h"

void Choice::sort()
{
    for (int j = 0; j < m_size - 1; ++j)
    {
        int min = j;
        for (int i = j + 1; i < m_size; ++i)
        {
            if (m_data[min] > m_data[i])
                min = i;
        }
        if (min != j)
            std::swap(m_data[j], m_data[min]);
    }
}

void Choice::foreach()
{
    for (int i = 0; i < m_size; i++)
    {
        if (m_data[i] < 0)
            m_data[i] = NAN;
        else
            m_data[i] = log(m_data[i]);
    }
}
