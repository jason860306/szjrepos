#include "tiny_isrc_online_cmd.h"

int tiny_lsrc_online::proc_cmd()
{
///    m_out.m_result = 0;
///    m_out.m_breport = 1;

    static char isrc_online[] = { "yes, i'm here!" };
    tiny_base_command<tiny_isrc_online_cmd, tiny_lsrc_online_res_cmd>::trans_msg(isrc_online, sizeof(isrc_online));

    return 0;
}
