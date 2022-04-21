void writeConfig( unsigned int8 i2cAdress = 0, unsigned int16 config = 0 );
unsigned int16 readConversion( unsigned int8 i2cAdress = 0 );

void writeConfig( unsigned int8 i2cAdress = 0, unsigned int16 config = 0 )
{
   unsigned int8 MSB = 0;
   unsigned int8 LSB = 0;
   
   MSB = config >> 8;
   LSB = config & 0xFF;
   
   i2c_start();
   i2c_write( i2cAdress | ADDR_WRITE_REGISTER );
   i2c_write( ADDR_POINTER_CONFIGURATION );
   i2c_write( MSB );
   i2c_write( LSB );
   i2c_stop();
   
   delay_us( 1000 );
}

unsigned int16 readConversion( unsigned int8 i2cAdress = 0 )
{
   unsigned int8 MSB = 0;
   unsigned int8 LSB = 0;
   
   i2c_start();
   i2c_write( i2cAdress | ADDR_WRITE_REGISTER );
   i2c_write( ADDR_POINTER_CONVERSION );
   i2c_stop();
   
   i2c_start();
   i2c_write( i2cAdress | ADDR_READ_REGISTER );
   MSB = i2c_read();
   LSB = i2c_read();
   i2c_write( ADDR_POINTER_CONVERSION );
   i2c_stop();
   
   return make16( MSB, LSB );
}
