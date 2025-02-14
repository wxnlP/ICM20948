#include "timer.h"

/**********************************************************************
 * 函数名称： system_get_ns
 * 功能描述： 获得系统时间(单位ns)
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 系统时间(单位ns)
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2023/08/03	     V1.0	  韦东山	      创建
 ***********************************************************************/
uint64_t system_get_ns(void)
{
    //extern uint32_t HAL_GetTick(void);
    extern TIM_HandleTypeDef        htim6;
    TIM_HandleTypeDef *hHalTim = &htim6;

    uint64_t ns = HAL_GetTick();
    uint64_t cnt;
    uint64_t reload;

    cnt = __HAL_TIM_GET_COUNTER(hHalTim);
    reload = __HAL_TIM_GET_AUTORELOAD(hHalTim);

    ns *= 1000000;
    ns += cnt * 1000000 / reload;
    return ns;
}
