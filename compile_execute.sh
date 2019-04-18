cmake -B Folder_test -DUSE_VULKAN=ON
cd Folder_test
make -j 4
./Exemples/Test
..
rm -rf Folder_test
