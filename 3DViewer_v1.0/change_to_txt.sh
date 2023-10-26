# change .obj files to .txt
for file in models/*.obj ; do mv "$file" "${file%.*}.txt" ; done