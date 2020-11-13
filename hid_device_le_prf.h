#ifndef BARECO_HID_DEVICE_LE_PRF_H__
#define BARECO_HID_DEVICE_LE_PRF_H__ 1
#include <stdint.h>
#include <sdkconfig.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Battery Service Attributes Indexes
enum
{
    BAS_IDX_SVC,

    BAS_IDX_BATT_LVL_CHAR,
    BAS_IDX_BATT_LVL_VAL,
    BAS_IDX_BATT_LVL_NTF_CFG,
    BAS_IDX_BATT_LVL_PRES_FMT,

    BAS_IDX_NB,
};


#define CHAR_DECLARATION_SIZE   (sizeof(uint8_t))


void esp_hidd_prf_cb_hdl(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param);

extern const uint8_t hidReportMap[];
extern const int hidReportMapSize;

extern const uint16_t primary_service_uuid;
extern const uint16_t include_service_uuid;
extern const uint16_t character_declaration_uuid;
extern const uint16_t character_client_config_uuid;
extern const uint16_t hid_info_char_uuid;
extern const uint16_t hid_report_map_uuid   ;
extern const uint16_t hid_control_point_uuid;
extern const uint16_t hid_report_uuid;
extern const uint16_t hid_proto_mode_uuid;
extern const uint16_t hid_kb_input_uuid;
extern const uint16_t hid_kb_output_uuid;
extern const uint16_t hid_mouse_input_uuid;
extern const uint16_t hid_repot_map_ext_desc_uuid;
extern const uint16_t hid_report_ref_descr_uuid;
extern const uint8_t char_prop_notify;
extern const uint8_t char_prop_read;
extern const uint8_t char_prop_write_nr;
extern const uint8_t char_prop_read_write;
extern const uint8_t char_prop_read_notify;
extern const uint8_t char_prop_read_write_notify;
extern const uint8_t char_prop_read_write_write_nr;
extern const uint16_t battary_svc;
extern const uint16_t bat_lev_uuid;
extern const uint8_t   bat_lev_ccc[2];
extern const uint16_t char_format_uuid;
extern const esp_gatts_attr_db_t bas_att_db[BAS_IDX_NB];
extern const uint8_t hidInfo[HID_INFORMATION_LEN];

#ifdef __cplusplus
}
#endif

#endif
