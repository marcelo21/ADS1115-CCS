void writeConfig( unsigned int16 config = 0 );
unsigned int16 readConversion( unsigned int16 CHANNEL = 0 );

void writeConfig( unsigned int16 config = 0 )
{
   unsigned int8 MSB = 0;
   unsigned int8 LSB = 0;
   
   MSB = config >> 8;
   LSB = config & 0xFF;
   
   i2c_start();
   delay_us( 1 );
   i2c_write( ADDR_GND | ADDR_WRITE_REGISTER );
   i2c_write( ADDR_POINTER_CONFIGURATION );
   i2c_write( MSB );
   i2c_write( LSB );
   i2c_stop();
}

unsigned int16 readConversion( unsigned int16 CHANNEL = 0 )
{
   unsigned int16 config = 0;
   
   unsigned int8 MSB = 0;
   unsigned int8 LSB = 0;
   
   unsigned int16 result;
   
   //////////////////////////////////////////////////////////////////////////// CONFIGURATION
   config = ADDR_CONFIG_OS_TRUE       |
            ADDR_CONFIG_PGA_1         |
            ADDR_CONFIG_MODE_SINGLE   |
            ADDR_CONFIG_DATA_RATE_8   |
            ADDR_CONFIG_COMP_MODE_1   |
            ADDR_CONFIG_COMP_POL_1    |
            ADDR_CONFIG_COMP_LAT_1    |
            ADDR_CONFIG_COMP_QUE_4;
            
   switch( CHANNEL ){
      case 1:
         config |= ADDR_CONFIG_MUX_5;
         break;
         
      case 2:
         config |= ADDR_CONFIG_MUX_6;
         break;
         
      case 3:  
         config |= ADDR_CONFIG_MUX_7;
         break;
         
      case 4:
         config |= ADDR_CONFIG_MUX_8;
         break;
         
      default:
         config |= ADDR_CONFIG_MUX_5;
         break;
   }
   
   writeConfig( config );
   delay_us( 30 );           // MUY IMPORTANTE, NO QUITAR.
   ////////////////////////////////////////////////////////////////////////////
   
   //////////////////////////////////////////////////////////////////////////// ¿ CONVERSION COMPLETE ?
   do{
      MSB = 0;
      LSB = 0;
   
      i2c_start();
      delay_us( 1 );
      i2c_write( ADDR_GND | ADDR_READ_REGISTER );
      i2c_write( ADDR_POINTER_CONFIGURATION );
      MSB = i2c_read();
      LSB = i2c_read();
      i2c_stop();
   }while( ( make16( MSB, LSB ) & 0x8000 ) == 0 );
   ////////////////////////////////////////////////////////////////////////////
   
   i2c_start();
   delay_us( 1 );
   i2c_write( ADDR_GND | ADDR_WRITE_REGISTER );
   i2c_write( ADDR_POINTER_CONVERSION );
   i2c_stop();
   
   MSB = 0;
   LSB = 0;
   
   i2c_start();
   delay_us( 1 );
   i2c_write( ADDR_GND | ADDR_READ_REGISTER );
   MSB = i2c_read();
   LSB = i2c_read();
   i2c_stop();  
   
   result = 0;
   result = make16( MSB, LSB ) >> 4;
   
   //if( result > 4000 ){ result = 0; } // filter.
   
   return result;
}
