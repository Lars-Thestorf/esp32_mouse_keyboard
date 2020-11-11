// Copyright 2017-2018 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "esp_hidd_prf_api.h"
#include "hidd_le_prf_int.h"
#include "hid_dev.h"
#include <stdlib.h>
#include <string.h>
#include "esp_log.h"
#include "hid_mem.h"
#include "hidd_le_prf_int.h"
#include "hid_device_le_prf.h"

// HID keyboard input report length
#define HID_KEYBOARD_IN_RPT_LEN     8

// HID LED output report length
#define HID_LED_OUT_RPT_LEN         1

// HID mouse input report length
#define HID_MOUSE_IN_RPT_LEN        5

// HID consumer control input report length
#define HID_CC_IN_RPT_LEN           2

esp_err_t esp_hidd_register_callbacks(esp_hidd_event_cb_t callbacks)
{
    esp_err_t hidd_status;

    if(callbacks != NULL) {
   	    ble_hid_mem->hidd_le_env.hidd_cb = callbacks;
    } else {
        return ESP_FAIL;
    }

    if((hidd_status = hidd_register_cb()) != ESP_OK) {
        return hidd_status;
    }

    esp_ble_gatts_app_register(BATTRAY_APP_ID);
    
    if((hidd_status = esp_ble_gatts_app_register(HIDD_APP_ID)) != ESP_OK) {
        return hidd_status;
    }
    
    ///@note It seems that the MTU has no effect on compatibility. The BLE stack works with all systems without setting the MTU to 23Bytes.
    /*hidd_status = esp_ble_gatt_set_local_mtu(23);
    if (hidd_status != ESP_OK){
        ESP_LOGE(HID_LE_PRF_TAG, "set local  MTU failed, error code = %x", hidd_status);
    }*/
   
    return hidd_status;
}

