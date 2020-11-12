if(CONFIG_BLUEDROID_ENABLED)
idf_component_register(SRCS "esp_hidd_prf_api.c"
                            "hid_dev.c"
                            "hid_device_le_prf.c"
                    REQUIRES bt
                    INCLUDE_DIRS ".")
target_compile_options(${COMPONENT_LIB} PRIVATE -Wno-unused-const-variable)
else()
idf_component_register()
message(WARNING, "Bluethoot is disabled we will not build ble hid interface")
endif()

