#ifndef COM_MAIN_H
#define COM_MAIN_H

// Telemetry timing.
#define AIC_CLOCK_RESOLUTION               100 // ticks per second
#define AIC_TELEMETRY_RETRY                (1*AIC_CLOCK_RESOLUTION)
#define AIC_TELEMETRY_WARNING_PERIOD       (120*AIC_CLOCK_RESOLUTION)
#define AIC_INTERROGRATE_MODEM_TONE_PERIOD (6*AIC_CLOCK_RESOLUTION)


//Phone tone timers
#define AIC_TONE_ONTIME    500
#define AIC_TONE_QUIETTIME 2375


#endif

