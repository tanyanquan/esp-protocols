/*
 * SPDX-FileCopyrightText: 2021-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
//
// Created on: 23.08.2022
// Author: franz


#pragma once


#include "cxx_include/esp_modem_dce_factory.hpp"
#include "cxx_include/esp_modem_dce_module.hpp"
#include "cxx_include/esp_modem_types.hpp"

#include "sim70xx_gps.h"

using PdpContext = esp_modem::PdpContext;

/**
 * @brief Definition of a custom SIM7070 class with GNSS capabilities.
 * This inherits from the official esp-modem's SIM7070 device which contains all common library methods.
 * On top of that, the SIM7070_gnss adds reading GNSS information, which is implemented in a private component.
 */
class SIM7070_gnss: public esp_modem::SIM7070 {
    using SIM7070::SIM7070;
public:
    esp_modem::command_result get_gnss_information_sim70xx(sim70xx_gps_t &gps);
};

/**
 * @brief DCE for the SIM7070_gnss. Here we've got to forward the general commands, aa well as the GNSS one.
 */
class DCE_gnss : public esp_modem::DCE_T<SIM7070_gnss> {
public:

    using DCE_T<SIM7070_gnss>::DCE_T;

    /**
     * @brief Sends the initial AT sequence to sync up with the device
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result sync()
    {
        return device->sync();
    }
    /**
     * @brief Reads the operator name
     * @param[out] name operator name
     * @param[out] act access technology
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result get_operator_name(std::string &name, int &act)
    {
        return device->get_operator_name(name, act);
    }
    /**
     * @brief Stores current user profile
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result store_profile()
    {
        return device->store_profile();
    }
    /**
     * @brief Sets the supplied PIN code
     * @param[in] pin Pin
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result set_pin(const std::string &pin)
    {
        return device->set_pin(pin);
    }
    /**
     * @brief Execute the supplied AT command in raw mode (doesn't append '\r' to command, returns everything)
     * @param[in] cmd String command that's send to DTE
     * @param[out] out Raw output from DTE
     * @param[in] pass Pattern in response for the API to return OK
     * @param[in] fail Pattern in response for the API to return FAIL
     * @param[in] timeout AT command timeout in milliseconds
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result at_raw(const std::string &cmd, std::string &out, const std::string &pass, const std::string &fail, int timeout)
    {
        return device->at_raw(cmd, out, pass, fail, timeout);
    }
    /**
     * @brief Execute the supplied AT command
     * @param[in] cmd AT command
     * @param[out] out Command output string
     * @param[in] timeout AT command timeout in milliseconds
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result at(const std::string &cmd, std::string &out, int timeout)
    {
        return device->at(cmd, out, timeout);
    }
    /**
     * @brief Checks if the SIM needs a PIN
     * @param[out] pin_ok true if the SIM card doesn't need a PIN to unlock
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result read_pin(bool &pin_ok)
    {
        return device->read_pin(pin_ok);
    }
    /**
     * @brief Sets echo mode
     * @param[in] echo_on true if echo mode on (repeats the commands)
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result set_echo(const bool echo_on)
    {
        return device->set_echo(echo_on);
    }
    /**
     * @brief Sets the Txt or Pdu mode for SMS (only txt is supported)
     * @param[in] txt true if txt mode
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result sms_txt_mode(const bool txt)
    {
        return device->sms_txt_mode(txt);
    }
    /**
     * @brief Sets the default (GSM) character set
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result sms_character_set()
    {
        return device->sms_character_set();
    }
    /**
     * @brief Sends SMS message in txt mode
     * @param[in] number Phone number to send the message to
     * @param[in] message Text message to be sent
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result send_sms(const std::string &number, const std::string &message)
    {
        return device->send_sms(number, message);
    }
    /**
     * @brief Resumes data mode (Switches back to the data mode, which was temporarily suspended)
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result resume_data_mode()
    {
        return device->resume_data_mode();
    }
    /**
     * @brief Sets php context
     * @param[in] p1 PdP context struct to setup modem cellular connection
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result set_pdp_context(PdpContext &pdp)
    {
        return device->set_pdp_context(pdp);
    }
    /**
     * @brief Switches to the command mode
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result set_command_mode()
    {
        return device->set_command_mode();
    }
    /**
     * @brief Switches to the CMUX mode
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result set_cmux()
    {
        return device->set_cmux();
    }
    /**
     * @brief Reads the IMSI number
     * @param[out] imsi Module's IMSI number
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result get_imsi(std::string &imsi)
    {
        return device->get_imsi(imsi);
    }
    /**
     * @brief Reads the IMEI number
     * @param[out] imei Module's IMEI number
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result get_imei(std::string &imei)
    {
        return device->get_imei(imei);
    }
    /**
     * @brief Reads the module name
     * @param[out] name module name
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result get_module_name(std::string &name)
    {
        return device->get_module_name(name);
    }
    /**
     * @brief Sets the modem to data mode
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result set_data_mode()
    {
        return device->set_data_mode();
    }
    /**
     * @brief Get Signal quality
     * @param[out] rssi signal strength indication
     * @param[out] ber channel bit error rate
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result get_signal_quality(int &rssi, int &ber)
    {
        return device->get_signal_quality(rssi, ber);
    }
    /**
     * @brief Sets HW control flow
     * @param[in] dce_flow 0=none, 2=RTS hw flow control of DCE
     * @param[in] dte_flow 0=none, 2=CTS hw flow control of DTE
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result set_flow_control(int dce_flow, int dte_flow)
    {
        return device->set_flow_control(dce_flow, dte_flow);
    }
    /**
     * @brief Hangs up current data call
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result hang_up()
    {
        return device->hang_up();
    }
    /**
     * @brief Get voltage levels of modem power up circuitry
     * @param[out] voltage Current status in mV
     * @param[out] bcs charge status (-1-Not available, 0-Not charging, 1-Charging, 2-Charging done)
     * @param[out] bcl 1-100% battery capacity, -1-Not available
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result get_battery_status(int &voltage, int &bcs, int &bcl)
    {
        return device->get_battery_status(voltage, bcs, bcl);
    }
    /**
     * @brief Power down the module
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result power_down()
    {
        return device->power_down();
    }
    /**
     * @brief Reset the module
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result reset()
    {
        return device->reset();
    }
    /**
     * @brief Configures the baudrate
     * @param[in] baud Desired baud rate of the DTE
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result set_baud(int baud)
    {
        return device->set_baud(baud);
    }
    /**
     * @brief Force an attempt to connect to a specific operator
     * @param[in] mode mode of attempt
     * mode=0 - automatic
     * mode=1 - manual
     * mode=2 - deregister
     * mode=3 - set format for read operation
     * mode=4 - manual with fallback to automatic
     * @param[in] format what format the operator is given in
     * format=0 - long format
     * format=1 - short format
     * format=2 - numeric
     * @param[in] oper the operator to connect to
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result set_operator(int mode, int format, const std::string &oper)
    {
        return device->set_operator(mode, format, oper);
    }
    /**
     * @brief Attach or detach from the GPRS service
     * @param[in] state 1-attach 0-detach
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result set_network_attachment_state(int state)
    {
        return device->set_network_attachment_state(state);
    }
    /**
     * @brief Get network attachment state
     * @param[out] state 1-attached 0-detached
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result get_network_attachment_state(int &state)
    {
        return device->get_network_attachment_state(state);
    }
    /**
     * @brief What mode the radio should be set to
     * @param[in] state state 1-full 0-minimum ...
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result set_radio_state(int state)
    {
        return device->set_radio_state(state);
    }
    /**
     * @brief Get current radio state
     * @param[out] state 1-full 0-minimum ...
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result get_radio_state(int &state)
    {
        return device->get_radio_state(state);
    }
    /**
     * @brief Set network mode
     * @param[in] mode preferred mode
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result set_network_mode(int mode)
    {
        return device->set_network_mode(mode);
    }
    /**
     * @brief Preferred network mode (CAT-M and/or NB-IoT)
     * @param[in] mode preferred selection
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result set_preferred_mode(int mode)
    {
        return device->set_preferred_mode(mode);
    }
    /**
     * @brief Set network bands for CAT-M or NB-IoT
     * @param[in] mode CAT-M or NB-IoT
     * @param[in] bands bitmap in hex representing bands
     * @param[in] size size of teh bands bitmap
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result set_network_bands(const std::string &mode, const int *bands, int size)
    {
        return device->set_network_bands(mode, bands, size);
    }
    /**
     * @brief Show network system mode
     * @param[out] mode current network mode
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result get_network_system_mode(int &mode)
    {
        return device->get_network_system_mode(mode);
    }
    /**
     * @brief GNSS power control
     * @param[out] mode power mode (0 - off, 1 - on)
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result set_gnss_power_mode(int mode)
    {
        return device->set_gnss_power_mode(mode);
    }
    /**
     * @brief GNSS power control
     * @param[out] mode power mode (0 - off, 1 - on)
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result get_gnss_power_mode(int &mode)
    {
        return device->get_gnss_power_mode(mode);
    }
    /**
     * @brief Configure PSM
     * @param[in] mode psm mode (0 - off, 1 - on, 2 - off & discard stored params)
     * @return OK, FAIL or TIMEOUT
     */
    esp_modem::command_result config_psm(int mode, const std::string &tau, const std::string &active_time)
    {
        return device->config_psm(mode, tau, active_time);
    }
    /**
     * @brief Configure CEREG urc
     * @param[in] value
     * value = 0 - Disable network URC
     * value = 1 - Enable network URC
     * value = 2 - Enable network URC with location information
     * value = 3 - Enable network URC with location information and EMM cause
     * value = 4 - Enable network URC with location information and PSM value
     * value = 5 - Enable network URC with location information and PSM value, EMM cause
     */
    esp_modem::command_result config_network_registration_urc(int value)
    {
        return device->config_network_registration_urc(value);
    }
    /**
     *  @brief Gets the current network registration state
     *  @param[out] state The current network registration state
     *  state = 0 - Not registered, MT is not currently searching an operator to register to
     *  state = 1 - Registered, home network
     *  state = 2 - Not registered, but MT is currently trying to attach or searching an operator to register to
     *  state = 3 - Registration denied
     *  state = 4 - Unknown
     *  state = 5 - Registered, Roaming
     *  state = 6 - Registered, for SMS only, home network (NB-IoT only)
     *  state = 7 - Registered, for SMS only, roaming (NB-IoT only)
     *  state = 8 - Attached for emergency bearer services only
     *  state = 9 - Registered for CSFB not preferred, home network
     *  state = 10 - Registered for CSFB not preferred, roaming
     */
    esp_modem::command_result get_network_registration_state(int &state)
    {
        return device->get_network_registration_state(state);
    }
    /**
     *  @brief Configures the mobile termination error (+CME ERROR)
     *  @param[in] mode The form of the final result code
     *  mode = 0 - Disable, use and send ERROR instead
     *  mode = 1 - Enable, use numeric error values
     *  mode = 2 - Enable, result code and use verbose error values
     */
    esp_modem::command_result config_mobile_termination_error(int mode)
    {
        return device->config_mobile_termination_error(mode);
    }
    /**
     * @brief Configure eDRX
     * @param[in] mode
     * mode = 0 - Disable
     * mode = 1 - Enable
     * mode = 2 - Enable + URC
     * mode = 3 - Disable + Reset parameter.
     * @param[in] access_technology
     * act = 0 - ACT is not using eDRX (used in URC)
     * act = 1 - EC-GSM-IoT (A/Gb mode)
     * act = 2 - GSM (A/Gb mode)
     * act = 3 - UTRAN (Iu mode)
     * act = 4 - E-UTRAN (WB-S1 mode)
     * act = 5 - E-UTRAN (NB-S1 mode)
     * @param[in] edrx_value nible string containing encoded eDRX time
     * @param[in] ptw_value nible string containing encoded Paging Time Window
     */
    esp_modem::command_result config_edrx(int mode, int access_technology, const std::string &edrx_value)
    {
        return device->config_edrx(mode, access_technology, edrx_value);
    }
    esp_modem::command_result get_gnss_information_sim70xx(sim70xx_gps_t &gps);
    esp_modem::command_result get_operator_name(std::string &name)
    {
        return device->get_operator_name(name);
    }
};
/**
 * @brief Helper create method which employs the customized DCE factory for building DCE_gnss objects
 * @return unique pointer of the specific DCE
 */
std::unique_ptr<DCE_gnss> create_SIM7070_GNSS_dce(const esp_modem::dce_config *config,
                                                  std::shared_ptr<esp_modem::DTE> dte,
                                                  esp_netif_t *netif);
