cmake -B Folder_test -DUSE_VULKAN=ON
cd Folder_test
make -j 6 &&
./Exemples/Test 
cd ..
#rm -rf Folder_test
