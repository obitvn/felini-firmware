idf_component_register(SRCS "PD_UFP.cpp" "PD_UFP_Protocol.c"  "FUSB302_UFP.c"
                        INCLUDE_DIRS "."
                        REQUIRES driver
                        i2c_manager
                        )

