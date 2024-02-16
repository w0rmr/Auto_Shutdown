gcc -o "auto_shut" "src.c" -lX11 

if [ "$?" -ne 0 ]; then
    echo "Compilation failed->"
    exit 1
fi

sudo mv "auto_shut" /bin
if [ "$?" -ne 0 ]; then
    echo "Error: Failed to move the executable to /bin."
    rm auto_shut
    exit 1
fi
echo "compilation successful, run auto_shut -h to see the options"