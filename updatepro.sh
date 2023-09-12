#!/bin/bash

# Define the directories
SRC_DIR="src"
INCLUDE_DIR="include"
FORMS_DIR="forms"

# Backup the original .pro file
cp mercuryFLR.pro mercuryFLR.pro.bak

# Create or truncate the temporary file
> mercuryFLR_temp.pro

# Copy non-auto-generated content
awk '/SOURCES \+/,/RESOURCES \+=/ {next} 1' mercuryFLR.pro.bak > mercuryFLR_temp.pro

# Append auto-generated sections

# Sources
echo "SOURCES += \\" >> mercuryFLR_temp.pro
for file in $SRC_DIR/*.cc; do
    echo "    $file \\" >> mercuryFLR_temp.pro
done

# Headers
echo -e "\nHEADERS += \\" >> mercuryFLR_temp.pro
for file in $INCLUDE_DIR/*.h; do
    echo "    $file \\" >> mercuryFLR_temp.pro
done

# Forms
echo -e "\nFORMS += \\" >> mercuryFLR_temp.pro
for file in $FORMS_DIR/*.ui; do
    echo "    $file \\" >> mercuryFLR_temp.pro
done

echo -e "\nRESOURCES += resources.qrc" >> mercuryFLR_temp.pro

# Replace the original .pro file
mv mercuryFLR_temp.pro mercuryFLR.pro
