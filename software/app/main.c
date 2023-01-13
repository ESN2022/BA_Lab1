#include <system.h>
#include <altera_avalon_pio_regs.h>
#include <sys/alt_stdio.h>
#include <sys/alt_irq.h>
#include <alt_types.h>
#include <io.h>
#include <unistd.h>

void chenillard_simple(void);
void chenillard_button_polling(void);
void chenillard_button_interrupt(void);
static void init_button_pio(void);
static void init_switch_pio(void);
//  void chenillard_switch_control_speed(void);

/*Interrupts_functions*/
static void button_IRQ(void *context, alt_u32 id);
static void switch_IRQ(void *context, alt_u32 id);

int start = 0;
int vitesse_chenillard = 0;

int main()
{
    init_button_pio();
    init_switch_pio();
    //   chenillard_simple();
    // chenillard_button_polling();
    chenillard_button_interrupt();

    return 0;
}

void chenillard_simple(void)
{
    int led = 0x01;

    while (1)
    {

        if (led == 0x10000000)
        {
            led = 0x01;
        }
        IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, led);
        led = led << 1;

        usleep(100000);
    }
}

void chenillard_button_polling(void)
{
    int led = 0x01;

    while (1)
    {
        /*Si le boutton est appuyé*/
        if (IORD_ALTERA_AVALON_PIO_DATA(PIO_1_BASE) == 0)
        {
            if (led == 0x10000000)
            {
                led = 0x01;
            }
            IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, led);
            led = led << 1;

            usleep(100000);
        }
        else
            IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, 0);
    }
}

void chenillard_button_interrupt(void)
{
    int led = 0x01;
    long tempo = 0;

    while (1)
    {
        if (start == 1)
        {
            tempo = vitesse_chenillard * 100;
            if (led == 0x10000000)
            {
                led = 0x01;
            }
            IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, led);
            led = led << 1;
            usleep(tempo);
        }
    }
}

static void button_IRQ(void *context, alt_u32 id)
{
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE, 0);
    start = 1; // notifie qu'il y a une interruption pour déclencher le chenillard
}

static void switch_IRQ(void *context, alt_u32 id)
{
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_2_BASE, 0);
    int switch_value = IORD_ALTERA_AVALON_PIO_DATA(PIO_2_BASE);
    alt_printf("sw_value = %x\n", switch_value);

    switch (switch_value)
    {
    case 1:
        vitesse_chenillard = 100;
        break;
    case 2:
        vitesse_chenillard = 200;
        break;
    case 4:
        vitesse_chenillard = 300;
        break;
    case 8:
        vitesse_chenillard = 400;
        break;
    default:
        vitesse_chenillard = 1000;
    }
}

static void init_button_pio(void)
{
    /* Enable all 4 button interrupts. */
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_1_BASE, 0x1);
    /* Reset the edge capture register. */
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE, 0);
    /* Register the ISR. */
    alt_irq_register(PIO_1_IRQ, NULL, (void *)button_IRQ);
}

static void init_switch_pio(void)
{
    /* Enable all 4 button interrupts. */
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_2_BASE, 0x7F);
    /* Reset the edge capture register. */
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_2_BASE, 0);
    /* Register the ISR. */
    alt_irq_register(PIO_2_IRQ, NULL, (void *)switch_IRQ);
}