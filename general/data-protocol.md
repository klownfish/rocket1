# Radio protocol
## general structure
Everything is little endian

`00`  - `'$'`\
`01`  - length of message, including the `$` and checksum
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
## rocket -> gateway(0x01 - 0x80)

### 0x01 - telemetry
|type|value|scale|
|-----|-----|----|
| int16_t  | rssi | 0 |
| uint16_t | meters above sea | 3 |
| uint16_t | temperature | 3 |
| int16_t | acceleration x | 3 |
| int16_t | acceleration y | 3 |
| int16_t | acceleration z | 3 |
| int16_t | gyro x | 3 |
| int16_t | gyro y | 3 |
| int16_t | gyro z | 3 |
| uint16_t | battery voltage | 3 |

### 0x02 - state
|type|value|scale|
|-----|-----|----|
| uint16_t | battery voltage | 3 |
| uint16_t | hpa at sea level | 3|
| uint16_t | ground level | 3 |
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

# USB protocol

## pc to flight controller 
a single byte 

`0x01` respond with all the contents of the flashchip \
`0x02` reply `0x02`

## pc to gateway
`0x03` reply `0x03` \
`0x04` after this is sent the gateway will relay every single byte that is sent to it, no going back