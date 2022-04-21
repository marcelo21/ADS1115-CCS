///////////////////////////////////////////////////////////////////////////////ADDR.
#define ADDR_GND                    0b10010000           // GND
#define ADDR_VDD                    0b10010010           // VDD
#define ADDR_SDA                    0b10010100           // SDA
#define ADDR_SCL                    0b10010110           // SCL

///////////////////////////////////////////////////////////////////////////////ADDR POINTER REGISTER.
#define ADDR_POINTER_CONVERSION     0b00000000           // Conversion register 
#define ADDR_POINTER_CONFIGURATION  0b00000001           // Config register
#define ADDR_POINTER_LO_THRESH      0b00000010           // Lo_thresh register 
#define ADDR_POINTER_HI_THRESH      0b00000011           // Hi_thresh register

///////////////////////////////////////////////////////////////////////////////CONVERSION REGISTER.
#define ADDR_CONVERSION_RESET       0x0000               // Reset

///////////////////////////////////////////////////////////////////////////////CONFIG REGISTER.
#define ADDR_CONFIG_OS_FALSE        0b0000000000000000   // No effect
#define ADDR_CONFIG_OS_TRUE         0b1000000000000000   // Start a single conversion (when in power-down state) 

#define ADDR_CONFIG_MUX_1           0b0000000000000000   // (+): AIN0 __ (-): AIN1 (default)
#define ADDR_CONFIG_MUX_2           0b0001000000000000   // (+): AIN0 __ (-): AIN3
#define ADDR_CONFIG_MUX_3           0b0010000000000000   // (+): AIN1 __ (-): AIN3
#define ADDR_CONFIG_MUX_4           0b0011000000000000   // (+): AIN2 __ (-): AIN3
#define ADDR_CONFIG_MUX_5           0b0100000000000000   // (+): AIN0 __ (-): GND
#define ADDR_CONFIG_MUX_6           0b0101000000000000   // (+): AIN1 __ (-): GND
#define ADDR_CONFIG_MUX_7           0b0110000000000000   // (+): AIN2 __ (-): GND
#define ADDR_CONFIG_MUX_8           0b0111000000000000   // (+): AIN3 __ (-): GND

#define ADDR_CONFIG_PGA_1           0b0000000000000000   // FSR: +/- 6.144 V
#define ADDR_CONFIG_PGA_2           0b0000001000000000   // FSR: +/- 4.096 V
#define ADDR_CONFIG_PGA_3           0b0000010000000000   // FSR: +/- 2.048 V (default)
#define ADDR_CONFIG_PGA_4           0b0000011000000000   // FSR: +/- 1.024 V
#define ADDR_CONFIG_PGA_5           0b0000100000000000   // FSR: +/- 0.512 V
#define ADDR_CONFIG_PGA_6           0b0000101000000000   // FSR: +/- 0.256 V
#define ADDR_CONFIG_PGA_7           0b0000110000000000   // FSR: +/- 0.256 V
#define ADDR_CONFIG_PGA_8           0b0000111000000000   // FSR: +/- 0.256 V

#define ADDR_CONFIG_MODE_CONTINUOUS 0b0000000000000000   // Continuous-conversion mode
#define ADDR_CONFIG_MODE_SINGLE     0b0000000100000000   // Single-shot mode or power-down state (default)

                                                         // ADS 1115 - ADS 1015 :)                                                         
#define ADDR_CONFIG_DATA_RATE_1     0b0000000000000000   // 8   SPS - 128 SPS
#define ADDR_CONFIG_DATA_RATE_2     0b0000000000100000   // 16  SPS - 250 SPS
#define ADDR_CONFIG_DATA_RATE_3     0b0000000001000000   // 32  SPS - 490 SPS
#define ADDR_CONFIG_DATA_RATE_4     0b0000000001100000   // 64  SPS - 920 SPS 
#define ADDR_CONFIG_DATA_RATE_5     0b0000000010000000   // 128 SPS - 1600 SPS (default)
#define ADDR_CONFIG_DATA_RATE_6     0b0000000010100000   // 250 SPS - 2400 SPS
#define ADDR_CONFIG_DATA_RATE_7     0b0000000011000000   // 475 SPS - 3300 SPS
#define ADDR_CONFIG_DATA_RATE_8     0b0000000011100000   // 860 SPS - 3300 SPS

