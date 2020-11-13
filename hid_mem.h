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
	uint8_t number_of_connections;
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
	struct gatts_profile_inst heart_rate_profile_tab[PROFILE_NUM];
	// hid Service uuid
	uint16_t hid_le_svc;
	uint16_t hid_count;
	esp_gatts_incl_svc_desc_t incl_svc;
	uint8_t battary_lev;
} ble_hid_mem_t;



extern ble_hid_mem_t *ble_hid_mem;

#ifdef __cplusplus
}
#endif




#endif
