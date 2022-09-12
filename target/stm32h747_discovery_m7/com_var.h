struct  com_var{
    uint32_t    free_count;
    uint32_t    tim1_count;
    int8_t      push_hsem;
};

#define COM_AREA ((struct com_var*)0x10040000)

#define COM_FREE_COUNT  (COM_AREA->free_count)
#define COM_TIM1_COUNT  (COM_AREA->tim1_count)
#define COM_PUSH_HSEM   (COM_AREA->push_hsem)

#define HSEM_CM4_to_CM7_CLK_IT      0
#define HSEM_CM4_to_CM7_SYSLOG_IT   1
