#ifndef BARECO_HID_MEM_H__
#define BARECO_HID_MEM_H__ 1

#include <stdint.h>
#include "hid_dev.h"
#include <sdkconfig.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ble_hid_mem_t
{
	hid_report_map_t *hid_dev_rpt_tbl;
	uint8_t hid_dev_rpt_tbl_Len;
	hid_report_map_t hid_rpt_map[HID_NUM_REPORTS];
	hidd_le_env_t hidd_le_env;
	uint8_t hidReportMapLen;
	uint8_t hidProtocolMode;
	uint16_t hidExtReportRefDesc;
	uint8_t hidReportRefMouseIn[HID_REPORT_REF_LEN];
	uint8_t hidReportRefKeyIn[HID_REPORT_REF_LEN];
	uint8_t hidReportRefLedOut[HID_REPORT_REF_LEN];
#if (SUPPORT_REPORT_VENDOR  == true)
	uint8_t hidReportRefVendorOut[HID_REPORT_REF_LEN];
#endif
	uint8_t hidReportRefFeature[HID_REPORT_REF_LEN];
	uint8_t hidReportRefCCIn[HID_REPORT_REF_LEN];
	esp_gatts_attr_db_t hidd_le_gatt_db[HIDD_LE_IDX_NB];
	// hid Service uuid
	uint16_t hid_le_svc;
	uint16_t hid_count;
	esp_gatts_incl_svc_desc_t incl_svc;
} ble_hid_mem_t;


// uint8_t hidReportMapLen = sizeof(hidReportMap);
// uint8_t hidProtocolMode = HID_PROTOCOL_MODE_REPORT;

// // HID External Report Reference Descriptor
// static uint16_t hidExtReportRefDesc = ESP_GATT_UUID_BATTERY_LEVEL;
// 
// // HID Report Reference characteristic descriptor, mouse input
// static uint8_t hidReportRefMouseIn[HID_REPORT_REF_LEN] =
//              { HID_RPT_ID_MOUSE_IN, HID_REPORT_TYPE_INPUT };
// 
// 
// // HID Report Reference characteristic descriptor, key input
// static uint8_t hidReportRefKeyIn[HID_REPORT_REF_LEN] =
//              { HID_RPT_ID_KEY_IN, HID_REPORT_TYPE_INPUT };
// 
// // HID Report Reference characteristic descriptor, LED output
// static uint8_t hidReportRefLedOut[HID_REPORT_REF_LEN] =
//              { HID_RPT_ID_LED_OUT, HID_REPORT_TYPE_OUTPUT };
// 
// #if (SUPPORT_REPORT_VENDOR  == true)
// 
// static uint8_t hidReportRefVendorOut[HID_REPORT_REF_LEN] =
//              {HID_RPT_ID_VENDOR_OUT, HID_REPORT_TYPE_OUTPUT};
// #endif
// 
// // HID Report Reference characteristic descriptor, Feature
// static uint8_t hidReportRefFeature[HID_REPORT_REF_LEN] =
//              { HID_RPT_ID_FEATURE, HID_REPORT_TYPE_FEATURE };
// 
// // HID Report Reference characteristic descriptor, consumer control input
// static uint8_t hidReportRefCCIn[HID_REPORT_REF_LEN] =
//              { HID_RPT_ID_CC_IN, HID_REPORT_TYPE_INPUT };




// // hid Service uuid
// static uint16_t hid_le_svc = ATT_SVC_HID;
// uint16_t            hid_count = 0;
// esp_gatts_incl_svc_desc_t incl_svc = {0};

extern ble_hid_mem_t *ble_hid_mem;

#ifdef __cplusplus
}
#endif




#endif
