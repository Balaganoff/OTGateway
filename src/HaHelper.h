#pragma once
#include <HomeAssistantHelper.h>

class HaHelper : public HomeAssistantHelper {
public:
  static const byte TEMP_SOURCE_HEATING = 0;
  static const byte TEMP_SOURCE_INDOOR = 1;
  
  bool publishSelectOutdoorSensorType(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_COMMAND_TEMPLATE)] = F("{\"sensors\": {\"outdoor\": {\"type\": {% if value == 'Boiler' %}0{% elif value == 'Manual' %}1{% elif value == 'External' %}2{% endif %}}}}");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("outdoor_sensor_type");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("outdoor_sensor_type");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_NAME)] = F("Outdoor temperature source");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{% if value_json.sensors.outdoor.type == 0 %}Boiler{% elif value_json.sensors.outdoor.type == 1 %}Manual{% elif value_json.sensors.outdoor.type == 2 %}External{% endif %}");
    doc[FPSTR(HA_OPTIONS)][0] = F("Boiler");
    doc[FPSTR(HA_OPTIONS)][1] = F("Manual");
    doc[FPSTR(HA_OPTIONS)][2] = F("External");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("select", "outdoor_sensor_type").c_str(), doc);
  }

  bool publishSelectIndoorSensorType(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
#if USE_BLE
    doc[FPSTR(HA_COMMAND_TEMPLATE)] = F("{\"sensors\": {\"indoor\": {\"type\": {% if value == 'Manual' %}1{% elif value == 'External' %}2{% elif value == 'Bluetooth' %}3{% endif %}}}}");
#else
    doc[FPSTR(HA_COMMAND_TEMPLATE)] = F("{\"sensors\": {\"indoor\": {\"type\": {% if value == 'Manual' %}1{% elif value == 'External' %}2{% endif %}}}}");
#endif
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("indoor_sensor_type");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("indoor_sensor_type");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_NAME)] = F("Indoor temperature source");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("settings");
#if USE_BLE
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{% if value_json.sensors.indoor.type == 1 %}Manual{% elif value_json.sensors.indoor.type == 2 %}External{% elif value_json.sensors.indoor.type == 3 %}Bluetooth{% endif %}");
#else
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{% if value_json.sensors.indoor.type == 1 %}Manual{% elif value_json.sensors.indoor.type == 2 %}External{% endif %}");
#endif
    doc[FPSTR(HA_OPTIONS)][0] = F("Manual");
    doc[FPSTR(HA_OPTIONS)][1] = F("External");
#if USE_BLE
    doc[FPSTR(HA_OPTIONS)][2] = F("Bluetooth");
