OLED_DRIVER_ENABLE = no   # Enables the use of OLED displays
ENCODER_ENABLE = no       # Enables the use of one or more encoders
RGBLIGHT_ENABLE = no      # Enable keyboard RGB underglow

# features
COMBO_ENABLE = yes
EXTRAKEY_ENABLE = yes     # Audio control and System control

SRC += ../../../../users/baffalop/casemodes.c \
	   ../../../../users/baffalop/combos.c
