#cmakemake.sh
#this poorly written pipline will probably make the cmake file
# #cmakeception
printf "cmake_minimum_required (VERSION 2.6)\n" > ../CMakeLists.txt
printf "add_compile_options(-std=c++11)\n\n" >> ../CMakeLists.txt
printf "#Project Name:\nproject (DubstepZombies)\n\n" >> ../CMakeLists.txt
printf "include_directories(/usr/include/allegro5)\n\n" >> ../CMakeLists.txt
  
printf "#BUILD ORDER\n#Comment out any libaries not ready\n" >> ../CMakeLists.txt 
#build the build order
find ../src/ -mindepth 2 -name "*.cpp" | #find all cpp files
cut -d'/' -f  2-4 | #cut at 2nd / to end of file
xargs -I% printf '%\n%\n' | #print twice
while read word; #read a line
   do echo $word | cut -d'/' -f 3 | cut -d'.' -f1;  #cut everthing after/bf .
   read word; #read next line
   echo $word; #just repeat it
done | #move on
while read word; #read a line 
   do printf "add_library($word STATIC "; #change to cmake format!
   read word; printf "$word)\n"; 
done >> ../CMakeLists.txt

#Now find out what depends on what, 
#run it through the program called linkedlibraries.cpp
#Also create executable
printf "\n#Make an executable" >> ../CMakeLists.txt
printf "\nadd_executable(../bin/DZ src/launcher.cpp)" >> ../CMakeLists.txt

printf "\n#Libraries that require other libraries\n" >> ../CMakeLists.txt
g++ linklibraries.cpp -o "target_link_libraries"

find ../src/ -mindepth 2 -name "*.cpp" | #find all .h files
cut -d'/' -f  2-4 |
xargs -I% printf '%\n%\n' |
while read word; 
   do echo $word | cut -d'/' -f 3 | cut -d'.' -f1;
   read word;
   printf "$word\n";
   echo $word | cut -d'.' -f 1 | xargs -I%  printf '%.h\n';
done | #Now we need to open every even file and find the #includes 
while read word;
   do echo $word;
   read word;
   grep -rnw ../$word -e '#include "' | cut -d':' -f 2;
   read word;
   grep -rnw ../$word -e '#include "' | cut -d':' -f 2;
done |
./target_link_libraries >> ../CMakeLists.txt

#Finally, load all the libraries:
printf "\n#Link against it\n" >> ../CMakeLists.txt

grep ../CMakeLists.txt -e 'add_library(' | 
cut -d'(' -f 2 |
cut -d' ' -f 1 |
xargs -I% printf 'target_link_libraries(../bin/DZ %)\n' >> ../CMakeLists.txt
 
