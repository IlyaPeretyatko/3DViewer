# change .obj files to .txt
for file in models/*.txt ; do mv "$file" "${file%.*}.obj" ; done