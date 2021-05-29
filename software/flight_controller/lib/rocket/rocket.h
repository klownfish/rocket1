/*****************************
GENERATED FILE DO NOT EDIT
******************************/

#ifndef _rocket_H
#define _rocket_H
// if you want to use floats or doubles
#define rocket_FLOAT_DEF float

#include <math.h>
#include <stdint.h>
#include <string.h>

namespace rocket {
enum struct state : uint8_t {
  sleeping = 0,
  awake = 1,
  ready = 2,
  ascending = 3,
  falling = 4,
  landed = 5,
};
enum struct nodes : uint8_t {
  local = 0,
  rocket = 1,
  ground = 2,
  relay = 3,
};
enum struct fields : uint8_t {
  local_timestamp = 0,
  ms_since_boot = 1,
  declination = 2,
  this_to_42 = 3,
  is_enabled = 4,
  address = 5,
  altitude = 6,
  temperature = 7,
  acc_x = 8,
  acc_y = 9,
  acc_z = 10,
  gyro_x = 11,
  gyro_y = 12,
  gyro_z = 13,
  mag_x = 14,
  mag_y = 15,
  mag_z = 16,
  voltage = 17,
  state = 18,
  rssi = 19,
};
enum struct messages : uint8_t {
  local_timestamp = 0,
  timestamp = 1,
  handshake = 2,
  simple_calibration = 3,
  mag_calibration = 4,
  wipe_flash = 5,
  play_music = 6,
  set_logging = 7,
  dump_flash = 8,
  flash_address = 9,
  bmp = 10,
  mpu = 11,
  battery_voltage = 12,
  set_state = 13,
  state = 14,
  rssi = 15,
  ms_since_boot = 16,
};
enum struct categories : uint8_t {
  none = 0,
};
template <typename T>
void scaledFloat_to_uint(rocket_FLOAT_DEF value, rocket_FLOAT_DEF scale,
                         T *out) {
  *out = value * scale;
}

template <typename T>
void uint_to_scaledFloat(T value, rocket_FLOAT_DEF scale,
                         rocket_FLOAT_DEF *out) {
  *out = value / scale;
}

template <typename T>
void packedFloat_to_uint(rocket_FLOAT_DEF value, rocket_FLOAT_DEF minValue,
                         rocket_FLOAT_DEF maxValue, T *out) {
  T intMax = ~0;
  if (value < minValue) {
    *out = 0;
    return;
  }
  if (value > maxValue) {
    *out = intMax;
    return;
  }
  rocket_FLOAT_DEF ratio = (value - minValue) / (maxValue - minValue);
  *out = 1 + ((intMax - 2)) * ratio;
}

template <typename T>
void uint_to_packedFloat(T value, rocket_FLOAT_DEF minValue,
                         rocket_FLOAT_DEF maxValue, rocket_FLOAT_DEF *out) {
  T intMax = ~0;
  if (value <= 0) {
    *out = minValue - 1.0;
    return;
  }
  if (value >= intMax) {
    *out = maxValue + 1.0;
    return;
  }
  rocket_FLOAT_DEF ratio = (value - 1) / (intMax - 2);
  *out = ratio * (maxValue - minValue) + minValue;
}

class MessageBase {
public:
  virtual void build_buf(uint8_t *buf, uint8_t *index) {}
  virtual void parse_buf(uint8_t *buf) {}
  virtual uint8_t get_id() {}
  virtual enum categories get_category() {}
  virtual enum nodes get_receiver() {}
  virtual enum nodes get_sender() {}
  virtual uint8_t get_size() {}
};
class local_timestamp_from_local_to_local : public MessageBase {
public:
  uint32_t local_timestamp;
  static_assert((sizeof(local_timestamp) == 4), "invalid size");
  uint8_t size = 4;
  enum messages message = messages::local_timestamp;
  enum nodes sender = nodes::local;
  enum nodes receiver = nodes::local;
  enum categories category = categories::none;
  uint8_t id = 0;
  enum categories get_category() override { return category; }
  uint8_t get_size() override { return size; }
  enum nodes get_sender() override { return sender; }
  enum nodes get_receiver() override { return receiver; }
  uint8_t get_id() override { return id; }
  void set_local_timestamp(uint32_t value) { local_timestamp = value; }
  uint32_t get_local_timestamp() { return local_timestamp; }
  void build_buf(uint8_t *buf, uint8_t *index) override {
    memcpy(buf + *index, &local_timestamp, sizeof(local_timestamp));
    *index += sizeof(local_timestamp);
  }
  void parse_buf(uint8_t *buf) override {
    uint8_t index = 0;
    memcpy(&local_timestamp, buf + index, sizeof(local_timestamp));
    index += sizeof(local_timestamp);
  }
};

class timestamp_from_rocket_to_ground : public MessageBase {
public:
  uint32_t ms_since_boot;
  static_assert((sizeof(ms_since_boot) == 4), "invalid size");
  uint8_t size = 4;
  enum messages message = messages::timestamp;
  enum nodes sender = nodes::rocket;
  enum nodes receiver = nodes::ground;
  enum categories category = categories::none;
  uint8_t id = 1;
  enum categories get_category() override { return category; }
  uint8_t get_size() override { return size; }
  enum nodes get_sender() override { return sender; }
  enum nodes get_receiver() override { return receiver; }
  uint8_t get_id() override { return id; }
  void set_ms_since_boot(uint32_t value) { ms_since_boot = value; }
  uint32_t get_ms_since_boot() { return ms_since_boot; }
  void build_buf(uint8_t *buf, uint8_t *index) override {
    memcpy(buf + *index, &ms_since_boot, sizeof(ms_since_boot));
    *index += sizeof(ms_since_boot);
  }
  void parse_buf(uint8_t *buf) override {
    uint8_t index = 0;
    memcpy(&ms_since_boot, buf + index, sizeof(ms_since_boot));
    index += sizeof(ms_since_boot);
  }
};

class handshake_from_ground_to_rocket : public MessageBase {
public:
  uint8_t size = 0;
  enum messages message = messages::handshake;
  enum nodes sender = nodes::ground;
  enum nodes receiver = nodes::rocket;
  enum categories category = categories::none;
  uint8_t id = 2;
  enum categories get_category() override { return category; }
  uint8_t get_size() override { return size; }
  enum nodes get_sender() override { return sender; }
  enum nodes get_receiver() override { return receiver; }
  uint8_t get_id() override { return id; }
  void build_buf(uint8_t *buf, uint8_t *index) override {}
  void parse_buf(uint8_t *buf) override {}
};

class handshake_from_rocket_to_ground : public MessageBase {
public:
  uint8_t size = 0;
  enum messages message = messages::handshake;
  enum nodes sender = nodes::rocket;
  enum nodes receiver = nodes::ground;
  enum categories category = categories::none;
  uint8_t id = 3;
  enum categories get_category() override { return category; }
  uint8_t get_size() override { return size; }
  enum nodes get_sender() override { return sender; }
  enum nodes get_receiver() override { return receiver; }
  uint8_t get_id() override { return id; }
  void build_buf(uint8_t *buf, uint8_t *index) override {}
  void parse_buf(uint8_t *buf) override {}
};

class simple_calibration_from_ground_to_rocket : public MessageBase {
public:
  uint8_t size = 0;
  enum messages message = messages::simple_calibration;
  enum nodes sender = nodes::ground;
  enum nodes receiver = nodes::rocket;
  enum categories category = categories::none;
  uint8_t id = 4;
  enum categories get_category() override { return category; }
  uint8_t get_size() override { return size; }
  enum nodes get_sender() override { return sender; }
  enum nodes get_receiver() override { return receiver; }
  uint8_t get_id() override { return id; }
  void build_buf(uint8_t *buf, uint8_t *index) override {}
  void parse_buf(uint8_t *buf) override {}
};

class mag_calibration_from_ground_to_rocket : public MessageBase {
public:
  float_t declination;
  static_assert((sizeof(declination) == 4), "invalid size");
  uint8_t size = 4;
  enum messages message = messages::mag_calibration;
  enum nodes sender = nodes::ground;
  enum nodes receiver = nodes::rocket;
  enum categories category = categories::none;
  uint8_t id = 5;
  enum categories get_category() override { return category; }
  uint8_t get_size() override { return size; }
  enum nodes get_sender() override { return sender; }
  enum nodes get_receiver() override { return receiver; }
  uint8_t get_id() override { return id; }
  void set_declination(float_t value) { declination = value; }
  float_t get_declination() { return declination; }
  void build_buf(uint8_t *buf, uint8_t *index) override {
    memcpy(buf + *index, &declination, sizeof(declination));
    *index += sizeof(declination);
  }
  void parse_buf(uint8_t *buf) override {
    uint8_t index = 0;
    memcpy(&declination, buf + index, sizeof(declination));
    index += sizeof(declination);
  }
};

class wipe_flash_from_ground_to_rocket : public MessageBase {
public:
  uint8_t this_to_42;
  static_assert((sizeof(this_to_42) == 1), "invalid size");
  uint8_t size = 1;
  enum messages message = messages::wipe_flash;
  enum nodes sender = nodes::ground;
  enum nodes receiver = nodes::rocket;
  enum categories category = categories::none;
  uint8_t id = 6;
  enum categories get_category() override { return category; }
  uint8_t get_size() override { return size; }
  enum nodes get_sender() override { return sender; }
  enum nodes get_receiver() override { return receiver; }
  uint8_t get_id() override { return id; }
  void set_this_to_42(uint8_t value) { this_to_42 = value; }
  uint8_t get_this_to_42() { return this_to_42; }
  void build_buf(uint8_t *buf, uint8_t *index) override {
    memcpy(buf + *index, &this_to_42, sizeof(this_to_42));
    *index += sizeof(this_to_42);
  }
  void parse_buf(uint8_t *buf) override {
    uint8_t index = 0;
    memcpy(&this_to_42, buf + index, sizeof(this_to_42));
    index += sizeof(this_to_42);
  }
};

class play_music_from_ground_to_rocket : public MessageBase {
public:
  uint8_t size = 0;
  enum messages message = messages::play_music;
  enum nodes sender = nodes::ground;
  enum nodes receiver = nodes::rocket;
  enum categories category = categories::none;
  uint8_t id = 7;
  enum categories get_category() override { return category; }
  uint8_t get_size() override { return size; }
  enum nodes get_sender() override { return sender; }
  enum nodes get_receiver() override { return receiver; }
  uint8_t get_id() override { return id; }
  void build_buf(uint8_t *buf, uint8_t *index) override {}
  void parse_buf(uint8_t *buf) override {}
};

class set_logging_from_ground_to_rocket : public MessageBase {
public:
  uint8_t bit_field = 0;
  static_assert((sizeof(bit_field) == 1), "invalid size");
  void set_is_enabled(bool value) {
    bit_field =
        value * (bit_field | (1 << 0)) + !value * (bit_field & ~(1 << 0));
  }
  bool get_is_enabled() { return bit_field & (1 << 0); }
  uint8_t size = 1;
  enum messages message = messages::set_logging;
  enum nodes sender = nodes::ground;
  enum nodes receiver = nodes::rocket;
  enum categories category = categories::none;
  uint8_t id = 8;
  enum categories get_category() override { return category; }
  uint8_t get_size() override { return size; }
  enum nodes get_sender() override { return sender; }
  enum nodes get_receiver() override { return receiver; }
  uint8_t get_id() override { return id; }
  void build_buf(uint8_t *buf, uint8_t *index) override {
    memcpy(buf + *index, &bit_field, sizeof(bit_field));
    *index += sizeof(bit_field);
  }
  void parse_buf(uint8_t *buf) override {
    uint8_t index = 0;
    memcpy(&bit_field, buf + index, sizeof(bit_field));
    index += sizeof(bit_field);
  }
};

class dump_flash_from_ground_to_rocket : public MessageBase {
public:
  uint8_t size = 0;
  enum messages message = messages::dump_flash;
  enum nodes sender = nodes::ground;
  enum nodes receiver = nodes::rocket;
  enum categories category = categories::none;
  uint8_t id = 9;
  enum categories get_category() override { return category; }
  uint8_t get_size() override { return size; }
  enum nodes get_sender() override { return sender; }
  enum nodes get_receiver() override { return receiver; }
  uint8_t get_id() override { return id; }
  void build_buf(uint8_t *buf, uint8_t *index) override {}
  void parse_buf(uint8_t *buf) override {}
};

class flash_address_from_rocket_to_ground : public MessageBase {
public:
  uint32_t address;
  static_assert((sizeof(address) == 4), "invalid size");
  uint8_t size = 4;
  enum messages message = messages::flash_address;
  enum nodes sender = nodes::rocket;
  enum nodes receiver = nodes::ground;
  enum categories category = categories::none;
  uint8_t id = 10;
  enum categories get_category() override { return category; }
  uint8_t get_size() override { return size; }
  enum nodes get_sender() override { return sender; }
  enum nodes get_receiver() override { return receiver; }
  uint8_t get_id() override { return id; }
  void set_address(uint32_t value) { address = value; }
  uint32_t get_address() { return address; }
  void build_buf(uint8_t *buf, uint8_t *index) override {
    memcpy(buf + *index, &address, sizeof(address));
    *index += sizeof(address);
  }
  void parse_buf(uint8_t *buf) override {
    uint8_t index = 0;
    memcpy(&address, buf + index, sizeof(address));
    index += sizeof(address);
  }
};

class bmp_from_rocket_to_ground : public MessageBase {
public:
  float_t altitude;
  static_assert((sizeof(altitude) == 4), "invalid size");
  float_t temperature;
  static_assert((sizeof(temperature) == 4), "invalid size");
  uint8_t size = 8;
  enum messages message = messages::bmp;
  enum nodes sender = nodes::rocket;
  enum nodes receiver = nodes::ground;
  enum categories category = categories::none;
  uint8_t id = 11;
  enum categories get_category() override { return category; }
  uint8_t get_size() override { return size; }
  enum nodes get_sender() override { return sender; }
  enum nodes get_receiver() override { return receiver; }
  uint8_t get_id() override { return id; }
  void set_altitude(float_t value) { altitude = value; }
  void set_temperature(float_t value) { temperature = value; }
  float_t get_altitude() { return altitude; }
  float_t get_temperature() { return temperature; }
  void build_buf(uint8_t *buf, uint8_t *index) override {
    memcpy(buf + *index, &altitude, sizeof(altitude));
    *index += sizeof(altitude);
    memcpy(buf + *index, &temperature, sizeof(temperature));
    *index += sizeof(temperature);
  }
  void parse_buf(uint8_t *buf) override {
    uint8_t index = 0;
    memcpy(&altitude, buf + index, sizeof(altitude));
    index += sizeof(altitude);
    memcpy(&temperature, buf + index, sizeof(temperature));
    index += sizeof(temperature);
  }
};

class mpu_from_rocket_to_ground : public MessageBase {
public:
  float_t acc_x;
  static_assert((sizeof(acc_x) == 4), "invalid size");
  float_t acc_y;
  static_assert((sizeof(acc_y) == 4), "invalid size");
  float_t acc_z;
  static_assert((sizeof(acc_z) == 4), "invalid size");
  float_t gyro_x;
  static_assert((sizeof(gyro_x) == 4), "invalid size");
  float_t gyro_y;
  static_assert((sizeof(gyro_y) == 4), "invalid size");
  float_t gyro_z;
  static_assert((sizeof(gyro_z) == 4), "invalid size");
  float_t mag_x;
  static_assert((sizeof(mag_x) == 4), "invalid size");
  float_t mag_y;
  static_assert((sizeof(mag_y) == 4), "invalid size");
  float_t mag_z;
  static_assert((sizeof(mag_z) == 4), "invalid size");
  uint8_t size = 36;
  enum messages message = messages::mpu;
  enum nodes sender = nodes::rocket;
  enum nodes receiver = nodes::ground;
  enum categories category = categories::none;
  uint8_t id = 12;
  enum categories get_category() override { return category; }
  uint8_t get_size() override { return size; }
  enum nodes get_sender() override { return sender; }
  enum nodes get_receiver() override { return receiver; }
  uint8_t get_id() override { return id; }
  void set_acc_x(float_t value) { acc_x = value; }
  void set_acc_y(float_t value) { acc_y = value; }
  void set_acc_z(float_t value) { acc_z = value; }
  void set_gyro_x(float_t value) { gyro_x = value; }
  void set_gyro_y(float_t value) { gyro_y = value; }
  void set_gyro_z(float_t value) { gyro_z = value; }
  void set_mag_x(float_t value) { mag_x = value; }
  void set_mag_y(float_t value) { mag_y = value; }
  void set_mag_z(float_t value) { mag_z = value; }
  float_t get_acc_x() { return acc_x; }
  float_t get_acc_y() { return acc_y; }
  float_t get_acc_z() { return acc_z; }
  float_t get_gyro_x() { return gyro_x; }
  float_t get_gyro_y() { return gyro_y; }
  float_t get_gyro_z() { return gyro_z; }
  float_t get_mag_x() { return mag_x; }
  float_t get_mag_y() { return mag_y; }
  float_t get_mag_z() { return mag_z; }
  void build_buf(uint8_t *buf, uint8_t *index) override {
    memcpy(buf + *index, &acc_x, sizeof(acc_x));
    *index += sizeof(acc_x);
    memcpy(buf + *index, &acc_y, sizeof(acc_y));
    *index += sizeof(acc_y);
    memcpy(buf + *index, &acc_z, sizeof(acc_z));
    *index += sizeof(acc_z);
    memcpy(buf + *index, &gyro_x, sizeof(gyro_x));
    *index += sizeof(gyro_x);
    memcpy(buf + *index, &gyro_y, sizeof(gyro_y));
    *index += sizeof(gyro_y);
    memcpy(buf + *index, &gyro_z, sizeof(gyro_z));
    *index += sizeof(gyro_z);
    memcpy(buf + *index, &mag_x, sizeof(mag_x));
    *index += sizeof(mag_x);
    memcpy(buf + *index, &mag_y, sizeof(mag_y));
    *index += sizeof(mag_y);
    memcpy(buf + *index, &mag_z, sizeof(mag_z));
    *index += sizeof(mag_z);
  }
  void parse_buf(uint8_t *buf) override {
    uint8_t index = 0;
    memcpy(&acc_x, buf + index, sizeof(acc_x));
    index += sizeof(acc_x);
    memcpy(&acc_y, buf + index, sizeof(acc_y));
    index += sizeof(acc_y);
    memcpy(&acc_z, buf + index, sizeof(acc_z));
    index += sizeof(acc_z);
    memcpy(&gyro_x, buf + index, sizeof(gyro_x));
    index += sizeof(gyro_x);
    memcpy(&gyro_y, buf + index, sizeof(gyro_y));
    index += sizeof(gyro_y);
    memcpy(&gyro_z, buf + index, sizeof(gyro_z));
    index += sizeof(gyro_z);
    memcpy(&mag_x, buf + index, sizeof(mag_x));
    index += sizeof(mag_x);
    memcpy(&mag_y, buf + index, sizeof(mag_y));
    index += sizeof(mag_y);
    memcpy(&mag_z, buf + index, sizeof(mag_z));
    index += sizeof(mag_z);
  }
};

class battery_voltage_from_rocket_to_ground : public MessageBase {
public:
  float_t voltage;
  static_assert((sizeof(voltage) == 4), "invalid size");
  uint8_t size = 4;
  enum messages message = messages::battery_voltage;
  enum nodes sender = nodes::rocket;
  enum nodes receiver = nodes::ground;
  enum categories category = categories::none;
  uint8_t id = 13;
  enum categories get_category() override { return category; }
  uint8_t get_size() override { return size; }
  enum nodes get_sender() override { return sender; }
  enum nodes get_receiver() override { return receiver; }
  uint8_t get_id() override { return id; }
  void set_voltage(float_t value) { voltage = value; }
  float_t get_voltage() { return voltage; }
  void build_buf(uint8_t *buf, uint8_t *index) override {
    memcpy(buf + *index, &voltage, sizeof(voltage));
    *index += sizeof(voltage);
  }
  void parse_buf(uint8_t *buf) override {
    uint8_t index = 0;
    memcpy(&voltage, buf + index, sizeof(voltage));
    index += sizeof(voltage);
  }
};

class set_state_from_ground_to_rocket : public MessageBase {
public:
  enum state state;
  static_assert((sizeof(state) == 1), "invalid size");
  uint8_t size = 1;
  enum messages message = messages::set_state;
  enum nodes sender = nodes::ground;
  enum nodes receiver = nodes::rocket;
  enum categories category = categories::none;
  uint8_t id = 14;
  enum categories get_category() override { return category; }
  uint8_t get_size() override { return size; }
  enum nodes get_sender() override { return sender; }
  enum nodes get_receiver() override { return receiver; }
  uint8_t get_id() override { return id; }
  void set_state(enum state value) { state = value; }
  enum state get_state() { return state; }
  void build_buf(uint8_t *buf, uint8_t *index) override {
    memcpy(buf + *index, &state, sizeof(state));
    *index += sizeof(state);
  }
  void parse_buf(uint8_t *buf) override {
    uint8_t index = 0;
    memcpy(&state, buf + index, sizeof(state));
    index += sizeof(state);
  }
};

class state_from_rocket_to_ground : public MessageBase {
public:
  enum state state;
  static_assert((sizeof(state) == 1), "invalid size");
  uint8_t size = 1;
  enum messages message = messages::state;
  enum nodes sender = nodes::rocket;
  enum nodes receiver = nodes::ground;
  enum categories category = categories::none;
  uint8_t id = 15;
  enum categories get_category() override { return category; }
  uint8_t get_size() override { return size; }
  enum nodes get_sender() override { return sender; }
  enum nodes get_receiver() override { return receiver; }
  uint8_t get_id() override { return id; }
  void set_state(enum state value) { state = value; }
  enum state get_state() { return state; }
  void build_buf(uint8_t *buf, uint8_t *index) override {
    memcpy(buf + *index, &state, sizeof(state));
    *index += sizeof(state);
  }
  void parse_buf(uint8_t *buf) override {
    uint8_t index = 0;
    memcpy(&state, buf + index, sizeof(state));
    index += sizeof(state);
  }
};

class rssi_from_rocket_to_ground : public MessageBase {
public:
  int16_t rssi;
  static_assert((sizeof(rssi) == 2), "invalid size");
  uint8_t size = 2;
  enum messages message = messages::rssi;
  enum nodes sender = nodes::rocket;
  enum nodes receiver = nodes::ground;
  enum categories category = categories::none;
  uint8_t id = 16;
  enum categories get_category() override { return category; }
  uint8_t get_size() override { return size; }
  enum nodes get_sender() override { return sender; }
  enum nodes get_receiver() override { return receiver; }
  uint8_t get_id() override { return id; }
  void set_rssi(rocket_FLOAT_DEF value) {
    scaledFloat_to_uint(value, 100, &rssi);
  }
  rocket_FLOAT_DEF get_rssi() {
    rocket_FLOAT_DEF out;
    uint_to_scaledFloat(rssi, 100, &out);
    return out;
  }
  void build_buf(uint8_t *buf, uint8_t *index) override {
    memcpy(buf + *index, &rssi, sizeof(rssi));
    *index += sizeof(rssi);
  }
  void parse_buf(uint8_t *buf) override {
    uint8_t index = 0;
    memcpy(&rssi, buf + index, sizeof(rssi));
    index += sizeof(rssi);
  }
};

class rssi_from_relay_to_ground : public MessageBase {
public:
  int16_t rssi;
  static_assert((sizeof(rssi) == 2), "invalid size");
  uint8_t size = 2;
  enum messages message = messages::rssi;
  enum nodes sender = nodes::relay;
  enum nodes receiver = nodes::ground;
  enum categories category = categories::none;
  uint8_t id = 17;
  enum categories get_category() override { return category; }
  uint8_t get_size() override { return size; }
  enum nodes get_sender() override { return sender; }
  enum nodes get_receiver() override { return receiver; }
  uint8_t get_id() override { return id; }
  void set_rssi(rocket_FLOAT_DEF value) {
    scaledFloat_to_uint(value, 100, &rssi);
  }
  rocket_FLOAT_DEF get_rssi() {
    rocket_FLOAT_DEF out;
    uint_to_scaledFloat(rssi, 100, &out);
    return out;
  }
  void build_buf(uint8_t *buf, uint8_t *index) override {
    memcpy(buf + *index, &rssi, sizeof(rssi));
    *index += sizeof(rssi);
  }
  void parse_buf(uint8_t *buf) override {
    uint8_t index = 0;
    memcpy(&rssi, buf + index, sizeof(rssi));
    index += sizeof(rssi);
  }
};

class ms_since_boot_from_rocket_to_ground : public MessageBase {
public:
  uint32_t ms_since_boot;
  static_assert((sizeof(ms_since_boot) == 4), "invalid size");
  uint8_t size = 4;
  enum messages message = messages::ms_since_boot;
  enum nodes sender = nodes::rocket;
  enum nodes receiver = nodes::ground;
  enum categories category = categories::none;
  uint8_t id = 18;
  enum categories get_category() override { return category; }
  uint8_t get_size() override { return size; }
  enum nodes get_sender() override { return sender; }
  enum nodes get_receiver() override { return receiver; }
  uint8_t get_id() override { return id; }
  void set_ms_since_boot(uint32_t value) { ms_since_boot = value; }
  uint32_t get_ms_since_boot() { return ms_since_boot; }
  void build_buf(uint8_t *buf, uint8_t *index) override {
    memcpy(buf + *index, &ms_since_boot, sizeof(ms_since_boot));
    *index += sizeof(ms_since_boot);
  }
  void parse_buf(uint8_t *buf) override {
    uint8_t index = 0;
    memcpy(&ms_since_boot, buf + index, sizeof(ms_since_boot));
    index += sizeof(ms_since_boot);
  }
};

void rx(local_timestamp_from_local_to_local msg);
void rx(local_timestamp_from_local_to_local msg, void *misc);
void rx(timestamp_from_rocket_to_ground msg);
void rx(timestamp_from_rocket_to_ground msg, void *misc);
void rx(handshake_from_ground_to_rocket msg);
void rx(handshake_from_ground_to_rocket msg, void *misc);
void rx(handshake_from_rocket_to_ground msg);
void rx(handshake_from_rocket_to_ground msg, void *misc);
void rx(simple_calibration_from_ground_to_rocket msg);
void rx(simple_calibration_from_ground_to_rocket msg, void *misc);
void rx(mag_calibration_from_ground_to_rocket msg);
void rx(mag_calibration_from_ground_to_rocket msg, void *misc);
void rx(wipe_flash_from_ground_to_rocket msg);
void rx(wipe_flash_from_ground_to_rocket msg, void *misc);
void rx(play_music_from_ground_to_rocket msg);
void rx(play_music_from_ground_to_rocket msg, void *misc);
void rx(set_logging_from_ground_to_rocket msg);
void rx(set_logging_from_ground_to_rocket msg, void *misc);
void rx(dump_flash_from_ground_to_rocket msg);
void rx(dump_flash_from_ground_to_rocket msg, void *misc);
void rx(flash_address_from_rocket_to_ground msg);
void rx(flash_address_from_rocket_to_ground msg, void *misc);
void rx(bmp_from_rocket_to_ground msg);
void rx(bmp_from_rocket_to_ground msg, void *misc);
void rx(mpu_from_rocket_to_ground msg);
void rx(mpu_from_rocket_to_ground msg, void *misc);
void rx(battery_voltage_from_rocket_to_ground msg);
void rx(battery_voltage_from_rocket_to_ground msg, void *misc);
void rx(set_state_from_ground_to_rocket msg);
void rx(set_state_from_ground_to_rocket msg, void *misc);
void rx(state_from_rocket_to_ground msg);
void rx(state_from_rocket_to_ground msg, void *misc);
void rx(rssi_from_rocket_to_ground msg);
void rx(rssi_from_rocket_to_ground msg, void *misc);
void rx(rssi_from_relay_to_ground msg);
void rx(rssi_from_relay_to_ground msg, void *misc);
void rx(ms_since_boot_from_rocket_to_ground msg);
void rx(ms_since_boot_from_rocket_to_ground msg, void *misc);
void parse_message(uint8_t id, uint8_t *buf);
void parse_message(uint8_t id, uint8_t *buf, void *misc);
bool is_valid_id(uint8_t id);
uint8_t id_to_len(uint8_t id);
enum nodes id_to_sender(uint8_t id);
enum nodes id_to_receiver(uint8_t id);
enum categories id_to_category(uint8_t id);
} // namespace rocket
#endif
