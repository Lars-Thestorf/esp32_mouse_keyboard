#include "hid_mem.h"


/// Full Hid device Database Description - Used to add attributes into the database
// static esp_gatts_attr_db_t hidd_le_gatt_db[HIDD_LE_IDX_NB] =
// {
//             // HID Service Declaration
//     [HIDD_LE_IDX_SVC]                       = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&primary_service_uuid,
//                                                              ESP_GATT_PERM_READ_ENCRYPTED, sizeof(uint16_t), sizeof(hid_le_svc),
//                                                             (uint8_t *)&hid_le_svc}},
// 
//     // HID Service Declaration
//     [HIDD_LE_IDX_INCL_SVC]               = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&include_service_uuid,
//                                                             ESP_GATT_PERM_READ,
//                                                             sizeof(esp_gatts_incl_svc_desc_t), sizeof(esp_gatts_incl_svc_desc_t),
//                                                             (uint8_t *)&incl_svc}},
// 
//     // HID Information Characteristic Declaration
//     [HIDD_LE_IDX_HID_INFO_CHAR]     = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid,
//                                                             ESP_GATT_PERM_READ,
//                                                             CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE,
//                                                             (uint8_t *)&char_prop_read}},
//     // HID Information Characteristic Value
//     [HIDD_LE_IDX_HID_INFO_VAL]       = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_info_char_uuid,
//                                                             ESP_GATT_PERM_READ,
//                                                             sizeof(hids_hid_info_t), sizeof(hidInfo),
//                                                             (uint8_t *)&hidInfo}},
// 
//     // HID Control Point Characteristic Declaration
//     [HIDD_LE_IDX_HID_CTNL_PT_CHAR]  = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid,
//                                                               ESP_GATT_PERM_READ,
//                                                               CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE,
//                                                               (uint8_t *)&char_prop_write_nr}},
//     // HID Control Point Characteristic Value
//     [HIDD_LE_IDX_HID_CTNL_PT_VAL]    = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_control_point_uuid,
//                                                              ESP_GATT_PERM_WRITE,
//                                                              sizeof(uint8_t), 0,
//                                                              NULL}},
// 
//     // Report Map Characteristic Declaration
//     [HIDD_LE_IDX_REPORT_MAP_CHAR]   = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid,
//                                                               ESP_GATT_PERM_READ,
//                                                               CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE,
//                                                               (uint8_t *)&char_prop_read}},
//     // Report Map Characteristic Value
//     [HIDD_LE_IDX_REPORT_MAP_VAL]     = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_report_map_uuid,
//                                                               ESP_GATT_PERM_READ,
//                                                               HIDD_LE_REPORT_MAP_MAX_LEN, sizeof(hidReportMap),
//                                                               (uint8_t *)&hidReportMap}},
// 
//     // Report Map Characteristic - External Report Reference Descriptor
//     [HIDD_LE_IDX_REPORT_MAP_EXT_REP_REF]  = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_repot_map_ext_desc_uuid,
//                                                                         ESP_GATT_PERM_READ,
//                                                                         sizeof(uint16_t), sizeof(uint16_t),
//                                                                         (uint8_t *)&hidExtReportRefDesc}},
// 
//     // Protocol Mode Characteristic Declaration
//     [HIDD_LE_IDX_PROTO_MODE_CHAR]            = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid,
//                                                                         ESP_GATT_PERM_READ,
//                                                                         CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE,
//                                                                         (uint8_t *)&char_prop_read_write}},
//     // Protocol Mode Characteristic Value
//     [HIDD_LE_IDX_PROTO_MODE_VAL]               = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_proto_mode_uuid,
//                                                                         (ESP_GATT_PERM_READ|ESP_GATT_PERM_WRITE),
//                                                                         sizeof(uint8_t), sizeof(hidProtocolMode),
//                                                                         (uint8_t *)&hidProtocolMode}},
//                                                                         
//     // Report Characteristic Declaration
//     [HIDD_LE_IDX_REPORT_KEY_IN_CHAR]         = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid,
//                                                                          ESP_GATT_PERM_READ,
//                                                                          CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE,
//                                                                          (uint8_t *)&char_prop_read_notify}},
//     // Report Characteristic Value
//     [HIDD_LE_IDX_REPORT_KEY_IN_VAL]            = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_report_uuid,
//                                                                        ESP_GATT_PERM_READ,
//                                                                        HIDD_LE_REPORT_MAX_LEN, 0,
//                                                                        NULL}},
//     // Report KEY INPUT Characteristic - Client Characteristic Configuration Descriptor
//     [HIDD_LE_IDX_REPORT_KEY_IN_CCC]              = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_client_config_uuid,
//                                                                       (ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE),
//                                                                       sizeof(uint16_t), 0,
//                                                                       NULL}},
//      // Report Characteristic - Report Reference Descriptor
//     [HIDD_LE_IDX_REPORT_KEY_IN_REP_REF]       = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_report_ref_descr_uuid,
//                                                                        ESP_GATT_PERM_READ,
//                                                                        sizeof(hidReportRefKeyIn), sizeof(hidReportRefKeyIn),
//                                                                        hidReportRefKeyIn}},
// 
//      // Report Characteristic Declaration
//     [HIDD_LE_IDX_REPORT_LED_OUT_CHAR]         = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid,
//                                                                          ESP_GATT_PERM_READ,
//                                                                          CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE,
//                                                                          (uint8_t *)&char_prop_read_write_write_nr}},
// 
//     [HIDD_LE_IDX_REPORT_LED_OUT_VAL]            = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_report_uuid,
//                                                                        ESP_GATT_PERM_READ|ESP_GATT_PERM_WRITE,
//                                                                        HIDD_LE_REPORT_MAX_LEN, 0,
//                                                                        NULL}},
//     [HIDD_LE_IDX_REPORT_LED_OUT_REP_REF]      =  {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_report_ref_descr_uuid,
//                                                                        ESP_GATT_PERM_READ,
//                                                                        sizeof(hidReportRefLedOut), sizeof(hidReportRefLedOut),
//                                                                        hidReportRefLedOut}},
//                                                                        
//     [HIDD_LE_IDX_REPORT_MOUSE_IN_CHAR]       = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid,
//                                                                          ESP_GATT_PERM_READ,
//                                                                          CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE,
//                                                                          (uint8_t *)&char_prop_read_notify}},
// 
//     [HIDD_LE_IDX_REPORT_MOUSE_IN_VAL]        = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_report_uuid,
//                                                                        ESP_GATT_PERM_READ,
//                                                                        HIDD_LE_REPORT_MAX_LEN, 0,
//                                                                        NULL}},
// 
//     [HIDD_LE_IDX_REPORT_MOUSE_IN_CCC]        = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_client_config_uuid,
//                                                                       (ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE),
//                                                                       sizeof(uint16_t), 0,
//                                                                       NULL}},
// 
//     [HIDD_LE_IDX_REPORT_MOUSE_REP_REF]       = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_report_ref_descr_uuid,
//                                                                        ESP_GATT_PERM_READ,
//                                                                        sizeof(hidReportRefMouseIn), sizeof(hidReportRefMouseIn),
//                                                                        hidReportRefMouseIn}},
// #if (SUPPORT_REPORT_VENDOR  == true)
//     // Report Characteristic Declaration
//     [HIDD_LE_IDX_REPORT_VENDOR_OUT_CHAR]        = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid,
//                                                                          ESP_GATT_PERM_READ,
//                                                                          CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE,
//                                                                          (uint8_t *)&char_prop_read_write_notify}},
//     [HIDD_LE_IDX_REPORT_VENDOR_OUT_VAL]         = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_report_uuid,
//                                                                        ESP_GATT_PERM_READ|ESP_GATT_PERM_WRITE,
//                                                                        HIDD_LE_REPORT_MAX_LEN, 0,
//                                                                        NULL}},
//     [HIDD_LE_IDX_REPORT_VENDOR_OUT_REP_REF]     = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_report_ref_descr_uuid,
//                                                                        ESP_GATT_PERM_READ,
//                                                                        sizeof(hidReportRefVendorOut), sizeof(hidReportRefVendorOut),
//                                                                        hidReportRefVendorOut}},
// #endif
//     // Report Characteristic Declaration
//     [HIDD_LE_IDX_REPORT_CC_IN_CHAR]         = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid,
//                                                                          ESP_GATT_PERM_READ,
//                                                                          CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE,
//                                                                          (uint8_t *)&char_prop_read_notify}},
//     // Report Characteristic Value
//     [HIDD_LE_IDX_REPORT_CC_IN_VAL]            = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_report_uuid,
//                                                                        ESP_GATT_PERM_READ,
//                                                                        HIDD_LE_REPORT_MAX_LEN, 0,
//                                                                        NULL}},
//     // Report KEY INPUT Characteristic - Client Characteristic Configuration Descriptor
//     [HIDD_LE_IDX_REPORT_CC_IN_CCC]              = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_client_config_uuid,
//                                                                       (ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE_ENCRYPTED),
//                                                                       sizeof(uint16_t), 0,
//                                                                       NULL}},
//      // Report Characteristic - Report Reference Descriptor
//     [HIDD_LE_IDX_REPORT_CC_IN_REP_REF]       = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_report_ref_descr_uuid,
//                                                                        ESP_GATT_PERM_READ,
//                                                                        sizeof(hidReportRefCCIn), sizeof(hidReportRefCCIn),
//                                                                        hidReportRefCCIn}},
// 
//     // Boot Keyboard Input Report Characteristic Declaration
//     [HIDD_LE_IDX_BOOT_KB_IN_REPORT_CHAR] = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid,
//                                                                         ESP_GATT_PERM_READ,
//                                                                         CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE,
//                                                                         (uint8_t *)&char_prop_read_notify}},
//     // Boot Keyboard Input Report Characteristic Value
//     [HIDD_LE_IDX_BOOT_KB_IN_REPORT_VAL]   = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_kb_input_uuid,
//                                                                         ESP_GATT_PERM_READ,
//                                                                         HIDD_LE_BOOT_REPORT_MAX_LEN, 0,
//                                                                         NULL}},
//     // Boot Keyboard Input Report Characteristic - Client Characteristic Configuration Descriptor
//     [HIDD_LE_IDX_BOOT_KB_IN_REPORT_NTF_CFG]  = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_client_config_uuid,
//                                                                               (ESP_GATT_PERM_READ|ESP_GATT_PERM_WRITE),
//                                                                               sizeof(uint16_t), 0,
//                                                                               NULL}},
// 
//     // Boot Keyboard Output Report Characteristic Declaration
//     [HIDD_LE_IDX_BOOT_KB_OUT_REPORT_CHAR]    = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid,
//                                                                               ESP_GATT_PERM_READ,
//                                                                               CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE,
//                                                                               (uint8_t *)&char_prop_read_write_write_nr}},
//     // Boot Keyboard Output Report Characteristic Value
//     [HIDD_LE_IDX_BOOT_KB_OUT_REPORT_VAL]      = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_kb_output_uuid,
//                                                                               (ESP_GATT_PERM_READ|ESP_GATT_PERM_WRITE),
//                                                                               HIDD_LE_BOOT_REPORT_MAX_LEN, 0,
//                                                                               NULL}},
// 
//     // Boot Mouse Input Report Characteristic Declaration
//     [HIDD_LE_IDX_BOOT_MOUSE_IN_REPORT_CHAR] = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid,
//                                                                               ESP_GATT_PERM_READ,
//                                                                               CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE,
//                                                                               (uint8_t *)&char_prop_read_notify}},
//     // Boot Mouse Input Report Characteristic Value
//     [HIDD_LE_IDX_BOOT_MOUSE_IN_REPORT_VAL]   = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_mouse_input_uuid,
//                                                                               ESP_GATT_PERM_READ,
//                                                                               HIDD_LE_BOOT_REPORT_MAX_LEN, 0,
//                                                                               NULL}},
//     // Boot Mouse Input Report Characteristic - Client Characteristic Configuration Descriptor
//     [HIDD_LE_IDX_BOOT_MOUSE_IN_REPORT_NTF_CFG]    = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_client_config_uuid,
//                                                                                       (ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE),
//                                                                                       sizeof(uint16_t), 0,
//                                                                                       NULL}},
// 
//     // Report Characteristic Declaration
//     [HIDD_LE_IDX_REPORT_CHAR]                    = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid,
//                                                                          ESP_GATT_PERM_READ,
//                                                                          CHAR_DECLARATION_SIZE, CHAR_DECLARATION_SIZE,
//                                                                          (uint8_t *)&char_prop_read_write}},
//     // Report Characteristic Value
//     [HIDD_LE_IDX_REPORT_VAL]                      = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_report_uuid,
//                                                                        ESP_GATT_PERM_READ,
//                                                                        HIDD_LE_REPORT_MAX_LEN, 0,
//                                                                        NULL}},
//     // Report Characteristic - Report Reference Descriptor
//     [HIDD_LE_IDX_REPORT_REP_REF]               = {{ESP_GATT_AUTO_RSP}, {ESP_UUID_LEN_16, (uint8_t *)&hid_report_ref_descr_uuid,
//                                                                        ESP_GATT_PERM_READ,
//                                                                        sizeof(hidReportRefFeature), sizeof(hidReportRefFeature),
//                                                                        hidReportRefFeature}},
// };