esp_err_t esp_hidd_profile_init(void)
{
if (ble_hid_mem != NULL) {
			ESP_LOGE(HID_LE_PRF_TAG, "HID device profile already initialized");
			return ESP_FAIL;
	}
	ble_hid_mem = heap_caps_malloc(sizeof(ble_hid_mem_t), MALLOC_CAP_DMA);
	
	
	/// Full Hid device Database Description - Used to add attributes into the database
	esp_gatts_attr_db_t hidd_le_gatt_db[HIDD_LE_IDX_NB] =
	{
							// HID Service Declaration
			[HIDD_LE_IDX_SVC]                       = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&primary_service_uuid,
																															ESP_GATT_PERM_READ_ENCRYPTED, sizeof(uint16_t), sizeof(ble_hid_mem->hid_le_svc),
																															(uint8_t *)&ble_hid_mem->hid_le_svc}},

			// HID Service Declaration
			[HIDD_LE_IDX_INCL_SVC]               = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&include_service_uuid,
																															ESP_GATT_PERM_READ,
																															sizeof(esp_gatts_incl_svc_desc_t), sizeof(esp_gatts_incl_svc_desc_t),
																															(uint8_t *)&ble_hid_mem->incl_svc}},

			// HID Information Characteristic Declaration
			[HIDD_LE_IDX_HID_INFO_CHAR]     = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid,
																															ESP_GATT_PERM_READ,
																															CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE,
																															(uint8_t *)&char_prop_read}},
			// HID Information Characteristic Value
			[HIDD_LE_IDX_HID_INFO_VAL]       = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_info_char_uuid,
																															ESP_GATT_PERM_READ,
																															sizeof(hids_hid_info_t), sizeof(hidInfo),
																															(uint8_t *)&hidInfo}},

			// HID Control Point Characteristic Declaration
			[HIDD_LE_IDX_HID_CTNL_PT_CHAR]  = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid,
																																ESP_GATT_PERM_READ,
																																CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE,
																																(uint8_t *)&char_prop_write_nr}},
			// HID Control Point Characteristic Value
			[HIDD_LE_IDX_HID_CTNL_PT_VAL]    = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_control_point_uuid,
																															ESP_GATT_PERM_WRITE,
																															sizeof(uint8_t), 0,
																															NULL}},

			// Report Map Characteristic Declaration
			[HIDD_LE_IDX_REPORT_MAP_CHAR]   = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid,
																																ESP_GATT_PERM_READ,
																																CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE,
																																(uint8_t *)&char_prop_read}},
			// Report Map Characteristic Value
			[HIDD_LE_IDX_REPORT_MAP_VAL]     = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_report_map_uuid,
																																ESP_GATT_PERM_READ,
																																HIDD_LE_REPORT_MAP_MAX_LEN, sizeof(hidReportMap),
																																(uint8_t *)&hidReportMap}},

			// Report Map Characteristic - External Report Reference Descriptor
			[HIDD_LE_IDX_REPORT_MAP_EXT_REP_REF]  = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_repot_map_ext_desc_uuid,
																																					ESP_GATT_PERM_READ,
																																					sizeof(uint16_t), sizeof(uint16_t),
																																					(uint8_t *)&ble_hid_mem->hidExtReportRefDesc}},

			// Protocol Mode Characteristic Declaration
			[HIDD_LE_IDX_PROTO_MODE_CHAR]            = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid,
																																					ESP_GATT_PERM_READ,
																																					CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE,
																																					(uint8_t *)&char_prop_read_write}},
			// Protocol Mode Characteristic Value
			[HIDD_LE_IDX_PROTO_MODE_VAL]               = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_proto_mode_uuid,
																																					(ESP_GATT_PERM_READ|ESP_GATT_PERM_WRITE),
																																					sizeof(uint8_t), sizeof(hidProtocolMode),
																																					(uint8_t *)&hidProtocolMode}},
																																					
			// Report Characteristic Declaration
			[HIDD_LE_IDX_REPORT_KEY_IN_CHAR]         = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid,
																																					ESP_GATT_PERM_READ,
																																					CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE,
																																					(uint8_t *)&char_prop_read_notify}},
			// Report Characteristic Value
			[HIDD_LE_IDX_REPORT_KEY_IN_VAL]            = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_report_uuid,
																																				ESP_GATT_PERM_READ,
																																				HIDD_LE_REPORT_MAX_LEN, 0,
																																				NULL}},
			// Report KEY INPUT Characteristic - Client Characteristic Configuration Descriptor
			[HIDD_LE_IDX_REPORT_KEY_IN_CCC]              = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_client_config_uuid,
																																				(ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE),
																																				sizeof(uint16_t), 0,
																																				NULL}},
			// Report Characteristic - Report Reference Descriptor
			[HIDD_LE_IDX_REPORT_KEY_IN_REP_REF]       = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_report_ref_descr_uuid,
																																				ESP_GATT_PERM_READ,
																																				sizeof(hidReportRefKeyIn), sizeof(hidReportRefKeyIn),
																																				hidReportRefKeyIn}},

			// Report Characteristic Declaration
			[HIDD_LE_IDX_REPORT_LED_OUT_CHAR]         = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid,
																																					ESP_GATT_PERM_READ,
																																					CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE,
																																					(uint8_t *)&char_prop_read_write_write_nr}},

			[HIDD_LE_IDX_REPORT_LED_OUT_VAL]            = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_report_uuid,
																																				ESP_GATT_PERM_READ|ESP_GATT_PERM_WRITE,
																																				HIDD_LE_REPORT_MAX_LEN, 0,
																																				NULL}},
			[HIDD_LE_IDX_REPORT_LED_OUT_REP_REF]      =  {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_report_ref_descr_uuid,
																																				ESP_GATT_PERM_READ,
																																				sizeof(hidReportRefLedOut), sizeof(hidReportRefLedOut),
																																				hidReportRefLedOut}},
																																				
			[HIDD_LE_IDX_REPORT_MOUSE_IN_CHAR]       = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid,
																																					ESP_GATT_PERM_READ,
																																					CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE,
																																					(uint8_t *)&char_prop_read_notify}},

			[HIDD_LE_IDX_REPORT_MOUSE_IN_VAL]        = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_report_uuid,
																																				ESP_GATT_PERM_READ,
																																				HIDD_LE_REPORT_MAX_LEN, 0,
																																				NULL}},

			[HIDD_LE_IDX_REPORT_MOUSE_IN_CCC]        = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_client_config_uuid,
																																				(ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE),
																																				sizeof(uint16_t), 0,
																																				NULL}},

			[HIDD_LE_IDX_REPORT_MOUSE_REP_REF]       = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_report_ref_descr_uuid,
																																				ESP_GATT_PERM_READ,
																																				sizeof(hidReportRefMouseIn), sizeof(hidReportRefMouseIn),
																																				hidReportRefMouseIn}},
	#if (SUPPORT_REPORT_VENDOR  == true)
			// Report Characteristic Declaration
			[HIDD_LE_IDX_REPORT_VENDOR_OUT_CHAR]        = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid,
																																					ESP_GATT_PERM_READ,
																																					CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE,
																																					(uint8_t *)&char_prop_read_write_notify}},
			[HIDD_LE_IDX_REPORT_VENDOR_OUT_VAL]         = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_report_uuid,
																																				ESP_GATT_PERM_READ|ESP_GATT_PERM_WRITE,
																																				HIDD_LE_REPORT_MAX_LEN, 0,
																																				NULL}},
			[HIDD_LE_IDX_REPORT_VENDOR_OUT_REP_REF]     = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_report_ref_descr_uuid,
																																				ESP_GATT_PERM_READ,
																																				sizeof(hidReportRefVendorOut), sizeof(hidReportRefVendorOut),
																																				hidReportRefVendorOut}},
	#endif
			// Report Characteristic Declaration
			[HIDD_LE_IDX_REPORT_CC_IN_CHAR]         = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid,
																																					ESP_GATT_PERM_READ,
																																					CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE,
																																					(uint8_t *)&char_prop_read_notify}},
			// Report Characteristic Value
			[HIDD_LE_IDX_REPORT_CC_IN_VAL]            = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_report_uuid,
																																				ESP_GATT_PERM_READ,
																																				HIDD_LE_REPORT_MAX_LEN, 0,
																																				NULL}},
			// Report KEY INPUT Characteristic - Client Characteristic Configuration Descriptor
			[HIDD_LE_IDX_REPORT_CC_IN_CCC]              = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_client_config_uuid,
																																				(ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE_ENCRYPTED),
																																				sizeof(uint16_t), 0,
																																				NULL}},
			// Report Characteristic - Report Reference Descriptor
			[HIDD_LE_IDX_REPORT_CC_IN_REP_REF]       = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_report_ref_descr_uuid,
																																				ESP_GATT_PERM_READ,
																																				sizeof(hidReportRefCCIn), sizeof(hidReportRefCCIn),
																																				hidReportRefCCIn}},

			// Boot Keyboard Input Report Characteristic Declaration
			[HIDD_LE_IDX_BOOT_KB_IN_REPORT_CHAR] = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid,
																																					ESP_GATT_PERM_READ,
																																					CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE,
																																					(uint8_t *)&char_prop_read_notify}},
			// Boot Keyboard Input Report Characteristic Value
			[HIDD_LE_IDX_BOOT_KB_IN_REPORT_VAL]   = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_kb_input_uuid,
																																					ESP_GATT_PERM_READ,
																																					HIDD_LE_BOOT_REPORT_MAX_LEN, 0,
																																					NULL}},
			// Boot Keyboard Input Report Characteristic - Client Characteristic Configuration Descriptor
			[HIDD_LE_IDX_BOOT_KB_IN_REPORT_NTF_CFG]  = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_client_config_uuid,
																																								(ESP_GATT_PERM_READ|ESP_GATT_PERM_WRITE),
																																								sizeof(uint16_t), 0,
																																								NULL}},

			// Boot Keyboard Output Report Characteristic Declaration
			[HIDD_LE_IDX_BOOT_KB_OUT_REPORT_CHAR]    = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid,
																																								ESP_GATT_PERM_READ,
																																								CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE,
																																								(uint8_t *)&char_prop_read_write_write_nr}},
			// Boot Keyboard Output Report Characteristic Value
			[HIDD_LE_IDX_BOOT_KB_OUT_REPORT_VAL]      = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_kb_output_uuid,
																																								(ESP_GATT_PERM_READ|ESP_GATT_PERM_WRITE),
																																								HIDD_LE_BOOT_REPORT_MAX_LEN, 0,
																																								NULL}},

			// Boot Mouse Input Report Characteristic Declaration
			[HIDD_LE_IDX_BOOT_MOUSE_IN_REPORT_CHAR] = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid,
																																								ESP_GATT_PERM_READ,
																																								CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE,
																																								(uint8_t *)&char_prop_read_notify}},
			// Boot Mouse Input Report Characteristic Value
			[HIDD_LE_IDX_BOOT_MOUSE_IN_REPORT_VAL]   = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_mouse_input_uuid,
																																								ESP_GATT_PERM_READ,
																																								HIDD_LE_BOOT_REPORT_MAX_LEN, 0,
																																								NULL}},
			// Boot Mouse Input Report Characteristic - Client Characteristic Configuration Descriptor
			[HIDD_LE_IDX_BOOT_MOUSE_IN_REPORT_NTF_CFG]    = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_client_config_uuid,
																																												(ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE),
																																												sizeof(uint16_t), 0,
																																												NULL}},

			// Report Characteristic Declaration
			[HIDD_LE_IDX_REPORT_CHAR]                    = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid,
																																					ESP_GATT_PERM_READ,
																																					CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE,
																																					(uint8_t *)&char_prop_read_write}},
			// Report Characteristic Value
			[HIDD_LE_IDX_REPORT_VAL]                      = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_report_uuid,
																																				ESP_GATT_PERM_READ,
																																				HIDD_LE_REPORT_MAX_LEN, 0,
																																				NULL}},
			// Report Characteristic - Report Reference Descriptor
			[HIDD_LE_IDX_REPORT_REP_REF]               = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_report_ref_descr_uuid,
																																				ESP_GATT_PERM_READ,
																																				sizeof(hidReportRefFeature), sizeof(hidReportRefFeature),
																																				hidReportRefFeature}},
	};

	
	// Reset the hid device target environment
	memset(&ble_hid_mem->hidd_le_env, 0, sizeof(hidd_le_env_t));
	ble_hid_mem->hidd_le_env.enabled = true;
	return ESP_OK;
}

