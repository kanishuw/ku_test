@echo off

:: Bin file path
set BIN_PATH=C:\Program Files (x86)\Microchip\MPLABX\gnuBins\GnuWin32\bin
:: Source path
set SRC_PATH=.\source

echo --Setting path variable---------------
set PATH=%BIN_PATH%;%PATH%
echo --Navigating to Source Directory------
cd %SRC_PATH%
echo --Building----------------------------
make
echo --Build Script Exiting----------------