#endif
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("select", "indoor_sensor_type").c_str(), doc);
  }

  bool publishNumberOutdoorSensorOffset(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_VALUE_TEMPLATE)] = F("{{ iif(value_json.sensors.outdoor.type != 1, 'online', 'offline') }}");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("outdoor_sensor_offset");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("outdoor_sensor_offset");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("temperature");
    doc[FPSTR(HA_UNIT_OF_MEASUREMENT)] = F("°C");
    doc[FPSTR(HA_NAME)] = F("Outdoor sensor offset");
    doc[FPSTR(HA_ICON)] = F("mdi:altimeter");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.sensors.outdoor.offset|float(0)|round(2) }}");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_COMMAND_TEMPLATE)] = F("{\"sensors\": {\"outdoor\" : {\"offset\" : {{ value }}}}}");
    doc[FPSTR(HA_MIN)] = -10;
    doc[FPSTR(HA_MAX)] = 10;
    doc[FPSTR(HA_STEP)] = 0.1;
    doc[FPSTR(HA_MODE)] = "box";
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("number", "outdoor_sensor_offset").c_str(), doc);
  }

  bool publishNumberIndoorSensorOffset(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_VALUE_TEMPLATE)] = F("{{ iif(value_json.sensors.indoor.type != 1, 'online', 'offline') }}");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("indoor_sensor_offset");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("indoor_sensor_offset");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("temperature");
    doc[FPSTR(HA_UNIT_OF_MEASUREMENT)] = F("°C");
    doc[FPSTR(HA_NAME)] = F("Indoor sensor offset");
    doc[FPSTR(HA_ICON)] = F("mdi:altimeter");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.sensors.indoor.offset|float(0)|round(2) }}");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_COMMAND_TEMPLATE)] = F("{\"sensors\": {\"indoor\" : {\"offset\" : {{ value }}}}}");
    doc[FPSTR(HA_MIN)] = -10;
    doc[FPSTR(HA_MAX)] = 10;
    doc[FPSTR(HA_STEP)] = 0.1;
    doc[FPSTR(HA_MODE)] = "box";
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("number", "indoor_sensor_offset").c_str(), doc);
  }


  bool publishSwitchDebug(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("debug");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("debug");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_NAME)] = F("Debug");
    doc[FPSTR(HA_ICON)] = F("mdi:code-braces");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_STATE_ON)] = true;
    doc[FPSTR(HA_STATE_OFF)] = false;
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.debug }}");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_PAYLOAD_ON)] = F("{\"debug\": true}");
    doc[FPSTR(HA_PAYLOAD_OFF)] = F("{\"debug\": false}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("switch", "debug").c_str(), doc);
  }


  bool publishSwitchEmergency(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("emergency");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("emergency");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_NAME)] = F("Use emergency");
    doc[FPSTR(HA_ICON)] = F("mdi:sun-snowflake-variant");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_STATE_ON)] = true;
    doc[FPSTR(HA_STATE_OFF)] = false;
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.emergency.enable }}");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_PAYLOAD_ON)] = F("{\"emergency\": {\"enable\" : true}}");
    doc[FPSTR(HA_PAYLOAD_OFF)] = F("{\"emergency\": {\"enable\" : false}}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("switch", "emergency").c_str(), doc);
  }

  bool publishNumberEmergencyTarget(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("emergency_target");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("emergency_target");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("temperature");
    doc[FPSTR(HA_UNIT_OF_MEASUREMENT)] = F("°C");
    doc[FPSTR(HA_NAME)] = F("Emergency target temp");
    doc[FPSTR(HA_ICON)] = F("mdi:thermometer-alert");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.emergency.target|float(0)|round(1) }}");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_COMMAND_TEMPLATE)] = F("{\"emergency\": {\"target\" : {{ value }}}}");
    doc[FPSTR(HA_MIN)] = 5;
    doc[FPSTR(HA_MAX)] = 50;
    doc[FPSTR(HA_STEP)] = 0.5;
    doc[FPSTR(HA_MODE)] = "box";
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("number", "emergency_target").c_str(), doc);
  }

  bool publishSwitchEmergencyUseEquitherm(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_VALUE_TEMPLATE)] = F("{{ iif(value_json.sensors.outdoor.type != 1, 'online', 'offline') }}");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("emergency_use_equitherm");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("emergency_use_equitherm");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_NAME)] = F("Use equitherm in emergency");
    doc[FPSTR(HA_ICON)] = F("mdi:snowflake-alert");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_STATE_ON)] = true;
    doc[FPSTR(HA_STATE_OFF)] = false;
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.emergency.useEquitherm }}");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_PAYLOAD_ON)] = F("{\"emergency\": {\"useEquitherm\" : true}}");
    doc[FPSTR(HA_PAYLOAD_OFF)] = F("{\"emergency\": {\"useEquitherm\" : false}}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("switch", "emergency_use_equitherm").c_str(), doc);
  }

  bool publishSwitchEmergencyUsePid(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_VALUE_TEMPLATE)] = F("{{ iif(value_json.sensors.indoor.type != 1, 'online', 'offline') }}");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("emergency_use_pid");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("emergency_use_pid");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_NAME)] = F("Use PID in emergency");
    doc[FPSTR(HA_ICON)] = F("mdi:snowflake-alert");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_STATE_ON)] = true;
    doc[FPSTR(HA_STATE_OFF)] = false;
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.emergency.usePid }}");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_PAYLOAD_ON)] = F("{\"emergency\": {\"usePid\" : true}}");
    doc[FPSTR(HA_PAYLOAD_OFF)] = F("{\"emergency\": {\"usePid\" : false}}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("switch", "emergency_use_pid").c_str(), doc);
  }


  bool publishSwitchHeating(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_TOPIC)] = this->getDeviceTopic("status");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("heating");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("heating");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_NAME)] = F("Heating");
    doc[FPSTR(HA_ICON)] = F("mdi:radiator");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_STATE_ON)] = true;
    doc[FPSTR(HA_STATE_OFF)] = false;
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.heating.enable }}");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_PAYLOAD_ON)] = F("{\"heating\": {\"enable\" : true}}");
    doc[FPSTR(HA_PAYLOAD_OFF)] = F("{\"heating\": {\"enable\" : false}}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("switch", "heating").c_str(), doc);
  }

  bool publishSwitchHeatingTurbo(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_TOPIC)] = this->getDeviceTopic("status");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("heating_turbo");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("heating_turbo");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_NAME)] = F("Turbo heating");
    doc[FPSTR(HA_ICON)] = F("mdi:rocket-launch-outline");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_STATE_ON)] = true;
    doc[FPSTR(HA_STATE_OFF)] = false;
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.heating.turbo }}");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_PAYLOAD_ON)] = F("{\"heating\": {\"turbo\" : true}}");
    doc[FPSTR(HA_PAYLOAD_OFF)] = F("{\"heating\": {\"turbo\" : false}}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("switch", "heating_turbo").c_str(), doc);
  }

  bool publishNumberHeatingTarget(byte minTemp = 20, byte maxTemp = 90, bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_TOPIC)] = this->getDeviceTopic("status");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("heating_target");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("heating_target");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("temperature");
    doc[FPSTR(HA_UNIT_OF_MEASUREMENT)] = F("°C");
    doc[FPSTR(HA_NAME)] = F("Heating target");
    doc[FPSTR(HA_ICON)] = F("mdi:radiator");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.heating.target|float(0)|round(1) }}");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_COMMAND_TEMPLATE)] = F("{\"heating\": {\"target\" : {{ value }}}}");
    doc[FPSTR(HA_MIN)] = minTemp;
    doc[FPSTR(HA_MAX)] = maxTemp;
    doc[FPSTR(HA_STEP)] = 0.5;
    doc[FPSTR(HA_MODE)] = "box";
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("number", "heating_target").c_str(), doc);
  }

  bool publishNumberHeatingHysteresis(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("heating_hysteresis");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("heating_hysteresis");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("temperature");
    doc[FPSTR(HA_UNIT_OF_MEASUREMENT)] = F("°C");
    doc[FPSTR(HA_NAME)] = F("Heating hysteresis");
    doc[FPSTR(HA_ICON)] = F("mdi:altimeter");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.heating.hysteresis|float(0)|round(1) }}");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_COMMAND_TEMPLATE)] = F("{\"heating\": {\"hysteresis\" : {{ value }}}}");
    doc[FPSTR(HA_MIN)] = 0;
    doc[FPSTR(HA_MAX)] = 5;
    doc[FPSTR(HA_STEP)] = 0.1;
    doc[FPSTR(HA_MODE)] = "box";
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("number", "heating_hysteresis").c_str(), doc);
  }

  bool publishSensorHeatingSetpoint(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_TOPIC)] = this->getDeviceTopic("status");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("heating_setpoint");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("heating_setpoint");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("diagnostic");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("temperature");
    doc[FPSTR(HA_STATE_CLASS)] = F("measurement");
    doc[FPSTR(HA_UNIT_OF_MEASUREMENT)] = F("°C");
    doc[FPSTR(HA_NAME)] = F("Heating setpoint");
    doc[FPSTR(HA_ICON)] = F("mdi:coolant-temperature");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("state");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.parameters.heatingSetpoint|int(0) }}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("sensor", "heating_setpoint").c_str(), doc);
  }

  bool publishSensorBoilerHeatingMinTemp(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_TOPIC)] = this->getDeviceTopic("status");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("boiler_heating_min_temp");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("boiler_heating_min_temp");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("diagnostic");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("temperature");
    doc[FPSTR(HA_STATE_CLASS)] = F("measurement");
    doc[FPSTR(HA_UNIT_OF_MEASUREMENT)] = F("°C");
    doc[FPSTR(HA_NAME)] = F("Boiler heating min temp");
    doc[FPSTR(HA_ICON)] = F("mdi:thermometer-chevron-down");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("state");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.parameters.heatingMinTemp|int(0) }}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("sensor", "boiler_heating_min_temp").c_str(), doc);
  }

  bool publishSensorBoilerHeatingMaxTemp(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_TOPIC)] = this->getDeviceTopic("status");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("boiler_heating_max_temp");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("boiler_heating_max_temp");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("diagnostic");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("temperature");
    doc[FPSTR(HA_STATE_CLASS)] = F("measurement");
    doc[FPSTR(HA_UNIT_OF_MEASUREMENT)] = F("°C");
    doc[FPSTR(HA_NAME)] = F("Boiler heating max temp");
    doc[FPSTR(HA_ICON)] = F("mdi:thermometer-chevron-up");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("state");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.parameters.heatingMaxTemp|int(0) }}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("sensor", "boiler_heating_max_temp").c_str(), doc);
  }

  bool publishNumberHeatingMinTemp(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("heating_min_temp");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("heating_min_temp");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("temperature");
    doc[FPSTR(HA_UNIT_OF_MEASUREMENT)] = F("°C");
    doc[FPSTR(HA_NAME)] = F("Heating min temp");
    doc[FPSTR(HA_ICON)] = F("mdi:thermometer-chevron-down");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.heating.minTemp|float(0)|round(1) }}");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_COMMAND_TEMPLATE)] = F("{\"heating\": {\"minTemp\" : {{ value }}}}");
    doc[FPSTR(HA_MIN)] = 0;
    doc[FPSTR(HA_MAX)] = 99;
    doc[FPSTR(HA_STEP)] = 1;
    doc[FPSTR(HA_MODE)] = "box";
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("number", "heating_min_temp").c_str(), doc);
  }

  bool publishNumberHeatingMaxTemp(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("heating_max_temp");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("heating_max_temp");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("temperature");
    doc[FPSTR(HA_UNIT_OF_MEASUREMENT)] = F("°C");
    doc[FPSTR(HA_NAME)] = F("Heating max temp");
    doc[FPSTR(HA_ICON)] = F("mdi:thermometer-chevron-up");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.heating.maxTemp|float(0)|round(1) }}");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_COMMAND_TEMPLATE)] = F("{\"heating\": {\"maxTemp\" : {{ value }}}}");
    doc[FPSTR(HA_MIN)] = 1;
    doc[FPSTR(HA_MAX)] = 100;
    doc[FPSTR(HA_STEP)] = 1;
    doc[FPSTR(HA_MODE)] = "box";
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("number", "heating_max_temp").c_str(), doc);
  }

  bool publishNumberHeatingMaxModulation(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("heating_max_modulation");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("heating_max_modulation");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("power_factor");
    doc[FPSTR(HA_UNIT_OF_MEASUREMENT)] = F("%");
    doc[FPSTR(HA_NAME)] = F("Max modulation");
    doc[FPSTR(HA_ICON)] = F("mdi:speedometer");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.heating.maxModulation|int(1) }}");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_COMMAND_TEMPLATE)] = F("{\"heating\": {\"maxModulation\" : {{ value }}}}");
    doc[FPSTR(HA_MIN)] = 1;
    doc[FPSTR(HA_MAX)] = 100;
    doc[FPSTR(HA_STEP)] = 1;
    doc[FPSTR(HA_MODE)] = "box";
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("number", "heating_max_modulation").c_str(), doc);
  }


  bool publishSwitchDhw(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_TOPIC)] = this->getDeviceTopic("status");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("dhw");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("dhw");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_NAME)] = F("DHW");
    doc[FPSTR(HA_ICON)] = F("mdi:water-pump");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_STATE_ON)] = true;
    doc[FPSTR(HA_STATE_OFF)] = false;
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.dhw.enable }}");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_PAYLOAD_ON)] = F("{\"dhw\": {\"enable\" : true}}");
    doc[FPSTR(HA_PAYLOAD_OFF)] = F("{\"dhw\": {\"enable\" : false}}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("switch", "dhw").c_str(), doc);
  }

  bool publishNumberDhwTarget(byte minTemp = 40, byte maxTemp = 60, bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_TOPIC)] = this->getDeviceTopic("status");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("dhw_target");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("dhw_target");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("temperature");
    doc[FPSTR(HA_UNIT_OF_MEASUREMENT)] = F("°C");
    doc[FPSTR(HA_NAME)] = F("DHW target");
    doc[FPSTR(HA_ICON)] = F("mdi:water-pump");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.dhw.target|int(0) }}");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_COMMAND_TEMPLATE)] = F("{\"dhw\": {\"target\" : {{ value|int(0) }}}}");
    doc[FPSTR(HA_MIN)] = minTemp;
    doc[FPSTR(HA_MAX)] = maxTemp <= minTemp ? maxTemp : maxTemp;
    doc[FPSTR(HA_STEP)] = 1;
    doc[FPSTR(HA_MODE)] = "box";
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("number", "dhw_target").c_str(), doc);
  }

  bool publishSensorBoilerDhwMinTemp(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_TOPIC)] = this->getDeviceTopic("status");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("boiler_dhw_min_temp");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("boiler_dhw_min_temp");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("diagnostic");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("temperature");
    doc[FPSTR(HA_STATE_CLASS)] = F("measurement");
    doc[FPSTR(HA_UNIT_OF_MEASUREMENT)] = F("°C");
    doc[FPSTR(HA_NAME)] = F("Boiler DHW min temp");
    doc[FPSTR(HA_ICON)] = F("mdi:thermometer-chevron-down");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("state");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.parameters.dhwMinTemp|int(0) }}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("sensor", "boiler_dhw_min_temp").c_str(), doc);
  }

  bool publishSensorBoilerDhwMaxTemp(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_TOPIC)] = this->getDeviceTopic("status");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("boiler_dhw_max_temp");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("boiler_dhw_max_temp");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("diagnostic");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("temperature");
    doc[FPSTR(HA_STATE_CLASS)] = F("measurement");
    doc[FPSTR(HA_UNIT_OF_MEASUREMENT)] = F("°C");
    doc[FPSTR(HA_NAME)] = F("Boiler DHW max temp");
    doc[FPSTR(HA_ICON)] = F("mdi:thermometer-chevron-up");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("state");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.parameters.dhwMaxTemp|int(0) }}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("sensor", "boiler_dhw_max_temp").c_str(), doc);
  }

  bool publishNumberDhwMinTemp(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("dhw_min_temp");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("dhw_min_temp");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("temperature");
    doc[FPSTR(HA_UNIT_OF_MEASUREMENT)] = F("°C");
    doc[FPSTR(HA_NAME)] = F("DHW min temp");
    doc[FPSTR(HA_ICON)] = F("mdi:thermometer-chevron-down");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.dhw.minTemp|float(0)|round(1) }}");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_COMMAND_TEMPLATE)] = F("{\"dhw\": {\"minTemp\" : {{ value }}}}");
    doc[FPSTR(HA_MIN)] = 0;
    doc[FPSTR(HA_MAX)] = 99;
    doc[FPSTR(HA_STEP)] = 1;
    doc[FPSTR(HA_MODE)] = "box";
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("number", "dhw_min_temp").c_str(), doc);
  }

  bool publishNumberDhwMaxTemp(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("dhw_max_temp");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("dhw_max_temp");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("temperature");
    doc[FPSTR(HA_UNIT_OF_MEASUREMENT)] = F("°C");
    doc[FPSTR(HA_NAME)] = F("DHW max temp");
    doc[FPSTR(HA_ICON)] = F("mdi:thermometer-chevron-up");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.dhw.maxTemp|float(0)|round(1) }}");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_COMMAND_TEMPLATE)] = F("{\"dhw\": {\"maxTemp\" : {{ value }}}}");
    doc[FPSTR(HA_MIN)] = 1;
    doc[FPSTR(HA_MAX)] = 100;
    doc[FPSTR(HA_STEP)] = 1;
    doc[FPSTR(HA_MODE)] = "box";
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("number", "dhw_max_temp").c_str(), doc);
  }


  bool publishSwitchPid(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("pid");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("pid");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_NAME)] = F("PID");
    doc[FPSTR(HA_ICON)] = F("mdi:chart-bar-stacked");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_STATE_ON)] = true;
    doc[FPSTR(HA_STATE_OFF)] = false;
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.pid.enable }}");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_PAYLOAD_ON)] = F("{\"pid\": {\"enable\" : true}}");
    doc[FPSTR(HA_PAYLOAD_OFF)] = F("{\"pid\": {\"enable\" : false}}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("switch", "pid").c_str(), doc);
  }

  bool publishNumberPidFactorP(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("pid_p");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("pid_p");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_NAME)] = F("PID factor P");
    doc[FPSTR(HA_ICON)] = F("mdi:alpha-p-circle-outline");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.pid.p_factor|float(0)|round(3) }}");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_COMMAND_TEMPLATE)] = F("{\"pid\": {\"p_factor\" : {{ value }}}}");
    doc[FPSTR(HA_MIN)] = 0.1;
    doc[FPSTR(HA_MAX)] = 1000;
    doc[FPSTR(HA_STEP)] = 0.1;
    doc[FPSTR(HA_MODE)] = "box";
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("number", "pid_p_factor").c_str(), doc);
  }

  bool publishNumberPidFactorI(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("pid_i");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("pid_i");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_NAME)] = F("PID factor I");
    doc[FPSTR(HA_ICON)] = F("mdi:alpha-i-circle-outline");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.pid.i_factor|float(0)|round(3) }}");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_COMMAND_TEMPLATE)] = F("{\"pid\": {\"i_factor\" : {{ value }}}}");
    doc[FPSTR(HA_MIN)] = 0;
    doc[FPSTR(HA_MAX)] = 100;
    doc[FPSTR(HA_STEP)] = 0.001;
    doc[FPSTR(HA_MODE)] = "box";
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("number", "pid_i_factor").c_str(), doc);
  }

  bool publishNumberPidFactorD(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("pid_d");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("pid_d");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_NAME)] = F("PID factor D");
    doc[FPSTR(HA_ICON)] = F("mdi:alpha-d-circle-outline");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.pid.d_factor|float(0)|round(3) }}");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_COMMAND_TEMPLATE)] = F("{\"pid\": {\"d_factor\" : {{ value }}}}");
    doc[FPSTR(HA_MIN)] = 0;
    doc[FPSTR(HA_MAX)] = 100000;
    doc[FPSTR(HA_STEP)] = 1;
    doc[FPSTR(HA_MODE)] = "box";
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("number", "pid_d_factor").c_str(), doc);
  }

  bool publishNumberPidDt(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("pid_dt");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("pid_dt");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("duration");
    doc[FPSTR(HA_UNIT_OF_MEASUREMENT)] = F("s");
    doc[FPSTR(HA_NAME)] = F("PID DT");
    doc[FPSTR(HA_ICON)] = F("mdi:timer-cog-outline");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.pid.dt|int(0) }}");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_COMMAND_TEMPLATE)] = F("{\"pid\": {\"dt\" : {{ value }}}}");
    doc[FPSTR(HA_MIN)] = 30;
    doc[FPSTR(HA_MAX)] = 600;
    doc[FPSTR(HA_STEP)] = 1;
    doc[FPSTR(HA_MODE)] = "box";
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("number", "pid_dt").c_str(), doc);
  }

  bool publishNumberPidMinTemp(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("pid_min_temp");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("pid_min_temp");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("temperature");
    doc[FPSTR(HA_UNIT_OF_MEASUREMENT)] = F("°C");
    doc[FPSTR(HA_NAME)] = F("PID min temp");
    doc[FPSTR(HA_ICON)] = F("mdi:thermometer-chevron-down");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.pid.minTemp|float(0)|round(1) }}");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_COMMAND_TEMPLATE)] = F("{\"pid\": {\"minTemp\" : {{ value }}}}");
    doc[FPSTR(HA_MIN)] = 0;
    doc[FPSTR(HA_MAX)] = 99;
    doc[FPSTR(HA_STEP)] = 1;
    doc[FPSTR(HA_MODE)] = "box";
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("number", "pid_min_temp").c_str(), doc);
  }

  bool publishNumberPidMaxTemp(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("pid_max_temp");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("pid_max_temp");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("temperature");
    doc[FPSTR(HA_UNIT_OF_MEASUREMENT)] = F("°C");
    doc[FPSTR(HA_NAME)] = F("PID max temp");
    doc[FPSTR(HA_ICON)] = F("mdi:thermometer-chevron-up");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.pid.maxTemp|float(0)|round(1) }}");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_COMMAND_TEMPLATE)] = F("{\"pid\": {\"maxTemp\" : {{ value }}}}");
    doc[FPSTR(HA_MIN)] = 1;
    doc[FPSTR(HA_MAX)] = 100;
    doc[FPSTR(HA_STEP)] = 1;
    doc[FPSTR(HA_MODE)] = "box";
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("number", "pid_max_temp").c_str(), doc);
  }


  bool publishSwitchEquitherm(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("equitherm");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("equitherm");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_NAME)] = F("Equitherm");
    doc[FPSTR(HA_ICON)] = F("mdi:sun-snowflake-variant");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_STATE_ON)] = true;
    doc[FPSTR(HA_STATE_OFF)] = false;
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.equitherm.enable }}");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_PAYLOAD_ON)] = F("{\"equitherm\": {\"enable\" : true}}");
    doc[FPSTR(HA_PAYLOAD_OFF)] = F("{\"equitherm\": {\"enable\" : false}}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("switch", "equitherm").c_str(), doc);
  }

  bool publishNumberEquithermFactorN(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("equitherm_n");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("equitherm_n");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_NAME)] = F("Equitherm factor N");
    doc[FPSTR(HA_ICON)] = F("mdi:alpha-n-circle-outline");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.equitherm.n_factor|float(0)|round(3) }}");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_COMMAND_TEMPLATE)] = F("{\"equitherm\": {\"n_factor\" : {{ value }}}}");
    doc[FPSTR(HA_MIN)] = 0.001;
    doc[FPSTR(HA_MAX)] = 10;
    doc[FPSTR(HA_STEP)] = 0.001;
    doc[FPSTR(HA_MODE)] = "box";
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("number", "equitherm_n_factor").c_str(), doc);
  }

  bool publishNumberEquithermFactorK(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("equitherm_k");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("equitherm_k");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_NAME)] = F("Equitherm factor K");
    doc[FPSTR(HA_ICON)] = F("mdi:alpha-k-circle-outline");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.equitherm.k_factor|float(0)|round(2) }}");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_COMMAND_TEMPLATE)] = F("{\"equitherm\": {\"k_factor\" : {{ value }}}}");
    doc[FPSTR(HA_MIN)] = 0;
    doc[FPSTR(HA_MAX)] = 10;
    doc[FPSTR(HA_STEP)] = 0.01;
    doc[FPSTR(HA_MODE)] = "box";
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("number", "equitherm_k_factor").c_str(), doc);
  }

  bool publishNumberEquithermFactorT(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_VALUE_TEMPLATE)] = F("{{ iif(value_json.pid.enable, 'offline', 'online') }}");
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("equitherm_t");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("equitherm_t");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_NAME)] = F("Equitherm factor T");
    doc[FPSTR(HA_ICON)] = F("mdi:alpha-t-circle-outline");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.equitherm.t_factor|float(0)|round(2) }}");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_COMMAND_TEMPLATE)] = F("{\"equitherm\": {\"t_factor\" : {{ value }}}}");
    doc[FPSTR(HA_MIN)] = 0;
    doc[FPSTR(HA_MAX)] = 10;
    doc[FPSTR(HA_STEP)] = 0.01;
    doc[FPSTR(HA_MODE)] = "box";
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("number", "equitherm_t_factor").c_str(), doc);
  }


  bool publishSwitchTuning(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("tuning");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("tuning");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_NAME)] = F("Tuning");
    doc[FPSTR(HA_ICON)] = F("mdi:tune-vertical");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("state");
    doc[FPSTR(HA_STATE_ON)] = true;
    doc[FPSTR(HA_STATE_OFF)] = false;
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.tuning.enable }}");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("state/set");
    doc[FPSTR(HA_PAYLOAD_ON)] = F("{\"tuning\": {\"enable\" : true}}");
    doc[FPSTR(HA_PAYLOAD_OFF)] = F("{\"tuning\": {\"enable\" : false}}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("switch", "tuning").c_str(), doc);
  }

  bool publishSelectTuningRegulator(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_TOPIC)] = this->getDeviceTopic("status");
    doc[FPSTR(HA_AVAILABILITY_MODE)] = F("all");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("state/set");
    doc[FPSTR(HA_COMMAND_TEMPLATE)] = F("{\"tuning\": {\"regulator\": {% if value == 'Equitherm' %}0{% elif value == 'PID' %}1{% endif %}}}");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("tuning_regulator");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("tuning_regulator");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_NAME)] = F("Tuning regulator");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("state");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{% if value_json.tuning.regulator == 0 %}Equitherm{% elif value_json.tuning.regulator == 1 %}PID{% endif %}");
    doc[FPSTR(HA_OPTIONS)][0] = F("Equitherm");
    doc[FPSTR(HA_OPTIONS)][1] = F("PID");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("select", "tuning_regulator").c_str(), doc);
  }


  bool publishBinSensorStatus(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("status");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("status");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("diagnostic");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("problem");
    doc[FPSTR(HA_NAME)] = F("Status");
    doc[FPSTR(HA_ICON)] = F("mdi:list-status");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("status");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ iif(value == 'online', 'OFF', 'ON') }}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 60;
    doc.shrinkToFit();

    return this->publish(this->getTopic("binary_sensor", "status").c_str(), doc);
  }

  bool publishBinSensorOtStatus(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("ot_status");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("ot_status");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("diagnostic");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("problem");
    doc[FPSTR(HA_NAME)] = F("Opentherm status");
    doc[FPSTR(HA_ICON)] = F("mdi:list-status");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("state");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ iif(value_json.states.otStatus, 'OFF', 'ON') }}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("binary_sensor", "ot_status").c_str(), doc);
  }

  bool publishBinSensorHeating(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_TOPIC)] = this->getDeviceTopic("status");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("heating");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("heating");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("diagnostic");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("running");
    doc[FPSTR(HA_NAME)] = F("Heating");
    doc[FPSTR(HA_ICON)] = F("mdi:radiator");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("state");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ iif(value_json.states.heating, 'ON', 'OFF') }}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("binary_sensor", "heating").c_str(), doc);
  }

  bool publishBinSensorDhw(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_TOPIC)] = this->getDeviceTopic("status");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("dhw");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("dhw");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("diagnostic");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("running");
    doc[FPSTR(HA_NAME)] = F("DHW");
    doc[FPSTR(HA_ICON)] = F("mdi:water-pump");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("state");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ iif(value_json.states.dhw, 'ON', 'OFF') }}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("binary_sensor", "dhw").c_str(), doc);
  }

  bool publishBinSensorFlame(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_TOPIC)] = this->getDeviceTopic("status");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("flame");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("flame");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("diagnostic");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("running");
    doc[FPSTR(HA_NAME)] = F("Flame");
    doc[FPSTR(HA_ICON)] = F("mdi:fire");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("state");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ iif(value_json.states.flame, 'ON', 'OFF') }}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("binary_sensor", "flame").c_str(), doc);
  }

  bool publishBinSensorFault(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_TOPIC)] = this->getDeviceTopic("state");
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_VALUE_TEMPLATE)] = F("{{ iif(value_json.states.otStatus, 'online', 'offline') }}");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("fault");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("fault");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("diagnostic");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("problem");
    doc[FPSTR(HA_NAME)] = F("Fault");
    doc[FPSTR(HA_ICON)] = F("mdi:water-boiler-alert");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("state");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ iif(value_json.states.fault, 'ON', 'OFF') }}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("binary_sensor", "fault").c_str(), doc);
  }

  bool publishBinSensorDiagnostic(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_TOPIC)] = this->getDeviceTopic("status");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("diagnostic");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("diagnostic");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("diagnostic");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("problem");
    doc[FPSTR(HA_NAME)] = F("Diagnostic");
    doc[FPSTR(HA_ICON)] = F("mdi:account-wrench");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("state");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ iif(value_json.states.diagnostic, 'ON', 'OFF') }}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("binary_sensor", "diagnostic").c_str(), doc);
  }

  bool publishSensorFaultCode(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_TOPIC)] = this->getDeviceTopic("state");
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_VALUE_TEMPLATE)] = F("{{ iif(value_json.states.fault, 'online', 'offline') }}");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("fault_code");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("fault_code");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("diagnostic");
    doc[FPSTR(HA_NAME)] = F("Fault code");
    doc[FPSTR(HA_ICON)] = F("mdi:chat-alert-outline");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("state");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ \"E%02d\"|format(value_json.sensors.faultCode) }}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("sensor", "fault_code").c_str(), doc);
  }

  bool publishSensorRssi(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_TOPIC)] = this->getDeviceTopic("status");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("rssi");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("rssi");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("diagnostic");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("signal_strength");
    doc[FPSTR(HA_STATE_CLASS)] = F("measurement");
    doc[FPSTR(HA_UNIT_OF_MEASUREMENT)] = F("dBm");
    doc[FPSTR(HA_NAME)] = F("RSSI");
    doc[FPSTR(HA_ICON)] = F("mdi:signal");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("state");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.sensors.rssi|float(0)|round(1) }}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("sensor", "rssi").c_str(), doc);
  }

  bool publishSensorUptime(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_TOPIC)] = this->getDeviceTopic("status");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("uptime");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("uptime");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("diagnostic");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("duration");
    doc[FPSTR(HA_STATE_CLASS)] = F("total_increasing");
    doc[FPSTR(HA_UNIT_OF_MEASUREMENT)] = F("s");
    doc[FPSTR(HA_NAME)] = F("Uptime");
    doc[FPSTR(HA_ICON)] = F("mdi:clock-start");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("state");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.sensors.uptime|int(0) }}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("sensor", "uptime").c_str(), doc);
  }


  bool publishSensorModulation(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_TOPIC)] = this->getDeviceTopic("status");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("modulation_level");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("modulation_level");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("diagnostic");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("power_factor");
    doc[FPSTR(HA_STATE_CLASS)] = F("measurement");
    doc[FPSTR(HA_UNIT_OF_MEASUREMENT)] = F("%");
    doc[FPSTR(HA_NAME)] = F("Modulation level");
    doc[FPSTR(HA_ICON)] = F("mdi:fire-circle");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("state");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.sensors.modulation|float(0)|round(0) }}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("sensor", "modulation").c_str(), doc);
  }

  bool publishSensorPressure(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_TOPIC)] = this->getDeviceTopic("status");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("pressure");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("pressure");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("diagnostic");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("pressure");
    doc[FPSTR(HA_STATE_CLASS)] = F("measurement");
    doc[FPSTR(HA_UNIT_OF_MEASUREMENT)] = F("bar");
    doc[FPSTR(HA_NAME)] = F("Pressure");
    doc[FPSTR(HA_ICON)] = F("mdi:gauge");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("state");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.sensors.pressure|float(0)|round(2) }}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("sensor", "pressure").c_str(), doc);
  }

  bool publishSensorDhwFlowRate(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_TOPIC)] = this->getDeviceTopic("status");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("dhw_flow_rate");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("dhw_flow_rate");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("diagnostic");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("volume");
    doc[FPSTR(HA_STATE_CLASS)] = F("measurement");
    doc[FPSTR(HA_UNIT_OF_MEASUREMENT)] = F("L/min");
    doc[FPSTR(HA_NAME)] = F("DHW flow rate");
    doc[FPSTR(HA_ICON)] = F("mdi:water-pump");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("state");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.sensors.dhwFlowRate|float(0)|round(2) }}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("sensor", "dhw_flow_rate").c_str(), doc);
  }


  bool publishNumberIndoorTemp(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("indoor_temp");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("indoor_temp");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_UNIT_OF_MEASUREMENT)] = F("°C");
    doc[FPSTR(HA_NAME)] = F("Indoor temperature");
    doc[FPSTR(HA_ICON)] = F("mdi:home-thermometer");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("state");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.temperatures.indoor|float(0)|round(1) }}");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("state/set");
    doc[FPSTR(HA_COMMAND_TEMPLATE)] = F("{\"temperatures\": {\"indoor\":{{ value }}}}");
    doc[FPSTR(HA_MIN)] = -99;
    doc[FPSTR(HA_MAX)] = 99;
    doc[FPSTR(HA_STEP)] = 0.01;
    doc[FPSTR(HA_MODE)] = "box";
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("number", "indoor_temp").c_str(), doc);
  }

  bool publishSensorIndoorTemp(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][0][FPSTR(HA_TOPIC)] = this->getDeviceTopic("status");
    doc[FPSTR(HA_AVAILABILITY_MODE)] = F("any");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("indoor_temp");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("indoor_temp");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("diagnostic");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("temperature");
    doc[FPSTR(HA_STATE_CLASS)] = F("measurement");
    doc[FPSTR(HA_UNIT_OF_MEASUREMENT)] = F("°C");
    doc[FPSTR(HA_NAME)] = F("Indoor temperature");
    doc[FPSTR(HA_ICON)] = F("mdi:home-thermometer");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("state");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.temperatures.indoor|float(0)|round(1) }}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("sensor", "indoor_temp").c_str(), doc);
  }

  bool publishNumberOutdoorTemp(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("outdoor_temp");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("outdoor_temp");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_UNIT_OF_MEASUREMENT)] = F("°C");
    doc[FPSTR(HA_NAME)] = F("Outdoor temperature");
    doc[FPSTR(HA_ICON)] = F("mdi:home-thermometer-outline");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("state");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.temperatures.outdoor|float(0)|round(1) }}");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("state/set");
    doc[FPSTR(HA_COMMAND_TEMPLATE)] = F("{\"temperatures\": {\"outdoor\":{{ value }}}}");
    doc[FPSTR(HA_MIN)] = -99;
    doc[FPSTR(HA_MAX)] = 99;
    doc[FPSTR(HA_STEP)] = 0.01;
    doc[FPSTR(HA_MODE)] = "box";
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("number", "outdoor_temp").c_str(), doc);
  }

  bool publishSensorOutdoorTemp(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][0][FPSTR(HA_TOPIC)] = this->getDeviceTopic("status");
    doc[FPSTR(HA_AVAILABILITY_MODE)] = F("any");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("outdoor_temp");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("outdoor_temp");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("diagnostic");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("temperature");
    doc[FPSTR(HA_STATE_CLASS)] = F("measurement");
    doc[FPSTR(HA_UNIT_OF_MEASUREMENT)] = F("°C");
    doc[FPSTR(HA_NAME)] = F("Outdoor temperature");
    doc[FPSTR(HA_ICON)] = F("mdi:home-thermometer-outline");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("state");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.temperatures.outdoor|float(0)|round(1) }}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("sensor", "outdoor_temp").c_str(), doc);
  }

  bool publishSensorHeatingTemp(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_TOPIC)] = this->getDeviceTopic("status");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("heating_temp");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("heating_temp");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("diagnostic");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("temperature");
    doc[FPSTR(HA_STATE_CLASS)] = F("measurement");
    doc[FPSTR(HA_UNIT_OF_MEASUREMENT)] = F("°C");
    doc[FPSTR(HA_NAME)] = F("Heating temperature");
    doc[FPSTR(HA_ICON)] = F("mdi:radiator");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("state");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.temperatures.heating|float(0)|round(2) }}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("sensor", "heating_temp").c_str(), doc);
  }

  bool publishSensorDhwTemp(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_TOPIC)] = this->getDeviceTopic("status");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("dhw_temp");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("dhw_temp");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("diagnostic");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("temperature");
    doc[FPSTR(HA_STATE_CLASS)] = F("measurement");
    doc[FPSTR(HA_UNIT_OF_MEASUREMENT)] = F("°C");
    doc[FPSTR(HA_NAME)] = F("DHW temperature");
    doc[FPSTR(HA_ICON)] = F("mdi:water-pump");
    doc[FPSTR(HA_STATE_TOPIC)] = this->getDeviceTopic("state");
    doc[FPSTR(HA_VALUE_TEMPLATE)] = F("{{ value_json.temperatures.dhw|float(0)|round(2) }}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("sensor", "dhw_temp").c_str(), doc);
  }


  bool publishClimateHeating(byte minTemp = 20, byte maxTemp = 90, byte currentTempSource = HaHelper::TEMP_SOURCE_HEATING, bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_TOPIC)] = this->getDeviceTopic("status");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("heating");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("heating");
    doc[FPSTR(HA_NAME)] = F("Heating");
    doc[FPSTR(HA_ICON)] = F("mdi:radiator");

    if (currentTempSource == HaHelper::TEMP_SOURCE_HEATING || currentTempSource == HaHelper::TEMP_SOURCE_INDOOR) {
      doc[FPSTR(HA_CURRENT_TEMPERATURE_TOPIC)] = this->getDeviceTopic("state");
    }

    if (currentTempSource == HaHelper::TEMP_SOURCE_HEATING) {
      doc[FPSTR(HA_CURRENT_TEMPERATURE_TEMPLATE)] = F("{{ value_json.temperatures.heating|float(0)|round(2) }}");

    } else if (currentTempSource == HaHelper::TEMP_SOURCE_INDOOR) {
      doc[FPSTR(HA_CURRENT_TEMPERATURE_TEMPLATE)] = F("{{ value_json.temperatures.indoor|float(0)|round(2) }}");
    }

    doc[FPSTR(HA_TEMPERATURE_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_TEMPERATURE_COMMAND_TEMPLATE)] = F("{\"heating\": {\"target\" : {{ value }}}}");

    doc[FPSTR(HA_TEMPERATURE_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_TEMPERATURE_STATE_TEMPLATE)] = F("{{ value_json.heating.target|float(0)|round(1) }}");

    doc[FPSTR(HA_MODE_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_MODE_COMMAND_TEMPLATE)] = F("{% if value == 'heat' %}{\"heating\": {\"enable\" : true}}"
      "{% elif value == 'off' %}{\"heating\": {\"enable\" : false}}{% endif %}");
    doc[FPSTR(HA_MODE_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_MODE_STATE_TEMPLATE)] = F("{{ iif(value_json.heating.enable, 'heat', 'off') }}");
    doc[FPSTR(HA_MODES)][0] = F("off");
    doc[FPSTR(HA_MODES)][1] = F("heat");

    doc[FPSTR(HA_ACTION_TOPIC)] = this->getDeviceTopic("state");
    doc[FPSTR(HA_ACTION_TEMPLATE)] = F("{{ iif(value_json.states.heating, 'heating', 'idle') }}");

    doc[FPSTR(HA_PRESET_MODE_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_PRESET_MODE_COMMAND_TEMPLATE)] = F("{% if value == 'boost' %}{\"heating\": {\"turbo\" : true}}"
      "{% elif value == 'none' %}{\"heating\": {\"turbo\" : false}}{% endif %}");
    doc[FPSTR(HA_PRESET_MODE_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_PRESET_MODE_VALUE_TEMPLATE)] = F("{{ iif(value_json.heating.turbo, 'boost', 'none') }}");
    doc[FPSTR(HA_PRESET_MODES)][0] = F("boost");

    doc[FPSTR(HA_MIN_TEMP)] = minTemp;
    doc[FPSTR(HA_MAX_TEMP)] = maxTemp;
    doc[FPSTR(HA_TEMP_STEP)] = 0.5;
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("climate", "heating", '_').c_str(), doc);
  }

  bool publishClimateDhw(byte minTemp = 40, byte maxTemp = 60, bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_TOPIC)] = this->getDeviceTopic("status");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("dhw");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("dhw");
    doc[FPSTR(HA_NAME)] = F("DHW");
    doc[FPSTR(HA_ICON)] = F("mdi:water-pump");

    doc[FPSTR(HA_CURRENT_TEMPERATURE_TOPIC)] = this->getDeviceTopic("state");
    doc[FPSTR(HA_CURRENT_TEMPERATURE_TEMPLATE)] = F("{{ value_json.temperatures.dhw|float(0)|round(1) }}");

    doc[FPSTR(HA_TEMPERATURE_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_TEMPERATURE_COMMAND_TEMPLATE)] = F("{\"dhw\": {\"target\" : {{ value|int(0) }}}}");

    doc[FPSTR(HA_TEMPERATURE_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_TEMPERATURE_STATE_TEMPLATE)] = F("{{ value_json.dhw.target|int(0) }}");

    doc[FPSTR(HA_MODE_COMMAND_TOPIC)] = this->getDeviceTopic("settings/set");
    doc[FPSTR(HA_MODE_COMMAND_TEMPLATE)] = F("{% if value == 'heat' %}{\"dhw\": {\"enable\" : true}}"
      "{% elif value == 'off' %}{\"dhw\": {\"enable\" : false}}{% endif %}");
    doc[FPSTR(HA_MODE_STATE_TOPIC)] = this->getDeviceTopic("settings");
    doc[FPSTR(HA_MODE_STATE_TEMPLATE)] = F("{{ iif(value_json.dhw.enable, 'heat', 'off') }}");
    doc[FPSTR(HA_MODES)][0] = F("off");
    doc[FPSTR(HA_MODES)][1] = F("heat");

    doc[FPSTR(HA_ACTION_TOPIC)] = this->getDeviceTopic("state");
    doc[FPSTR(HA_ACTION_TEMPLATE)] = F("{{ iif(value_json.states.dhw, 'heating', 'idle') }}");

    doc[FPSTR(HA_MIN_TEMP)] = minTemp;
    doc[FPSTR(HA_MAX_TEMP)] = maxTemp;
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("climate", "dhw", '_').c_str(), doc);
  }


  bool publishButtonRestart(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("restart");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("restart");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("restart");
    doc[FPSTR(HA_NAME)] = F("Restart");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("state/set");
    doc[FPSTR(HA_COMMAND_TEMPLATE)] = F("{\"actions\": {\"restart\": true}}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("button", "restart").c_str(), doc);
  }

  bool publishButtonResetFault(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_TOPIC)] = this->getDeviceTopic("state");
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_VALUE_TEMPLATE)] = F("{{ iif(value_json.states.fault, 'online', 'offline') }}");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("reset_fault");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("reset_fault");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("restart");
    doc[FPSTR(HA_NAME)] = F("Reset fault");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("state/set");
    doc[FPSTR(HA_COMMAND_TEMPLATE)] = F("{\"actions\": {\"resetFault\": true}}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("button", "reset_fault").c_str(), doc);
  }

  bool publishButtonResetDiagnostic(bool enabledByDefault = true) {
    JsonDocument doc;
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_TOPIC)] = this->getDeviceTopic("state");
    doc[FPSTR(HA_AVAILABILITY)][FPSTR(HA_VALUE_TEMPLATE)] = F("{{ iif(value_json.states.diagnostic, 'online', 'offline') }}");
    doc[FPSTR(HA_ENABLED_BY_DEFAULT)] = enabledByDefault;
    doc[FPSTR(HA_UNIQUE_ID)] = this->getObjectId("reset_diagnostic");
    doc[FPSTR(HA_OBJECT_ID)] = this->getObjectId("reset_diagnostic");
    doc[FPSTR(HA_ENTITY_CATEGORY)] = F("config");
    doc[FPSTR(HA_DEVICE_CLASS)] = F("restart");
    doc[FPSTR(HA_NAME)] = F("Reset diagnostic");
    doc[FPSTR(HA_COMMAND_TOPIC)] = this->getDeviceTopic("state/set");
    doc[FPSTR(HA_COMMAND_TEMPLATE)] = F("{\"actions\": {\"resetDiagnostic\": true}}");
    doc[FPSTR(HA_EXPIRE_AFTER)] = 120;
    doc.shrinkToFit();

    return this->publish(this->getTopic("button", "reset_diagnostic").c_str(), doc);
  }


  bool deleteNumberOutdoorTemp() {
    return this->publish(this->getTopic("number", "outdoor_temp").c_str());
  }

  bool deleteSensorOutdoorTemp() {
    return this->publish(this->getTopic("sensor", "outdoor_temp").c_str());
  }

  bool deleteNumberIndoorTemp() {
    return this->publish(this->getTopic("number", "indoor_temp").c_str());
  }

  bool deleteSensorIndoorTemp() {
    return this->publish(this->getTopic("sensor", "indoor_temp").c_str());
  }

  bool deleteSwitchDhw() {
    return this->publish(this->getTopic("switch", "dhw").c_str());
  }

  bool deleteSensorBoilerDhwMinTemp() {
    return this->publish(this->getTopic("sensor", "boiler_dhw_min_temp").c_str());
  }

  bool deleteSensorBoilerDhwMaxTemp() {
    return this->publish(this->getTopic("sensor", "boiler_dhw_max_temp").c_str());
  }

  bool deleteNumberDhwMinTemp() {
    return this->publish(this->getTopic("number", "dhw_min_temp").c_str());
  }

  bool deleteNumberDhwMaxTemp() {
    return this->publish(this->getTopic("number", "dhw_max_temp").c_str());
  }

  bool deleteBinSensorDhw() {
    return this->publish(this->getTopic("binary_sensor", "dhw").c_str());
  }

  bool deleteSensorDhwTemp() {
    return this->publish(this->getTopic("sensor", "dhw_temp").c_str());
  }

  bool deleteNumberDhwTarget() {
    return this->publish(this->getTopic("number", "dhw_target").c_str());
  }

  bool deleteSensorDhwFlowRate() {
    return this->publish(this->getTopic("sensor", "dhw_flow_rate").c_str());
  }

  bool deleteClimateDhw() {
    return this->publish(this->getTopic("climate", "dhw", '_').c_str());
  }
};
