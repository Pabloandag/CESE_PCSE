// EJERCICIO 2
// La entrega consiste en subir a su repositorio una función que implemente el comando random read.


uint8_t EEPROM24LC1025RandomRead ( uint16_t address ){
    uint8_t i2cSlaveAddress = 0b01010010; // Address de 7 bits definido en el datasheet
    // Creo el buffer dividiendo el address en 2 bytes.
    uint8_t addressBuffer[2] = {
        (uint8_t) (address >> 8),
        (uint8_t) (address & 0x00FF)
    };

    uint8_t receivedByte = 0;

    i2cWriteRead(   I2C0,
                    i2cSlaveAddress,
                    addressBuffer,
                    2,
                    false,
                    &receivedByte,
                    1,
                    true);
}