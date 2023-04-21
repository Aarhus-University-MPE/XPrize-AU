// https://discuss.ardupilot.org/t/mavlink-and-arduino-step-by-step/25566
#include <SoftwareSerial.h>
#include <mavlink.h>

#define RXpin 3
#define TXpin 2

SoftwareSerial SerialMAV(RXpin, TXpin);
// #define SerialMAV Serial

unsigned long previousMillisMAVLink       = 0;
const unsigned long next_interval_MAVLink = 1000;

const int sysid  = 1;  ///< ID 20 for this airplane. 1 PX, 255 ground station
const int compid = 1;  ///< The component sending the message

bool paramSent = false;

// Launch the serial port in setup
void setup() {
  // Serial.begin(115200);
  // Serial.print(F("Initializing System ... "));

  // MAVLink interface start
  SerialMAV.begin(57600);

  // Serial.println(F("System Online"));
}

// Loop your program
void loop() {
  // MAVLink config
  /* The default UART header for your MCU */
  int type = MAV_TYPE_GROUND_ROVER;

  // Define the system type, in this case an airplane -> on-board controller
  uint8_t system_type    = MAV_TYPE_GENERIC;
  uint8_t autopilot_type = MAV_AUTOPILOT_INVALID;

  uint8_t system_mode  = MAV_MODE_PREFLIGHT;  ///< Booting up
  uint32_t custom_mode = 0;                   ///< Custom mode, can be defined by user/adopter
  uint8_t system_state = MAV_STATE_STANDBY;   ///< System ready for flight

  // Send the message with the standard UART send function
  // uart0_send might be named differently depending on
  // the individual microcontroller / library in use.
  unsigned long currentMillisMAVLink = millis();
  if (currentMillisMAVLink - previousMillisMAVLink >= next_interval_MAVLink) {
    // Timing variables
    previousMillisMAVLink = currentMillisMAVLink;

    // Initialize the required buffers
    mavlink_message_t msg;

    digitalWrite(LED_BUILTIN, true);

    // Heartbeat
    mavlink_msg_heartbeat_pack(sysid, compid, &msg, type, autopilot_type, system_mode, custom_mode, system_state);
    sendMsg(&msg);

    // GPS Position
    int32_t lat = 570565970;
    int32_t lon = 99001524;

    mavlink_msg_global_position_int_pack(sysid, compid, &msg, millis(), lat, lon, 0, 0, 0, 0, 0, 0);
    sendMsg(&msg);

    // Battery Level, Flight Mode, etc.
    int16_t voltage     = 12100;
    int16_t currentDraw = 321;
    int8_t remaining    = 81;

    mavlink_msg_sys_status_pack(sysid, compid, &msg, 0, 0, 0, 0, voltage, currentDraw, remaining, 0, 0, 0, 0, 0, 0);
    sendMsg(&msg);

    // GPS Data (Sateliste count, etc)
    uint8_t fix_type;
    mavlink_msg_gps_raw_int_pack(sysid, compid, &msg, millis(), 2, lat, lon, 0, 65535, 65535, 3400, 7500, 8);
    sendMsg(&msg);

    // Speed, throttle
    float speed  = 3.4f;
    int throttle = 32;
    mavlink_msg_vfr_hud_pack(sysid, compid, &msg, 0, speed, 0, throttle, 0, 0);
    sendMsg(&msg);

    // Compass
    float heading = 3.14f;
    mavlink_msg_attitude_pack(sysid, compid, &msg, millis(), 0.0f, 0.0f, DEG_TO_RAD * heading, 0, 0, 0);
    sendMsg(&msg);
  }

  // Check reception buffer
  comm_receive();
}

void sendMsg(mavlink_message_t* msg) {
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];

  // Copy the message to the send buffer
  uint16_t len = mavlink_msg_to_send_buffer(buf, msg);

  // Send message
  Serial.write(buf, len);  // Write command to Serial Port
  // SerialMAV.write(buf, len); // Write command to Telem Port
}

void comm_receive() {
  mavlink_message_t msg;
  mavlink_status_t status;

  while (SerialMAV.available() > 0) {
    uint8_t c = SerialMAV.read();
    // Serial.write(c);

    // Try to get a new message
    if (mavlink_parse_char(MAVLINK_COMM_0, c, &msg, &status)) {
      // Serial.println(msg.msgid);
      // Handle message
      switch (msg.msgid) {
        case MAVLINK_MSG_ID_HEARTBEAT:  // #0: Heartbeat
        {
          // Serial.println("Heartbeat!");

          // E.g. read GCS heartbeat and go into
          // comm lost mode if timer times out
        } break;

        case MAVLINK_MSG_ID_SYS_STATUS:  // #1: SYS_STATUS
        {
          /* Message decoding: PRIMITIVE
           *    mavlink_msg_sys_status_decode(const mavlink_message_t* msg, mavlink_sys_status_t* sys_status)
           */
          // mavlink_message_t* msg;
          mavlink_sys_status_t sys_status;
          mavlink_msg_sys_status_decode(&msg, &sys_status);
        } break;

        case 21:  // #21 PARAM_REQUEST_LIST
          // Serial.println(F("PARAM_REQUEST_LIST"));
          break;

        case MAVLINK_MSG_ID_PARAM_VALUE:  // #22: PARAM_VALUE
        {
          /* Message decoding: PRIMITIVE
           *    mavlink_msg_param_value_decode(const mavlink_message_t* msg, mavlink_param_value_t* param_value)
           */
          // mavlink_message_t* msg;
          mavlink_param_value_t param_value;
          mavlink_msg_param_value_decode(&msg, &param_value);
        } break;

        case MAVLINK_MSG_ID_RAW_IMU:  // #27: RAW_IMU
        {
          /* Message decoding: PRIMITIVE
           *    static inline void mavlink_msg_raw_imu_decode(const mavlink_message_t* msg, mavlink_raw_imu_t* raw_imu)
           */
          mavlink_raw_imu_t raw_imu;
          mavlink_msg_raw_imu_decode(&msg, &raw_imu);
        } break;

        case MAVLINK_MSG_ID_ATTITUDE:  // #30
        {
          /* Message decoding: PRIMITIVE
           *    mavlink_msg_attitude_decode(const mavlink_message_t* msg, mavlink_attitude_t* attitude)
           */

        } break;
        case MAVLINK_MSG_ID_COMMAND_LONG:  // 76
        {
          /* Message decoding: PRIMITIVE
           *    mavlink_msg_attitude_decode(const mavlink_message_t* msg, mavlink_attitude_t* attitude)
           */
          // Serial.println("MAVLINK_MSG_ID_COMMAND_LONG");

          mavlink_command_long_t command_value;
          mavlink_msg_command_long_decode(&msg, &command_value);

          switch (command_value.command) {
            case 519:  // MAV_CMD_REQUEST_PROTOCOL_VERSION
              // if (!paramSent) {
              // aramSent = true;
              // Serial.println("Sending test parameter");
              // }
              break;

            default:
              break;
          }
        } break;
        default:
          break;
      }
    }
  }
}