#define ADDR_CONFIG_COMP_MODE_1     0b0000000000000000   // Traditional comparator (default)
#define ADDR_CONFIG_COMP_MODE_2     0b0000000000010000   // Window comparator

#define ADDR_CONFIG_COMP_POL_1      0b0000000000000000   // Active low (default) 
#define ADDR_CONFIG_COMP_POL_2      0b0000000000001000   // Active high

#define ADDR_CONFIG_COMP_LAT_1      0b0000000000000000   // Nonlatching comparator (default)
#define ADDR_CONFIG_COMP_LAT_2      0b0000000000000100   // Latching comparator

#define ADDR_CONFIG_COMP_QUE_1      0b0000000000000000   // Assert after one conversion 
#define ADDR_CONFIG_COMP_QUE_2      0b0000000000000001   // Assert after two conversions
#define ADDR_CONFIG_COMP_QUE_3      0b0000000000000010   // Assert after four conversions
#define ADDR_CONFIG_COMP_QUE_4      0b0000000000000011   // Disable comparator and set ALERT/RDY pin to high-impedance (default)

///////////////////////////////////////////////////////////////////////////////LO_THRESH & HI_THRESH
#define ADDR_LO_THRESH_RESET        0x8000               // Reset
#define ADDR_HI_THRESH_RESET        0x7FFF               // Reset

///////////////////////////////////////////////////////////////////////////////READ & WRITE
#define ADDR_WRITE_REGISTER         0b00000000           // Write registers = low
#define ADDR_READ_REGISTER          0b00000001           // Read registers = high

///////////////////////////////////////////////////////////////////////////////RESET
#define ADDR_GLOBAL_RESET           0x06                 // Internal reset

/* EXAMPLE - 1

   -W = not( W )

   1. Write to Config register:

   - First byte : 0b10010000 (first 7-bit I2C address followed by a "low" R/-W bit) 
   - Second byte: 0b00000001 (points to Config register)
   - Third byte : 0b10000100 (MSB of the Config register to be written)
   - Fourth byte: 0b10000011 (LSB of the Config register to be written)

   2. Write to Address Pointer register:

   - First byte : 0b10010000 (first 7-bit I2C address followed by a "low" R/-W bit) 
   - Second byte: 0b00000000 (points to Conversion register) 

   3. Read Conversion register: 

   - First byte : 0b10010001 (first 7-bit I2C address followed by a "high" R/-W bit) 
   - Second byte: the ADS111x response with the MSB of the Conversion register 
   - Third byte : the ADS111x response with the LSB of the Conversion register

*/

/* EXAMPLE - 2

   -W = not( W )

   1. Write to Config register:
   
   i2c_start();               //
   i2c_write( 0b10010000 );   // first 7-bit I2C address followed by a "low" R/-W bit
   i2c_write( 0b00000001 );   // points to Config register
   i2c_write( 0b10000101 );   // MSB of the Config register to be written 
   i2c_write( 0b10000011 );   // LSB of the Config register to be written
   i2c_stop();                //
   
   2. Write to Address Pointer register:
         
   i2c_start();               //
   i2c_write( 0b10010000 );   // first 7-bit I2C address followed by a "low" R/-W bit
   i2c_write( 0b00000000 );   // points to Conversion register   
   i2c_stop();                //
         
   delay_ms( 10 );            // 
   
   3. Read Conversion register:
         
   i2c_start();               //
   i2c_write( 0b10010001 );   // first 7-bit I2C address followed by a "high" R/-W bit
   MSB = i2c_read();          // the ADS111x response with the MSB of the Conversion register
   LSB = i2c_read();          // the ADS111x response with the LSB of the Conversion register
   i2c_write( 0b00000000 );   // points to Conversion register
   i2c_stop();                //
         
   data = make16( MSB, LSB ); //

*/
