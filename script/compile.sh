#!/bin/bash
rm -rf photon_firmware.bin
particle compile photon && mv photon_firmware_* photon_firmware.bin

