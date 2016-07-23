#include "utils.h"

bool in_diapazon(int num, int start_num, int end_num)
{
    if (num >= start_num && num <= end_num)
        return true;
    return false;
}
