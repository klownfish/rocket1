# Radio protocol
## general structure
Everything is little endian

`00`  - `'$'`\
`01`  - length of message, including the `$`, excluding checksum
`02`  - ms_since_boot byte 1
`03`  - ms_since_boot byte 2
`04`  - ms_since_boot byte 3
`05`  - ms_since_boot byte 4
`06`  - id-byte\
`07`  - data byte 1\
`08`  - data byte 2\
...\
`n+2` - data byte n\
`n+3` - checksum (xor all the bytes, including '$' and the length)

## IDs and corresponding data
## rocket -> gateway(0x01 - 0x40)

### 0x01 - telemetry
|type|value|scale|
|-----|-----|----|
| int32_t | meters above sea | 3 |
| int32_t | temperature | 3 |
| int32_t | acceleration x | 3 |
| int32_t | acceleration y | 3 |
| int32_t | acceleration z | 3 |
| int32_t | gyro x | 3 |
| int32_t | gyro y | 3 |
| int32_t | gyro z | 3 |
| int32_t | battery voltage | 3 |

### 0x02 - state
|type|value|scale|
|-----|-----|----|
| int32_t  | rssi | 0 |
| int32_t | battery voltage | 3 |
| int32_t | hpa at sea level | 3|
| int32_t | ground level | 3 |
| enum | 0 - normal, 1 - sleeping|

## gateway -> rocket(0x81 - 0xAA)
The rocket always responds with a state (0x02) message.

### 0x81 - update parameters
|type|value|scale|
|-----|-----|----|
|uint16_t| hpa at sea level| 3 |

### 0x82 - calibrate
empty

### 0x83 - sleep
empty

### 0x84 - wake_up
empty

## PC -> USB
All radio commands should work over USB, not all USB commands should work over radio
### 0xB0 - handshake
responds with 0xB00

### 0xB1 - Dump flash 
responds with the contents of the flash chip

### 0xB2 - Start transmit
makes the gateway transmit everything that's sent over serial

### 0xB3 - is controller
responds 1 if the unit is a controller
else 0

### 0xB3 - is gateway
responds 1 if the unit is a gateway
else 0

## gateway -> PC
### 0xE0 - gateway rssi
rssi as int32