esp_err_t esp_hidd_profile_deinit(void)
{
    uint16_t hidd_svc_hdl = ble_hid_mem->hidd_le_env.hidd_inst.att_tbl[HIDD_LE_IDX_SVC];
    if (!ble_hid_mem->hidd_le_env.enabled) {
        ESP_LOGE(HID_LE_PRF_TAG, "HID device profile already deinitialized");
        return ESP_OK;
    }

    if(hidd_svc_hdl != 0) {
		esp_ble_gatts_stop_service(hidd_svc_hdl);
		esp_ble_gatts_delete_service(hidd_svc_hdl);
    } else {
		return ESP_FAIL;
	}
    
    /* register the HID device profile to the BTA_GATTS module*/
    esp_ble_gatts_app_unregister(ble_hid_mem->hidd_le_env.gatt_if);
    
    //set hidd enabled to false
    //THX @Lars-Thestorf
    //see issue #44
    ble_hid_mem->hidd_le_env.enabled = false;

    return ESP_OK;
}

uint16_t esp_hidd_get_version(void)
{
	return HIDD_VERSION;
}

void esp_hidd_send_consumer_value(uint16_t conn_id, uint8_t key_cmd, bool key_pressed)
{
    uint8_t buffer[HID_CC_IN_RPT_LEN] = {0, 0};
    if (key_pressed) {
        ESP_LOGD(HID_LE_PRF_TAG, "hid_consumer_build_report");
        hid_consumer_build_report(buffer, key_cmd);
    }
    ESP_LOGD(HID_LE_PRF_TAG, "buffer[0] = %x, buffer[1] = %x", buffer[0], buffer[1]);
    hid_dev_send_report(ble_hid_mem->hidd_le_env.gatt_if, conn_id,
                        HID_RPT_ID_CC_IN, HID_REPORT_TYPE_INPUT, HID_CC_IN_RPT_LEN, buffer);
    return;
}

