all : lab_intro

lab_intro : main.o PNG.o HSLAPixel.o lodepng.o lab_intro.o
	clang++ main.o PNG.o HSLAPixel.o lodepng.o lab_intro.o -std=c++1y -stdlib=libc++ -lc++abi -lm -o lab_intro

main.o : main.cpp lab_intro.h cs225/PNG.h
	clang++ -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic main.cpp

lab_intro.o : lab_intro.cpp lab_intro.h
	clang++ -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic lab_intro.cpp

PNG.o : cs225/PNG.cpp cs225/PNG.h
	clang++ -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic cs225/PNG.cpp

HSLAPixel.o : cs225/HSLAPixel.cpp cs225/HSLAPixel.h
	clang++ -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic cs225/HSLAPixel.cpp

lodepng.o : cs225/lodepng/lodepng.cpp cs225/lodepng/lodepng.h
	clang++ -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic cs225/lodepng/lodepng.cpp








test: output_msg catchmain.o tests-part1.o tests-part2.o PNG.o HSLAPixel.o lodepng.o lab_intro.o
	$(LD) catchmain.o tests-part1.o tests-part2.o PNG.o HSLAPixel.o lodepng.o lab_intro.o $(LDFLAGS) -o test

catchmain.o : cs225/catch/catchmain.cpp cs225/catch/catch.hpp
	$(CXX) $(CXXFLAGS) cs225/catch/catchmain.cpp

tests-part1.o : tests/tests-part1.cpp cs225/catch/catch.hpp lab_intro.cpp lab_intro.h
	$(CXX) $(CXXFLAGS) tests/tests-part1.cpp

tests-part2.o : tests/tests-part2.cpp cs225/catch/catch.hpp lab_intro.cpp lab_intro.h
	$(CXX) $(CXXFLAGS) tests/tests-part2.cpp


clean :
	-rm -f *.o $(EXENAME) test
