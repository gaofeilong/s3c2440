#define	GPBCON		(*(volatile unsigned long *)0x56000010)
#define	GPBDAT		(*(volatile unsigned long *)0x56000014)

typedef void (*init_fun)(void);

void  wait(unsigned long dly)
{
	for(; dly > 0; dly--);
}

static void led_up(void)
{
	GPBCON = 0x00111400;
        GPBDAT = 0x140;
}

static init_fun init[] =
{
        led_up,
        0
};

int main(void)
{
	// ��LED1-4��Ӧ��GPB5/6/7/8�ĸ�������Ϊ���
        int i;
        for (i = 0; init[i]; ++i) {
                init[i](); 
        }
        while (1);

        return 0;
}
