for run in {1..1000}; do
./bin/client test;


if [ $? -gt 0 ]; then
echo "Test failed, program crashed" 
exit 128
fi
done
