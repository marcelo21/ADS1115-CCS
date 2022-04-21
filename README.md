# ADS1115-CCS
Here you will find the driver to manipulate the ads1115 for the CCS compiler

# Functions

```c
void writeConfig( unsigned int8 i2cAdress = 0, unsigned int16 config = 0 );

unsigned int16 readConversion( unsigned int8 i2cAdress = 0 );
```

# Example

Now look at an example and remember the ADDR = GND.

1. Set config variable (see ADS1115.h)
2. Write config (call function)
3. Read config (call function)

```c
#include "ADS1115.h"
#include "ADS1115.c"

unsigned int16 data = 0;
unsigned int16 config = 0;

data = 0;
config = 0;
         
config = ADDR_CONFIG_OS_TRUE       |
         ADDR_CONFIG_MUX_5         |
         ADDR_CONFIG_PGA_3         |
         ADDR_CONFIG_MODE_SINGLE   |
         ADDR_CONFIG_DATA_RATE_5   |
         ADDR_CONFIG_COMP_MODE_1   |
         ADDR_CONFIG_COMP_POL_1    |
         ADDR_CONFIG_COMP_LAT_1    |
         ADDR_CONFIG_COMP_QUE_4;
         
writeConfig( ADDR_GND, config );
data = readConversion( ADDR_GND );

printf("%d", data);
```