void esp_hidd_send_keyboard_value(uint16_t conn_id, key_mask_t special_key_mask, uint8_t *keyboard_cmd, uint8_t num_key)
{
    if (num_key > HID_KEYBOARD_IN_RPT_LEN - 2) {
        ESP_LOGE(HID_LE_PRF_TAG, "%s(), the number key should not be more than %d", __func__, HID_KEYBOARD_IN_RPT_LEN);
        return;
    }
   
    uint8_t buffer[HID_KEYBOARD_IN_RPT_LEN] = {0};
   
    buffer[0] = special_key_mask;
    
    for (int i = 0; i < num_key; i++) {
        buffer[i+2] = keyboard_cmd[i];
    }

    ESP_LOGD(HID_LE_PRF_TAG, "the key vaule = %d,%d,%d, %d, %d, %d,%d, %d", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7]);
    hid_dev_send_report(ble_hid_mem->hidd_le_env.gatt_if, conn_id,
                        HID_RPT_ID_KEY_IN, HID_REPORT_TYPE_INPUT, HID_KEYBOARD_IN_RPT_LEN, buffer);
    return;
}

void esp_hidd_send_mouse_value(uint16_t conn_id, uint8_t mouse_button, int8_t mickeys_x, int8_t mickeys_y, int8_t wheel)
{
    uint8_t buffer[HID_MOUSE_IN_RPT_LEN];
    
    buffer[0] = mouse_button;   // Buttons
    buffer[1] = mickeys_x;           // X
    buffer[2] = mickeys_y;           // Y
    buffer[3] = wheel;           // Wheel
    buffer[4] = 0;           // AC Pan

    hid_dev_send_report(ble_hid_mem->hidd_le_env.gatt_if, conn_id,
                        HID_RPT_ID_MOUSE_IN, HID_REPORT_TYPE_INPUT, HID_MOUSE_IN_RPT_LEN, buffer);
    return;
}



